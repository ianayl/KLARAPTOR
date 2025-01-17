
#include "interpolator.h"

#define INTERP_DEBUG 0

#define FLOAT_EPS 1e-8


//foward declarations of internal methods
void interpEnumerateCurrentVals(Interpolator_t* interp);
void interpAddPolynomialRow(Interpolator_t* interp, mpq_t* point);
PolyInterpStatus_t rfInterpGetPolyDegenerative(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly);
PolyInterpStatus_t rfInterpGetPolyAmbiguous(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly);
PolyInterpStatus_t _rfInterpGetPoly(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly, double maximumResidual, int rfInterpGetPoly_EarlyTerm);

Interpolator_t* interpInit(int nvar, int* degreeBounds) {
	Interpolator_t* interp = (Interpolator_t*) malloc(sizeof(Interpolator_t));

	interp->nvar = nvar;
	interp->degreeBounds = (int*) malloc(sizeof(int)*nvar);
	memcpy(interp->degreeBounds, degreeBounds, sizeof(int)*nvar);
	interp->requiredPoints = 1;
	for (int i = 0; i < nvar; ++i) {
		interp->requiredPoints *= (interp->degreeBounds[i] + 1);
	}

	interp->meshSet = 0;
	interp->meshMins = interp->meshMaxs = interp->meshIncrements = NULL;
	interp->opType = MESH_INCR_ADDITION;

	interp->enumerateDone = 0;
	interp->currentVals = NULL;

	interp->valAlloc = 0;
	interp->valSize = 0;
	interp->mpPoints = NULL;
	interp->mpVals = NULL;

	// interp->delta = 1;
	interp->deltaNum = NULL; 
	interp->deltaDen = NULL; 
	interp->deltaFlipFlip = 0; //0 means update deltaNum first

	interp->n = interp->requiredPoints;
	interp->curRows = 0;
	interp->allocRows = 0;
	interp->A = NULL;
	interp->usedRows = NULL;
	interp->availableRows = NULL;
	interp->numAvailRows = 0;

	interp->denomDegreeBounds = NULL;
	interp->numeratorNumTerms = 0;
	interp->denomZeroTerms = 0;

	return interp;
}

void interpFree(Interpolator_t* interp) {
	interpResetPointsVals(interp);
	free(interp->degreeBounds);
	if (interp->meshMins != NULL) {
		free(interp->meshMins);
	}
	if (interp->meshMaxs != NULL) {
		free(interp->meshMaxs);
	}
	if (interp->meshIncrements != NULL) {
		free(interp->meshIncrements);
	}
	if (interp->currentVals != NULL) {
		free(interp->currentVals);
	}
	if (interp->deltaNum != NULL) {
		free(interp->deltaNum);
	}
	if (interp->deltaDen != NULL) {
		free(interp->deltaDen);
	}
	free(interp);
}


long interpGetRequiredNumPoints(Interpolator_t* interp) {
	return interp->requiredPoints;
}

void interpSetMeshBounds(Interpolator_t* interp, long long int* meshMins, long long int* meshMaxs, long long int* meshIncrements, MeshIncrementOp_t incrementOp, int reset) {
	if (reset && interp->currentVals != NULL) {
		free(interp->currentVals);
		interp->currentVals = NULL;
	
		interpResetPointsVals(interp);
	}

	if (interp->meshMins != NULL) {
		free(interp->meshMins);
		interp->meshMins = NULL;
	}
	if (interp->meshMaxs != NULL) {
		free(interp->meshMaxs);
		interp->meshMaxs = NULL;
	}
	if (interp->meshIncrements != NULL) {
		free(interp->meshIncrements);
		interp->meshIncrements = NULL;
	}

	int nvar = interp->nvar;
	interp->meshMins = (long long int*) malloc(sizeof(long long int)*nvar);
	interp->meshMaxs = (long long int*) malloc(sizeof(long long int)*nvar);
	interp->meshIncrements = (long long int*) malloc(sizeof(long long int)*nvar);

	memcpy(interp->meshMins, meshMins, sizeof(long long int)*nvar);
	memcpy(interp->meshMaxs, meshMaxs, sizeof(long long int)*nvar);
	memcpy(interp->meshIncrements, meshIncrements, sizeof(long long int)*nvar);

	interp->opType = incrementOp;

	interp->meshSet = 1;
}

int interpPeekNextPoint(Interpolator_t* interp, long long int* point) {
	if (interp->enumerateDone) {
		return 0;
	}

	if (interp->meshSet == 0) {
		for (int i = 0; i < interp->nvar; ++i) {
			point[i] = -1;
		}
		return 1;
	}

	int nvar = interp->nvar;
	if (interp->currentVals == NULL) {
		interp->currentVals = (long long int*) malloc(sizeof(long long int)*nvar);
		for (int i = 0; i < nvar; ++i) {
			interp->currentVals[i] = interp->meshMins[i];
			point[i] = interp->meshMins[i];
		}
		return 1;
	}

	for (int i = 0; i < nvar; ++i) {
		point[i] = interp->currentVals[i];
	}
	return 1;
}

void interpEnumerateCurrentVals(Interpolator_t* interp) {
	int idx = 0;
	if (interp->opType == MESH_INCR_ADDITION) {
		while(interp->currentVals[idx] + interp->meshIncrements[idx] > interp->meshMaxs[idx]) {
			++idx;
			if (idx > interp->nvar) {
				interp->enumerateDone = 1;
				return;
			}
		}
	} else /* if (interp->opType == MESH_INCR_MULTIPLICATION) */ {
		while(interp->currentVals[idx] * interp->meshIncrements[idx] > interp->meshMaxs[idx]) {
			++idx;
			if (idx > interp->nvar) {
				interp->enumerateDone = 1;
				return;
			}
		}
	
	}

	if (interp->opType == MESH_INCR_ADDITION) {
		interp->currentVals[idx] += interp->meshIncrements[idx];
	} else /* if (interp->opType == MESH_INCR_MULTIPLICATION) */ {
		interp->currentVals[idx] *= interp->meshIncrements[idx];
	}
	
	for (int i = 0; i < idx; ++i) {
		interp->currentVals[i] = interp->meshMins[i];
	} 
}

int interpGetNextPoint(Interpolator_t* interp, long long int* point) {
	if (interp->enumerateDone) {
		return 0;
	}

	if (interp->currentVals == NULL) {
		interpPeekNextPoint(interp, point);
	}

	for (int i = 0; i < interp->nvar; ++i) {
		point[i] = interp->currentVals[i];
	}

	//increment current vals for next peek
	interpEnumerateCurrentVals(interp);
	return 1;
}

void interpAddPointValLong(Interpolator_t* interp, long long int* point, long long int val) {
	mpq_t mpVal;
	mpq_init(mpVal);
	mpq_set_si(mpVal, val, 1);

	int nvar = interp->nvar;
	mpq_t* mpPoint = (mpq_t*) malloc(nvar*sizeof(mpq_t));
	for (int i = 0; i < nvar; ++i) {
		mpq_init(mpPoint[i]);
		mpq_set_si(mpPoint[i], point[i], 1);
	}

	interpAddPointValMP(interp, mpPoint, mpVal);

	mpq_clear(mpVal);
	for (int i = 0; i < nvar; ++i) {
		mpq_clear(mpPoint[i]);
	}
	free(mpPoint);
}

void interpResetPointsVals(Interpolator_t* interp) {
	int valSize = interp->valSize;
	for (int i = 0; i < valSize; ++i) {
		mpq_clear(interp->mpVals[i]);
		for (int j = 0; j < interp->nvar; ++j) {
			mpq_clear(interp->mpPoints[i][j]);
		}
		free(interp->mpPoints[i]);
	}
	free(interp->mpPoints);
	free(interp->mpVals);
	interp->mpPoints = NULL;
	interp->mpVals = NULL;
	interp->valSize = interp->valAlloc = 0;
	if (interp->A != NULL) {
		long n = interp->n;
		for (int i = 0; i < interp->curRows; ++i) { 
			for (int j = 0; j < n; ++j) {
				mpq_clear(interp->A[i*n + j]);
			}
		}

		free(interp->A);
		interp->A = NULL;
	}
	if (interp->availableRows != NULL) {
		free(interp->availableRows);
		interp->availableRows = NULL;
	}
	interp->curRows = 0;
}

int enumerateMonomials(int* degrees, int* degreeBounds, int nvar) {
	int idx = nvar-1;
	while(degrees[idx] + 1 > degreeBounds[idx]) {
		--idx;
		if (idx < 0) {
			return 0;
		}
	}

	++(degrees[idx]);
	
	for (int i = nvar-1; i > idx; --i) {
		degrees[i] = 0;
	} 
	return 1;
} 

int enumerateDegreeBounds(int* degrees, int* degreeBounds, int nvar) {
	int idx = 0;
	for (int i = 0; i < nvar-1; ++i) {
		if(degrees[i] >= degreeBounds[i]) {
			++idx;
		} else if (degrees[i] >= degrees[i+1]) {
			++idx;
		} else {
			break;
		}
	}

	for (int i = idx; i < nvar; ++i) {
		if(degrees[i] >= degreeBounds[i]) {
			++idx;
		} else {
			break;
		}
	}

	if (idx == nvar) {
		//Then we have reached the lowest degree bound on all variables.
		//Now check is the degree bounds are uneven.
		for (int i = 0; i < nvar; ++i) {
			if (degrees[i] < degreeBounds[i]) {
				++(degrees[i]);
				return 1;
			}
			degrees[i] = degreeBounds[i];
		}
		return 0;
	}

	++(degrees[idx]);
	return 1;
}

int monomialInBounds(int* degrees, int* degreeBounds, int nvar) {
	for (int i = 0; i < nvar; ++i) {
		if (degrees[i] > degreeBounds[i]) {
			return 0;
		}
	}

	return 1;
}

void interpAddPolynomialRow(Interpolator_t* interp, mpq_t* point) {
	long n = interp->n;
	if (interp->A == NULL) {
		interp->A = (mpq_t*) malloc(sizeof(mpq_t)*n*n);
	}

	long curRows = interp->curRows;
	long numAvailRows = interp->numAvailRows;

	if (curRows == n && numAvailRows == 0) {
#if INTERP_DEBUG
		fprintf(stderr, "ROWS ALREADY AT MAX!!\n");
#endif
		return;
	}

	long insertRow = curRows;
	if (numAvailRows > 0) {
		insertRow = interp->availableRows[interp->numAvailRows-1];
		--(interp->numAvailRows);
		if (interp->numAvailRows > 0) {
			interp->availableRows = (long*) realloc(interp->availableRows, sizeof(long) * interp->numAvailRows);
		} else {
			free(interp->availableRows);
			interp->availableRows = NULL;
		}
	}

	int nvar = interp->nvar;
	int* degrees = (int*) calloc(nvar, sizeof(int));
	
	//yes this is silly and has only one iteration
	for (int i = insertRow; i < insertRow + 1; ++i) { 
		mpq_init(interp->A[i*n + 0]);
		mpq_set_si(interp->A[i*n + 0], 1l, 1l);

		mpq_t varExp;
		mpq_init(varExp);
		for (int j = 1; j < n; ++j) {
			mpq_init(interp->A[i*n + j]);
			int enumSuccess = enumerateMonomials(degrees, interp->degreeBounds, nvar);
			if (!enumSuccess) {
				fprintf(stderr, "Could not enumerate monomials! How can this happen? requiredPoints: %ld\n", n);
				exit(1);
			}

			mpq_set_si(interp->A[i*n + j], 1l, 1l);
			for (int k = 0; k < nvar; ++k) {
				mpz_pow_ui(mpq_numref(varExp), mpq_numref(point[k]), (unsigned long int) degrees[k]);
				mpz_pow_ui(mpq_denref(varExp), mpq_denref(point[k]), (unsigned long int) degrees[k]);
				mpq_canonicalize(varExp);

				mpq_mul(interp->A[i*n + j], interp->A[i*n + j], varExp);
			}
		}
		mpq_clear(varExp);
	}
	
	if (curRows < n) {
		++(interp->curRows);
	}
	free(degrees);

#if INTERP_DEBUG
	fprintf(stderr, "Current A: \n");
	printMPQMat(interp->A, interp->curRows, n);
	fprintf(stderr, "\n" );
#endif
}

void interpAddPointValMP(Interpolator_t* interp, mpq_t* point, mpq_t val) {

	long n = interp->n;
	int valSize = interp->valSize;

	if (valSize == n && interp->numAvailRows == 0) {
#if INTERP_DEBUG
		fprintf(stderr, "ROWS ALREADY AT MAX!!\n");
#endif
		return;
	}

	int insertRow = valSize;
	int numAvailRows = interp->numAvailRows;
	if (numAvailRows > 0) {
		insertRow = interp->availableRows[interp->numAvailRows-1];
	}

	if (valSize < interp->n) {
		if (valSize + 1 > interp->valAlloc) {
			interp->valAlloc += 10;
			interp->mpVals = (mpq_t*) realloc(interp->mpVals, interp->valAlloc*sizeof(mpq_t));
			interp->mpPoints = (mpq_t**) realloc(interp->mpPoints, interp->valAlloc*sizeof(mpq_t*));
		}

		mpq_init(interp->mpVals[interp->valSize]);
		mpq_set(interp->mpVals[interp->valSize], val);

		int nvar = interp->nvar;
		interp->mpPoints[interp->valSize] = (mpq_t*) malloc(nvar*sizeof(mpq_t));
		for (int i = 0; i < nvar; ++i) {
			mpq_init(interp->mpPoints[interp->valSize][i]);
			mpq_set(interp->mpPoints[interp->valSize][i], point[i]);
		}

		interpAddPolynomialRow(interp, interp->mpPoints[interp->valSize]);
		++(interp->valSize);
	} else {
		int nvar = interp->nvar;
		mpq_set(interp->mpVals[insertRow], val);
		for (int i = 0; i < nvar; ++i) {
			mpq_set(interp->mpPoints[insertRow][i], point[i]);
		}
		interpAddPolynomialRow(interp, interp->mpPoints[insertRow]);
	}
}

AltArr_t* buildPolyFromCoefArrayWithEps(int* degreeBounds, int nvar, mpq_t* X, double eps) {
	eps = eps < 0.0 ? -eps : eps;

	mpq_t mpEps;
	mpq_init(mpEps);
	mpq_set_d(mpEps, eps);

	mpq_t absX;
	mpq_init(absX);

	long size = 1;
	for (int i = 0; i < nvar; ++i) {
		// fprintf(stderr, "size: %ld, degreeBounds: %d\n",size, degreeBounds[i]);
		size *= (degreeBounds[i]+1);
	}


	long actualSize = 0;
	for (int i = 0; i < size; ++i) {
		mpq_abs(absX, X[i]);
		// gmp_fprintf(stderr, "X[%d]: %Qd, absX: %Qd\n", i, X[i], absX);
		// gmp_fprintf(stderr, "mpEps: %Qd\n", mpEps);
		if (mpq_cmp(absX, mpEps) > 0) {
			++actualSize;
			// fprintf(stderr, "actualSize: %ld\n", actualSize);
		}
	}

	if (actualSize == 0) {
		return NULL;
	}

	AltArr_t* aa = makePolynomial_AA(actualSize, nvar);

	//coef array X is in ~increasing~ lex order. We need decreasing. 
	int degrees[nvar];
	for (int k = 0; k < nvar; ++k) {
		degrees[k] = 0;	
	}
	degrees[nvar-1] = -1;

	AAElem_t* elems = aa->elems;
	int curIdx = actualSize - 1;
	int* sizes = getExpOffsetArray(nvar);

	for (int i = size-1; i >= 0; --i) {
		enumerateMonomials(degrees, degreeBounds, nvar);
		// for (int k = 0; k < nvar; ++k) {
		// 	fprintf(stderr, " %d", degrees[k]);
		// }
		// fprintf(stderr, "\n");
		// fprintf(stderr, "X[%d]: %g\n", size-1 - i, mpq_get_d(X[size-1 - i]));


		mpq_abs(absX, X[size-1 - i]);
		if (mpq_cmp(absX, mpEps) <= 0) {
			continue;
		}

		elems[curIdx].degs = 0;

		for (int k = 0; k < nvar; ++k) {
			elems[curIdx].degs |= ((degrees_t) degrees[k] << sizes[k]);
		}

		// gmp_fprintf(stderr, "setting index %d to degs: %llx, coef: %Qd", curIdx, elems[curIdx].degs, X[size-1-i]);

		mpq_init(elems[curIdx].coef);
		mpq_set(elems[curIdx].coef, X[size-1 - i]);
		--curIdx;
	}

	aa->size = actualSize;
	
	free(sizes);

	mpq_clear(absX);
	mpq_clear(mpEps);

	return aa;
}

AltArr_t* buildPolyFromCoefArray(int* degreeBounds, int nvar, mpq_t* X) {
	long size = 1;
	for (int i = 0; i < nvar; ++i) {
		size *= (degreeBounds[i]+1);
	}

	long actualSize = 0;
	for (int i = 0; i < size; ++i) {
		if (mpq_sgn(X[i]) != 0) {
			++actualSize;
		}
	}

	AltArr_t* aa = makePolynomial_AA(actualSize, nvar);

	//coef array X is in ~increasing~ lex order. We need decreasing. 
	int degrees[nvar];
	for (int k = 0; k < nvar; ++k) {
		degrees[k] = 0;	
	}

	int* sizes = getExpOffsetArray(nvar);
	
	AAElem_t* elems = aa->elems;
	long curIdx = actualSize - 1;
	if (mpq_sgn(X[0]) != 0) {
		elems[curIdx].degs = 0;
		mpq_init(elems[curIdx].coef);
		mpq_set(elems[curIdx].coef, X[0]);		
		--curIdx;
	} 

	for (int i = size-2; i >= 0; --i) {
		enumerateMonomials(degrees, degreeBounds, nvar);

		if (mpq_sgn(X[size-1 - i]) == 0) {
			continue;
		}

		elems[curIdx].degs = 0;

		for (int k = 0; k < nvar; ++k) {
			elems[curIdx].degs |= ((degrees_t) degrees[k] << sizes[k]);
		}
		
		mpq_init(elems[curIdx].coef);
		mpq_set(elems[curIdx].coef, X[size-1 - i]);
		--curIdx;
	}

	aa->size = actualSize;
	
	free(sizes);

	return aa;
}


PolyInterpStatus_t interpGetPoly(Interpolator_t* interp, AltArr_t** poly) {
	if (interp->valSize < interp->requiredPoints || interp->numAvailRows > 0) {
		return POLY_INTERP_MORE_POINTS;
	}

	mpq_t* A = interp->A;
	mpq_t* b = interp->mpVals;
	long n = interp->n;
	long* rowList = NULL;

	mpq_t* X = NULL;

	long rank =  0;//solveMPQSystem(A, b, n, &X, &rowList);

#if INTERP_DEBUG
	fprintf(stderr, "Got rank: %ld\n", rank);
#endif
	if (rank == n) {
#if INTERP_DEBUG
		fprintf(stderr, "Got a solution!\n");
		printMPQMat(interp->A, interp->curRows, n);
		fprintf(stderr, "\n" );
		printMPQMat(b, n, 1);
		fprintf(stderr, "\n" );
		printMPQMat(X, n, 1);
		fprintf(stderr, "\n" );
#endif
		*poly = buildPolyFromCoefArray(interp->degreeBounds, interp->nvar, X);
		return POLY_INTERP_SUCCESS;
	} else {
		int d = n - rank;
		interp->availableRows = (long*) malloc(sizeof(long)*d);
		interp->numAvailRows = d;
		memcpy(interp->availableRows, &(rowList[rank]), sizeof(long)*d);

		return POLY_INTERP_MORE_POINTS;
	}

}

const mpq_t* interpGetPointMatrix(Interpolator_t* interp) {
	return interp->A;
}

const mpq_t* interpGetValMatrix(Interpolator_t* interp) {
	return interp->mpVals;
}


/******
* Rational Function Interpolation
******/

/**
 * Create and initialize an interpolator given a number of variables and 
 * a degree bound (inclusive) for each variable for numerator and denominator. 
 */
Interpolator_t* rfInterpInit(int nvar, int* degreeBounds, int* denomDegreeBounds) {
	Interpolator_t* interp = interpInit(nvar, degreeBounds);

	interp->denomDegreeBounds = (int*) malloc(sizeof(int)*nvar);
	memcpy(interp->denomDegreeBounds, denomDegreeBounds, sizeof(int)*nvar);
	interp->numeratorNumTerms = 1;
	interp->requiredPoints = 1;
	for (int i = 0; i < nvar; ++i) {
		interp->numeratorNumTerms *= (interp->degreeBounds[i] + 1);
		interp->requiredPoints *= (interp->denomDegreeBounds[i] + 1);
	}
	interp->requiredPoints += interp->numeratorNumTerms;
	interp->n = interp->requiredPoints;

	interp->deltaNum = (int*) calloc(nvar, sizeof(int)); 
	interp->deltaDen = (int*) calloc(nvar, sizeof(int)); 
	for (int i = 0; i < nvar; ++i) {
		interp->deltaNum[i] = 1;
	}

	// enumerateDegreeBounds(interp->deltaNum, interp->degreeBounds, interp->nvar);
	// enumerateDegreeBounds(interp->deltaNum, interp->degreeBounds, interp->nvar);
	enumerateDegreeBounds(interp->deltaDen, interp->denomDegreeBounds, interp->nvar);
	// enumerateDegreeBounds(interp->deltaDen, interp->denomDegreeBounds, interp->nvar);
	interp->deltaFlipFlip = 0; //0 means update deltaNum first

	return interp;
}

void rfInterpResetPointsVals(Interpolator_t* interp) {
	int valSize = interp->valSize;
	for (int i = 0; i < valSize; ++i) {
		mpq_clear(interp->mpVals[i]);
		for (int j = 0; j < interp->nvar; ++j) {
			mpq_clear(interp->mpPoints[i][j]);
		}
		free(interp->mpPoints[i]);
	}
	free(interp->mpPoints);
	free(interp->mpVals);

	interp->mpPoints = NULL;
	interp->mpVals = NULL;
	interp->valSize = interp->valAlloc = 0;

	if (interp->A != NULL) {
		long n = interp->n;
		for (int i = 0; i < interp->curRows; ++i) { 
			for (int j = 0; j < n; ++j) {
				mpq_clear(interp->A[i*n + j]);
			}
		}

		free(interp->A);
		interp->A = NULL;
	}
	if (interp->availableRows != NULL) {
		free(interp->availableRows);
		interp->availableRows = NULL;
	}
	interp->curRows = 0;
}


/**
 * Clean up an interpolator and any memory used by it.
 * The interp pointer is invalidated by a call to this functions.
 */
void rfInterpFree(Interpolator_t* interp) {
	if (interp->denomDegreeBounds != NULL) {
		free(interp->denomDegreeBounds);
	}
	rfInterpResetPointsVals(interp);

	interpFree(interp);
}

/** 
 * After an increase in delta we must update the matrix to match.
 */
void rfInterpUpdateMatrix(Interpolator_t* interp, int* degreeBounds, int* denomDegreeBounds) {
	if (interp->A == NULL) {
		return;
	}
	// fprintf(stderr, "Before update: \n");
	// printMPQMat(interp->A, interp->n, interp->n);

	long n = interp->n;
	int nvar = interp->nvar;
	int* degrees = (int*) calloc(nvar, sizeof(int));
	int n2 = interp->numeratorNumTerms;
	
	mpq_t* point;
	mpq_t* val;
	mpq_t varExp;
	mpq_init(varExp);

//	for (int i = 0; i < n; ++i){
//		fprintf(stderr, "usedRows[%d]: %d\n", i, interp->usedRows[i]);
//	}

	for (int i = 0; i < n; ++i) {
		// fprintf(stderr, "i: %d\n", i);
		if (interp->usedRows[i] == -1) {
			continue;
		}
		
		// fprintf(stderr, "usedRows[%d]: %d\n", i, interp->usedRows[i]);
		point = interp->mpPoints[interp->usedRows[i]];
		val = &(interp->mpVals[interp->usedRows[i]]);
	
		for (int j = 1; j < n2; ++j) {
			enumerateMonomials(degrees, interp->degreeBounds, nvar);
			// fprintf(stderr, "degs: " );		
			// for (int k = 0; k < nvar; ++k) {
			// 	fprintf(stderr, "%d ", degrees[k]);
			// }
			// fprintf(stderr, "\n");

			if (!monomialInBounds(degrees, degreeBounds, nvar)) {
				continue;
			}

			mpq_set_si(interp->A[i*n + j], 1l, 1l);
			for (int k = 0; k < nvar; ++k) {
				// gmp_fprintf(stderr, "varExp: %Qd, point[%d]: %Qd, degrees[%d]: %d\n", varExp, k, point[k], k, degrees[k]);
				mpz_pow_ui(mpq_numref(varExp), mpq_numref(point[k]), (unsigned long int) degrees[k]);
				mpz_pow_ui(mpq_denref(varExp), mpq_denref(point[k]), (unsigned long int) degrees[k]);
				mpq_canonicalize(varExp);
				mpq_mul(interp->A[i*n + j], interp->A[i*n + j], varExp);
			}
		}	
		// fprintf(stderr, "reset degs\n");
		for (int k = 0; k < nvar; ++k) {
			//reset degrees for denom
			degrees[k] = 0;
		}
		for (int j = n2+1; j < n; ++j) {
			enumerateMonomials(degrees, interp->denomDegreeBounds, nvar);	
			// fprintf(stderr, "degs: " );		
			// for (int k = 0; k < nvar; ++k) {
			// 	fprintf(stderr, "%d ", degrees[k]);
			// }
			// fprintf(stderr, "\n");

			if (!monomialInBounds(degrees, denomDegreeBounds, nvar)) {
				continue;
			}

			mpq_neg(interp->A[i*n + j], *val); //for denominator we multiply through by -val
			for (int k = 0; k < nvar; ++k) {
				mpz_pow_ui(mpq_numref(varExp), mpq_numref(point[k]), (unsigned long int) degrees[k]);
				mpz_pow_ui(mpq_denref(varExp), mpq_denref(point[k]), (unsigned long int) degrees[k]);
				mpq_canonicalize(varExp);
				mpq_mul(interp->A[i*n + j], interp->A[i*n + j], varExp);
			}
		}
		for (int k = 0; k < nvar; ++k) {
			//reset degrees for denom
			degrees[k] = 0;
		}
		// fprintf(stderr, "\n");
	}

	// fprintf(stderr, "After update: \n" );
	// printMPQMat(interp->A, interp->n, interp->n);
	// fprintf(stderr, "\n");
	mpq_clear(varExp);
	// free(degrees);
}

void rfInterpAddPolynomialRow(Interpolator_t* interp, int pointValIdx) {
	long n = interp->n;
	if (interp->A == NULL) {
		//start with 10 rows
		interp->A = (mpq_t*) malloc(sizeof(mpq_t)*n*10);
		interp->allocRows = 10;

		interp->usedRows = (long*) malloc(n*sizeof(long));
		for (int i = 0; i < n; ++i) {
			interp->usedRows[i] = -1l;
		}

		int i = 0;
		int n2 = interp->numeratorNumTerms;
		for (int j = 0; j < n; ++j) {
			mpq_init(interp->A[i*n + j]);
		}
		mpq_set_si(interp->A[i*n + n2], 1l, 1l);
		interp->usedRows[0] = 0;
		++(interp->curRows);
	}

	long curRows = interp->curRows;
	long numAvailRows = interp->numAvailRows;

	int nvar = interp->nvar;
	int* degrees = (int*) calloc(nvar, sizeof(int));
	int n2 = interp->numeratorNumTerms;

	long insertRow = curRows;
	if (numAvailRows > 0) {
		insertRow = interp->availableRows[interp->numAvailRows-1];
		--(interp->numAvailRows);
		if (interp->numAvailRows > 0) {
			interp->availableRows = (long*) realloc(interp->availableRows, sizeof(long) * interp->numAvailRows);
		} else {
			interp->availableRows = NULL;
		}
	}

	if (insertRow >= interp->allocRows) {
		interp->allocRows += 10;
		interp->A = (mpq_t*) realloc(interp->A, sizeof(mpq_t)*n*interp->allocRows);
	}

	// fprintf(stderr, "///////////////////////// INSERTING TO ROW: %d\n", insertRow);

	// fprintf(stderr, "A before:\n");
	// printMPQMat(interp->A, interp->curRows, interp->n);

	mpq_t* point = interp->mpPoints[pointValIdx];
	mpq_t* val = &(interp->mpVals[pointValIdx]);

	// fprintf(stderr, "Insert row: %ld\n", insertRow);
	//yes this is silly and has only one iteration
	for (int i = insertRow; i < insertRow + 1; ++i) { 

		int n2 = interp->numeratorNumTerms;
		mpq_init(interp->A[i*n + 0]);
		mpq_set_si(interp->A[i*n + 0], 1l, 1l);
#if INTERP_DEBUG
		fprintf(stderr, "///////////// ADDING ROW: " );
		fprintf(stderr, "x^%dy^%d ", degrees[0], degrees[1]);
#endif

		mpq_t varExp;
		mpq_init(varExp);


		for (int j = 1; j < n2; ++j) {
			mpq_init(interp->A[i*n + j]);
			int enumSuccess = enumerateMonomials(degrees, interp->degreeBounds, nvar);
			if (!enumSuccess) {
				fprintf(stderr, "Could not enumerate monomials! How can this happen? requiredPoints: %ld\n", n);
				exit(1);
			}
#if INTERP_DEBUG
			fprintf(stderr, "x^%dy^%d ", degrees[0], degrees[1]);
#endif
			// if (!monomialInBounds(degrees, interp->deltaNum, nvar)) {
			// 	continue;
			// }

			mpq_set_si(interp->A[i*n + j], 1l, 1l);
			for (int k = 0; k < nvar; ++k) {
				mpz_pow_ui(mpq_numref(varExp), mpq_numref(point[k]), (unsigned long int) degrees[k]);
				mpz_pow_ui(mpq_denref(varExp), mpq_denref(point[k]), (unsigned long int) degrees[k]);
				mpq_canonicalize(varExp);
				mpq_mul(interp->A[i*n + j], interp->A[i*n + j], varExp);
			}
		}
		//reset
		for (int k = 0; k < nvar; ++k) {
			degrees[k] = 0;
		}
		//do denominator
		mpq_init(interp->A[i*n + n2]);
		mpq_neg(interp->A[i*n + n2], *val); //for denominator we multiply through by -val
#if INTERP_DEBUG
		gmp_fprintf(stderr, "(-1*%Qd)x^%dy^%d ", *val, degrees[0], degrees[1]);
#endif
		for (int j = n2+1; j < n; ++j) {
			mpq_init(interp->A[i*n] + j);
			int enumSuccess = enumerateMonomials(degrees, interp->denomDegreeBounds, nvar);
			if (!enumSuccess) {
				fprintf(stderr, "Could not enumerate monomials! How can this happen? requiredPoints: %ld\n", n);
				exit(1);
			}
#if INTERP_DEBUG
			gmp_fprintf(stderr, "(-1*%Qd)x^%dy^%d ", *val, degrees[0], degrees[1]);
#endif
			// if (!monomialInBounds(degrees, interp->deltaDen, nvar)) {
			// 	continue;
			// }
			// int tdeg = 0;
			// for (int k = 0; k < nvar; ++k) {
			// 	tdeg += degrees[k];
			// }
			// if (tdeg > interp->delta) {
			// 	//leave the matrix entry as zero as delta is our current
			// 	//degree bound target
			// 	continue;
			// }

			mpq_neg(interp->A[i*n + j], *val); //for denominator we multiply through by -val
			for (int k = 0; k < nvar; ++k) {
				mpz_pow_ui(mpq_numref(varExp), mpq_numref(point[k]), (unsigned long int) degrees[k]);
				mpz_pow_ui(mpq_denref(varExp), mpq_denref(point[k]), (unsigned long int) degrees[k]);
				mpq_canonicalize(varExp);
				mpq_mul(interp->A[i*n + j], interp->A[i*n + j], varExp);
			}			
		}
#if INTERP_DEBUG
		fprintf(stderr, "\n");
#endif
		mpq_clear(varExp);
	}
	
	++(interp->curRows);

	free(degrees);

#if INTERP_DEBUG
	fprintf(stderr, "Current A: \n");
	printMPQMat(interp->A, interp->curRows, n);
	fprintf(stderr, "\n" );
#endif
}

double* _rfInterpGetSampleMatrix(Interpolator_t* interp, int* degreeBounds, int* denomDegreeBounds, long* lRows, long* lCols, long* lN2) {
	int nvar = interp->nvar;

	long rows = interp->valSize;
	long n = 1;
	long denomn = 1;
	for (int k = 0; k < nvar; ++k) {
		n *= (degreeBounds[k] + 1);
		denomn *= (denomDegreeBounds[k] + 1);
	}
	long n2 = n;
	n += denomn;

	*lRows = rows;
	*lCols = n;
	*lN2 = n2;

	mpq_t* mpA = (mpq_t*) malloc(sizeof(mpq_t)*n*rows);
	for (int i = 0; i < 1; ++i) {
		for (int j = 0; j < n; ++j) {
			mpq_init(mpA[i*n + j]);
		}
	}
	mpq_set_si(mpA[0*n + n2], 1l, 1l);
	// double* A = (double*) malloc(sizeof(double)*n*rows);
	// for (int i = 0; i < 1; ++i) {
	// 	for (int j = 0; j < n; ++j) {
	// 		A[i*n + j] = 0.0;
	// 	}
	// }
	// A[0*n + n2] = 1.0;

	int* degrees = (int*) calloc(nvar, sizeof(int));

	mpq_t* point;
	mpq_t* val;
	mpq_t varExp;
	mpq_init(varExp);

	for (int i = 1; i < rows; ++i) {
		point = interp->mpPoints[i];
		val = &(interp->mpVals[i]);
		for (int k = 0; k < nvar; ++k) {
			degrees[k] = 0;
		}
		mpq_init(mpA[i*n + 0]);
		mpq_set_si(mpA[i*n + 0], 1l, 1l);
		// A[i*n + 0] = 1;
		for (int j = 1; j < n2; ++j) {
			int enumSuccess = enumerateMonomials(degrees, degreeBounds, nvar);
			if (!enumSuccess) {
				fprintf(stderr, "Could not enumerate monomials! How can this happen? requiredPoints: %ld\n", n);
				exit(1);
			}
			// A[i*n + j] = 1;
			mpq_init(mpA[i*n + j]);
			mpq_set_si(mpA[i*n + j], 1l, 1l);
			for (int k = 0; k < nvar; ++k) {
				mpz_pow_ui(mpq_numref(varExp), mpq_numref(point[k]), (unsigned long int) degrees[k]);
				mpz_pow_ui(mpq_denref(varExp), mpq_denref(point[k]), (unsigned long int) degrees[k]);
				mpq_canonicalize(varExp);
				mpq_mul(mpA[i*n + j], mpA[i*n + j], varExp);
				// A[i*n + j] *= mpq_get_d(varExp);
			}
		}
		//reset
		for (int k = 0; k < nvar; ++k) {
			degrees[k] = 0;
		}
		mpq_init(mpA[i*n + n2]);
		mpq_neg(mpA[i*n + n2], *val);
		// A[i*n + n2] = -1.0 * mpq_get_d(*val);
		for (int j = n2+1; j < n; ++j) {
			int enumSuccess = enumerateMonomials(degrees, denomDegreeBounds, nvar);
			if (!enumSuccess) {
				fprintf(stderr, "Could not enumerate monomials! How can this happen? requiredPoints: %ld\n", n);
				exit(1);
			}
			mpq_init(mpA[i*n + j]);	
			mpq_neg(mpA[i*n + j], *val);
			// A[i*n + j] = -1.0 * mpq_get_d(*val);
			for (int k = 0; k < nvar; ++k) {
				mpz_pow_ui(mpq_numref(varExp), mpq_numref(point[k]), (unsigned long int) degrees[k]);
				mpz_pow_ui(mpq_denref(varExp), mpq_denref(point[k]), (unsigned long int) degrees[k]);
				mpq_canonicalize(varExp);
				mpq_mul(mpA[i*n + j], mpA[i*n + j], varExp);
				// A[i*n + j] *= mpq_get_d(varExp);
			}
		}
	}

	mpq_clear(varExp);

	double* A = (double*) malloc(sizeof(double)*n*rows);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < n; ++j) {
			A[i*n + j] = mpq_get_d(mpA[i*n + j]);
			mpq_clear(mpA[i*n + j]);
		}
	}
	free(mpA);

	free(degrees);

	return A;
}



/**
 * Add a point,value pair to the interpolation where points and vals are longs.
 */
void rfInterpAddPointValLong(Interpolator_t* interp, long long int* point, long long int val) {
	mpq_t mpVal;
	mpq_init(mpVal);
	mpq_set_si(mpVal, val, 1);

	int nvar = interp->nvar;
	mpq_t* mpPoint = (mpq_t*) malloc(nvar*sizeof(mpq_t));
	for (int i = 0; i < nvar; ++i) {
		mpq_init(mpPoint[i]);
		mpq_set_si(mpPoint[i], point[i], 1);
	}

	rfInterpAddPointValMP(interp, mpPoint, mpVal);

	mpq_clear(mpVal);
	for (int i = 0; i < nvar; ++i) {
		mpq_clear(mpPoint[i]);
	}
	free(mpPoint);

}

void rfInterpAddPointValMP(Interpolator_t* interp, mpq_t* point, mpq_t val) {
	if (interp->valSize == 0) {
		interp->valAlloc = 10;
		interp->mpVals = (mpq_t*) malloc(sizeof(mpq_t)*interp->valAlloc);
		interp->mpPoints = (mpq_t**) malloc(sizeof(mpq_t*)*interp->valAlloc);
		interp->mpPoints[0] = (mpq_t*) malloc(sizeof(mpq_t)*interp->nvar);
		for (int i = 0; i < interp->nvar; ++i) {
			mpq_init(interp->mpPoints[0][i]);
		}

		mpq_init(interp->mpVals[0]);
		mpq_set_si(interp->mpVals[0], 1l, 1l);
		interp->valSize = 1;
	}


	int valSize = interp->valSize;

// 	if (valSize == interp->requiredPoints && interp->numAvailRows == 0) {
// #if INTERP_DEBUG
// 		fprintf(stderr, "ROWS ALREADY AT MAX!!\n");
// #endif
// 		return;
// 	}



	int insertRow = valSize;
	// int numAvailRows = interp->numAvailRows;
	// if (numAvailRows > 0) {
	// 	insertRow = interp->availableRows[interp->numAvailRows-1];
	// }

	// fprintf(stderr, "///////////////////////// INSERT ROW: %d\n", insertRow);

	// if (valSize < interp->requiredPoints) {
		if (valSize + 2 > interp->valAlloc) {
			interp->valAlloc += 10;
			interp->mpVals = (mpq_t*) realloc(interp->mpVals, interp->valAlloc*sizeof(mpq_t));
			interp->mpPoints = (mpq_t**) realloc(interp->mpPoints, interp->valAlloc*sizeof(mpq_t*));
		}

		mpq_init(interp->mpVals[interp->valSize]);
		mpq_set(interp->mpVals[interp->valSize], val);

		int nvar = interp->nvar;
		interp->mpPoints[interp->valSize] = (mpq_t*) malloc(nvar*sizeof(mpq_t));
		for (int i = 0; i < nvar; ++i) {
			mpq_init(interp->mpPoints[interp->valSize][i]);
			mpq_set(interp->mpPoints[interp->valSize][i], point[i]);
		}

		rfInterpAddPolynomialRow(interp, interp->valSize);
		++(interp->valSize);

		// if (interp->valSize == n-1) {
		// 	//insert dummy val for the constant term row at n-1'th row
		// 	mpq_init(interp->mpVals[interp->valSize]);
		// 	mpq_set_si(interp->mpVals[interp->valSize], 1l, 1l);

		// 	interp->mpPoints[interp->valSize] = (mpq_t*) malloc(nvar*sizeof(mpq_t));
		// 	for (int i = 0; i < nvar; ++i) {
		// 		mpq_init(interp->mpPoints[interp->valSize][i]);
		// 		mpq_set_si(interp->mpPoints[interp->valSize][i], 0l, 1l);
		// 	}
		// 	++(interp->valSize);
		// }

	// } else {
	// 	int nvar = interp->nvar;
	// 	mpq_set(interp->mpVals[insertRow], val);
	// 	for (int i = 0; i < nvar; ++i) {
	// 		mpq_set(interp->mpPoints[insertRow][i], point[i]);
	// 	}
	// 	rfInterpAddPolynomialRow(interp, insertRow);
	// }

}

mpq_t* deepCopyMatrix(mpq_t* A, long n, long m) {
	mpq_t* ret = (mpq_t*) malloc(sizeof(mpq_t)*n*m);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			mpq_init(ret[i*m + j]);
			mpq_set(ret[i*m + j], A[i*m+j]);
		}
	}

	return ret;
}

void freeMatrix(mpq_t* A, long n, long m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			mpq_clear(A[i*m + j]);
		}
	}	
	free(A);
}

long rfInterpGetPointsForDelta(Interpolator_t* interp) {
	int nvar = interp->nvar;
	long num = 1, den = 1;
	for (int i = 0; i < nvar; ++i) {
		num *= (interp->deltaNum[i] + 1); 
		den *= (interp->deltaDen[i] + 1); 
	}
	return (num + den - 1);
}

void rfInterpIncrementDelta(Interpolator_t* interp) {
	
	int enumSucc = 0;
	if (interp->deltaFlipFlip) {
		enumSucc = enumerateDegreeBounds(interp->deltaDen, interp->denomDegreeBounds, interp->nvar);
		if (!enumSucc) {
			enumSucc = enumerateDegreeBounds(interp->deltaNum, interp->degreeBounds, interp->nvar);
			interp->deltaFlipFlip = 0;
		} else {
			interp->deltaFlipFlip = 1 - interp->deltaFlipFlip;
		}
	} else {
		enumSucc = enumerateDegreeBounds(interp->deltaNum, interp->degreeBounds, interp->nvar);
		if (!enumSucc) {
			enumSucc = enumerateDegreeBounds(interp->deltaDen, interp->denomDegreeBounds, interp->nvar);
			interp->deltaFlipFlip = 1;
		} else {
			interp->deltaFlipFlip = 1 - interp->deltaFlipFlip;
		}
	}

	// fprintf(stderr, "deltaNum: ");
	// for (int k = 0; k < interp->nvar; ++k) {
	// 	fprintf(stderr, "%d ", interp->deltaNum[k]);
	// }
	// fprintf(stderr, "\ndeltaDen: ");
	// for (int k = 0; k < interp->nvar; ++k) {
	// 	fprintf(stderr, "%d ", interp->deltaDen[k]);
	// }
	// fprintf(stderr, "\n");

	rfInterpUpdateMatrix(interp, interp->deltaNum, interp->deltaDen);
}

int _rfInterpIncrementDeltas(int* deltaNum, int* degreeBounds, int* deltaDen, int* denomDegreeBounds, int* flipflop, int nvar) {	

	int enumSucc = 0;
	if (*flipflop) {
		enumSucc = enumerateDegreeBounds(deltaDen, denomDegreeBounds, nvar);
		if (!enumSucc) {
			enumSucc = enumerateDegreeBounds(deltaNum, degreeBounds, nvar);
			*flipflop = 0;
		} else {
			*flipflop = 1 - *flipflop;
		}
	} else {
		enumSucc = enumerateDegreeBounds(deltaNum, degreeBounds, nvar);
		if (!enumSucc) {
			enumSucc = enumerateDegreeBounds(deltaDen, denomDegreeBounds, nvar);
			*flipflop = 1;
		} else {
			*flipflop = 1 - *flipflop;
		}
	}

	return enumSucc;
}


void _rfInterpCheckPoly(Interpolator_t* interp, AltArr_t* numPoly, AltArr_t* denomPoly, mpq_t residual) {
	int npoints = interp->valSize;

	if (npoints == 0) {
		mpz_set_ui(mpq_numref(residual), 1l);
		mpz_set_ui(mpq_denref(residual), 1l);
	}

	mpq_t numVal;
	mpq_t denVal;
	mpq_init(numVal);
	mpq_init(denVal);

	mpq_t valSum;
	mpq_init(valSum);

	// fprintf(stderr, "# of points: %d\n", npoints);

	for (int i = 1; i < npoints; ++i) {
		mpq_t* point = interp->mpPoints[i];
		mpq_t* val = &(interp->mpVals[i]);
		mpq_add(valSum, valSum, *val);

		evalPolyToVal_AA(numPoly, point, interp->nvar, numVal);
		evalPolyToVal_AA(denomPoly, point, interp->nvar, denVal);

		if (mpq_sgn(denVal) == 0) {
			mpq_set_si(residual, LLONG_MAX, 1l);
			break;
		}
		mpq_div(numVal, numVal, denVal);

		//gmp_fprintf(stderr, "Got val: %g, expected: %g\n", mpq_get_d(numVal), mpq_get_d(*val));
		mpq_sub(numVal, numVal, *val);
		mpq_mul(numVal, numVal, numVal);
//		gmp_fprintf(stderr, "Got diff: %g\n", mpq_get_d(numVal));
//		gmp_fprintf(stderr, "Got val: %g\n", mpq_get_d(*val));
//		gmp_fprintf(stderr, "Diff as percent: %g\n", mpq_get_d(numVal) / mpq_get_d(*val));		
		
		mpq_add(residual, residual, numVal);
	}


	double d = mpq_get_d(residual);
	//fprintf(stderr, "got residual double: %g and sqrt: %g\n", d, sqrt(d));
		
	if (fabs(mpq_get_d(residual)) > FLOAT_EPS && fabs(mpq_get_d(valSum)) > FLOAT_EPS) {

		//gmp_fprintf(stderr, "residual: %Qd\n", residual);
		///calculate average observation value

		mpq_t mp_npoints;
		mpq_init(mp_npoints);
		mpq_set_si(mp_npoints, npoints, 1l);
		mpq_div(valSum, valSum, mp_npoints);


		mpq_div(residual, residual, mp_npoints);

		//gmp_fprintf(stderr, "Val sum: %Qd\n", valSum);

		double d = mpq_get_d(residual);
		//fprintf(stderr, "got residual double: %g and sqrt: %g\n", d, sqrt(d));
		mpq_set_d(residual, sqrt(d));

		// Error

		mpq_div(residual, residual, valSum);


		//fprintf(stderr, "TEST\n");
		mpq_clear(mp_npoints);
	}

	mpq_clear(valSum);

	// evalPolyToVal_AA(numPoly, newpoint, interp->nvar, numVal);
	// evalPolyToVal_AA(denomPoly, newpoint, interp->nvar, denVal);
	// if (mpq_sgn(denVal) == 0) {
	// 	mpq_set_si(residual, 999999999999l, 1l);
	// 	mpq_clear(numVal);
	// 	mpq_clear(denVal);
	// 	return;
	// }
	// mpq_div(numVal, numVal, denVal);
	// mpq_sub(numVal, numVal, newval);
	// mpq_mul(numVal, numVal, numVal);
	// mpq_add(residual, residual, numVal);
  	// fprintf(stderr, "\n\n\n");

	mpq_clear(numVal);
	mpq_clear(denVal);	
}

PolyInterpStatus_t rfInterpGetPoly_EarlyTerm(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly, double maximumResidual) {
	return _rfInterpGetPoly(interp, numPoly, denomPoly, maximumResidual, 1);
}

PolyInterpStatus_t rfInterpGetPoly(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly, double maximumResidual) {	
	return _rfInterpGetPoly(interp, numPoly, denomPoly, maximumResidual, 0);
}

PolyInterpStatus_t _rfInterpGetPoly(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly, double maximumResidual, int earlyTerm) {	
	//fprintf(stderr, "Valsize: %ld\n\n", interp->valSize);

	if (interp->valSize <= 2) {
		return POLY_INTERP_FAILURE;
	}

	long cols = interp->n;
	long rows = interp->valSize;
	long n2 = interp->numeratorNumTerms;
	int nvar = interp->nvar;

	

	int deltaNum[nvar];
	int deltaDen[nvar];
	for (int k = 0; k < nvar; ++k) {
		deltaNum[k] = 0;
		deltaDen[k] = 0;
	}
	
	// double* dA = (double*) malloc(sizeof(double)*rows*cols);
	double* db = (double*) malloc(sizeof(double)*rows*1);
	double* X = (double*) malloc(sizeof(double)*cols*1);
	for (int i = 0; i < rows; ++i) {
		db[i] = 0;
	}
	db[0] = 1;

	AltArr_t* bestNum = NULL, *bestDen = NULL;
	mpq_t bestResidual;
	mpq_init(bestResidual);
	mpq_set_si(bestResidual, -1l, 1l);
	mpq_t* mpX = (mpq_t*) malloc(sizeof(mpq_t)*cols);
	for (int i = 0; i < cols; ++i) {
		mpq_init(mpX[i]);
	}	

	int flipflop = 0; //0 means update numerator first
	while(_rfInterpIncrementDeltas(deltaNum, interp->degreeBounds, deltaDen, interp->denomDegreeBounds, &flipflop, nvar)) {

		// fprintf(stderr, "DeltaNum: ");
		// for (int i = 0; i < nvar; ++i) {
		// 	fprintf(stderr, "%d ", deltaNum[i]);
		// }
		// fprintf(stderr, "\nDeltaDen: ");
		// for (int i = 0; i < nvar; ++i) {
		// 	fprintf(stderr, "%d ", deltaDen[i]);
		// }
		// fprintf(stderr, "\n\n");

		double* dA = _rfInterpGetSampleMatrix(interp, deltaNum, deltaDen, &rows, &cols, &n2);

		if (cols > rows) {
			free(dA);
			continue;
		}

	//	fprintf(stderr, "rows: %ld, cols: %ld, n2: %ld\n", rows, cols, n2);	
	//	fprintf(stderr, "Got sample A:\n");
	//	printDoubleMat(dA, 1, cols);
	//	fprintf(stderr, "\n\n");
		// continue;

		//iterate over the terms to normalize
		for (int l = 0; l < cols - n2; ++l) {
			for (int i = 0; i < 1; ++i) {
				for (int j = 0; j < cols; ++j) {
					dA[i*cols + j] = 0.0;
				}
			}
			dA[0*cols + n2 + l] = 1.0;
		
#if INTERP_DEBUG
			fprintf(stderr, "Solving A:\n");
			printDoubleMat(dA, rows, cols);
			fprintf(stderr, "Solving b:\n");
			printDoubleMat(db, rows, 1);
#endif
			long rank = solveDoubleSystem(dA, db, rows, cols, X);

#if INTERP_DEBUG
			fprintf(stderr, "Got rank: %ld   ", rank);
			fprintf(stderr, "X: ");
			for (int i = 0; i < cols; ++i) {
				 gmp_fprintf(stderr, " %g", X[i]);
			}
			fprintf(stderr, "\n");
#endif

			int failed = 0;
			for (int i = 0; i < cols; ++i) {
				if (X[i] != X[i] || isinf(X[i])) {
					failed = 1;
					break;
				}
				mpq_set_d(mpX[i], X[i]);
			}
			if (failed) {
				continue;
			}

			double eps = 1e-50;
			AltArr_t* curNum = buildPolyFromCoefArrayWithEps(deltaNum, interp->nvar, mpX, eps);
			AltArr_t* curDen = buildPolyFromCoefArrayWithEps(deltaDen, interp->nvar, mpX + n2, eps);

			if (curDen == NULL) {
#if INTERP_DEBUG
				fprintf(stderr, "curDen was null\n");
#endif
				freePolynomial_AA(curNum);
				continue;
			}

#if INTERP_DEBUG
			char* syms[] = {"x", "y", "z"};
			fprintf(stderr, "num:\n");
			printPolyDouble_AA(stderr, curNum, syms, interp->nvar);
			fprintf(stderr, "\n");
			fprintf(stderr, "den:\n");
			printPolyDouble_AA(stderr, curDen, syms, interp->nvar);
			fprintf(stderr, "\n\n");
#endif
			mpq_t residual;
			mpq_init(residual);
			_rfInterpCheckPoly(interp, curNum, curDen, residual);
			double dres = mpq_get_d(residual);
			// fprintf(stderr, "residual: %g\n\n", dres);

			if (mpq_sgn(bestResidual) < 0) {
				bestNum = curNum;
				bestDen = curDen;
				mpq_set(bestResidual, residual);
			} else {
				if (mpq_cmp(residual, bestResidual) < 0) {
					freePolynomial_AA(bestNum);
					freePolynomial_AA(bestDen);
					bestNum = curNum;
					bestDen = curDen;
					mpq_set(bestResidual, residual);
				} else {
					freePolynomial_AA(curNum);
					freePolynomial_AA(curDen);
				}
			}

			mpq_clear(residual);
		} //for l loop

		free(dA);
		if (mpq_sgn(bestResidual) < 0) {
			continue;
		}
		//mpq_abs(bestResidual, bestResidual);
		if (earlyTerm && mpq_get_d(bestResidual) < maximumResidual) {
			break;
		}

	} //while delta loop

	*numPoly = bestNum;
	*denomPoly = bestDen;


	for (int i = 0; i < cols; ++i) {
		mpq_clear(mpX[i]);
	}
	free(X);
	free(db);
	// free(dA);

	//now make denominator monic.
	if (*denomPoly != NULL && (*denomPoly)->size > 0) {
		mpq_t temp;
		mpq_init(temp);
		mpq_set(temp, (*denomPoly)->elems[0].coef);
		mpq_inv(temp, temp);
		multiplyByRational_AA_inp(*numPoly, temp);
		multiplyByRational_AA_inp(*denomPoly, temp);
		mpq_clear(temp);
	}

	mpq_abs(bestResidual, bestResidual);
	//fprintf(stderr, "\nBest residual: %g, maximumResidual: %g, abs: %g, cmp: %d\n", mpq_get_d(bestResidual), maximumResidual, mpq_get_d(bestResidual), mpq_get_d(bestResidual) > maximumResidual);

	if (mpq_sgn(bestResidual) < 0 || mpq_get_d(bestResidual) > maximumResidual) {

		mpq_clear(bestResidual);
		freePolynomial_AA(*numPoly);
		freePolynomial_AA(*denomPoly);
		*numPoly = NULL;
		*denomPoly = NULL;
		return POLY_INTERP_FAIL_BY_RESIDUAL;
	}

	mpq_clear(bestResidual);
	return POLY_INTERP_SUCCESS;
}

PolyInterpStatus_t rfInterpCheckPoly(Interpolator_t* interp, const AltArr_t* numPoly, const AltArr_t* denomPoly, mpq_t* point, mpq_t val) {
	return rfInterpCheckPolyWithTolerance(interp, numPoly, denomPoly, point, val, 0.0);
}

PolyInterpStatus_t rfInterpCheckPolyWithTolerance(Interpolator_t* interp, const AltArr_t* numPoly, const AltArr_t* denomPoly, mpq_t* point, mpq_t val, double tolerance) {
	mpq_t numVal;
	mpq_t denVal;
	mpq_init(numVal);
	mpq_init(denVal);

	evalPolyToVal_AA(numPoly, point, interp->nvar, numVal);
	evalPolyToVal_AA(denomPoly, point, interp->nvar, denVal);
	if (mpq_sgn(denVal) == 0) {
		mpq_clear(numVal);
		mpq_clear(denVal);
		return POLY_INTERP_MORE_POINTS;
	}


	mpq_div(numVal, numVal, denVal);

	int cmp = 1;
	double eps = 1e-8;
	if (tolerance < eps) {
		cmp = mpq_cmp(numVal, val);
	} else {
		mpq_sub(numVal, numVal, val);
		mpq_div(numVal, numVal, val);
		if (mpq_sgn(numVal) < 0) {
			mpq_neg(numVal, numVal);
		}
		double dVal = mpq_get_d(numVal);
		if (dVal < tolerance) {
			cmp = 0;
		}
	}

	// gmp_fprintf(stderr, "\n\n////////////////////////// Check Poly got val: %Qd, Expected: %Qd\n", numVal, val);
	// gmp_fprintf(stderr, "point: ");
	// for (int i = 0; i < interp->nvar; ++i) {
		// gmp_fprintf(stderr, "%Qd ", point[i]);
	// }
	// fprintf(stderr, "\n");

	mpq_clear(numVal);
	mpq_clear(denVal);

	if (cmp == 0) {
		return POLY_INTERP_SUCCESS;
	} else {
		return POLY_INTERP_MORE_POINTS;
	}
}

void enumSubsets(int n, int k, int*** result, int* resultSize) {
	if (k == 0) {
		*result = (int**) calloc(1, sizeof(int*));
		*resultSize = 1;
		return;
	}

	if (n < k) {
		*result = NULL;
		*resultSize = 0;
		return;
	}

	int** n1k1 = NULL;
	int n1k1Size;
	int** n1k = NULL;
	int n1kSize;
	enumSubsets(n-1, k-1, &n1k1, &n1k1Size);
	enumSubsets(n-1, k, &n1k, &n1kSize);

	for (int i = 0; i < n1k1Size; ++i) {
		n1k1[i] = (int*) realloc(n1k1[i], k*sizeof(int));
		n1k1[i][k-1] = n-1; // -1 for 0-based indices
	}

	int** temp = (int**) malloc(sizeof(int*)*(n1k1Size + n1kSize));
	for (int i = 0; i < n1k1Size; ++i) {
		temp[i] = n1k1[i];
	}
	for (int i = 0; i < n1kSize; ++i) {
		temp[n1k1Size + i] = n1k[i];
	}

	*result = temp;
	*resultSize = n1k1Size + n1kSize; 

	free(n1k1);
	free(n1k);
}

PolyInterpStatus_t rfInterpGetPolyAmbiguous(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly) {
	// fprintf(stderr, "///////////////////////////// Get AMBIGUOUS Poly\n");

	long n = interp->n;
	long n2 = interp->numeratorNumTerms;
	int nvar = interp->nvar;

	long rank = 0;
	long* tempRowsList;
	mpq_t* X;

	int* denBounds = interp->denomDegreeBounds;

	mpq_t* A = interp->A;
	//TODO
	mpq_t* tempA = NULL;// getMPQIdentity(n);
	//tempA will always have at least the numerator rows equal
	for (int i = 0; i < n2; ++i) {
		for (int j = 0; j < n; ++j) {
			mpq_set(tempA[i*n + j], A[i*n + j]);
		}
	}

	mpq_t b[n];
	for (int i = 0; i < n; ++i) {
		mpq_init(b[i]);
	}
	mpq_set_si(b[n2], 1l, 1l);
	
	int tempDenBounds[nvar];
	int degrees[nvar];

	for (int k = 0; k < nvar; ++k) {
		tempDenBounds[k] = 0;
		degrees[0] = 0;
	}
	tempDenBounds[nvar-1] = -1;

	while(enumerateMonomials(tempDenBounds, denBounds, nvar)) {
		// fprintf(stderr, "tempNumBounds: ");
		// for (int i = 0; i < nvar; ++i) {
		// 	fprintf(stderr, "%d", tempNumBounds[i]);
		// }
		// fprintf(stderr, "\ntempDenBounds: ");
		// for (int i = 0; i < nvar; ++i) {
		// 	fprintf(stderr, "%d", tempDenBounds[i]);
		// }
		// fprintf(stderr, "\n");

		for (int i = 0; i < nvar; ++i) {
			degrees[i] = 0;
		}
		for (int i = n2+1; i < n; ++i) {
			enumerateMonomials(degrees, denBounds, nvar);
			if (!monomialInBounds(degrees, tempDenBounds, nvar)) {
				continue;
			}
			for (int j = 0; j < n; ++j) {
				mpq_set(tempA[i*n + j], A[i*n + j]);
			}
		}
	
		//iterate through denominator terms which should be normalized to 1.
		long row = n2;
		for (int i = n2; i < n; ++i) {
			int j = i-1;
			mpq_set_si(tempA[row*n + j], 0l, 1l);
			mpq_set_si(tempA[row*n + i], 1l, 1l);

			// fprintf(stderr, "\nn2: %d, denom j: %d\n", n2, i);
			// fprintf(stderr, "tempA: \n");
			// printMPQMat(tempA, n, n);
			// fprintf(stderr, "b: ");
			// printMPQMat(b, 1, n);
			// fprintf(stderr, "\n");
			rank = 0;//solveMPQSystem(tempA, b, n, &X, &tempRowsList);
			// fprintf(stderr, "\nRank3: %ld\n", rank);
		
			if (rank == n) {
				*numPoly = buildPolyFromCoefArray(interp->degreeBounds, interp->nvar, X);
				*denomPoly = buildPolyFromCoefArray(interp->denomDegreeBounds, interp->nvar, X + interp->numeratorNumTerms);
				char* syms[] = {"x", "y", "z"};
				// fprintf(stderr, "GOT AMBIGUOUS POLY /////////////////////////////////");
				// fprintf(stderr, "num:\n");
				// printPoly_AA(stderr, *numPoly, syms, nvar);
				// fprintf(stderr, "den:\n");
				// printPoly_AA(stderr, *denomPoly, syms, nvar);
			
				for (int i = 0; i < interp->valSize; ++i) {
					// fprintf(stderr, "check i: %d ////////////////////////////////////////////////////////\n", i);
					PolyInterpStatus_t checkStat = rfInterpCheckPoly(interp, *numPoly, *denomPoly, interp->mpPoints[i], interp->mpVals[i]);
					if (checkStat != POLY_INTERP_SUCCESS) {
						// fprintf(stderr, "Check failed!\n");
						freePolynomial_AA(*numPoly);
						freePolynomial_AA(*denomPoly);
						*numPoly = NULL;
						*denomPoly = NULL;
						rank = 0;
						break;
					}
				}

				if (rank == n) {
					break;
				}
			}
		} //test all denom normalizations

		//all values passed so we're good!
		if (rank == n) {
			break;
		}

		//reset lower part of A to be identity
		for (int i = n2; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j) {
					mpq_set_si(tempA[i*n+j], 1l, 1l);
				} else {
					mpq_set_si(tempA[i*n+j], 0l, 1l);
				}
			}
		}
	} //iterating denominator degree bounds

	if (rank == n) {
		//now make denominator monic.
		if (*denomPoly != NULL && (*denomPoly)->size > 0) {
			mpq_t temp;
			mpq_init(temp);
			mpq_set(temp, (*denomPoly)->elems[0].coef);
			mpq_inv(temp, temp);
			multiplyByRational_AA_inp(*numPoly, temp);
			multiplyByRational_AA_inp(*denomPoly, temp);
			mpq_clear(temp);
		}

		for (int i = 0; i < n; ++i) {
			mpq_clear(b[i]);
		}
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j) {
				mpq_clear(tempA[i*n + j]);
			}
		}
		free(tempA);

		return POLY_INTERP_SUCCESS;		
	} 

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j) {
			mpq_clear(tempA[i*n + j]);
		}
	}
	free(tempA);
	for (int i = 0; i < n; ++i) {
		mpq_clear(b[i]);
	}
	return POLY_INTERP_MORE_POINTS;		

}

PolyInterpStatus_t rfInterpGetPolyDegenerative(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly) {
	long n = interp->n;
	long n2 = interp->numeratorNumTerms;
	int nvar = interp->nvar;

	long rank = 0;
	long* tempRowsList;
	mpq_t* X;

	int* numBounds = interp->degreeBounds;
	int* denBounds = interp->denomDegreeBounds;

	mpq_t* A = interp->A;
	//TODO
	mpq_t* tempA = NULL;//getMPQIdentity(n);
	mpq_t b[n];
	for (int i = 0; i < n; ++i) {
		mpq_init(b[i]);
	}
	
	int tempNumBounds[nvar];
	int tempDenBounds[nvar];

	int degrees[nvar];

	for (int subsetSize = nvar-1; subsetSize >= 1; --subsetSize) {
		int** subsetList = NULL;
		int numSubsets;
		enumSubsets(nvar, subsetSize, &subsetList, &numSubsets);

		// fprintf(stderr, "got subsets:    {");
		// for (int i = 0; i < numSubsets; ++i) {
		// 	fprintf(stderr, "{");
		// 	for (int j = 0; j < subsetSize; ++j) {
		// 		fprintf(stderr, "%d ", subsetList[i][j]);
		// 	}
		// 	fprintf(stderr, "} ");
		// }
		// fprintf(stderr, "}\n");

		for (int subsetItr = 0; subsetItr < numSubsets; ++subsetItr) {
			int* curSubset = subsetList[subsetItr];

			//setup bounds for this current subset
			for (int k = 0; k < nvar; ++k) {
				tempNumBounds[k] = 0;
				tempDenBounds[k] = 0;
				degrees[0] = 0;
			}
			for (int k = 0; k < subsetSize; ++k) {
				tempNumBounds[curSubset[k]] = numBounds[curSubset[k]];
				tempDenBounds[curSubset[k]] = denBounds[curSubset[k]];
			}

			// fprintf(stderr, "tempNumBounds: ");
			// for (int i = 0; i < nvar; ++i) {
			// 	fprintf(stderr, "%d", tempNumBounds[i]);
			// }
			// fprintf(stderr, "\ntempDenBounds: ");
			// for (int i = 0; i < nvar; ++i) {
			// 	fprintf(stderr, "%d", tempDenBounds[i]);
			// }
			// fprintf(stderr, "\n");

			//get number of points needed for this collection of tempbounds
			int numPoints = 1;
			int denPoints = 1;
			for (int k = 0; k < nvar; ++k) {
				numPoints *= (tempNumBounds[k] + 1);
				denPoints *= (tempDenBounds[k] + 1);
			}
			int nPoints = numPoints + denPoints - 1; //-1 for constant row

			// while (enumerateMonomials(degrees, interp->numBounds, nvar)) {
			// 	if (monomialInBounds(degrees, tempBounds, nvar)) {
			// 		++nPoints;
			// 	}
			// }
			// for (int i = 0; i < nvar; ++i) {
			// 	degrees[i] = 0;
			// }
			// tempBounds[0] = interp->denomDegreeBounds[0];
			// while (enumerateMonomials(degrees, interp->denomDegreeBounds, nvar)) {
			// 	if (monomialInBounds(degrees, tempBounds, nvar)) {
			// 		++nPoints;
			// 	}			
			// }

			for (int i = 0; i < nvar; ++i) {
				degrees[i] = 0;
			}
			for (int i = 0; i < 1; ++i) {
				for (int j = 0; j < n; ++j) {
					mpq_set(tempA[i*n + j], A[i*n + j]);
				}
				--nPoints;
			}
			for (int i = 1; i < n2; ++i) {
				enumerateMonomials(degrees, numBounds, nvar);
				if (!monomialInBounds(degrees, tempNumBounds, nvar)) {
					continue;
				}
				for (int j = 0; j < n; ++j) {
					mpq_set(tempA[i*n + j], A[i*n + j]);
				}
				--nPoints;
			}
			for (int i = 0; i < nvar; ++i) {
				degrees[i] = 0;
			}
			for (int i = n2+1; i < n; ++i) {
				enumerateMonomials(degrees, denBounds, nvar);
				if (!monomialInBounds(degrees, tempDenBounds, nvar)) {
					continue;
				}
				for (int j = 0; j < n; ++j) {
					mpq_set(tempA[i*n + j], A[i*n + j]);
				}
				--nPoints;
			}

			for (int i = 0; i < n; ++i) {
				mpq_set_si(b[i], 0l, 1l);
			}
			mpq_set_si(b[n2], 1l, 1l);
		
			//iterate through denominator terms which should be normalized to 1.
			long row = n2;
			for (int i = n2; i < n; ++i) {
				int j = i-1;
				mpq_set_si(tempA[row*n + j], 0l, 1l);
				mpq_set_si(tempA[row*n + i], 1l, 1l);

				// fprintf(stderr, "\nn2: %d, denom j: %d\n", n2, i);
				// fprintf(stderr, "tempA: \n");
				// printMPQMat(tempA, n, n);
				// fprintf(stderr, "b: ");
				// printMPQMat(b, 1, n);
				// fprintf(stderr, "\n");
				rank = 0;//solveMPQSystem(tempA, b, n, &X, &tempRowsList);
				// fprintf(stderr, "\nRank3: %ld\n", rank);
			
				if (rank == n) {
					*numPoly = buildPolyFromCoefArray(interp->degreeBounds, interp->nvar, X);
					*denomPoly = buildPolyFromCoefArray(interp->denomDegreeBounds, interp->nvar, X + interp->numeratorNumTerms);
					char* syms[] = {"x", "y", "z"};
					// fprintf(stderr, "GOT DEGENERATIVE POLY /////////////////////////////////");
					// fprintf(stderr, "num:\n");
					// printPoly_AA(stderr, *numPoly, syms, nvar);
					// fprintf(stderr, "den:\n");
					// printPoly_AA(stderr, *denomPoly, syms, nvar);
				
					for (int i = 0; i < interp->valSize; ++i) {
						// fprintf(stderr, "check i: %d ////////////////////////////////////////////////////////\n", i);
						PolyInterpStatus_t checkStat = rfInterpCheckPoly(interp, *numPoly, *denomPoly, interp->mpPoints[i], interp->mpVals[i]);
						if (checkStat != POLY_INTERP_SUCCESS) {
							// fprintf(stderr, "Check failed!\n");
							freePolynomial_AA(*numPoly);
							freePolynomial_AA(*denomPoly);
							*numPoly = NULL;
							*denomPoly = NULL;
							rank = 0;
							break;
						}
					}

					if (rank == n) {
						break;
					}
				}
			}

			//all values passed so we're good!
			if (rank == n) {
				break;
			}

			//reset A to be identity
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (i == j) {
						mpq_set_si(tempA[i*n+j], 1l, 1l);
					} else {
						mpq_set_si(tempA[i*n+j], 0l, 1l);
					}
				}
			}
		} //iterating over each subset

		for (int i = 0; i < numSubsets; ++i) {
			free(subsetList[i]);
		}
		free(subsetList);
		if (rank == n) {
			break;
		}

	} //for subsetSize = nvar-1:1

	if (rank == n) {
		// *numPoly = buildPolyFromCoefArray(interp->degreeBounds, interp->nvar, X);
		// *denomPoly = buildPolyFromCoefArray(interp->denomDegreeBounds, interp->nvar, X + interp->numeratorNumTerms);
		// char* syms[] = {"x", "y", "z"};
		// fprintf(stderr, "GOT DEGENERATIVE POLY /////////////////////////////////");
		// fprintf(stderr, "num:\n");
		// printPoly_AA(stderr, *numPoly, syms, nvar);
		// fprintf(stderr, "den:\n");
		// printPoly_AA(stderr, *denomPoly, syms, nvar);
		//now make denominator monic.
		if (*denomPoly != NULL && (*denomPoly)->size > 0) {
			mpq_t temp;
			mpq_init(temp);
			mpq_set(temp, (*denomPoly)->elems[0].coef);
			mpq_inv(temp, temp);
			multiplyByRational_AA_inp(*numPoly, temp);
			multiplyByRational_AA_inp(*denomPoly, temp);
			mpq_clear(temp);
		}

		for (int i = 0; i < n; ++i) {
			mpq_clear(b[i]);
		}
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j) {
				mpq_clear(tempA[i*n + j]);
			}
		}
		free(tempA);

		return POLY_INTERP_SUCCESS;		
	} else {
		//Very last try now. Try for a constant. 
		for (int i = 0; i < 1; ++i) {
			for (int j = 0; j < n; ++j) {
				mpq_set(tempA[i*n + j], A[i*n + j]);
			}
		}
		rank = 0;//solveMPQSystem(tempA, b, n, &X, &tempRowsList);
		// fprintf(stderr, "\nRank3: %ld\n", rank);
	
		if (rank == n) {
			*numPoly = buildPolyFromCoefArray(interp->degreeBounds, interp->nvar, X);
			*denomPoly = buildPolyFromCoefArray(interp->denomDegreeBounds, interp->nvar, X + interp->numeratorNumTerms);
			// char* syms[] = {"x", "y", "z"};
			// fprintf(stderr, "GOT DEGENERATIVE POLY /////////////////////////////////");
			// fprintf(stderr, "num:\n");
			// printPoly_AA(stderr, *numPoly, syms, nvar);
			// fprintf(stderr, "den:\n");
			// printPoly_AA(stderr, *denomPoly, syms, nvar);
		
			for (int i = 0; i < interp->valSize; ++i) {
				// fprintf(stderr, "check i: %d ////////////////////////////////////////////////////////\n", i);
				PolyInterpStatus_t checkStat = rfInterpCheckPoly(interp, *numPoly, *denomPoly, interp->mpPoints[i], interp->mpVals[i]);
				if (checkStat != POLY_INTERP_SUCCESS) {
					// fprintf(stderr, "Check failed!\n");
					freePolynomial_AA(*numPoly);
					freePolynomial_AA(*denomPoly);
					*numPoly = NULL;
					*denomPoly = NULL;
					rank = 0;
					break;
				}
			}
		}

	}

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j) {
			mpq_clear(tempA[i*n + j]);
		}
	}
	free(tempA);
	for (int i = 0; i < n; ++i) {
		mpq_clear(b[i]);
	}
	return POLY_INTERP_MORE_POINTS;		
}
































#if INTERPOLATOR_TEST

#include <stdio.h>
int main(void) {

	char* syms[] = {"x", "y", "z"};
	int nvar = 3;
	int degreeBounds[nvar];
	for (int i = 0; i < nvar; ++i) {
		degreeBounds[i] = i+1;
	}
	// degreeBounds[0] = 2;


	Interpolator_t* interp = interpInit(nvar, degreeBounds);

	long long int meshMins[nvar];
	long long int meshMaxs[nvar];
	long long int meshIncrements[nvar];

	for (int i = 0; i < nvar; ++i) {
		meshMins[i] = 2;
		meshIncrements[i] = 2;
	}

	meshMaxs[0] = 8;
	meshMaxs[1] = 8;
	meshMaxs[2] = 16;

	// interpSetMeshBounds(interp, meshMins, meshMaxs, meshIncrements, MESH_INCR_ADDITION, 1);
	interpSetMeshBounds(interp, meshMins, meshMaxs, meshIncrements, MESH_INCR_MULTIPLICATION, 1);

	long long int point[nvar];
	
	gmp_randstate_t state;
	gmp_randinit_default (state);
	time_t seed = time(NULL);
	fprintf(stderr, "time: %lu\n", seed);
	gmp_randseed_ui (state, seed);

	mpq_t randVal;
	mpq_init(randVal);	
	mpq_t* mpPoint = (mpq_t*) malloc(nvar*sizeof(mpq_t));
	for (int i = 0; i < nvar; ++i) {
		mpq_init(mpPoint[i]);
	}	
	
	long nbits = 3;

	AltArr_t* poly = NULL;
	while (interpGetNextPoint(interp, point)) {
#if INTERP_DEBUG
		fprintf(stderr, "Got point %d: [", i);
		for (int j = 0; j < nvar-1; ++j) {
			fprintf(stderr, "%lld, ", point[j]);
		}
		fprintf(stderr, "%lld]\n", point[nvar-1]);
#endif
		for (int i = 0; i < nvar; ++i) {
			mpq_set_si(mpPoint[i], point[i], 1);
		}	

		//random point generation
		mpz_urandomb (mpq_numref(randVal), state, nbits);
#if INTERP_DEBUG
		gmp_fprintf(stderr, "Got val: %Zd\n", randVal);
#endif
		
		//add (point, val);
		interpAddPointValMP(interp, mpPoint, randVal);
				
		//check poly stat
		PolyInterpStatus_t stat = interpGetPoly(interp, &poly);
		if (stat == POLY_INTERP_SUCCESS) {
			fprintf(stderr, "Interpolated a polynomial: \n");
			printLocalAA(poly, syms, nvar);
			break;
		} else if (stat == POLY_INTERP_FAILURE) {
			fprintf(stderr, "ERROR: Failed to interpolate!\n");
			break;
		}
	}

	if (poly == NULL) {
		fprintf(stderr, "ERROR: Failed to interpolate!\n");
	}

	for (int i = 0; i < nvar; ++i) {
		mpq_clear(mpPoint[i]);
	}
	free(mpPoint);

	freePolynomial_AA(poly);

	return 0;
}

#endif











