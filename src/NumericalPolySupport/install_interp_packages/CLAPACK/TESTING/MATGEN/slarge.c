#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__3 = 3;
static integer c__1 = 1;
static real c_b8 = 1.f;
static real c_b10 = 0.f;

/* Subroutine */ int slarge_(integer *n, real *a, integer *lda, integer *
	iseed, real *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1;
    real r__1;

    /* Builtin functions */
    double r_sign(real *, real *);

    /* Local variables */
    extern /* Subroutine */ int sger_(integer *, integer *, real *, real *, 
	    integer *, real *, integer *, real *, integer *);
    extern doublereal snrm2_(integer *, real *, integer *);
    static integer i__;
    extern /* Subroutine */ int sscal_(integer *, real *, real *, integer *), 
	    sgemv_(char *, integer *, integer *, real *, real *, integer *, 
	    real *, integer *, real *, real *, integer *);
    static real wa, wb, wn;
    extern /* Subroutine */ int xerbla_(char *, integer *), slarnv_(
	    integer *, integer *, integer *, real *);
    static real tau;


#define a_ref(a_1,a_2) a[(a_2)*a_dim1 + a_1]


/*  -- LAPACK auxiliary test routine (version 3.0)   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    SLARGE pre- and post-multiplies a real general n by n matrix A   
    with a random orthogonal matrix: A = U*D*U'.   

    Arguments   
    =========   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    A       (input/output) REAL array, dimension (LDA,N)   
            On entry, the original n by n matrix A.   
            On exit, A is overwritten by U*A*U' for some random   
            orthogonal matrix U.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= N.   

    ISEED   (input/output) INTEGER array, dimension (4)   
            On entry, the seed of the random number generator; the array   
            elements must be between 0 and 4095, and ISEED(4) must be   
            odd.   
            On exit, the seed is updated.   

    WORK    (workspace) REAL array, dimension (2*N)   

    INFO    (output) INTEGER   
            = 0: successful exit   
            < 0: if INFO = -i, the i-th argument had an illegal value   

    =====================================================================   


       Test the input arguments   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --iseed;
    --work;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -1;
    } else if (*lda < max(1,*n)) {
	*info = -3;
    }
    if (*info < 0) {
	i__1 = -(*info);
	xerbla_("SLARGE", &i__1);
	return 0;
    }

/*     pre- and post-multiply A by random orthogonal matrix */

    for (i__ = *n; i__ >= 1; --i__) {

/*        generate random reflection */

	i__1 = *n - i__ + 1;
	slarnv_(&c__3, &iseed[1], &i__1, &work[1]);
	i__1 = *n - i__ + 1;
	wn = snrm2_(&i__1, &work[1], &c__1);
	wa = r_sign(&wn, &work[1]);
	if (wn == 0.f) {
	    tau = 0.f;
	} else {
	    wb = work[1] + wa;
	    i__1 = *n - i__;
	    r__1 = 1.f / wb;
	    sscal_(&i__1, &r__1, &work[2], &c__1);
	    work[1] = 1.f;
	    tau = wb / wa;
	}

/*        multiply A(i:n,1:n) by random reflection from the left */

	i__1 = *n - i__ + 1;
	sgemv_("Transpose", &i__1, n, &c_b8, &a_ref(i__, 1), lda, &work[1], &
		c__1, &c_b10, &work[*n + 1], &c__1);
	i__1 = *n - i__ + 1;
	r__1 = -tau;
	sger_(&i__1, n, &r__1, &work[1], &c__1, &work[*n + 1], &c__1, &a_ref(
		i__, 1), lda);

/*        multiply A(1:n,i:n) by random reflection from the right */

	i__1 = *n - i__ + 1;
	sgemv_("No transpose", n, &i__1, &c_b8, &a_ref(1, i__), lda, &work[1],
		 &c__1, &c_b10, &work[*n + 1], &c__1);
	i__1 = *n - i__ + 1;
	r__1 = -tau;
	sger_(n, &i__1, &r__1, &work[*n + 1], &c__1, &work[1], &c__1, &a_ref(
		1, i__), lda);
/* L10: */
    }
    return 0;

/*     End of SLARGE */

} /* slarge_ */

#undef a_ref


