#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int cptt05_(integer *n, integer *nrhs, real *d__, complex *e,
	 complex *b, integer *ldb, complex *x, integer *ldx, complex *xact, 
	integer *ldxact, real *ferr, real *berr, real *reslts)
{
    /* System generated locals */
    integer b_dim1, b_offset, x_dim1, x_offset, xact_dim1, xact_offset, i__1, 
	    i__2, i__3, i__4, i__5, i__6, i__7, i__8, i__9;
    real r__1, r__2, r__3, r__4, r__5, r__6, r__7, r__8, r__9, r__10, r__11, 
	    r__12;
    complex q__1, q__2;

    /* Builtin functions */
    double r_imag(complex *);

    /* Local variables */
    static real diff, axbi;
    static integer imax;
    static real unfl, ovfl;
    static integer i__, j, k;
    static real xnorm;
    extern integer icamax_(integer *, complex *, integer *);
    extern doublereal slamch_(char *);
    static integer nz;
    static real errbnd, eps, tmp;


#define xact_subscr(a_1,a_2) (a_2)*xact_dim1 + a_1
#define xact_ref(a_1,a_2) xact[xact_subscr(a_1,a_2)]
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

    CPTT05 tests the error bounds from iterative refinement for the   
    computed solution to a system of equations A*X = B, where A is a   
    Hermitian tridiagonal matrix of order n.   

    RESLTS(1) = test of the error bound   
              = norm(X - XACT) / ( norm(X) * FERR )   

    A large value is returned if this ratio is not less than one.   

    RESLTS(2) = residual from the iterative refinement routine   
              = the maximum of BERR / ( NZ*EPS + (*) ), where   
                (*) = NZ*UNFL / (min_i (abs(A)*abs(X) +abs(b))_i )   
                and NZ = max. number of nonzeros in any row of A, plus 1   

    Arguments   
    =========   

    N       (input) INTEGER   
            The number of rows of the matrices X, B, and XACT, and the   
            order of the matrix A.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of columns of the matrices X, B, and XACT.   
            NRHS >= 0.   

    D       (input) REAL array, dimension (N)   
            The n diagonal elements of the tridiagonal matrix A.   

    E       (input) COMPLEX array, dimension (N-1)   
            The (n-1) subdiagonal elements of the tridiagonal matrix A.   

    B       (input) COMPLEX array, dimension (LDB,NRHS)   
            The right hand side vectors for the system of linear   
            equations.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,N).   

    X       (input) COMPLEX array, dimension (LDX,NRHS)   
            The computed solution vectors.  Each vector is stored as a   
            column of the matrix X.   

    LDX     (input) INTEGER   
            The leading dimension of the array X.  LDX >= max(1,N).   

    XACT    (input) COMPLEX array, dimension (LDX,NRHS)   
            The exact solution vectors.  Each vector is stored as a   
            column of the matrix XACT.   

    LDXACT  (input) INTEGER   
            The leading dimension of the array XACT.  LDXACT >= max(1,N).   

    FERR    (input) REAL array, dimension (NRHS)   
            The estimated forward error bounds for each solution vector   
            X.  If XTRUE is the true solution, FERR bounds the magnitude   
            of the largest entry in (X - XTRUE) divided by the magnitude   
            of the largest entry in X.   

    BERR    (input) REAL array, dimension (NRHS)   
            The componentwise relative backward error of each solution   
            vector (i.e., the smallest relative change in any entry of A   
            or B that makes X an exact solution).   

    RESLTS  (output) REAL array, dimension (2)   
            The maximum over the NRHS solution vectors of the ratios:   
            RESLTS(1) = norm(X - XACT) / ( norm(X) * FERR )   
            RESLTS(2) = BERR / ( NZ*EPS + (*) )   

    =====================================================================   


       Quick exit if N = 0 or NRHS = 0.   

       Parameter adjustments */
    --d__;
    --e;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1 * 1;
    x -= x_offset;
    xact_dim1 = *ldxact;
    xact_offset = 1 + xact_dim1 * 1;
    xact -= xact_offset;
    --ferr;
    --berr;
    --reslts;

    /* Function Body */
    if (*n <= 0 || *nrhs <= 0) {
	reslts[1] = 0.f;
	reslts[2] = 0.f;
	return 0;
    }

    eps = slamch_("Epsilon");
    unfl = slamch_("Safe minimum");
    ovfl = 1.f / unfl;
    nz = 4;

/*     Test 1:  Compute the maximum of   
          norm(X - XACT) / ( norm(X) * FERR )   
       over all the vectors X and XACT using the infinity-norm. */

    errbnd = 0.f;
    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	imax = icamax_(n, &x_ref(1, j), &c__1);
/* Computing MAX */
	i__2 = x_subscr(imax, j);
	r__3 = (r__1 = x[i__2].r, dabs(r__1)) + (r__2 = r_imag(&x_ref(imax, j)
		), dabs(r__2));
	xnorm = dmax(r__3,unfl);
	diff = 0.f;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = x_subscr(i__, j);
	    i__4 = xact_subscr(i__, j);
	    q__2.r = x[i__3].r - xact[i__4].r, q__2.i = x[i__3].i - xact[i__4]
		    .i;
	    q__1.r = q__2.r, q__1.i = q__2.i;
/* Computing MAX */
	    r__3 = diff, r__4 = (r__1 = q__1.r, dabs(r__1)) + (r__2 = r_imag(&
		    q__1), dabs(r__2));
	    diff = dmax(r__3,r__4);
/* L10: */
	}

	if (xnorm > 1.f) {
	    goto L20;
	} else if (diff <= ovfl * xnorm) {
	    goto L20;
	} else {
	    errbnd = 1.f / eps;
	    goto L30;
	}

L20:
	if (diff / xnorm <= ferr[j]) {
/* Computing MAX */
	    r__1 = errbnd, r__2 = diff / xnorm / ferr[j];
	    errbnd = dmax(r__1,r__2);
	} else {
	    errbnd = 1.f / eps;
	}
L30:
	;
    }
    reslts[1] = errbnd;

/*     Test 2:  Compute the maximum of BERR / ( NZ*EPS + (*) ), where   
       (*) = NZ*UNFL / (min_i (abs(A)*abs(X) +abs(b))_i ) */

    i__1 = *nrhs;
    for (k = 1; k <= i__1; ++k) {
	if (*n == 1) {
	    i__2 = x_subscr(1, k);
	    q__2.r = d__[1] * x[i__2].r, q__2.i = d__[1] * x[i__2].i;
	    q__1.r = q__2.r, q__1.i = q__2.i;
	    i__3 = b_subscr(1, k);
	    axbi = (r__1 = b[i__3].r, dabs(r__1)) + (r__2 = r_imag(&b_ref(1, 
		    k)), dabs(r__2)) + ((r__3 = q__1.r, dabs(r__3)) + (r__4 = 
		    r_imag(&q__1), dabs(r__4)));
	} else {
	    i__2 = x_subscr(1, k);
	    q__2.r = d__[1] * x[i__2].r, q__2.i = d__[1] * x[i__2].i;
	    q__1.r = q__2.r, q__1.i = q__2.i;
	    i__3 = b_subscr(1, k);
	    i__4 = x_subscr(2, k);
	    axbi = (r__1 = b[i__3].r, dabs(r__1)) + (r__2 = r_imag(&b_ref(1, 
		    k)), dabs(r__2)) + ((r__3 = q__1.r, dabs(r__3)) + (r__4 = 
		    r_imag(&q__1), dabs(r__4))) + ((r__5 = e[1].r, dabs(r__5))
		     + (r__6 = r_imag(&e[1]), dabs(r__6))) * ((r__7 = x[i__4]
		    .r, dabs(r__7)) + (r__8 = r_imag(&x_ref(2, k)), dabs(r__8)
		    ));
	    i__2 = *n - 1;
	    for (i__ = 2; i__ <= i__2; ++i__) {
		i__3 = i__;
		i__4 = x_subscr(i__, k);
		q__2.r = d__[i__3] * x[i__4].r, q__2.i = d__[i__3] * x[i__4]
			.i;
		q__1.r = q__2.r, q__1.i = q__2.i;
		i__5 = b_subscr(i__, k);
		i__6 = i__ - 1;
		i__7 = x_subscr(i__ - 1, k);
		i__8 = i__;
		i__9 = x_subscr(i__ + 1, k);
		tmp = (r__1 = b[i__5].r, dabs(r__1)) + (r__2 = r_imag(&b_ref(
			i__, k)), dabs(r__2)) + ((r__3 = e[i__6].r, dabs(r__3)
			) + (r__4 = r_imag(&e[i__ - 1]), dabs(r__4))) * ((
			r__5 = x[i__7].r, dabs(r__5)) + (r__6 = r_imag(&x_ref(
			i__ - 1, k)), dabs(r__6))) + ((r__7 = q__1.r, dabs(
			r__7)) + (r__8 = r_imag(&q__1), dabs(r__8))) + ((r__9 
			= e[i__8].r, dabs(r__9)) + (r__10 = r_imag(&e[i__]), 
			dabs(r__10))) * ((r__11 = x[i__9].r, dabs(r__11)) + (
			r__12 = r_imag(&x_ref(i__ + 1, k)), dabs(r__12)));
		axbi = dmin(axbi,tmp);
/* L40: */
	    }
	    i__2 = *n;
	    i__3 = x_subscr(*n, k);
	    q__2.r = d__[i__2] * x[i__3].r, q__2.i = d__[i__2] * x[i__3].i;
	    q__1.r = q__2.r, q__1.i = q__2.i;
	    i__4 = b_subscr(*n, k);
	    i__5 = *n - 1;
	    i__6 = x_subscr(*n - 1, k);
	    tmp = (r__1 = b[i__4].r, dabs(r__1)) + (r__2 = r_imag(&b_ref(*n, 
		    k)), dabs(r__2)) + ((r__3 = e[i__5].r, dabs(r__3)) + (
		    r__4 = r_imag(&e[*n - 1]), dabs(r__4))) * ((r__5 = x[i__6]
		    .r, dabs(r__5)) + (r__6 = r_imag(&x_ref(*n - 1, k)), dabs(
		    r__6))) + ((r__7 = q__1.r, dabs(r__7)) + (r__8 = r_imag(&
		    q__1), dabs(r__8)));
	    axbi = dmin(axbi,tmp);
	}
/* Computing MAX */
	r__1 = axbi, r__2 = nz * unfl;
	tmp = berr[k] / (nz * eps + nz * unfl / dmax(r__1,r__2));
	if (k == 1) {
	    reslts[2] = tmp;
	} else {
	    reslts[2] = dmax(reslts[2],tmp);
	}
/* L50: */
    }

    return 0;

/*     End of CPTT05 */

} /* cptt05_ */

#undef x_ref
#undef x_subscr
#undef b_ref
#undef b_subscr
#undef xact_ref
#undef xact_subscr


