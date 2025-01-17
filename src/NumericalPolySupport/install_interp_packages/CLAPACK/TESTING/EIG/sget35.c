#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__6 = 6;
static real c_b35 = 1.f;

/* Subroutine */ int sget35_(real *rmax, integer *lmax, integer *ninfo, 
	integer *knt)
{
    /* Initialized data */

    static integer idim[8] = { 1,2,3,4,3,3,6,4 };
    static integer ival[288]	/* was [6][6][8] */ = { 1,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,-2,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
	    0,0,5,1,2,0,0,0,-8,-2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    3,4,0,0,0,0,-5,3,0,0,0,0,1,2,1,4,0,0,-3,-9,-1,1,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,1,0,0,0,0,0,2,3,0,0,0,0,5,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,3,-4,0,0,0,2,5,2,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,-2,0,0,0,0,0,5,6,3,4,0,0,-1,
	    -9,-5,2,0,0,8,8,8,8,5,6,9,9,9,9,-7,5,1,0,0,0,0,0,1,5,2,0,0,0,2,
	    -21,5,0,0,0,1,2,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2, r__3;

    /* Builtin functions */
    double sqrt(doublereal), sin(doublereal);

    /* Local variables */
    static integer info;
    static real cnrm;
    static integer isgn;
    static real rmul, tnrm, xnrm, a[36]	/* was [6][6] */, b[36]	/* was [6][6] 
	    */, c__[36]	/* was [6][6] */;
    static integer i__, j, m, n;
    static real scale;
    static char trana[1], tranb[1];
    extern /* Subroutine */ int sgemm_(char *, char *, integer *, integer *, 
	    integer *, real *, real *, integer *, real *, integer *, real *, 
	    real *, integer *);
    static integer imlda1, imlda2, imldb1;
    static real cc[36]	/* was [6][6] */;
    extern /* Subroutine */ int slabad_(real *, real *);
    extern doublereal slamch_(char *), slange_(char *, integer *, 
	    integer *, real *, integer *, real *);
    static integer imloff, itrana, itranb;
    static real bignum, smlnum, vm1[3], vm2[3];
    extern /* Subroutine */ int strsyl_(char *, char *, integer *, integer *, 
	    integer *, real *, integer *, real *, integer *, real *, integer *
	    , real *, integer *);
    static integer ima, imb;
    static real dum[1], eps, res, res1;


#define ival_ref(a_1,a_2,a_3) ival[((a_3)*6 + (a_2))*6 + a_1 - 43]
#define a_ref(a_1,a_2) a[(a_2)*6 + a_1 - 7]
#define b_ref(a_1,a_2) b[(a_2)*6 + a_1 - 7]
#define c___ref(a_1,a_2) c__[(a_2)*6 + a_1 - 7]
#define cc_ref(a_1,a_2) cc[(a_2)*6 + a_1 - 7]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    SGET35 tests STRSYL, a routine for solving the Sylvester matrix   
    equation   

       op(A)*X + ISGN*X*op(B) = scale*C,   

    A and B are assumed to be in Schur canonical form, op() represents an   
    optional transpose, and ISGN can be -1 or +1.  Scale is an output   
    less than or equal to 1, chosen to avoid overflow in X.   

    The test code verifies that the following residual is order 1:   

       norm(op(A)*X + ISGN*X*op(B) - scale*C) /   
           (EPS*max(norm(A),norm(B))*norm(X))   

    Arguments   
    ==========   

    RMAX    (output) REAL   
            Value of the largest test ratio.   

    LMAX    (output) INTEGER   
            Example number where largest test ratio achieved.   

    NINFO   (output) INTEGER   
            Number of examples where INFO is nonzero.   

    KNT     (output) INTEGER   
            Total number of examples tested.   

    =====================================================================   


       Get machine parameters */

    eps = slamch_("P");
    smlnum = slamch_("S") * 4.f / eps;
    bignum = 1.f / smlnum;
    slabad_(&smlnum, &bignum);

/*     Set up test case parameters */

    vm1[0] = sqrt(smlnum);
    vm1[1] = 1.f;
    vm1[2] = sqrt(bignum);
    vm2[0] = 1.f;
    vm2[1] = eps * 2.f + 1.f;
    vm2[2] = 2.f;

    *knt = 0;
    *ninfo = 0;
    *lmax = 0;
    *rmax = 0.f;

/*     Begin test loop */

    for (itrana = 1; itrana <= 2; ++itrana) {
	for (itranb = 1; itranb <= 2; ++itranb) {
	    for (isgn = -1; isgn <= 1; isgn += 2) {
		for (ima = 1; ima <= 8; ++ima) {
		    for (imlda1 = 1; imlda1 <= 3; ++imlda1) {
			for (imlda2 = 1; imlda2 <= 3; ++imlda2) {
			    for (imloff = 1; imloff <= 2; ++imloff) {
				for (imb = 1; imb <= 8; ++imb) {
				    for (imldb1 = 1; imldb1 <= 3; ++imldb1) {
					if (itrana == 1) {
					    *(unsigned char *)trana = 'N';
					}
					if (itrana == 2) {
					    *(unsigned char *)trana = 'T';
					}
					if (itranb == 1) {
					    *(unsigned char *)tranb = 'N';
					}
					if (itranb == 2) {
					    *(unsigned char *)tranb = 'T';
					}
					m = idim[ima - 1];
					n = idim[imb - 1];
					tnrm = 0.f;
					i__1 = m;
					for (i__ = 1; i__ <= i__1; ++i__) {
					    i__2 = m;
					    for (j = 1; j <= i__2; ++j) {
			  a_ref(i__, j) = (real) ival_ref(i__, j, ima);
			  if ((i__3 = i__ - j, abs(i__3)) <= 1) {
			      a_ref(i__, j) = a_ref(i__, j) * vm1[imlda1 - 1];
			      a_ref(i__, j) = a_ref(i__, j) * vm2[imlda2 - 1];
			  } else {
			      a_ref(i__, j) = a_ref(i__, j) * vm1[imloff - 1];
			  }
/* Computing MAX */
			  r__2 = tnrm, r__3 = (r__1 = a_ref(i__, j), dabs(
				  r__1));
			  tnrm = dmax(r__2,r__3);
/* L10: */
					    }
/* L20: */
					}
					i__1 = n;
					for (i__ = 1; i__ <= i__1; ++i__) {
					    i__2 = n;
					    for (j = 1; j <= i__2; ++j) {
			  b_ref(i__, j) = (real) ival_ref(i__, j, imb);
			  if ((i__3 = i__ - j, abs(i__3)) <= 1) {
			      b_ref(i__, j) = b_ref(i__, j) * vm1[imldb1 - 1];
			  } else {
			      b_ref(i__, j) = b_ref(i__, j) * vm1[imloff - 1];
			  }
/* Computing MAX */
			  r__2 = tnrm, r__3 = (r__1 = b_ref(i__, j), dabs(
				  r__1));
			  tnrm = dmax(r__2,r__3);
/* L30: */
					    }
/* L40: */
					}
					cnrm = 0.f;
					i__1 = m;
					for (i__ = 1; i__ <= i__1; ++i__) {
					    i__2 = n;
					    for (j = 1; j <= i__2; ++j) {
			  c___ref(i__, j) = sin((real) (i__ * j));
/* Computing MAX */
			  r__1 = cnrm, r__2 = c___ref(i__, j);
			  cnrm = dmax(r__1,r__2);
			  cc_ref(i__, j) = c___ref(i__, j);
/* L50: */
					    }
/* L60: */
					}
					++(*knt);
					strsyl_(trana, tranb, &isgn, &m, &n, 
						a, &c__6, b, &c__6, c__, &
						c__6, &scale, &info);
					if (info != 0) {
					    ++(*ninfo);
					}
					xnrm = slange_("M", &m, &n, c__, &
						c__6, dum);
					rmul = 1.f;
					if (xnrm > 1.f && tnrm > 1.f) {
					    if (xnrm > bignum / tnrm) {
			  rmul = 1.f / dmax(xnrm,tnrm);
					    }
					}
					r__1 = -scale * rmul;
					sgemm_(trana, "N", &m, &n, &m, &rmul, 
						a, &c__6, c__, &c__6, &r__1, 
						cc, &c__6);
					r__1 = (real) isgn * rmul;
					sgemm_("N", tranb, &m, &n, &n, &r__1, 
						c__, &c__6, b, &c__6, &c_b35, 
						cc, &c__6);
					res1 = slange_("M", &m, &n, cc, &c__6,
						 dum);
/* Computing MAX */
					r__1 = smlnum, r__2 = smlnum * xnrm, 
						r__1 = max(r__1,r__2), r__2 = 
						rmul * tnrm * eps * xnrm;
					res = res1 / dmax(r__1,r__2);
					if (res > *rmax) {
					    *lmax = *knt;
					    *rmax = res;
					}
/* L70: */
				    }
/* L80: */
				}
/* L90: */
			    }
/* L100: */
			}
/* L110: */
		    }
/* L120: */
		}
/* L130: */
	    }
/* L140: */
	}
/* L150: */
    }

    return 0;

/*     End of SGET35 */

} /* sget35_ */

#undef cc_ref
#undef c___ref
#undef b_ref
#undef a_ref
#undef ival_ref


