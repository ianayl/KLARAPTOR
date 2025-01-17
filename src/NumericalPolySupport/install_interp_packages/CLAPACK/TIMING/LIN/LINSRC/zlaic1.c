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

struct {
    doublereal opcnt[6], timng[6];
} lstime_;

#define lstime_1 lstime_

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int zlaic1_(integer *job, integer *j, doublecomplex *x, 
	doublereal *sest, doublecomplex *w, doublecomplex *gamma, doublereal *
	sestpr, doublecomplex *s, doublecomplex *c__)
{
    /* System generated locals */
    doublereal d__1, d__2;
    doublecomplex z__1, z__2, z__3, z__4, z__5, z__6;

    /* Builtin functions */
    double z_abs(doublecomplex *);
    void d_cnjg(doublecomplex *, doublecomplex *), z_sqrt(doublecomplex *, 
	    doublecomplex *);
    double sqrt(doublereal);
    void z_div(doublecomplex *, doublecomplex *, doublecomplex *);

    /* Local variables */
    static doublecomplex sine;
    static doublereal test, zeta1, zeta2, b, t;
    static doublecomplex alpha;
    static doublereal norma;
    extern /* Double Complex */ VOID zdotc_(doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *);
    static doublereal s1, s2;
    extern doublereal dlamch_(char *);
    static doublereal absgam, absalp;
    static doublecomplex cosine;
    static doublereal absest, scl, eps, tmp;


/*  -- LAPACK auxiliary routine (instrumented to count ops, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    ZLAIC1 applies one step of incremental condition estimation in   
    its simplest version:   

    Let x, twonorm(x) = 1, be an approximate singular vector of an j-by-j   
    lower triangular matrix L, such that   
             twonorm(L*x) = sest   
    Then ZLAIC1 computes sestpr, s, c such that   
    the vector   
                    [ s*x ]   
             xhat = [  c  ]   
    is an approximate singular vector of   
                    [ L     0  ]   
             Lhat = [ w' gamma ]   
    in the sense that   
             twonorm(Lhat*xhat) = sestpr.   

    Depending on JOB, an estimate for the largest or smallest singular   
    value is computed.   

    Note that [s c]' and sestpr**2 is an eigenpair of the system   

        diag(sest*sest, 0) + [alpha  gamma] * [ conjg(alpha) ]   
                                              [ conjg(gamma) ]   

    where  alpha =  conjg(x)'*w.   

    Arguments   
    =========   

    JOB     (input) INTEGER   
            = 1: an estimate for the largest singular value is computed.   
            = 2: an estimate for the smallest singular value is computed.   

    J       (input) INTEGER   
            Length of X and W   

    X       (input) COMPLEX*16 array, dimension (J)   
            The j-vector x.   

    SEST    (input) DOUBLE PRECISION   
            Estimated singular value of j by j matrix L   

    W       (input) COMPLEX*16 array, dimension (J)   
            The j-vector w.   

    GAMMA   (input) COMPLEX*16   
            The diagonal element gamma.   

    SESTPR  (output) DOUBLE PRECISION   
            Estimated singular value of (j+1) by (j+1) matrix Lhat.   

    S       (output) COMPLEX*16   
            Sine needed in forming xhat.   

    C       (output) COMPLEX*16   
            Cosine needed in forming xhat.   

    =====================================================================   


       Parameter adjustments */
    --w;
    --x;

    /* Function Body */
    eps = dlamch_("Epsilon");
    zdotc_(&z__1, j, &x[1], &c__1, &w[1], &c__1);
    alpha.r = z__1.r, alpha.i = z__1.i;

    absalp = z_abs(&alpha);
    absgam = z_abs(gamma);
    absest = abs(*sest);

    if (*job == 1) {

/*        Estimating largest singular value   

          special cases */

	if (*sest == 0.) {
	    s1 = max(absgam,absalp);
	    if (s1 == 0.) {
		s->r = 0., s->i = 0.;
		c__->r = 1., c__->i = 0.;
		*sestpr = 0.;
	    } else {
		latime_1.ops += 67;
		z__1.r = alpha.r / s1, z__1.i = alpha.i / s1;
		s->r = z__1.r, s->i = z__1.i;
		z__1.r = gamma->r / s1, z__1.i = gamma->i / s1;
		c__->r = z__1.r, c__->i = z__1.i;
		d_cnjg(&z__4, s);
		z__3.r = s->r * z__4.r - s->i * z__4.i, z__3.i = s->r * 
			z__4.i + s->i * z__4.r;
		d_cnjg(&z__6, c__);
		z__5.r = c__->r * z__6.r - c__->i * z__6.i, z__5.i = c__->r * 
			z__6.i + c__->i * z__6.r;
		z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
		z_sqrt(&z__1, &z__2);
		tmp = z__1.r;
		z__1.r = s->r / tmp, z__1.i = s->i / tmp;
		s->r = z__1.r, s->i = z__1.i;
		z__1.r = c__->r / tmp, z__1.i = c__->i / tmp;
		c__->r = z__1.r, c__->i = z__1.i;
		*sestpr = s1 * tmp;
	    }
	    return 0;
	} else if (absgam <= eps * absest) {
	    latime_1.ops += 7;
	    s->r = 1., s->i = 0.;
	    c__->r = 0., c__->i = 0.;
	    tmp = max(absest,absalp);
	    s1 = absest / tmp;
	    s2 = absalp / tmp;
	    *sestpr = tmp * sqrt(s1 * s1 + s2 * s2);
	    return 0;
	} else if (absalp <= eps * absest) {
	    s1 = absgam;
	    s2 = absest;
	    if (s1 <= s2) {
		s->r = 1., s->i = 0.;
		c__->r = 0., c__->i = 0.;
		*sestpr = s2;
	    } else {
		s->r = 0., s->i = 0.;
		c__->r = 1., c__->i = 0.;
		*sestpr = s1;
	    }
	    return 0;
	} else if (absest <= eps * absalp || absest <= eps * absgam) {
	    s1 = absgam;
	    s2 = absalp;
	    if (s1 <= s2) {
		latime_1.ops += 57;
		tmp = s1 / s2;
		scl = sqrt(tmp * tmp + 1.);
		*sestpr = s2 * scl;
		z__2.r = alpha.r / s2, z__2.i = alpha.i / s2;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		s->r = z__1.r, s->i = z__1.i;
		z__2.r = gamma->r / s2, z__2.i = gamma->i / s2;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		c__->r = z__1.r, c__->i = z__1.i;
	    } else {
		latime_1.ops += 57;
		tmp = s2 / s1;
		scl = sqrt(tmp * tmp + 1.);
		*sestpr = s1 * scl;
		z__2.r = alpha.r / s1, z__2.i = alpha.i / s1;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		s->r = z__1.r, s->i = z__1.i;
		z__2.r = gamma->r / s1, z__2.i = gamma->i / s1;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		c__->r = z__1.r, c__->i = z__1.i;
	    }
	    return 0;
	} else {

/*           normal case */

	    latime_1.ops += 8;
	    zeta1 = absalp / absest;
	    zeta2 = absgam / absest;

	    b = (1. - zeta1 * zeta1 - zeta2 * zeta2) * .5;
	    d__1 = zeta1 * zeta1;
	    c__->r = d__1, c__->i = 0.;
	    if (b > 0.) {
		latime_1.ops += 17;
		d__1 = b * b;
		z__4.r = d__1 + c__->r, z__4.i = c__->i;
		z_sqrt(&z__3, &z__4);
		z__2.r = b + z__3.r, z__2.i = z__3.i;
		z_div(&z__1, c__, &z__2);
		t = z__1.r;
	    } else {
		latime_1.ops += 5;
		d__1 = b * b;
		z__3.r = d__1 + c__->r, z__3.i = c__->i;
		z_sqrt(&z__2, &z__3);
		z__1.r = z__2.r - b, z__1.i = z__2.i;
		t = z__1.r;
	    }

	    latime_1.ops += 96;
	    z__3.r = alpha.r / absest, z__3.i = alpha.i / absest;
	    z__2.r = -z__3.r, z__2.i = -z__3.i;
	    z__1.r = z__2.r / t, z__1.i = z__2.i / t;
	    sine.r = z__1.r, sine.i = z__1.i;
	    z__3.r = gamma->r / absest, z__3.i = gamma->i / absest;
	    z__2.r = -z__3.r, z__2.i = -z__3.i;
	    d__1 = t + 1.;
	    z__1.r = z__2.r / d__1, z__1.i = z__2.i / d__1;
	    cosine.r = z__1.r, cosine.i = z__1.i;
	    d_cnjg(&z__4, &sine);
	    z__3.r = sine.r * z__4.r - sine.i * z__4.i, z__3.i = sine.r * 
		    z__4.i + sine.i * z__4.r;
	    d_cnjg(&z__6, &cosine);
	    z__5.r = cosine.r * z__6.r - cosine.i * z__6.i, z__5.i = cosine.r 
		    * z__6.i + cosine.i * z__6.r;
	    z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
	    z_sqrt(&z__1, &z__2);
	    tmp = z__1.r;
	    z__1.r = sine.r / tmp, z__1.i = sine.i / tmp;
	    s->r = z__1.r, s->i = z__1.i;
	    z__1.r = cosine.r / tmp, z__1.i = cosine.i / tmp;
	    c__->r = z__1.r, c__->i = z__1.i;
	    *sestpr = sqrt(t + 1.) * absest;
	    return 0;
	}

    } else if (*job == 2) {

/*        Estimating smallest singular value   

          special cases */

	if (*sest == 0.) {
	    *sestpr = 0.;
	    if (max(absgam,absalp) == 0.) {
		sine.r = 1., sine.i = 0.;
		cosine.r = 0., cosine.i = 0.;
	    } else {
		d_cnjg(&z__2, gamma);
		z__1.r = -z__2.r, z__1.i = -z__2.i;
		sine.r = z__1.r, sine.i = z__1.i;
		d_cnjg(&z__1, &alpha);
		cosine.r = z__1.r, cosine.i = z__1.i;
	    }
	    latime_1.ops += 66;
/* Computing MAX */
	    d__1 = z_abs(&sine), d__2 = z_abs(&cosine);
	    s1 = max(d__1,d__2);
	    z__1.r = sine.r / s1, z__1.i = sine.i / s1;
	    s->r = z__1.r, s->i = z__1.i;
	    z__1.r = cosine.r / s1, z__1.i = cosine.i / s1;
	    c__->r = z__1.r, c__->i = z__1.i;
	    d_cnjg(&z__4, s);
	    z__3.r = s->r * z__4.r - s->i * z__4.i, z__3.i = s->r * z__4.i + 
		    s->i * z__4.r;
	    d_cnjg(&z__6, c__);
	    z__5.r = c__->r * z__6.r - c__->i * z__6.i, z__5.i = c__->r * 
		    z__6.i + c__->i * z__6.r;
	    z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
	    z_sqrt(&z__1, &z__2);
	    tmp = z__1.r;
	    z__1.r = s->r / tmp, z__1.i = s->i / tmp;
	    s->r = z__1.r, s->i = z__1.i;
	    z__1.r = c__->r / tmp, z__1.i = c__->i / tmp;
	    c__->r = z__1.r, c__->i = z__1.i;
	    return 0;
	} else if (absgam <= eps * absest) {
	    s->r = 0., s->i = 0.;
	    c__->r = 1., c__->i = 0.;
	    *sestpr = absgam;
	    return 0;
	} else if (absalp <= eps * absest) {
	    s1 = absgam;
	    s2 = absest;
	    if (s1 <= s2) {
		s->r = 0., s->i = 0.;
		c__->r = 1., c__->i = 0.;
		*sestpr = s1;
	    } else {
		s->r = 1., s->i = 0.;
		c__->r = 0., c__->i = 0.;
		*sestpr = s2;
	    }
	    return 0;
	} else if (absest <= eps * absalp || absest <= eps * absgam) {
	    s1 = absgam;
	    s2 = absalp;
	    if (s1 <= s2) {
		latime_1.ops += 57;
		tmp = s1 / s2;
		scl = sqrt(tmp * tmp + 1.);
		*sestpr = absest * (tmp / scl);
		d_cnjg(&z__4, gamma);
		z__3.r = z__4.r / s2, z__3.i = z__4.i / s2;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		s->r = z__1.r, s->i = z__1.i;
		d_cnjg(&z__3, &alpha);
		z__2.r = z__3.r / s2, z__2.i = z__3.i / s2;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		c__->r = z__1.r, c__->i = z__1.i;
	    } else {
		latime_1.ops += 56;
		tmp = s2 / s1;
		scl = sqrt(tmp * tmp + 1.);
		*sestpr = absest / scl;
		d_cnjg(&z__4, gamma);
		z__3.r = z__4.r / s1, z__3.i = z__4.i / s1;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		s->r = z__1.r, s->i = z__1.i;
		d_cnjg(&z__3, &alpha);
		z__2.r = z__3.r / s1, z__2.i = z__3.i / s1;
		z__1.r = z__2.r / scl, z__1.i = z__2.i / scl;
		c__->r = z__1.r, c__->i = z__1.i;
	    }
	    return 0;
	} else {

/*           normal case */

	    latime_1.ops += 14;
	    zeta1 = absalp / absest;
	    zeta2 = absgam / absest;

/* Computing MAX */
	    d__1 = zeta1 * zeta1 + 1. + zeta1 * zeta2, d__2 = zeta1 * zeta2 + 
		    zeta2 * zeta2;
	    norma = max(d__1,d__2);

/*           See if root is closer to zero or to ONE */

	    test = (zeta1 - zeta2) * 2. * (zeta1 + zeta2) + 1.;
	    if (test >= 0.) {

/*              root is close to zero, compute directly */

		latime_1.ops += 62;
		b = (zeta1 * zeta1 + zeta2 * zeta2 + 1.) * .5;
		d__1 = zeta2 * zeta2;
		c__->r = d__1, c__->i = 0.;
		d__2 = b * b;
		z__2.r = d__2 - c__->r, z__2.i = -c__->i;
		d__1 = b + sqrt(z_abs(&z__2));
		z__1.r = c__->r / d__1, z__1.i = c__->i / d__1;
		t = z__1.r;
		z__2.r = alpha.r / absest, z__2.i = alpha.i / absest;
		d__1 = 1. - t;
		z__1.r = z__2.r / d__1, z__1.i = z__2.i / d__1;
		sine.r = z__1.r, sine.i = z__1.i;
		z__3.r = gamma->r / absest, z__3.i = gamma->i / absest;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		z__1.r = z__2.r / t, z__1.i = z__2.i / t;
		cosine.r = z__1.r, cosine.i = z__1.i;
		*sestpr = sqrt(t + eps * 4. * eps * norma) * absest;
	    } else {

/*              root is closer to ONE, shift by that amount */

		latime_1.ops += 6;
		b = (zeta2 * zeta2 + zeta1 * zeta1 - 1.) * .5;
		d__1 = zeta1 * zeta1;
		c__->r = d__1, c__->i = 0.;
		if (b >= 0.) {
		    latime_1.ops += 5;
		    z__2.r = -c__->r, z__2.i = -c__->i;
		    d__1 = b * b;
		    z__5.r = d__1 + c__->r, z__5.i = c__->i;
		    z_sqrt(&z__4, &z__5);
		    z__3.r = b + z__4.r, z__3.i = z__4.i;
		    z_div(&z__1, &z__2, &z__3);
		    t = z__1.r;
		} else {
		    latime_1.ops += 5;
		    d__1 = b * b;
		    z__3.r = d__1 + c__->r, z__3.i = c__->i;
		    z_sqrt(&z__2, &z__3);
		    z__1.r = b - z__2.r, z__1.i = -z__2.i;
		    t = z__1.r;
		}
		latime_1.ops += 5;
		z__3.r = alpha.r / absest, z__3.i = alpha.i / absest;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		z__1.r = z__2.r / t, z__1.i = z__2.i / t;
		sine.r = z__1.r, sine.i = z__1.i;
		z__3.r = gamma->r / absest, z__3.i = gamma->i / absest;
		z__2.r = -z__3.r, z__2.i = -z__3.i;
		d__1 = t + 1.;
		z__1.r = z__2.r / d__1, z__1.i = z__2.i / d__1;
		cosine.r = z__1.r, cosine.i = z__1.i;
		*sestpr = sqrt(t + 1. + eps * 4. * eps * norma) * absest;
	    }
	    latime_1.ops += 40;
	    d_cnjg(&z__4, &sine);
	    z__3.r = sine.r * z__4.r - sine.i * z__4.i, z__3.i = sine.r * 
		    z__4.i + sine.i * z__4.r;
	    d_cnjg(&z__6, &cosine);
	    z__5.r = cosine.r * z__6.r - cosine.i * z__6.i, z__5.i = cosine.r 
		    * z__6.i + cosine.i * z__6.r;
	    z__2.r = z__3.r + z__5.r, z__2.i = z__3.i + z__5.i;
	    z_sqrt(&z__1, &z__2);
	    tmp = z__1.r;
	    z__1.r = sine.r / tmp, z__1.i = sine.i / tmp;
	    s->r = z__1.r, s->i = z__1.i;
	    z__1.r = cosine.r / tmp, z__1.i = cosine.i / tmp;
	    c__->r = z__1.r, c__->i = z__1.i;
	    return 0;

	}
    }
    return 0;

/*     End of ZLAIC1 */

} /* zlaic1_ */

