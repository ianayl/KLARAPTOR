#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal ops, itcnt;
} latime_;

#define latime_1 latime_

/* Table of constant values */

static integer c__9 = 9;
static integer c__0 = 0;
static integer c__2 = 2;
static doublereal c_b23 = 1.;
static doublereal c_b24 = 0.;
static integer c__1 = 1;

/* Subroutine */ int dlaed0_(integer *icompq, integer *qsiz, integer *n, 
	doublereal *d__, doublereal *e, doublereal *q, integer *ldq, 
	doublereal *qstore, integer *ldqs, doublereal *work, integer *iwork, 
	integer *info)
{
    /* System generated locals */
    integer q_dim1, q_offset, qstore_dim1, qstore_offset, i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal);
    integer pow_ii(integer *, integer *);

    /* Local variables */
    static doublereal temp;
    static integer curr, i__, j, k;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *);
    static integer iperm;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer indxq, iwrem;
    extern /* Subroutine */ int dlaed1_(integer *, doublereal *, doublereal *,
	     integer *, integer *, doublereal *, integer *, doublereal *, 
	    integer *, integer *);
    static integer iqptr;
    extern /* Subroutine */ int dlaed7_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    integer *, integer *, doublereal *, integer *, doublereal *, 
	    integer *, integer *, integer *, integer *, integer *, doublereal 
	    *, doublereal *, integer *, integer *);
    static integer tlvls, iq;
    extern /* Subroutine */ int dlacpy_(char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, integer *);
    static integer igivcl;
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static integer igivnm, submat, curprb, subpbs, igivpt;
    extern /* Subroutine */ int dsteqr_(char *, integer *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *);
    static integer curlvl, matsiz, iprmpt, smlsiz, lgn, msd2, smm1, spm1, 
	    spm2;


#define q_ref(a_1,a_2) q[(a_2)*q_dim1 + a_1]
#define qstore_ref(a_1,a_2) qstore[(a_2)*qstore_dim1 + a_1]


/*  -- LAPACK routine (instrumented to count operations, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   

       Common block to return operation count and iteration count   
       ITCNT is unchanged, OPS is only incremented   

    Purpose   
    =======   

    DLAED0 computes all eigenvalues and corresponding eigenvectors of a   
    symmetric tridiagonal matrix using the divide and conquer method.   

    Arguments   
    =========   

    ICOMPQ  (input) INTEGER   
            = 0:  Compute eigenvalues only.   
            = 1:  Compute eigenvectors of original dense symmetric matrix   
                  also.  On entry, Q contains the orthogonal matrix used   
                  to reduce the original matrix to tridiagonal form.   
            = 2:  Compute eigenvalues and eigenvectors of tridiagonal   
                  matrix.   

    QSIZ   (input) INTEGER   
           The dimension of the orthogonal matrix used to reduce   
           the full matrix to tridiagonal form.  QSIZ >= N if ICOMPQ = 1.   

    N      (input) INTEGER   
           The dimension of the symmetric tridiagonal matrix.  N >= 0.   

    D      (input/output) DOUBLE PRECISION array, dimension (N)   
           On entry, the main diagonal of the tridiagonal matrix.   
           On exit, its eigenvalues.   

    E      (input) DOUBLE PRECISION array, dimension (N-1)   
           The off-diagonal elements of the tridiagonal matrix.   
           On exit, E has been destroyed.   

    Q      (input/output) DOUBLE PRECISION array, dimension (LDQ, N)   
           On entry, Q must contain an N-by-N orthogonal matrix.   
           If ICOMPQ = 0    Q is not referenced.   
           If ICOMPQ = 1    On entry, Q is a subset of the columns of the   
                            orthogonal matrix used to reduce the full   
                            matrix to tridiagonal form corresponding to   
                            the subset of the full matrix which is being   
                            decomposed at this time.   
           If ICOMPQ = 2    On entry, Q will be the identity matrix.   
                            On exit, Q contains the eigenvectors of the   
                            tridiagonal matrix.   

    LDQ    (input) INTEGER   
           The leading dimension of the array Q.  If eigenvectors are   
           desired, then  LDQ >= max(1,N).  In any case,  LDQ >= 1.   

    QSTORE (workspace) DOUBLE PRECISION array, dimension (LDQS, N)   
           Referenced only when ICOMPQ = 1.  Used to store parts of   
           the eigenvector matrix when the updating matrix multiplies   
           take place.   

    LDQS   (input) INTEGER   
           The leading dimension of the array QSTORE.  If ICOMPQ = 1,   
           then  LDQS >= max(1,N).  In any case,  LDQS >= 1.   

    WORK   (workspace) DOUBLE PRECISION array,   
           If ICOMPQ = 0 or 1, the dimension of WORK must be at least   
                       1 + 3*N + 2*N*lg N + 2*N**2   
                       ( lg( N ) = smallest integer k   
                                   such that 2^k >= N )   
           If ICOMPQ = 2, the dimension of WORK must be at least   
                       4*N + N**2.   

    IWORK  (workspace) INTEGER array,   
           If ICOMPQ = 0 or 1, the dimension of IWORK must be at least   
                          6 + 6*N + 5*N*lg N.   
                          ( lg( N ) = smallest integer k   
                                      such that 2^k >= N )   
           If ICOMPQ = 2, the dimension of IWORK must be at least   
                          3 + 5*N.   

    INFO   (output) INTEGER   
            = 0:  successful exit.   
            < 0:  if INFO = -i, the i-th argument had an illegal value.   
            > 0:  The algorithm failed to compute an eigenvalue while   
                  working on the submatrix lying in rows and columns   
                  INFO/(N+1) through mod(INFO,N+1).   

    Further Details   
    ===============   

    Based on contributions by   
       Jeff Rutter, Computer Science Division, University of California   
       at Berkeley, USA   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    --d__;
    --e;
    q_dim1 = *ldq;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;
    qstore_dim1 = *ldqs;
    qstore_offset = 1 + qstore_dim1 * 1;
    qstore -= qstore_offset;
    --work;
    --iwork;

    /* Function Body */
    *info = 0;

    if (*icompq < 0 || *icompq > 2) {
	*info = -1;
    } else if (*icompq == 1 && *qsiz < max(0,*n)) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*ldq < max(1,*n)) {
	*info = -7;
    } else if (*ldqs < max(1,*n)) {
	*info = -9;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DLAED0", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	return 0;
    }

    smlsiz = ilaenv_(&c__9, "DLAED0", " ", &c__0, &c__0, &c__0, &c__0, (
	    ftnlen)6, (ftnlen)1);

/*     Determine the size and placement of the submatrices, and save in   
       the leading elements of IWORK. */

    iwork[1] = *n;
    subpbs = 1;
    tlvls = 0;
L10:
    if (iwork[subpbs] > smlsiz) {
	for (j = subpbs; j >= 1; --j) {
	    iwork[j * 2] = (iwork[j] + 1) / 2;
	    iwork[(j << 1) - 1] = iwork[j] / 2;
/* L20: */
	}
	++tlvls;
	subpbs <<= 1;
	goto L10;
    }
    i__1 = subpbs;
    for (j = 2; j <= i__1; ++j) {
	iwork[j] += iwork[j - 1];
/* L30: */
    }

/*     Divide the matrix into SUBPBS submatrices of size at most SMLSIZ+1   
       using rank-1 modifications (cuts). */

    spm1 = subpbs - 1;
    latime_1.ops += spm1 << 1;
    i__1 = spm1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	submat = iwork[i__] + 1;
	smm1 = submat - 1;
	d__[smm1] -= (d__1 = e[smm1], abs(d__1));
	d__[submat] -= (d__1 = e[smm1], abs(d__1));
/* L40: */
    }

    indxq = (*n << 2) + 3;
    if (*icompq != 2) {

/*        Set up workspaces for eigenvalues only/accumulate new vectors   
          routine */

	latime_1.ops += 3;
	temp = log((doublereal) (*n)) / log(2.);
	lgn = (integer) temp;
	if (pow_ii(&c__2, &lgn) < *n) {
	    ++lgn;
	}
	if (pow_ii(&c__2, &lgn) < *n) {
	    ++lgn;
	}
	iprmpt = indxq + *n + 1;
	iperm = iprmpt + *n * lgn;
	iqptr = iperm + *n * lgn;
	igivpt = iqptr + *n + 2;
	igivcl = igivpt + *n * lgn;

	igivnm = 1;
	iq = igivnm + (*n << 1) * lgn;
/* Computing 2nd power */
	i__1 = *n;
	iwrem = iq + i__1 * i__1 + 1;

/*        Initialize pointers */

	i__1 = subpbs;
	for (i__ = 0; i__ <= i__1; ++i__) {
	    iwork[iprmpt + i__] = 1;
	    iwork[igivpt + i__] = 1;
/* L50: */
	}
	iwork[iqptr] = 1;
    }

/*     Solve each submatrix eigenproblem at the bottom of the divide and   
       conquer tree. */

    curr = 0;
    i__1 = spm1;
    for (i__ = 0; i__ <= i__1; ++i__) {
	if (i__ == 0) {
	    submat = 1;
	    matsiz = iwork[1];
	} else {
	    submat = iwork[i__] + 1;
	    matsiz = iwork[i__ + 1] - iwork[i__];
	}
	if (*icompq == 2) {
	    dsteqr_("I", &matsiz, &d__[submat], &e[submat], &q_ref(submat, 
		    submat), ldq, &work[1], info);
	    if (*info != 0) {
		goto L130;
	    }
	} else {
	    dsteqr_("I", &matsiz, &d__[submat], &e[submat], &work[iq - 1 + 
		    iwork[iqptr + curr]], &matsiz, &work[1], info);
	    if (*info != 0) {
		goto L130;
	    }
	    if (*icompq == 1) {
		latime_1.ops += (doublereal) (*qsiz) * 2 * matsiz * matsiz;
		dgemm_("N", "N", qsiz, &matsiz, &matsiz, &c_b23, &q_ref(1, 
			submat), ldq, &work[iq - 1 + iwork[iqptr + curr]], &
			matsiz, &c_b24, &qstore_ref(1, submat), ldqs);
	    }
/* Computing 2nd power */
	    i__2 = matsiz;
	    iwork[iqptr + curr + 1] = iwork[iqptr + curr] + i__2 * i__2;
	    ++curr;
	}
	k = 1;
	i__2 = iwork[i__ + 1];
	for (j = submat; j <= i__2; ++j) {
	    iwork[indxq + j] = k;
	    ++k;
/* L60: */
	}
/* L70: */
    }

/*     Successively merge eigensystems of adjacent submatrices   
       into eigensystem for the corresponding larger matrix.   

       while ( SUBPBS > 1 ) */

    curlvl = 1;
L80:
    if (subpbs > 1) {
	spm2 = subpbs - 2;
	i__1 = spm2;
	for (i__ = 0; i__ <= i__1; i__ += 2) {
	    if (i__ == 0) {
		submat = 1;
		matsiz = iwork[2];
		msd2 = iwork[1];
		curprb = 0;
	    } else {
		submat = iwork[i__] + 1;
		matsiz = iwork[i__ + 2] - iwork[i__];
		msd2 = matsiz / 2;
		++curprb;
	    }

/*     Merge lower order eigensystems (of size MSD2 and MATSIZ - MSD2)   
       into an eigensystem of size MATSIZ.   
       DLAED1 is used only for the full eigensystem of a tridiagonal   
       matrix.   
       DLAED7 handles the cases in which eigenvalues only or eigenvalues   
       and eigenvectors of a full symmetric matrix (which was reduced to   
       tridiagonal form) are desired. */

	    if (*icompq == 2) {
		dlaed1_(&matsiz, &d__[submat], &q_ref(submat, submat), ldq, &
			iwork[indxq + submat], &e[submat + msd2 - 1], &msd2, &
			work[1], &iwork[subpbs + 1], info);
	    } else {
		dlaed7_(icompq, &matsiz, qsiz, &tlvls, &curlvl, &curprb, &d__[
			submat], &qstore_ref(1, submat), ldqs, &iwork[indxq + 
			submat], &e[submat + msd2 - 1], &msd2, &work[iq], &
			iwork[iqptr], &iwork[iprmpt], &iwork[iperm], &iwork[
			igivpt], &iwork[igivcl], &work[igivnm], &work[iwrem], 
			&iwork[subpbs + 1], info);
	    }
	    if (*info != 0) {
		goto L130;
	    }
	    iwork[i__ / 2 + 1] = iwork[i__ + 2];
/* L90: */
	}
	subpbs /= 2;
	++curlvl;
	goto L80;
    }

/*     end while   

       Re-merge the eigenvalues/vectors which were deflated at the final   
       merge step. */

    if (*icompq == 1) {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    j = iwork[indxq + i__];
	    work[i__] = d__[j];
	    dcopy_(qsiz, &qstore_ref(1, j), &c__1, &q_ref(1, i__), &c__1);
/* L100: */
	}
	dcopy_(n, &work[1], &c__1, &d__[1], &c__1);
    } else if (*icompq == 2) {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    j = iwork[indxq + i__];
	    work[i__] = d__[j];
	    dcopy_(n, &q_ref(1, j), &c__1, &work[*n * i__ + 1], &c__1);
/* L110: */
	}
	dcopy_(n, &work[1], &c__1, &d__[1], &c__1);
	dlacpy_("A", n, n, &work[*n + 1], n, &q[q_offset], ldq);
    } else {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    j = iwork[indxq + i__];
	    work[i__] = d__[j];
/* L120: */
	}
	dcopy_(n, &work[1], &c__1, &d__[1], &c__1);
    }
    goto L140;

L130:
    *info = submat * (*n + 1) + submat + matsiz - 1;

L140:
    return 0;

/*     End of DLAED0 */

} /* dlaed0_ */

#undef qstore_ref
#undef q_ref


