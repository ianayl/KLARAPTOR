#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int ztrt03_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, doublecomplex *a, integer *lda, doublereal *scale, 
	doublereal *cnorm, doublereal *tscal, doublecomplex *x, integer *ldx, 
	doublecomplex *b, integer *ldb, doublecomplex *work, doublereal *
	resid)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, x_dim1, x_offset, i__1;
    doublereal d__1, d__2;
    doublecomplex z__1;

    /* Builtin functions */
    double z_abs(doublecomplex *);

    /* Local variables */
    static integer j;
    extern logical lsame_(char *, char *);
    static doublereal xscal, tnorm, xnorm;
    extern /* Subroutine */ int zcopy_(integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *), zaxpy_(integer *, doublecomplex *, 
	    doublecomplex *, integer *, doublecomplex *, integer *), ztrmv_(
	    char *, char *, char *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *);
    extern doublereal dlamch_(char *);
    static integer ix;
    extern /* Subroutine */ int zdscal_(integer *, doublereal *, 
	    doublecomplex *, integer *);
    extern integer izamax_(integer *, doublecomplex *, integer *);
    static doublereal smlnum, eps, err;


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define b_subscr(a_1,a_2) (a_2)*b_dim1 + a_1
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]
#define x_subscr(a_1,a_2) (a_2)*x_dim1 + a_1
#define x_ref(a_1,a_2) x[x_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    ZTRT03 computes the residual for the solution to a scaled triangular   
    system of equations A*x = s*b,  A**T *x = s*b,  or  A**H *x = s*b.   
    Here A is a triangular matrix, A**T denotes the transpose of A, A**H   
    denotes the conjugate transpose of A, s is a scalar, and x and b are   
    N by NRHS matrices.  The test ratio is the maximum over the number of   
    right hand sides of   
       norm(s*b - op(A)*x) / ( norm(op(A)) * norm(x) * EPS ),   
    where op(A) denotes A, A**T, or A**H, and EPS is the machine epsilon.   

    Arguments   
    =========   

    UPLO    (input) CHARACTER*1   
            Specifies whether the matrix A is upper or lower triangular.   
            = 'U':  Upper triangular   
            = 'L':  Lower triangular   

    TRANS   (input) CHARACTER*1   
            Specifies the operation applied to A.   
            = 'N':  A *x = s*b     (No transpose)   
            = 'T':  A**T *x = s*b  (Transpose)   
            = 'C':  A**H *x = s*b  (Conjugate transpose)   

    DIAG    (input) CHARACTER*1   
            Specifies whether or not the matrix A is unit triangular.   
            = 'N':  Non-unit triangular   
            = 'U':  Unit triangular   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of right hand sides, i.e., the number of columns   
            of the matrices X and B.  NRHS >= 0.   

    A       (input) COMPLEX*16 array, dimension (LDA,N)   
            The triangular matrix A.  If UPLO = 'U', the leading n by n   
            upper triangular part of the array A contains the upper   
            triangular matrix, and the strictly lower triangular part of   
            A is not referenced.  If UPLO = 'L', the leading n by n lower   
            triangular part of the array A contains the lower triangular   
            matrix, and the strictly upper triangular part of A is not   
            referenced.  If DIAG = 'U', the diagonal elements of A are   
            also not referenced and are assumed to be 1.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,N).   

    SCALE   (input) DOUBLE PRECISION   
            The scaling factor s used in solving the triangular system.   

    CNORM   (input) DOUBLE PRECISION array, dimension (N)   
            The 1-norms of the columns of A, not counting the diagonal.   

    TSCAL   (input) DOUBLE PRECISION   
            The scaling factor used in computing the 1-norms in CNORM.   
            CNORM actually contains the column norms of TSCAL*A.   

    X       (input) COMPLEX*16 array, dimension (LDX,NRHS)   
            The computed solution vectors for the system of linear   
            equations.   

    LDX     (input) INTEGER   
            The leading dimension of the array X.  LDX >= max(1,N).   

    B       (input) COMPLEX*16 array, dimension (LDB,NRHS)   
            The right hand side vectors for the system of linear   
            equations.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,N).   

    WORK    (workspace) COMPLEX*16 array, dimension (N)   

    RESID   (output) DOUBLE PRECISION   
            The maximum over the number of right hand sides of   
            norm(op(A)*x - s*b) / ( norm(op(A)) * norm(x) * EPS ).   

    =====================================================================   


       Quick exit if N = 0   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --cnorm;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1 * 1;
    x -= x_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    --work;

    /* Function Body */
    if (*n <= 0 || *nrhs <= 0) {
	*resid = 0.;
	return 0;
    }
    eps = dlamch_("Epsilon");
    smlnum = dlamch_("Safe minimum");

/*     Compute the norm of the triangular matrix A using the column   
       norms already computed by ZLATRS. */

    tnorm = 0.;
    if (lsame_(diag, "N")) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	    d__1 = tnorm, d__2 = *tscal * z_abs(&a_ref(j, j)) + cnorm[j];
	    tnorm = max(d__1,d__2);
/* L10: */
	}
    } else {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	    d__1 = tnorm, d__2 = *tscal + cnorm[j];
	    tnorm = max(d__1,d__2);
/* L20: */
	}
    }

/*     Compute the maximum over the number of right hand sides of   
          norm(op(A)*x - s*b) / ( norm(op(A)) * norm(x) * EPS ). */

    *resid = 0.;
    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	zcopy_(n, &x_ref(1, j), &c__1, &work[1], &c__1);
	ix = izamax_(n, &work[1], &c__1);
/* Computing MAX */
	d__1 = 1., d__2 = z_abs(&x_ref(ix, j));
	xnorm = max(d__1,d__2);
	xscal = 1. / xnorm / (doublereal) (*n);
	zdscal_(n, &xscal, &work[1], &c__1);
	ztrmv_(uplo, trans, diag, n, &a[a_offset], lda, &work[1], &c__1);
	d__1 = -(*scale) * xscal;
	z__1.r = d__1, z__1.i = 0.;
	zaxpy_(n, &z__1, &b_ref(1, j), &c__1, &work[1], &c__1);
	ix = izamax_(n, &work[1], &c__1);
	err = *tscal * z_abs(&work[ix]);
	ix = izamax_(n, &x_ref(1, j), &c__1);
	xnorm = z_abs(&x_ref(ix, j));
	if (err * smlnum <= xnorm) {
	    if (xnorm > 0.) {
		err /= xnorm;
	    }
	} else {
	    if (err > 0.) {
		err = 1. / eps;
	    }
	}
	if (err * smlnum <= tnorm) {
	    if (tnorm > 0.) {
		err /= tnorm;
	    }
	} else {
	    if (err > 0.) {
		err = 1. / eps;
	    }
	}
	*resid = max(*resid,err);
/* L30: */
    }

    return 0;

/*     End of ZTRT03 */

} /* ztrt03_ */

#undef x_ref
#undef x_subscr
#undef b_ref
#undef b_subscr
#undef a_ref
#undef a_subscr


