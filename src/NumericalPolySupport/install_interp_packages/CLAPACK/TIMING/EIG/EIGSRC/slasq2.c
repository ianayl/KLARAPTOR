#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    real ops, itcnt;
} latime_;

#define latime_1 latime_

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__10 = 10;
static integer c__3 = 3;
static integer c__4 = 4;
static integer c__11 = 11;

/* Subroutine */ int slasq2_(integer *n, real *z__, integer *info)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static logical ieee;
    static integer nbig;
    static real dmin__, emin, emax;
    static integer ndiv, iter;
    static real qmin, temp, qmax, zmax;
    static integer splt;
    static real d__, e;
    static integer k;
    static real s, t;
    static integer nfail;
    static real desig, trace, sigma;
    static integer iinfo, i0, i4, n0;
    extern /* Subroutine */ int slasq3_(integer *, integer *, real *, integer 
	    *, real *, real *, real *, real *, integer *, integer *, integer *
	    , logical *);
    static integer pp;
    extern doublereal slamch_(char *);
    static integer iwhila, iwhilb;
    static real oldemn, safmin;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int slasrt_(char *, integer *, real *, integer *);
    static real eps, tol;
    static integer ipn4;
    static real tol2;


/*  -- LAPACK routine (instrumented to count ops, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1999   


    Purpose   
    =======   

    SLASQ2 computes all the eigenvalues of the symmetric positive   
    definite tridiagonal matrix associated with the qd array Z to high   
    relative accuracy are computed to high relative accuracy, in the   
    absence of denormalization, underflow and overflow.   

    To see the relation of Z to the tridiagonal matrix, let L be a   
    unit lower bidiagonal matrix with subdiagonals Z(2,4,6,,..) and   
    let U be an upper bidiagonal matrix with 1's above and diagonal   
    Z(1,3,5,,..). The tridiagonal is L*U or, if you prefer, the   
    symmetric tridiagonal to which it is similar.   

    Note : SLASQ2 defines a logical variable, IEEE, which is true   
    on machines which follow ieee-754 floating-point standard in their   
    handling of infinities and NaNs, and false otherwise. This variable   
    is passed to SLASQ3.   

    Arguments   
    =========   

    N     (input) INTEGER   
          The number of rows and columns in the matrix. N >= 0.   

    Z     (workspace) REAL array, dimension ( 4*N )   
          On entry Z holds the qd array. On exit, entries 1 to N hold   
          the eigenvalues in decreasing order, Z( 2*N+1 ) holds the   
          trace, and Z( 2*N+2 ) holds the sum of the eigenvalues. If   
          N > 2, then Z( 2*N+3 ) holds the iteration count, Z( 2*N+4 )   
          holds NDIVS/NIN^2, and Z( 2*N+5 ) holds the percentage of   
          shifts that failed.   

    INFO  (output) INTEGER   
          = 0: successful exit   
          < 0: if the i-th argument is a scalar and had an illegal   
               value, then INFO = -i, if the i-th argument is an   
               array and the j-entry had an illegal value, then   
               INFO = -(i*100+j)   
          > 0: the algorithm failed   
                = 1, a split was marked by a positive value in E   
                = 2, current block of Z not diagonalized after 30*N   
                     iterations (in inner while loop)   
                = 3, termination criterion of outer while loop not met   
                     (program created more than N unreduced blocks)   

    Further Details   
    ===============   
    Local Variables: I0:N0 defines a current unreduced segment of Z.   
    The shifts are accumulated in SIGMA. Iteration count is in ITER.   
    Ping-pong is controlled by PP (alternates between 0 and 1).   

    =====================================================================   


       Test the input arguments.   
       (in case SLASQ2 is not called by SLASQ1)   

       Parameter adjustments */
    --z__;

    /* Function Body */
    latime_1.ops += 2.f;
    *info = 0;
    eps = slamch_("Precision");
    safmin = slamch_("Safe minimum");
    tol = eps * 100.f;
/* Computing 2nd power */
    r__1 = tol;
    tol2 = r__1 * r__1;

    if (*n < 0) {
	*info = -1;
	xerbla_("SLASQ2", &c__1);
	return 0;
    } else if (*n == 0) {
	return 0;
    } else if (*n == 1) {

/*        1-by-1 case. */

	if (z__[1] < 0.f) {
	    *info = -201;
	    xerbla_("SLASQ2", &c__2);
	}
	return 0;
    } else if (*n == 2) {

/*        2-by-2 case. */

	if (z__[2] < 0.f || z__[3] < 0.f) {
	    *info = -2;
	    xerbla_("SLASQ2", &c__2);
	    return 0;
	} else if (z__[3] > z__[1]) {
	    d__ = z__[3];
	    z__[3] = z__[1];
	    z__[1] = d__;
	}
	latime_1.ops += 4.f;
	z__[5] = z__[1] + z__[2] + z__[3];
	if (z__[2] > z__[3] * tol2) {
	    latime_1.ops += 16.f;
	    t = (z__[1] - z__[3] + z__[2]) * .5f;
	    s = z__[3] * (z__[2] / t);
	    if (s <= t) {
		s = z__[3] * (z__[2] / (t * (sqrt(s / t + 1.f) + 1.f)));
	    } else {
		s = z__[3] * (z__[2] / (t + sqrt(t) * sqrt(t + s)));
	    }
	    t = z__[1] + (s + z__[2]);
	    z__[3] *= z__[1] / t;
	    z__[1] = t;
	}
	z__[2] = z__[3];
	z__[6] = z__[2] + z__[1];
	return 0;
    }

/*     Check for negative data and compute sums of q's and e's. */

    z__[*n * 2] = 0.f;
    emin = z__[2];
    qmax = 0.f;
    zmax = 0.f;
    d__ = 0.f;
    e = 0.f;

    latime_1.ops += (real) (*n << 1);
    i__1 = *n - 1 << 1;
    for (k = 1; k <= i__1; k += 2) {
	if (z__[k] < 0.f) {
	    *info = -(k + 200);
	    xerbla_("SLASQ2", &c__2);
	    return 0;
	} else if (z__[k + 1] < 0.f) {
	    *info = -(k + 201);
	    xerbla_("SLASQ2", &c__2);
	    return 0;
	}
	d__ += z__[k];
	e += z__[k + 1];
/* Computing MAX */
	r__1 = qmax, r__2 = z__[k];
	qmax = dmax(r__1,r__2);
/* Computing MIN */
	r__1 = emin, r__2 = z__[k + 1];
	emin = dmin(r__1,r__2);
/* Computing MAX */
	r__1 = max(qmax,zmax), r__2 = z__[k + 1];
	zmax = dmax(r__1,r__2);
/* L10: */
    }
    if (z__[(*n << 1) - 1] < 0.f) {
	*info = -((*n << 1) + 199);
	xerbla_("SLASQ2", &c__2);
	return 0;
    }
    d__ += z__[(*n << 1) - 1];
/* Computing MAX */
    r__1 = qmax, r__2 = z__[(*n << 1) - 1];
    qmax = dmax(r__1,r__2);
    zmax = dmax(qmax,zmax);

/*     Check for diagonality. */

    if (e == 0.f) {
	i__1 = *n;
	for (k = 2; k <= i__1; ++k) {
	    z__[k] = z__[(k << 1) - 1];
/* L20: */
	}
	slasrt_("D", n, &z__[1], &iinfo);
	z__[(*n << 1) - 1] = d__;
	return 0;
    }

    trace = d__ + e;

/*     Check for zero data. */

    if (trace == 0.f) {
	z__[(*n << 1) - 1] = 0.f;
	return 0;
    }

/*     Check whether the machine is IEEE conformable. */

    ieee = ilaenv_(&c__10, "SLASQ2", "N", &c__1, &c__2, &c__3, &c__4, (ftnlen)
	    6, (ftnlen)1) == 1 && ilaenv_(&c__11, "SLASQ2", "N", &c__1, &c__2,
	     &c__3, &c__4, (ftnlen)6, (ftnlen)1) == 1;

/*     Rearrange data for locality: Z=(q1,qq1,e1,ee1,q2,qq2,e2,ee2,...). */

    for (k = *n << 1; k >= 2; k += -2) {
	z__[k * 2] = 0.f;
	z__[(k << 1) - 1] = z__[k];
	z__[(k << 1) - 2] = 0.f;
	z__[(k << 1) - 3] = z__[k - 1];
/* L30: */
    }

    i0 = 1;
    n0 = *n;

/*     Reverse the qd-array, if warranted. */

    latime_1.ops += 1.f;
    if (z__[(i0 << 2) - 3] * 1.5f < z__[(n0 << 2) - 3]) {
	ipn4 = i0 + n0 << 2;
	i__1 = i0 + n0 - 1 << 1;
	for (i4 = i0 << 2; i4 <= i__1; i4 += 4) {
	    temp = z__[i4 - 3];
	    z__[i4 - 3] = z__[ipn4 - i4 - 3];
	    z__[ipn4 - i4 - 3] = temp;
	    temp = z__[i4 - 1];
	    z__[i4 - 1] = z__[ipn4 - i4 - 5];
	    z__[ipn4 - i4 - 5] = temp;
/* L40: */
	}
    }

/*     Initial split checking via dqd and Li's test. */

    pp = 0;

    for (k = 1; k <= 2; ++k) {

	latime_1.ops += (real) (n0 - i0);
	d__ = z__[(n0 << 2) + pp - 3];
	i__1 = (i0 << 2) + pp;
	for (i4 = (n0 - 1 << 2) + pp; i4 >= i__1; i4 += -4) {
	    if (z__[i4 - 1] <= tol2 * d__) {
		z__[i4 - 1] = 0.f;
		d__ = z__[i4 - 3];
	    } else {
		latime_1.ops += 3.f;
		d__ = z__[i4 - 3] * (d__ / (d__ + z__[i4 - 1]));
	    }
/* L50: */
	}

/*        dqd maps Z to ZZ plus Li's test. */

	latime_1.ops += (real) (n0 - i0);
	emin = z__[(i0 << 2) + pp + 1];
	d__ = z__[(i0 << 2) + pp - 3];
	i__1 = (n0 - 1 << 2) + pp;
	for (i4 = (i0 << 2) + pp; i4 <= i__1; i4 += 4) {
	    z__[i4 - (pp << 1) - 2] = d__ + z__[i4 - 1];
	    if (z__[i4 - 1] <= tol2 * d__) {
		z__[i4 - 1] = 0.f;
		z__[i4 - (pp << 1) - 2] = d__;
		z__[i4 - (pp << 1)] = 0.f;
		d__ = z__[i4 + 1];
	    } else if (safmin * z__[i4 + 1] < z__[i4 - (pp << 1) - 2] && 
		    safmin * z__[i4 - (pp << 1) - 2] < z__[i4 + 1]) {
		latime_1.ops += 5.f;
		temp = z__[i4 + 1] / z__[i4 - (pp << 1) - 2];
		z__[i4 - (pp << 1)] = z__[i4 - 1] * temp;
		d__ *= temp;
	    } else {
		latime_1.ops += 5.f;
		z__[i4 - (pp << 1)] = z__[i4 + 1] * (z__[i4 - 1] / z__[i4 - (
			pp << 1) - 2]);
		d__ = z__[i4 + 1] * (d__ / z__[i4 - (pp << 1) - 2]);
	    }
/* Computing MIN */
	    r__1 = emin, r__2 = z__[i4 - (pp << 1)];
	    emin = dmin(r__1,r__2);
/* L60: */
	}
	z__[(n0 << 2) - pp - 2] = d__;

/*        Now find qmax. */

	qmax = z__[(i0 << 2) - pp - 2];
	i__1 = (n0 << 2) - pp - 2;
	for (i4 = (i0 << 2) - pp + 2; i4 <= i__1; i4 += 4) {
/* Computing MAX */
	    r__1 = qmax, r__2 = z__[i4];
	    qmax = dmax(r__1,r__2);
/* L70: */
	}

/*        Prepare for the next iteration on K. */

	pp = 1 - pp;
/* L80: */
    }

    iter = 2;
    nfail = 0;
    ndiv = n0 - i0 << 1;

    i__1 = *n + 1;
    for (iwhila = 1; iwhila <= i__1; ++iwhila) {
	if (n0 < 1) {
	    goto L150;
	}

/*        While array unfinished do   

          E(N0) holds the value of SIGMA when submatrix in I0:N0   
          splits from the rest of the array, but is negated. */

	desig = 0.f;
	if (n0 == *n) {
	    sigma = 0.f;
	} else {
	    sigma = -z__[(n0 << 2) - 1];
	}
	if (sigma < 0.f) {
	    *info = 1;
	    return 0;
	}

/*        Find last unreduced submatrix's top index I0, find QMAX and   
          EMIN. Find Gershgorin-type bound if Q's much greater than E's. */

	emax = 0.f;
	if (n0 > i0) {
	    emin = (r__1 = z__[(n0 << 2) - 5], dabs(r__1));
	} else {
	    emin = 0.f;
	}
	qmin = z__[(n0 << 2) - 3];
	qmax = qmin;
	for (i4 = n0 << 2; i4 >= 8; i4 += -4) {
	    if (z__[i4 - 5] <= 0.f) {
		goto L100;
	    }
	    latime_1.ops += 2.f;
	    if (qmin >= emax * 4.f) {
/* Computing MIN */
		r__1 = qmin, r__2 = z__[i4 - 3];
		qmin = dmin(r__1,r__2);
/* Computing MAX */
		r__1 = emax, r__2 = z__[i4 - 5];
		emax = dmax(r__1,r__2);
	    }
/* Computing MAX */
	    r__1 = qmax, r__2 = z__[i4 - 7] + z__[i4 - 5];
	    qmax = dmax(r__1,r__2);
/* Computing MIN */
	    r__1 = emin, r__2 = z__[i4 - 5];
	    emin = dmin(r__1,r__2);
/* L90: */
	}
	i4 = 4;

L100:
	i0 = i4 / 4;

/*        Store EMIN for passing to SLASQ3. */

	z__[(n0 << 2) - 1] = emin;

/*        Put -(initial shift) into DMIN. */

	latime_1.ops += 5.f;
/* Computing MAX */
	r__1 = 0.f, r__2 = qmin - sqrt(qmin) * 2.f * sqrt(emax);
	dmin__ = -dmax(r__1,r__2);

/*        Now I0:N0 is unreduced. PP = 0 for ping, PP = 1 for pong. */

	pp = 0;

	nbig = (n0 - i0 + 1) * 30;
	i__2 = nbig;
	for (iwhilb = 1; iwhilb <= i__2; ++iwhilb) {
	    if (i0 > n0) {
		goto L130;
	    }

/*           While submatrix unfinished take a good dqds step. */

	    slasq3_(&i0, &n0, &z__[1], &pp, &dmin__, &sigma, &desig, &qmax, &
		    nfail, &iter, &ndiv, &ieee);

	    pp = 1 - pp;

/*           When EMIN is very small check for splits. */

	    if (pp == 0 && n0 - i0 >= 3) {
		latime_1.ops += 2.f;
		if (z__[n0 * 4] <= tol2 * qmax || z__[(n0 << 2) - 1] <= tol2 *
			 sigma) {
		    splt = i0 - 1;
		    qmax = z__[(i0 << 2) - 3];
		    emin = z__[(i0 << 2) - 1];
		    oldemn = z__[i0 * 4];
		    i__3 = n0 - 3 << 2;
		    for (i4 = i0 << 2; i4 <= i__3; i4 += 4) {
			latime_1.ops += 1.f;
			if (z__[i4] <= tol2 * z__[i4 - 3] || z__[i4 - 1] <= 
				tol2 * sigma) {
			    z__[i4 - 1] = -sigma;
			    splt = i4 / 4;
			    qmax = 0.f;
			    emin = z__[i4 + 3];
			    oldemn = z__[i4 + 4];
			} else {
/* Computing MAX */
			    r__1 = qmax, r__2 = z__[i4 + 1];
			    qmax = dmax(r__1,r__2);
/* Computing MIN */
			    r__1 = emin, r__2 = z__[i4 - 1];
			    emin = dmin(r__1,r__2);
/* Computing MIN */
			    r__1 = oldemn, r__2 = z__[i4];
			    oldemn = dmin(r__1,r__2);
			}
/* L110: */
		    }
		    z__[(n0 << 2) - 1] = emin;
		    z__[n0 * 4] = oldemn;
		    i0 = splt + 1;
		}
	    }

/* L120: */
	}

	*info = 2;
	return 0;

/*        end IWHILB */

L130:

/* L140: */
	;
    }

    *info = 3;
    return 0;

/*     end IWHILA */

L150:

/*     Move q's to the front. */

    i__1 = *n;
    for (k = 2; k <= i__1; ++k) {
	z__[k] = z__[(k << 2) - 3];
/* L160: */
    }

/*     Sort and compute sum of eigenvalues. */

    slasrt_("D", n, &z__[1], &iinfo);

    e = 0.f;
    for (k = *n; k >= 1; --k) {
	e += z__[k];
/* L170: */
    }

/*     Store trace, sum(eigenvalues) and information on performance. */

    z__[(*n << 1) + 1] = trace;
    z__[(*n << 1) + 2] = e;
    z__[(*n << 1) + 3] = (real) iter;
/* Computing 2nd power */
    i__1 = *n;
    z__[(*n << 1) + 4] = (real) ndiv / (real) (i__1 * i__1);
    z__[(*n << 1) + 5] = nfail * 100.f / (real) iter;
    return 0;

/*     End of SLASQ2 */

} /* slasq2_ */

