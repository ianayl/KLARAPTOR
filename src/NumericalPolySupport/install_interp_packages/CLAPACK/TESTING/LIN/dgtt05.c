#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int dgtt05_(char *trans, integer *n, integer *nrhs, 
	doublereal *dl, doublereal *d__, doublereal *du, doublereal *b, 
	integer *ldb, doublereal *x, integer *ldx, doublereal *xact, integer *
	ldxact, doublereal *ferr, doublereal *berr, doublereal *reslts)
{
    /* System generated locals */
    integer b_dim1, b_offset, x_dim1, x_offset, xact_dim1, xact_offset, i__1, 
	    i__2;
    doublereal d__1, d__2, d__3, d__4;

    /* Local variables */
    static doublereal diff, axbi;
    static integer imax;
    static doublereal unfl, ovfl;
    static integer i__, j, k;
    extern logical lsame_(char *, char *);
    static doublereal xnorm;
    extern doublereal dlamch_(char *);
    extern integer idamax_(integer *, doublereal *, integer *);
    static integer nz;
    static doublereal errbnd;
    static logical notran;
    static doublereal eps, tmp;


#define xact_ref(a_1,a_2) xact[(a_2)*xact_dim1 + a_1]
#define b_ref(a_1,a_2) b[(a_2)*b_dim1 + a_1]
#define x_ref(a_1,a_2) x[(a_2)*x_dim1 + a_1]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DGTT05 tests the error bounds from iterative refinement for the   
    computed solution to a system of equations A*X = B, where A is a   
    general tridiagonal matrix of order n and op(A) = A or A**T,   
    depending on TRANS.   

    RESLTS(1) = test of the error bound   
              = norm(X - XACT) / ( norm(X) * FERR )   

    A large value is returned if this ratio is not less than one.   

    RESLTS(2) = residual from the iterative refinement routine   
              = the maximum of BERR / ( NZ*EPS + (*) ), where   
                (*) = NZ*UNFL / (min_i (abs(op(A))*abs(X) +abs(b))_i )   
                and NZ = max. number of nonzeros in any row of A, plus 1   

    Arguments   
    =========   

    TRANS   (input) CHARACTER*1   
            Specifies the form of the system of equations.   
            = 'N':  A * X = B     (No transpose)   
            = 'T':  A**T * X = B  (Transpose)   
            = 'C':  A**H * X = B  (Conjugate transpose = Transpose)   

    N       (input) INTEGER   
            The number of rows of the matrices X and XACT.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of columns of the matrices X and XACT.  NRHS >= 0.   

    DL      (input) DOUBLE PRECISION array, dimension (N-1)   
            The (n-1) sub-diagonal elements of A.   

    D       (input) DOUBLE PRECISION array, dimension (N)   
            The diagonal elements of A.   

    DU      (input) DOUBLE PRECISION array, dimension (N-1)   
            The (n-1) super-diagonal elements of A.   

    B       (input) DOUBLE PRECISION array, dimension (LDB,NRHS)   
            The right hand side vectors for the system of linear   
            equations.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,N).   

    X       (input) DOUBLE PRECISION array, dimension (LDX,NRHS)   
            The computed solution vectors.  Each vector is stored as a   
            column of the matrix X.   

    LDX     (input) INTEGER   
            The leading dimension of the array X.  LDX >= max(1,N).   

    XACT    (input) DOUBLE PRECISION array, dimension (LDX,NRHS)   
            The exact solution vectors.  Each vector is stored as a   
            column of the matrix XACT.   

    LDXACT  (input) INTEGER   
            The leading dimension of the array XACT.  LDXACT >= max(1,N).   

    FERR    (input) DOUBLE PRECISION array, dimension (NRHS)   
            The estimated forward error bounds for each solution vector   
            X.  If XTRUE is the true solution, FERR bounds the magnitude   
            of the largest entry in (X - XTRUE) divided by the magnitude   
            of the largest entry in X.   

    BERR    (input) DOUBLE PRECISION array, dimension (NRHS)   
            The componentwise relative backward error of each solution   
            vector (i.e., the smallest relative change in any entry of A   
            or B that makes X an exact solution).   

    RESLTS  (output) DOUBLE PRECISION array, dimension (2)   
            The maximum over the NRHS solution vectors of the ratios:   
            RESLTS(1) = norm(X - XACT) / ( norm(X) * FERR )   
            RESLTS(2) = BERR / ( NZ*EPS + (*) )   

    =====================================================================   


       Quick exit if N = 0 or NRHS = 0.   

       Parameter adjustments */
    --dl;
    --d__;
    --du;
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
	reslts[1] = 0.;
	reslts[2] = 0.;
	return 0;
    }

    eps = dlamch_("Epsilon");
    unfl = dlamch_("Safe minimum");
    ovfl = 1. / unfl;
    notran = lsame_(trans, "N");
    nz = 4;

/*     Test 1:  Compute the maximum of   
          norm(X - XACT) / ( norm(X) * FERR )   
       over all the vectors X and XACT using the infinity-norm. */

    errbnd = 0.;
    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	imax = idamax_(n, &x_ref(1, j), &c__1);
/* Computing MAX */
	d__2 = (d__1 = x_ref(imax, j), abs(d__1));
	xnorm = max(d__2,unfl);
	diff = 0.;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
	    d__2 = diff, d__3 = (d__1 = x_ref(i__, j) - xact_ref(i__, j), abs(
		    d__1));
	    diff = max(d__2,d__3);
/* L10: */
	}

	if (xnorm > 1.) {
	    goto L20;
	} else if (diff <= ovfl * xnorm) {
	    goto L20;
	} else {
	    errbnd = 1. / eps;
	    goto L30;
	}

L20:
	if (diff / xnorm <= ferr[j]) {
/* Computing MAX */
	    d__1 = errbnd, d__2 = diff / xnorm / ferr[j];
	    errbnd = max(d__1,d__2);
	} else {
	    errbnd = 1. / eps;
	}
L30:
	;
    }
    reslts[1] = errbnd;

/*     Test 2:  Compute the maximum of BERR / ( NZ*EPS + (*) ), where   
       (*) = NZ*UNFL / (min_i (abs(op(A))*abs(X) +abs(b))_i ) */

    i__1 = *nrhs;
    for (k = 1; k <= i__1; ++k) {
	if (notran) {
	    if (*n == 1) {
		axbi = (d__1 = b_ref(1, k), abs(d__1)) + (d__2 = d__[1] * 
			x_ref(1, k), abs(d__2));
	    } else {
		axbi = (d__1 = b_ref(1, k), abs(d__1)) + (d__2 = d__[1] * 
			x_ref(1, k), abs(d__2)) + (d__3 = du[1] * x_ref(2, k),
			 abs(d__3));
		i__2 = *n - 1;
		for (i__ = 2; i__ <= i__2; ++i__) {
		    tmp = (d__1 = b_ref(i__, k), abs(d__1)) + (d__2 = dl[i__ 
			    - 1] * x_ref(i__ - 1, k), abs(d__2)) + (d__3 = 
			    d__[i__] * x_ref(i__, k), abs(d__3)) + (d__4 = du[
			    i__] * x_ref(i__ + 1, k), abs(d__4));
		    axbi = min(axbi,tmp);
/* L40: */
		}
		tmp = (d__1 = b_ref(*n, k), abs(d__1)) + (d__2 = dl[*n - 1] * 
			x_ref(*n - 1, k), abs(d__2)) + (d__3 = d__[*n] * 
			x_ref(*n, k), abs(d__3));
		axbi = min(axbi,tmp);
	    }
	} else {
	    if (*n == 1) {
		axbi = (d__1 = b_ref(1, k), abs(d__1)) + (d__2 = d__[1] * 
			x_ref(1, k), abs(d__2));
	    } else {
		axbi = (d__1 = b_ref(1, k), abs(d__1)) + (d__2 = d__[1] * 
			x_ref(1, k), abs(d__2)) + (d__3 = dl[1] * x_ref(2, k),
			 abs(d__3));
		i__2 = *n - 1;
		for (i__ = 2; i__ <= i__2; ++i__) {
		    tmp = (d__1 = b_ref(i__, k), abs(d__1)) + (d__2 = du[i__ 
			    - 1] * x_ref(i__ - 1, k), abs(d__2)) + (d__3 = 
			    d__[i__] * x_ref(i__, k), abs(d__3)) + (d__4 = dl[
			    i__] * x_ref(i__ + 1, k), abs(d__4));
		    axbi = min(axbi,tmp);
/* L50: */
		}
		tmp = (d__1 = b_ref(*n, k), abs(d__1)) + (d__2 = du[*n - 1] * 
			x_ref(*n - 1, k), abs(d__2)) + (d__3 = d__[*n] * 
			x_ref(*n, k), abs(d__3));
		axbi = min(axbi,tmp);
	    }
	}
/* Computing MAX */
	d__1 = axbi, d__2 = nz * unfl;
	tmp = berr[k] / (nz * eps + nz * unfl / max(d__1,d__2));
	if (k == 1) {
	    reslts[2] = tmp;
	} else {
	    reslts[2] = max(reslts[2],tmp);
	}
/* L60: */
    }

    return 0;

/*     End of DGTT05 */

} /* dgtt05_ */

#undef x_ref
#undef b_ref
#undef xact_ref


