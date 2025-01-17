#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Subroutine */ int zlaptm_(char *uplo, integer *n, integer *nrhs, 
	doublereal *alpha, doublereal *d__, doublecomplex *e, doublecomplex *
	x, integer *ldx, doublereal *beta, doublecomplex *b, integer *ldb)
{
    /* System generated locals */
    integer b_dim1, b_offset, x_dim1, x_offset, i__1, i__2, i__3, i__4, i__5, 
	    i__6, i__7, i__8, i__9;
    doublecomplex z__1, z__2, z__3, z__4, z__5, z__6, z__7;

    /* Builtin functions */
    void d_cnjg(doublecomplex *, doublecomplex *);

    /* Local variables */
    static integer i__, j;
    extern logical lsame_(char *, char *);


#define b_subscr(a_1,a_2) (a_2)*b_dim1 + a_1
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]
#define x_subscr(a_1,a_2) (a_2)*x_dim1 + a_1
#define x_ref(a_1,a_2) x[x_subscr(a_1,a_2)]


/*  -- LAPACK auxiliary routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    ZLAPTM multiplies an N by NRHS matrix X by a Hermitian tridiagonal   
    matrix A and stores the result in a matrix B.  The operation has the   
    form   

       B := alpha * A * X + beta * B   

    where alpha may be either 1. or -1. and beta may be 0., 1., or -1.   

    Arguments   
    =========   

    UPLO    (input) CHARACTER   
            Specifies whether the superdiagonal or the subdiagonal of the   
            tridiagonal matrix A is stored.   
            = 'U':  Upper, E is the superdiagonal of A.   
            = 'L':  Lower, E is the subdiagonal of A.   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of right hand sides, i.e., the number of columns   
            of the matrices X and B.   

    ALPHA   (input) DOUBLE PRECISION   
            The scalar alpha.  ALPHA must be 1. or -1.; otherwise,   
            it is assumed to be 0.   

    D       (input) DOUBLE PRECISION array, dimension (N)   
            The n diagonal elements of the tridiagonal matrix A.   

    E       (input) COMPLEX*16 array, dimension (N-1)   
            The (n-1) subdiagonal or superdiagonal elements of A.   

    X       (input) COMPLEX*16 array, dimension (LDX,NRHS)   
            The N by NRHS matrix X.   

    LDX     (input) INTEGER   
            The leading dimension of the array X.  LDX >= max(N,1).   

    BETA    (input) DOUBLE PRECISION   
            The scalar beta.  BETA must be 0., 1., or -1.; otherwise,   
            it is assumed to be 1.   

    B       (input/output) COMPLEX*16 array, dimension (LDB,NRHS)   
            On entry, the N by NRHS matrix B.   
            On exit, B is overwritten by the matrix expression   
            B := alpha * A * X + beta * B.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(N,1).   

    =====================================================================   


       Parameter adjustments */
    --d__;
    --e;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1 * 1;
    x -= x_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;

    /* Function Body */
    if (*n == 0) {
	return 0;
    }

    if (*beta == 0.) {
	i__1 = *nrhs;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *n;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = b_subscr(i__, j);
		b[i__3].r = 0., b[i__3].i = 0.;
/* L10: */
	    }
/* L20: */
	}
    } else if (*beta == -1.) {
	i__1 = *nrhs;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *n;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = b_subscr(i__, j);
		i__4 = b_subscr(i__, j);
		z__1.r = -b[i__4].r, z__1.i = -b[i__4].i;
		b[i__3].r = z__1.r, b[i__3].i = z__1.i;
/* L30: */
	    }
/* L40: */
	}
    }

    if (*alpha == 1.) {
	if (lsame_(uplo, "U")) {

/*           Compute B := B + A*X, where E is the superdiagonal of A. */

	    i__1 = *nrhs;
	    for (j = 1; j <= i__1; ++j) {
		if (*n == 1) {
		    i__2 = b_subscr(1, j);
		    i__3 = b_subscr(1, j);
		    i__4 = x_subscr(1, j);
		    z__2.r = d__[1] * x[i__4].r, z__2.i = d__[1] * x[i__4].i;
		    z__1.r = b[i__3].r + z__2.r, z__1.i = b[i__3].i + z__2.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		} else {
		    i__2 = b_subscr(1, j);
		    i__3 = b_subscr(1, j);
		    i__4 = x_subscr(1, j);
		    z__3.r = d__[1] * x[i__4].r, z__3.i = d__[1] * x[i__4].i;
		    z__2.r = b[i__3].r + z__3.r, z__2.i = b[i__3].i + z__3.i;
		    i__5 = x_subscr(2, j);
		    z__4.r = e[1].r * x[i__5].r - e[1].i * x[i__5].i, z__4.i =
			     e[1].r * x[i__5].i + e[1].i * x[i__5].r;
		    z__1.r = z__2.r + z__4.r, z__1.i = z__2.i + z__4.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		    i__2 = b_subscr(*n, j);
		    i__3 = b_subscr(*n, j);
		    d_cnjg(&z__4, &e[*n - 1]);
		    i__4 = x_subscr(*n - 1, j);
		    z__3.r = z__4.r * x[i__4].r - z__4.i * x[i__4].i, z__3.i =
			     z__4.r * x[i__4].i + z__4.i * x[i__4].r;
		    z__2.r = b[i__3].r + z__3.r, z__2.i = b[i__3].i + z__3.i;
		    i__5 = *n;
		    i__6 = x_subscr(*n, j);
		    z__5.r = d__[i__5] * x[i__6].r, z__5.i = d__[i__5] * x[
			    i__6].i;
		    z__1.r = z__2.r + z__5.r, z__1.i = z__2.i + z__5.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		    i__2 = *n - 1;
		    for (i__ = 2; i__ <= i__2; ++i__) {
			i__3 = b_subscr(i__, j);
			i__4 = b_subscr(i__, j);
			d_cnjg(&z__5, &e[i__ - 1]);
			i__5 = x_subscr(i__ - 1, j);
			z__4.r = z__5.r * x[i__5].r - z__5.i * x[i__5].i, 
				z__4.i = z__5.r * x[i__5].i + z__5.i * x[i__5]
				.r;
			z__3.r = b[i__4].r + z__4.r, z__3.i = b[i__4].i + 
				z__4.i;
			i__6 = i__;
			i__7 = x_subscr(i__, j);
			z__6.r = d__[i__6] * x[i__7].r, z__6.i = d__[i__6] * 
				x[i__7].i;
			z__2.r = z__3.r + z__6.r, z__2.i = z__3.i + z__6.i;
			i__8 = i__;
			i__9 = x_subscr(i__ + 1, j);
			z__7.r = e[i__8].r * x[i__9].r - e[i__8].i * x[i__9]
				.i, z__7.i = e[i__8].r * x[i__9].i + e[i__8]
				.i * x[i__9].r;
			z__1.r = z__2.r + z__7.r, z__1.i = z__2.i + z__7.i;
			b[i__3].r = z__1.r, b[i__3].i = z__1.i;
/* L50: */
		    }
		}
/* L60: */
	    }
	} else {

/*           Compute B := B + A*X, where E is the subdiagonal of A. */

	    i__1 = *nrhs;
	    for (j = 1; j <= i__1; ++j) {
		if (*n == 1) {
		    i__2 = b_subscr(1, j);
		    i__3 = b_subscr(1, j);
		    i__4 = x_subscr(1, j);
		    z__2.r = d__[1] * x[i__4].r, z__2.i = d__[1] * x[i__4].i;
		    z__1.r = b[i__3].r + z__2.r, z__1.i = b[i__3].i + z__2.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		} else {
		    i__2 = b_subscr(1, j);
		    i__3 = b_subscr(1, j);
		    i__4 = x_subscr(1, j);
		    z__3.r = d__[1] * x[i__4].r, z__3.i = d__[1] * x[i__4].i;
		    z__2.r = b[i__3].r + z__3.r, z__2.i = b[i__3].i + z__3.i;
		    d_cnjg(&z__5, &e[1]);
		    i__5 = x_subscr(2, j);
		    z__4.r = z__5.r * x[i__5].r - z__5.i * x[i__5].i, z__4.i =
			     z__5.r * x[i__5].i + z__5.i * x[i__5].r;
		    z__1.r = z__2.r + z__4.r, z__1.i = z__2.i + z__4.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		    i__2 = b_subscr(*n, j);
		    i__3 = b_subscr(*n, j);
		    i__4 = *n - 1;
		    i__5 = x_subscr(*n - 1, j);
		    z__3.r = e[i__4].r * x[i__5].r - e[i__4].i * x[i__5].i, 
			    z__3.i = e[i__4].r * x[i__5].i + e[i__4].i * x[
			    i__5].r;
		    z__2.r = b[i__3].r + z__3.r, z__2.i = b[i__3].i + z__3.i;
		    i__6 = *n;
		    i__7 = x_subscr(*n, j);
		    z__4.r = d__[i__6] * x[i__7].r, z__4.i = d__[i__6] * x[
			    i__7].i;
		    z__1.r = z__2.r + z__4.r, z__1.i = z__2.i + z__4.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		    i__2 = *n - 1;
		    for (i__ = 2; i__ <= i__2; ++i__) {
			i__3 = b_subscr(i__, j);
			i__4 = b_subscr(i__, j);
			i__5 = i__ - 1;
			i__6 = x_subscr(i__ - 1, j);
			z__4.r = e[i__5].r * x[i__6].r - e[i__5].i * x[i__6]
				.i, z__4.i = e[i__5].r * x[i__6].i + e[i__5]
				.i * x[i__6].r;
			z__3.r = b[i__4].r + z__4.r, z__3.i = b[i__4].i + 
				z__4.i;
			i__7 = i__;
			i__8 = x_subscr(i__, j);
			z__5.r = d__[i__7] * x[i__8].r, z__5.i = d__[i__7] * 
				x[i__8].i;
			z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
			d_cnjg(&z__7, &e[i__]);
			i__9 = x_subscr(i__ + 1, j);
			z__6.r = z__7.r * x[i__9].r - z__7.i * x[i__9].i, 
				z__6.i = z__7.r * x[i__9].i + z__7.i * x[i__9]
				.r;
			z__1.r = z__2.r + z__6.r, z__1.i = z__2.i + z__6.i;
			b[i__3].r = z__1.r, b[i__3].i = z__1.i;
/* L70: */
		    }
		}
/* L80: */
	    }
	}
    } else if (*alpha == -1.) {
	if (lsame_(uplo, "U")) {

/*           Compute B := B - A*X, where E is the superdiagonal of A. */

	    i__1 = *nrhs;
	    for (j = 1; j <= i__1; ++j) {
		if (*n == 1) {
		    i__2 = b_subscr(1, j);
		    i__3 = b_subscr(1, j);
		    i__4 = x_subscr(1, j);
		    z__2.r = d__[1] * x[i__4].r, z__2.i = d__[1] * x[i__4].i;
		    z__1.r = b[i__3].r - z__2.r, z__1.i = b[i__3].i - z__2.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		} else {
		    i__2 = b_subscr(1, j);
		    i__3 = b_subscr(1, j);
		    i__4 = x_subscr(1, j);
		    z__3.r = d__[1] * x[i__4].r, z__3.i = d__[1] * x[i__4].i;
		    z__2.r = b[i__3].r - z__3.r, z__2.i = b[i__3].i - z__3.i;
		    i__5 = x_subscr(2, j);
		    z__4.r = e[1].r * x[i__5].r - e[1].i * x[i__5].i, z__4.i =
			     e[1].r * x[i__5].i + e[1].i * x[i__5].r;
		    z__1.r = z__2.r - z__4.r, z__1.i = z__2.i - z__4.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		    i__2 = b_subscr(*n, j);
		    i__3 = b_subscr(*n, j);
		    d_cnjg(&z__4, &e[*n - 1]);
		    i__4 = x_subscr(*n - 1, j);
		    z__3.r = z__4.r * x[i__4].r - z__4.i * x[i__4].i, z__3.i =
			     z__4.r * x[i__4].i + z__4.i * x[i__4].r;
		    z__2.r = b[i__3].r - z__3.r, z__2.i = b[i__3].i - z__3.i;
		    i__5 = *n;
		    i__6 = x_subscr(*n, j);
		    z__5.r = d__[i__5] * x[i__6].r, z__5.i = d__[i__5] * x[
			    i__6].i;
		    z__1.r = z__2.r - z__5.r, z__1.i = z__2.i - z__5.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		    i__2 = *n - 1;
		    for (i__ = 2; i__ <= i__2; ++i__) {
			i__3 = b_subscr(i__, j);
			i__4 = b_subscr(i__, j);
			d_cnjg(&z__5, &e[i__ - 1]);
			i__5 = x_subscr(i__ - 1, j);
			z__4.r = z__5.r * x[i__5].r - z__5.i * x[i__5].i, 
				z__4.i = z__5.r * x[i__5].i + z__5.i * x[i__5]
				.r;
			z__3.r = b[i__4].r - z__4.r, z__3.i = b[i__4].i - 
				z__4.i;
			i__6 = i__;
			i__7 = x_subscr(i__, j);
			z__6.r = d__[i__6] * x[i__7].r, z__6.i = d__[i__6] * 
				x[i__7].i;
			z__2.r = z__3.r - z__6.r, z__2.i = z__3.i - z__6.i;
			i__8 = i__;
			i__9 = x_subscr(i__ + 1, j);
			z__7.r = e[i__8].r * x[i__9].r - e[i__8].i * x[i__9]
				.i, z__7.i = e[i__8].r * x[i__9].i + e[i__8]
				.i * x[i__9].r;
			z__1.r = z__2.r - z__7.r, z__1.i = z__2.i - z__7.i;
			b[i__3].r = z__1.r, b[i__3].i = z__1.i;
/* L90: */
		    }
		}
/* L100: */
	    }
	} else {

/*           Compute B := B - A*X, where E is the subdiagonal of A. */

	    i__1 = *nrhs;
	    for (j = 1; j <= i__1; ++j) {
		if (*n == 1) {
		    i__2 = b_subscr(1, j);
		    i__3 = b_subscr(1, j);
		    i__4 = x_subscr(1, j);
		    z__2.r = d__[1] * x[i__4].r, z__2.i = d__[1] * x[i__4].i;
		    z__1.r = b[i__3].r - z__2.r, z__1.i = b[i__3].i - z__2.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		} else {
		    i__2 = b_subscr(1, j);
		    i__3 = b_subscr(1, j);
		    i__4 = x_subscr(1, j);
		    z__3.r = d__[1] * x[i__4].r, z__3.i = d__[1] * x[i__4].i;
		    z__2.r = b[i__3].r - z__3.r, z__2.i = b[i__3].i - z__3.i;
		    d_cnjg(&z__5, &e[1]);
		    i__5 = x_subscr(2, j);
		    z__4.r = z__5.r * x[i__5].r - z__5.i * x[i__5].i, z__4.i =
			     z__5.r * x[i__5].i + z__5.i * x[i__5].r;
		    z__1.r = z__2.r - z__4.r, z__1.i = z__2.i - z__4.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		    i__2 = b_subscr(*n, j);
		    i__3 = b_subscr(*n, j);
		    i__4 = *n - 1;
		    i__5 = x_subscr(*n - 1, j);
		    z__3.r = e[i__4].r * x[i__5].r - e[i__4].i * x[i__5].i, 
			    z__3.i = e[i__4].r * x[i__5].i + e[i__4].i * x[
			    i__5].r;
		    z__2.r = b[i__3].r - z__3.r, z__2.i = b[i__3].i - z__3.i;
		    i__6 = *n;
		    i__7 = x_subscr(*n, j);
		    z__4.r = d__[i__6] * x[i__7].r, z__4.i = d__[i__6] * x[
			    i__7].i;
		    z__1.r = z__2.r - z__4.r, z__1.i = z__2.i - z__4.i;
		    b[i__2].r = z__1.r, b[i__2].i = z__1.i;
		    i__2 = *n - 1;
		    for (i__ = 2; i__ <= i__2; ++i__) {
			i__3 = b_subscr(i__, j);
			i__4 = b_subscr(i__, j);
			i__5 = i__ - 1;
			i__6 = x_subscr(i__ - 1, j);
			z__4.r = e[i__5].r * x[i__6].r - e[i__5].i * x[i__6]
				.i, z__4.i = e[i__5].r * x[i__6].i + e[i__5]
				.i * x[i__6].r;
			z__3.r = b[i__4].r - z__4.r, z__3.i = b[i__4].i - 
				z__4.i;
			i__7 = i__;
			i__8 = x_subscr(i__, j);
			z__5.r = d__[i__7] * x[i__8].r, z__5.i = d__[i__7] * 
				x[i__8].i;
			z__2.r = z__3.r - z__5.r, z__2.i = z__3.i - z__5.i;
			d_cnjg(&z__7, &e[i__]);
			i__9 = x_subscr(i__ + 1, j);
			z__6.r = z__7.r * x[i__9].r - z__7.i * x[i__9].i, 
				z__6.i = z__7.r * x[i__9].i + z__7.i * x[i__9]
				.r;
			z__1.r = z__2.r - z__6.r, z__1.i = z__2.i - z__6.i;
			b[i__3].r = z__1.r, b[i__3].i = z__1.i;
/* L110: */
		    }
		}
/* L120: */
	    }
	}
    }
    return 0;

/*     End of ZLAPTM */

} /* zlaptm_ */

#undef x_ref
#undef x_subscr
#undef b_ref
#undef b_subscr


