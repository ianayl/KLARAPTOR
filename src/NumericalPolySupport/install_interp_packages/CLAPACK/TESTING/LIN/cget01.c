#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static complex c_b1 = {1.f,0.f};
static integer c__1 = 1;
static integer c_n1 = -1;

/* Subroutine */ int cget01_(integer *m, integer *n, complex *a, integer *lda,
	 complex *afac, integer *ldafac, integer *ipiv, real *rwork, real *
	resid)
{
    /* System generated locals */
    integer a_dim1, a_offset, afac_dim1, afac_offset, i__1, i__2, i__3, i__4, 
	    i__5;
    complex q__1, q__2;

    /* Local variables */
    static integer i__, j, k;
    static complex t;
    extern /* Subroutine */ int cscal_(integer *, complex *, complex *, 
	    integer *), cgemv_(char *, integer *, integer *, complex *, 
	    complex *, integer *, complex *, integer *, complex *, complex *, 
	    integer *);
    static real anorm;
    extern /* Complex */ VOID cdotu_(complex *, integer *, complex *, integer 
	    *, complex *, integer *);
    extern /* Subroutine */ int ctrmv_(char *, char *, char *, integer *, 
	    complex *, integer *, complex *, integer *);
    extern doublereal clange_(char *, integer *, integer *, complex *, 
	    integer *, real *), slamch_(char *);
    extern /* Subroutine */ int claswp_(integer *, complex *, integer *, 
	    integer *, integer *, integer *, integer *);
    static real eps;


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define afac_subscr(a_1,a_2) (a_2)*afac_dim1 + a_1
#define afac_ref(a_1,a_2) afac[afac_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    CGET01 reconstructs a matrix A from its L*U factorization and   
    computes the residual   
       norm(L*U - A) / ( N * norm(A) * EPS ),   
    where EPS is the machine epsilon.   

    Arguments   
    ==========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input) COMPLEX array, dimension (LDA,N)   
            The original M x N matrix A.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    AFAC    (input/output) COMPLEX array, dimension (LDAFAC,N)   
            The factored form of the matrix A.  AFAC contains the factors   
            L and U from the L*U factorization as computed by CGETRF.   
            Overwritten with the reconstructed matrix, and then with the   
            difference L*U - A.   

    LDAFAC  (input) INTEGER   
            The leading dimension of the array AFAC.  LDAFAC >= max(1,M).   

    IPIV    (input) INTEGER array, dimension (N)   
            The pivot indices from CGETRF.   

    RWORK   (workspace) REAL array, dimension (M)   

    RESID   (output) REAL   
            norm(L*U - A) / ( N * norm(A) * EPS )   

    =====================================================================   


       Quick exit if M = 0 or N = 0.   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    afac_dim1 = *ldafac;
    afac_offset = 1 + afac_dim1 * 1;
    afac -= afac_offset;
    --ipiv;
    --rwork;

    /* Function Body */
    if (*m <= 0 || *n <= 0) {
	*resid = 0.f;
	return 0;
    }

/*     Determine EPS and the norm of A. */

    eps = slamch_("Epsilon");
    anorm = clange_("1", m, n, &a[a_offset], lda, &rwork[1]);

/*     Compute the product L*U and overwrite AFAC with the result.   
       A column at a time of the product is obtained, starting with   
       column N. */

    for (k = *n; k >= 1; --k) {
	if (k > *m) {
	    ctrmv_("Lower", "No transpose", "Unit", m, &afac[afac_offset], 
		    ldafac, &afac_ref(1, k), &c__1);
	} else {

/*           Compute elements (K+1:M,K) */

	    i__1 = afac_subscr(k, k);
	    t.r = afac[i__1].r, t.i = afac[i__1].i;
	    if (k + 1 <= *m) {
		i__1 = *m - k;
		cscal_(&i__1, &t, &afac_ref(k + 1, k), &c__1);
		i__1 = *m - k;
		i__2 = k - 1;
		cgemv_("No transpose", &i__1, &i__2, &c_b1, &afac_ref(k + 1, 
			1), ldafac, &afac_ref(1, k), &c__1, &c_b1, &afac_ref(
			k + 1, k), &c__1);
	    }

/*           Compute the (K,K) element */

	    i__1 = afac_subscr(k, k);
	    i__2 = k - 1;
	    cdotu_(&q__2, &i__2, &afac_ref(k, 1), ldafac, &afac_ref(1, k), &
		    c__1);
	    q__1.r = t.r + q__2.r, q__1.i = t.i + q__2.i;
	    afac[i__1].r = q__1.r, afac[i__1].i = q__1.i;

/*           Compute elements (1:K-1,K) */

	    i__1 = k - 1;
	    ctrmv_("Lower", "No transpose", "Unit", &i__1, &afac[afac_offset],
		     ldafac, &afac_ref(1, k), &c__1);
	}
/* L10: */
    }
    i__1 = min(*m,*n);
    claswp_(n, &afac[afac_offset], ldafac, &c__1, &i__1, &ipiv[1], &c_n1);

/*     Compute the difference  L*U - A  and store in AFAC. */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = afac_subscr(i__, j);
	    i__4 = afac_subscr(i__, j);
	    i__5 = a_subscr(i__, j);
	    q__1.r = afac[i__4].r - a[i__5].r, q__1.i = afac[i__4].i - a[i__5]
		    .i;
	    afac[i__3].r = q__1.r, afac[i__3].i = q__1.i;
/* L20: */
	}
/* L30: */
    }

/*     Compute norm( L*U - A ) / ( N * norm(A) * EPS ) */

    *resid = clange_("1", m, n, &afac[afac_offset], ldafac, &rwork[1]);

    if (anorm <= 0.f) {
	if (*resid != 0.f) {
	    *resid = 1.f / eps;
	}
    } else {
	*resid = *resid / (real) (*n) / anorm / eps;
    }

    return 0;

/*     End of CGET01 */

} /* cget01_ */

#undef afac_ref
#undef afac_subscr
#undef a_ref
#undef a_subscr


