#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Subroutine */ int ctbt06_(real *rcond, real *rcondc, char *uplo, char *
	diag, integer *n, integer *kd, complex *ab, integer *ldab, real *
	rwork, real *rat)
{
    /* System generated locals */
    integer ab_dim1, ab_offset;
    real r__1, r__2;

    /* Local variables */
    static real rmin, rmax, anorm;
    extern doublereal clantb_(char *, char *, char *, integer *, integer *, 
	    complex *, integer *, real *), slamch_(
	    char *);
    static real bignum, eps;


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    CTBT06 computes a test ratio comparing RCOND (the reciprocal   
    condition number of a triangular matrix A) and RCONDC, the estimate   
    computed by CTBCON.  Information about the triangular matrix A is   
    used if one estimate is zero and the other is non-zero to decide if   
    underflow in the estimate is justified.   

    Arguments   
    =========   

    RCOND   (input) REAL   
            The estimate of the reciprocal condition number obtained by   
            forming the explicit inverse of the matrix A and computing   
            RCOND = 1/( norm(A) * norm(inv(A)) ).   

    RCONDC  (input) REAL   
            The estimate of the reciprocal condition number computed by   
            CTBCON.   

    UPLO    (input) CHARACTER   
            Specifies whether the matrix A is upper or lower triangular.   
            = 'U':  Upper triangular   
            = 'L':  Lower triangular   

    DIAG    (input) CHARACTER   
            Specifies whether or not the matrix A is unit triangular.   
            = 'N':  Non-unit triangular   
            = 'U':  Unit triangular   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    KD      (input) INTEGER   
            The number of superdiagonals or subdiagonals of the   
            triangular band matrix A.  KD >= 0.   

    AB      (input) COMPLEX array, dimension (LDAB,N)   
            The upper or lower triangular band matrix A, stored in the   
            first kd+1 rows of the array. The j-th column of A is stored   
            in the j-th column of the array AB as follows:   
            if UPLO = 'U', AB(kd+1+i-j,j) = A(i,j) for max(1,j-kd)<=i<=j;   
            if UPLO = 'L', AB(1+i-j,j)    = A(i,j) for j<=i<=min(n,j+kd).   

    LDAB    (input) INTEGER   
            The leading dimension of the array AB.  LDAB >= KD+1.   

    RWORK   (workspace) REAL array, dimension (N)   

    RAT     (output) REAL   
            The test ratio.  If both RCOND and RCONDC are nonzero,   
               RAT = MAX( RCOND, RCONDC )/MIN( RCOND, RCONDC ) - 1.   
            If RAT = 0, the two estimates are exactly the same.   

    =====================================================================   


       Parameter adjustments */
    ab_dim1 = *ldab;
    ab_offset = 1 + ab_dim1 * 1;
    ab -= ab_offset;
    --rwork;

    /* Function Body */
    eps = slamch_("Epsilon");
    rmax = dmax(*rcond,*rcondc);
    rmin = dmin(*rcond,*rcondc);

/*     Do the easy cases first. */

    if (rmin < 0.f) {

/*        Invalid value for RCOND or RCONDC, return 1/EPS. */

	*rat = 1.f / eps;

    } else if (rmin > 0.f) {

/*        Both estimates are positive, return RMAX/RMIN - 1. */

	*rat = rmax / rmin - 1.f;

    } else if (rmax == 0.f) {

/*        Both estimates zero. */

	*rat = 0.f;

    } else {

/*        One estimate is zero, the other is non-zero.  If the matrix is   
          ill-conditioned, return the nonzero estimate multiplied by   
          1/EPS; if the matrix is badly scaled, return the nonzero   
          estimate multiplied by BIGNUM/TMAX, where TMAX is the maximum   
          element in absolute value in A. */

	bignum = 1.f / slamch_("Safe minimum");
	anorm = clantb_("M", uplo, diag, n, kd, &ab[ab_offset], ldab, &rwork[
		1]);

/* Computing MIN */
	r__1 = bignum / dmax(1.f,anorm), r__2 = 1.f / eps;
	*rat = rmax * dmin(r__1,r__2);
    }

    return 0;

/*     End of CTBT06 */

} /* ctbt06_ */

