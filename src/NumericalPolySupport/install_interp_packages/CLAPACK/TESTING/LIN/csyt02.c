#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static complex c_b1 = {1.f,0.f};
static integer c__1 = 1;

/* Subroutine */ int csyt02_(char *uplo, integer *n, integer *nrhs, complex *
	a, integer *lda, complex *x, integer *ldx, complex *b, integer *ldb, 
	real *rwork, real *resid)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, x_dim1, x_offset, i__1;
    real r__1, r__2;
    complex q__1;

    /* Local variables */
    static integer j;
    static real anorm, bnorm;
    extern /* Subroutine */ int csymm_(char *, char *, integer *, integer *, 
	    complex *, complex *, integer *, complex *, integer *, complex *, 
	    complex *, integer *);
    static real xnorm;
    extern doublereal slamch_(char *), clansy_(char *, char *, 
	    integer *, complex *, integer *, real *), scasum_(
	    integer *, complex *, integer *);
    static real eps;


#define b_subscr(a_1,a_2) (a_2)*b_dim1 + a_1
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]
#define x_subscr(a_1,a_2) (a_2)*x_dim1 + a_1
#define x_ref(a_1,a_2) x[x_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    CSYT02 computes the residual for a solution to a complex symmetric   
    system of linear equations  A*x = b:   

       RESID = norm(B - A*X) / ( norm(A) * norm(X) * EPS ),   

    where EPS is the machine epsilon.   

    Arguments   
    =========   

    UPLO    (input) CHARACTER*1   
            Specifies whether the upper or lower triangular part of the   
            symmetric matrix A is stored:   
            = 'U':  Upper triangular   
            = 'L':  Lower triangular   

    N       (input) INTEGER   
            The number of rows and columns of the matrix A.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of columns of B, the matrix of right hand sides.   
            NRHS >= 0.   

    A       (input) COMPLEX array, dimension (LDA,N)   
            The original complex symmetric matrix A.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,N)   

    X       (input) COMPLEX array, dimension (LDX,NRHS)   
            The computed solution vectors for the system of linear   
            equations.   

    LDX     (input) INTEGER   
            The leading dimension of the array X.   LDX >= max(1,N).   

    B       (input/output) COMPLEX array, dimension (LDB,NRHS)   
            On entry, the right hand side vectors for the system of   
            linear equations.   
            On exit, B is overwritten with the difference B - A*X.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,N).   

    RWORK   (workspace) REAL array, dimension (N)   

    RESID   (output) REAL   
            The maximum over the number of right hand sides of   
            norm(B - A*X) / ( norm(A) * norm(X) * EPS ).   

    =====================================================================   


       Quick exit if N = 0 or NRHS = 0   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1 * 1;
    x -= x_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    --rwork;

    /* Function Body */
    if (*n <= 0 || *nrhs <= 0) {
	*resid = 0.f;
	return 0;
    }

/*     Exit with RESID = 1/EPS if ANORM = 0. */

    eps = slamch_("Epsilon");
    anorm = clansy_("1", uplo, n, &a[a_offset], lda, &rwork[1]);
    if (anorm <= 0.f) {
	*resid = 1.f / eps;
	return 0;
    }

/*     Compute  B - A*X  (or  B - A'*X ) and store in B . */

    q__1.r = -1.f, q__1.i = 0.f;
    csymm_("Left", uplo, n, nrhs, &q__1, &a[a_offset], lda, &x[x_offset], ldx,
	     &c_b1, &b[b_offset], ldb);

/*     Compute the maximum over the number of right hand sides of   
          norm( B - A*X ) / ( norm(A) * norm(X) * EPS ) . */

    *resid = 0.f;
    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	bnorm = scasum_(n, &b_ref(1, j), &c__1);
	xnorm = scasum_(n, &x_ref(1, j), &c__1);
	if (xnorm <= 0.f) {
	    *resid = 1.f / eps;
	} else {
/* Computing MAX */
	    r__1 = *resid, r__2 = bnorm / anorm / xnorm / eps;
	    *resid = dmax(r__1,r__2);
	}
/* L10: */
    }

    return 0;

/*     End of CSYT02 */

} /* csyt02_ */

#undef x_ref
#undef x_subscr
#undef b_ref
#undef b_subscr


