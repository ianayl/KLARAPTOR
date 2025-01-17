
#ifndef _INTERPOLATOR_H_
#define _INTERPOLATOR_H_

#include "linAlgDouble.h"
#include "SMQP/SMQP_Support-AA.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Operand types for mesh point increments. Either addition or multiplication.
 */
typedef enum meshIncrementOp {
	MESH_INCR_ADDITION = 0x0,
	MESH_INCR_MULTIPLICATION
} MeshIncrementOp_t;

/**
 * Possible status conditions when attempting to obtain an interpolating
 * polynomial for a collection of (point, value) pairs.
 *
 * SUCCESS means the interpolating polynomial was successfully found
 * FAILURE means the interpolating polynomail is impossible given the degree bounds.
 * MORE_POINTS means that not enough points are supplied for the given degree
 * bounds, or some of the points supplied are linearly dependent. 
 */
typedef enum polyInterpStatus {
	POLY_INTERP_FAILURE = 0x0,
	POLY_INTERP_FAIL_BY_RESIDUAL,
	POLY_INTERP_MORE_POINTS,
	POLY_INTERP_SUCCESS
} PolyInterpStatus_t;

/**
 * A struct encapsulating all the necessary data to perform interpolation
 * of a continually updating data set. 
 * This struct, along with all the following methods prefixed by "interp"
 * automatically handle dense multivariate polynomial interpolation. 
 *
 * The general strategy is to first initialize an interpolator with interpInit()
 * followed by repeatedly adding (point,value) pairs via interpAddPointVal() 
 * and checking with interpGetPoly() after each pair until a polynomial
 * can be found or one cannot possibly be found. (Returned statis is anything
 * other than POLY_INTERP_MORE_POINTS).
 */
typedef struct interpolator {
	int nvar;
	int* degreeBounds;
	long requiredPoints;

	int meshSet;
	long long int* meshMins;
	long long int* meshMaxs;
	long long int* meshIncrements;
	MeshIncrementOp_t opType;

	int enumerateDone;
	long long int* currentVals;

	int valAlloc;
	int valSize;
	mpq_t** mpPoints;
	mpq_t* mpVals;

	int* deltaNum; 
	int* deltaDen; 
	int deltaFlipFlip;

	long n; 
	long curRows;
	long allocRows;
	long *usedRows;
	mpq_t* A;
	long* availableRows;
	long numAvailRows;

	int* denomDegreeBounds;
	long numeratorNumTerms;
	long denomZeroTerms;
} Interpolator_t;


/**********
 * Interpolator methods
 **********/

/**
 * Create and initialize an interpolator given a number of variables and 
 * a degree bound (inclusive) for each variable. 
 */
Interpolator_t* interpInit(int nvar, int* degreeBounds);

/**
 * Clean up an interpolator and any memory used by it.
 * The interp pointer is invalidated by a call to this functions.
 */
void interpFree(Interpolator_t* interp);

/**
 * Obtain the minimum number of points required for the supplied interpolator
 * to be able to interpolate.
 */
long interpGetRequiredNumPoints(Interpolator_t* interp);

/**
 * Setup the mesh bounds of the automatic point generation of the interpolator.
 *
 * meshMins is the minimum values for each variables, meshMins the max.
 * meshIncremenets is the change in each variable for each increment.
 * meshIncremenets will either be added or multiplied to the previous
 * values (starting at meshMins) to generate mesh points. Addition occurs
 * if incrementOp is MESH_INCR_ADDITION and multiplication if MESH_INCR_MULTIPLICATION.
 * 
 * if reset == 1 then all previously set points and values are removed from the
 * interpolation history. 
 *
 */
void interpSetMeshBounds(Interpolator_t* interp, long long int* meshMins, long long int* meshMaxs, long long int* meshIncrements, MeshIncrementOp_t incrementOp, int reset);

/**
 * Peek at the next point that would be generated by the mesh enumeration.
 * Returns 1 iff there is a next point availble.
 */
int interpPeekNextPoint(Interpolator_t* interp, long long int* point);

/**
 * Get the next point in the mesh points enumeration.
 * Returns 1 iff there is a next point availble.
 */
int interpGetNextPoint(Interpolator_t* interp, long long int* point);

/**
 * Add a point,value pair to the interpolation where points and vals are longs.
 */
void interpAddPointValLong(Interpolator_t* interp, long long int* point, long long int val);

/**
 * Add a point,value pair to the interpolation as GMP rational numbers.
 */
void interpAddPointValMP(Interpolator_t* interp, mpq_t* point, mpq_t val);

/**
 * Reset all the point,value pairs that have been added to the interpolator 
 * so far.
 */
void interpResetPointsVals(Interpolator_t* interp);

/**
 * Try to obtain an interpolating polynomial for the point value pairs
 * which have so far been added to the interpolator. The interpolating
 * polynomial is returned in poly, if one can be generated. Otherwise the
 * result is undefined.
 *
 * The returned PolyInterpStatus_t tells if the polynomial was successfully
 * generated and returned. If the status is POLY_INTERP_SUCCESS then the poly
 * is valid. If more points are needed to get a valid polynomial then 
 * POLY_INTERP_MORE_POINTS is returned.  
 */
PolyInterpStatus_t interpGetPoly(Interpolator_t* interp, AltArr_t** poly);

/**
 * Get a constant pointer to the underlying matrix of points in the interpolator.
 */
const mpq_t* interpGetPointMatrix(Interpolator_t* interp);

/**
 * Get a constant pointer to the underlying matrix of values in the interpolator.
 */
const mpq_t* interpGetValMatrix(Interpolator_t* interp);



/******
 * Rational Function Interpolation
 ******/

/**
 * Create and initialize an interpolator given a number of variables and 
 * a degree bound (inclusive) for each variable for numerator and denominator. 
 */
Interpolator_t* rfInterpInit(int nvar, int* degreeBounds, int* denomDegreeBounds);

/**
 * Clean up an interpolator and any memory used by it.
 * The interp pointer is invalidated by a call to this functions.
 */
void rfInterpFree(Interpolator_t* interp);

/**
 * Obtain the minimum number of points required for the supplied interpolator
 * to be able to interpolate.
 */
static inline long rfInterpGetRequiredNumPoints(Interpolator_t* interp) {
	return interpGetRequiredNumPoints(interp);
}

/**
 * Add a point,value pair to the interpolation where points and vals are longs.
 */
void rfInterpAddPointValLong(Interpolator_t* interp, long long int* point, long long int val);

/**
 * Add a point,value pair to the interpolation as GMP rational numbers.
 */
void rfInterpAddPointValMP(Interpolator_t* interp, mpq_t* point, mpq_t val);

/**
 * Try to obtain an interpolating rational function for the point value pairs
 * which have so far been added to the interpolator. The interpolating
 * polynomial is returned in poly, if one can be generated. Otherwise the
 * result is undefined.
 *
 * The returned PolyInterpStatus_t tells if the polynomial was successfully
 * generated and returned. If the status is POLY_INTERP_SUCCESS then the poly
 * is valid. If more points are needed to get a valid polynomial then 
 * POLY_INTERP_MORE_POINTS is returned.  
 */
// PolyInterpStatus_t rfInterpGetPoly(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly);
// PolyInterpStatus_t rfInterpGetPoly(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly, mpq_t* newpoint, mpq_t newval);
// PolyInterpStatus_t rfInterpGetPoly(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly, double eps, mpq_t* newpoint, mpq_t newval);
PolyInterpStatus_t rfInterpGetPoly(Interpolator_t* interp, AltArr_t** numPoly, AltArr_t** denomPoly, double maximumResidual);

/**
 * Using one more point,value pair, ensure that the interpolated polynomial is correct.
 * Returns POLY_INTERP_SUCCESS if the polynomial is good, otherwise POLY_INTERP_MORE_POINTS.
 */
PolyInterpStatus_t rfInterpCheckPoly(Interpolator_t* interp, const AltArr_t* numPoly, const AltArr_t* denomPoly, mpq_t* point, mpq_t val);

/**
 * Using one more point,value pair, ensure that the interpolated polynomial is correct.
 * Tolerance is a decimal such that the rational function evaluated at the supplied point
 * must match the supplied value within the supplied tolerance. 
 * That is, | (eval - val) / val | < tolerance. 
 * Returns POLY_INTERP_SUCCESS if the polynomial is good, otherwise POLY_INTERP_MORE_POINTS.
 */
PolyInterpStatus_t rfInterpCheckPolyWithTolerance(Interpolator_t* interp, const AltArr_t* numPoly, const AltArr_t* denomPoly, mpq_t* point, mpq_t val, double tolerance);



/******
 * Helper Functions
 ******/

int enumerateMonomials(int* degrees, int* degreeBounds, int nvar); 

int monomialInBounds(int* degrees, int* degreeBounds, int nvar); 


#ifdef __cplusplus
}
#endif

#endif



