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
static integer c__0 = 0;

/* Subroutine */ int slasq1_(integer *n, real *d__, real *e, real *work, 
	integer *info)
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2, r__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    extern /* Subroutine */ int slas2_(real *, real *, real *, real *, real *)
	    ;
    static integer i__;
    static real scale;
    static integer iinfo;
    static real sigmn, sigmx;
    extern /* Subroutine */ int scopy_(integer *, real *, integer *, real *, 
	    integer *), slasq2_(integer *, real *, integer *);
    extern doublereal slamch_(char *);
    static real safmin;
    extern /* Subroutine */ int xerbla_(char *, integer *), slascl_(
	    char *, integer *, integer *, real *, real *, integer *, integer *
	    , real *, integer *, integer *), slasrt_(char *, integer *
	    , real *, integer *);
    static real eps;


/*  -- LAPACK routine (instrumented to count ops, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1999   


    Purpose   
    =======   

    SLASQ1 computes the singular values of a real N-by-N bidiagonal   
    matrix with diagonal D and off-diagonal E. The singular values   
    are computed to high relative accuracy, in the absence of   
    denormalization, underflow and overflow. The algorithm was first   
    presented in   

    "Accurate singular values and differential qd algorithms" by K. V.   
    Fernando and B. N. Parlett, Numer. Math., Vol-67, No. 2, pp. 191-230,   
    1994,   

    and the present implementation is described in "An implementation of   
    the dqds Algorithm (Positive Case)", LAPACK Working Note.   

    Arguments   
    =========   

    N     (input) INTEGER   
          The number of rows and columns in the matrix. N >= 0.   

    D     (input/output) REAL array, dimension (N)   
          On entry, D contains the diagonal elements of the   
          bidiagonal matrix whose SVD is desired. On normal exit,   
          D contains the singular values in decreasing order.   

    E     (input/output) REAL array, dimension (N)   
          On entry, elements E(1:N-1) contain the off-diagonal elements   
          of the bidiagonal matrix whose SVD is desired.   
          On exit, E is overwritten.   

    WORK  (workspace) REAL array, dimension (4*N)   

    INFO  (output) INTEGER   
          = 0: successful exit   
          < 0: if INFO = -i, the i-th argument had an illegal value   
          > 0: the algorithm failed   
               = 1, a split was marked by a positive value in E   
               = 2, current block of Z not diagonalized after 30*N   
                    iterations (in inner while loop)   
               = 3, termination criterion of outer while loop not met   
                    (program created more than N unreduced blocks)   

    =====================================================================   


       Parameter adjustments */
    --work;
    --e;
    --d__;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -2;
	i__1 = -(*info);
	xerbla_("SLASQ1", &i__1);
	return 0;
    } else if (*n == 0) {
	return 0;
    } else if (*n == 1) {
	d__[1] = dabs(d__[1]);
	return 0;
    } else if (*n == 2) {
	slas2_(&d__[1], &e[1], &d__[2], &sigmn, &sigmx);
	d__[1] = sigmx;
	d__[2] = sigmn;
	return 0;
    }

/*     Estimate the largest singular value. */

    sigmx = 0.f;
    i__1 = *n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	d__[i__] = (r__1 = d__[i__], dabs(r__1));
/* Computing MAX */
	r__2 = sigmx, r__3 = (r__1 = e[i__], dabs(r__1));
	sigmx = dmax(r__2,r__3);
/* L10: */
    }
    d__[*n] = (r__1 = d__[*n], dabs(r__1));

/*     Early return if SIGMX is zero (matrix is already diagonal). */

    if (sigmx == 0.f) {
	slasrt_("D", n, &d__[1], &iinfo);
	return 0;
    }

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	r__1 = sigmx, r__2 = d__[i__];
	sigmx = dmax(r__1,r__2);
/* L20: */
    }

/*     Copy D and E into WORK (in the Z format) and scale (squaring the   
       input data makes scaling by a power of the radix pointless). */

    latime_1.ops += (real) ((*n << 1) + 1);
    eps = slamch_("Precision");
    safmin = slamch_("Safe minimum");
    scale = sqrt(eps / safmin);
    scopy_(n, &d__[1], &c__1, &work[1], &c__2);
    i__1 = *n - 1;
    scopy_(&i__1, &e[1], &c__1, &work[2], &c__2);
    i__1 = (*n << 1) - 1;
    i__2 = (*n << 1) - 1;
    slascl_("G", &c__0, &c__0, &sigmx, &scale, &i__1, &c__1, &work[1], &i__2, 
	    &iinfo);

/*     Compute the q's and e's. */

    latime_1.ops += (real) ((*n << 1) - 1);
    i__1 = (*n << 1) - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing 2nd power */
	r__1 = work[i__];
	work[i__] = r__1 * r__1;
/* L30: */
    }
    work[*n * 2] = 0.f;

    slasq2_(n, &work[1], info);

    if (*info == 0) {
	latime_1.ops += (real) (*n << 1);
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d__[i__] = sqrt(work[i__]);
/* L40: */
	}
	slascl_("G", &c__0, &c__0, &scale, &sigmx, n, &c__1, &d__[1], n, &
		iinfo);
    }

    return 0;

/*     End of SLASQ1 */

} /* slasq1_ */

