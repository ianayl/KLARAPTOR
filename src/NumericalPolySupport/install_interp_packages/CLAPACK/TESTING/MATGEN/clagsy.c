#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static complex c_b1 = {0.f,0.f};
static complex c_b2 = {1.f,0.f};
static integer c__3 = 3;
static integer c__1 = 1;

/* Subroutine */ int clagsy_(integer *n, integer *k, real *d__, complex *a, 
	integer *lda, integer *iseed, complex *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7, i__8, 
	    i__9;
    real r__1;
    complex q__1, q__2, q__3, q__4;

    /* Builtin functions */
    double c_abs(complex *);
    void c_div(complex *, complex *, complex *);

    /* Local variables */
    static integer i__, j;
    extern /* Subroutine */ int cgerc_(integer *, integer *, complex *, 
	    complex *, integer *, complex *, integer *, complex *, integer *);
    static complex alpha;
    extern /* Subroutine */ int cscal_(integer *, complex *, complex *, 
	    integer *);
    extern /* Complex */ VOID cdotc_(complex *, integer *, complex *, integer 
	    *, complex *, integer *);
    extern /* Subroutine */ int cgemv_(char *, integer *, integer *, complex *
	    , complex *, integer *, complex *, integer *, complex *, complex *
	    , integer *), caxpy_(integer *, complex *, complex *, 
	    integer *, complex *, integer *), csymv_(char *, integer *, 
	    complex *, complex *, integer *, complex *, integer *, complex *, 
	    complex *, integer *);
    extern doublereal scnrm2_(integer *, complex *, integer *);
    static integer ii, jj;
    static complex wa, wb;
    extern /* Subroutine */ int clacgv_(integer *, complex *, integer *);
    static real wn;
    extern /* Subroutine */ int xerbla_(char *, integer *), clarnv_(
	    integer *, integer *, integer *, complex *);
    static complex tau;


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]


/*  -- LAPACK auxiliary test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    CLAGSY generates a complex symmetric matrix A, by pre- and post-   
    multiplying a real diagonal matrix D with a random unitary matrix:   
    A = U*D*U**T. The semi-bandwidth may then be reduced to k by   
    additional unitary transformations.   

    Arguments   
    =========   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    K       (input) INTEGER   
            The number of nonzero subdiagonals within the band of A.   
            0 <= K <= N-1.   

    D       (input) REAL array, dimension (N)   
            The diagonal elements of the diagonal matrix D.   

    A       (output) COMPLEX array, dimension (LDA,N)   
            The generated n by n symmetric matrix A (the full matrix is   
            stored).   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= N.   

    ISEED   (input/output) INTEGER array, dimension (4)   
            On entry, the seed of the random number generator; the array   
            elements must be between 0 and 4095, and ISEED(4) must be   
            odd.   
            On exit, the seed is updated.   

    WORK    (workspace) COMPLEX array, dimension (2*N)   

    INFO    (output) INTEGER   
            = 0: successful exit   
            < 0: if INFO = -i, the i-th argument had an illegal value   

    =====================================================================   


       Test the input arguments   

       Parameter adjustments */
    --d__;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --iseed;
    --work;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -1;
    } else if (*k < 0 || *k > *n - 1) {
	*info = -2;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    }
    if (*info < 0) {
	i__1 = -(*info);
	xerbla_("CLAGSY", &i__1);
	return 0;
    }

/*     initialize lower triangle of A to diagonal matrix */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n;
	for (i__ = j + 1; i__ <= i__2; ++i__) {
	    i__3 = a_subscr(i__, j);
	    a[i__3].r = 0.f, a[i__3].i = 0.f;
/* L10: */
	}
/* L20: */
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = a_subscr(i__, i__);
	i__3 = i__;
	a[i__2].r = d__[i__3], a[i__2].i = 0.f;
/* L30: */
    }

/*     Generate lower triangle of symmetric matrix */

    for (i__ = *n - 1; i__ >= 1; --i__) {

/*        generate random reflection */

	i__1 = *n - i__ + 1;
	clarnv_(&c__3, &iseed[1], &i__1, &work[1]);
	i__1 = *n - i__ + 1;
	wn = scnrm2_(&i__1, &work[1], &c__1);
	r__1 = wn / c_abs(&work[1]);
	q__1.r = r__1 * work[1].r, q__1.i = r__1 * work[1].i;
	wa.r = q__1.r, wa.i = q__1.i;
	if (wn == 0.f) {
	    tau.r = 0.f, tau.i = 0.f;
	} else {
	    q__1.r = work[1].r + wa.r, q__1.i = work[1].i + wa.i;
	    wb.r = q__1.r, wb.i = q__1.i;
	    i__1 = *n - i__;
	    c_div(&q__1, &c_b2, &wb);
	    cscal_(&i__1, &q__1, &work[2], &c__1);
	    work[1].r = 1.f, work[1].i = 0.f;
	    c_div(&q__1, &wb, &wa);
	    r__1 = q__1.r;
	    tau.r = r__1, tau.i = 0.f;
	}

/*        apply random reflection to A(i:n,i:n) from the left   
          and the right   

          compute  y := tau * A * conjg(u) */

	i__1 = *n - i__ + 1;
	clacgv_(&i__1, &work[1], &c__1);
	i__1 = *n - i__ + 1;
	csymv_("Lower", &i__1, &tau, &a_ref(i__, i__), lda, &work[1], &c__1, &
		c_b1, &work[*n + 1], &c__1);
	i__1 = *n - i__ + 1;
	clacgv_(&i__1, &work[1], &c__1);

/*        compute  v := y - 1/2 * tau * ( u, y ) * u */

	q__3.r = -.5f, q__3.i = 0.f;
	q__2.r = q__3.r * tau.r - q__3.i * tau.i, q__2.i = q__3.r * tau.i + 
		q__3.i * tau.r;
	i__1 = *n - i__ + 1;
	cdotc_(&q__4, &i__1, &work[1], &c__1, &work[*n + 1], &c__1);
	q__1.r = q__2.r * q__4.r - q__2.i * q__4.i, q__1.i = q__2.r * q__4.i 
		+ q__2.i * q__4.r;
	alpha.r = q__1.r, alpha.i = q__1.i;
	i__1 = *n - i__ + 1;
	caxpy_(&i__1, &alpha, &work[1], &c__1, &work[*n + 1], &c__1);

/*        apply the transformation as a rank-2 update to A(i:n,i:n)   

          CALL CSYR2( 'Lower', N-I+1, -ONE, WORK, 1, WORK( N+1 ), 1,   
          $               A( I, I ), LDA ) */

	i__1 = *n;
	for (jj = i__; jj <= i__1; ++jj) {
	    i__2 = *n;
	    for (ii = jj; ii <= i__2; ++ii) {
		i__3 = a_subscr(ii, jj);
		i__4 = a_subscr(ii, jj);
		i__5 = ii - i__ + 1;
		i__6 = *n + jj - i__ + 1;
		q__3.r = work[i__5].r * work[i__6].r - work[i__5].i * work[
			i__6].i, q__3.i = work[i__5].r * work[i__6].i + work[
			i__5].i * work[i__6].r;
		q__2.r = a[i__4].r - q__3.r, q__2.i = a[i__4].i - q__3.i;
		i__7 = *n + ii - i__ + 1;
		i__8 = jj - i__ + 1;
		q__4.r = work[i__7].r * work[i__8].r - work[i__7].i * work[
			i__8].i, q__4.i = work[i__7].r * work[i__8].i + work[
			i__7].i * work[i__8].r;
		q__1.r = q__2.r - q__4.r, q__1.i = q__2.i - q__4.i;
		a[i__3].r = q__1.r, a[i__3].i = q__1.i;
/* L40: */
	    }
/* L50: */
	}
/* L60: */
    }

/*     Reduce number of subdiagonals to K */

    i__1 = *n - 1 - *k;
    for (i__ = 1; i__ <= i__1; ++i__) {

/*        generate reflection to annihilate A(k+i+1:n,i) */

	i__2 = *n - *k - i__ + 1;
	wn = scnrm2_(&i__2, &a_ref(*k + i__, i__), &c__1);
	r__1 = wn / c_abs(&a_ref(*k + i__, i__));
	i__2 = a_subscr(*k + i__, i__);
	q__1.r = r__1 * a[i__2].r, q__1.i = r__1 * a[i__2].i;
	wa.r = q__1.r, wa.i = q__1.i;
	if (wn == 0.f) {
	    tau.r = 0.f, tau.i = 0.f;
	} else {
	    i__2 = a_subscr(*k + i__, i__);
	    q__1.r = a[i__2].r + wa.r, q__1.i = a[i__2].i + wa.i;
	    wb.r = q__1.r, wb.i = q__1.i;
	    i__2 = *n - *k - i__;
	    c_div(&q__1, &c_b2, &wb);
	    cscal_(&i__2, &q__1, &a_ref(*k + i__ + 1, i__), &c__1);
	    i__2 = a_subscr(*k + i__, i__);
	    a[i__2].r = 1.f, a[i__2].i = 0.f;
	    c_div(&q__1, &wb, &wa);
	    r__1 = q__1.r;
	    tau.r = r__1, tau.i = 0.f;
	}

/*        apply reflection to A(k+i:n,i+1:k+i-1) from the left */

	i__2 = *n - *k - i__ + 1;
	i__3 = *k - 1;
	cgemv_("Conjugate transpose", &i__2, &i__3, &c_b2, &a_ref(*k + i__, 
		i__ + 1), lda, &a_ref(*k + i__, i__), &c__1, &c_b1, &work[1], 
		&c__1);
	i__2 = *n - *k - i__ + 1;
	i__3 = *k - 1;
	q__1.r = -tau.r, q__1.i = -tau.i;
	cgerc_(&i__2, &i__3, &q__1, &a_ref(*k + i__, i__), &c__1, &work[1], &
		c__1, &a_ref(*k + i__, i__ + 1), lda);

/*        apply reflection to A(k+i:n,k+i:n) from the left and the right   

          compute  y := tau * A * conjg(u) */

	i__2 = *n - *k - i__ + 1;
	clacgv_(&i__2, &a_ref(*k + i__, i__), &c__1);
	i__2 = *n - *k - i__ + 1;
	csymv_("Lower", &i__2, &tau, &a_ref(*k + i__, *k + i__), lda, &a_ref(*
		k + i__, i__), &c__1, &c_b1, &work[1], &c__1);
	i__2 = *n - *k - i__ + 1;
	clacgv_(&i__2, &a_ref(*k + i__, i__), &c__1);

/*        compute  v := y - 1/2 * tau * ( u, y ) * u */

	q__3.r = -.5f, q__3.i = 0.f;
	q__2.r = q__3.r * tau.r - q__3.i * tau.i, q__2.i = q__3.r * tau.i + 
		q__3.i * tau.r;
	i__2 = *n - *k - i__ + 1;
	cdotc_(&q__4, &i__2, &a_ref(*k + i__, i__), &c__1, &work[1], &c__1);
	q__1.r = q__2.r * q__4.r - q__2.i * q__4.i, q__1.i = q__2.r * q__4.i 
		+ q__2.i * q__4.r;
	alpha.r = q__1.r, alpha.i = q__1.i;
	i__2 = *n - *k - i__ + 1;
	caxpy_(&i__2, &alpha, &a_ref(*k + i__, i__), &c__1, &work[1], &c__1);

/*        apply symmetric rank-2 update to A(k+i:n,k+i:n)   

          CALL CSYR2( 'Lower', N-K-I+1, -ONE, A( K+I, I ), 1, WORK, 1,   
          $               A( K+I, K+I ), LDA ) */

	i__2 = *n;
	for (jj = *k + i__; jj <= i__2; ++jj) {
	    i__3 = *n;
	    for (ii = jj; ii <= i__3; ++ii) {
		i__4 = a_subscr(ii, jj);
		i__5 = a_subscr(ii, jj);
		i__6 = a_subscr(ii, i__);
		i__7 = jj - *k - i__ + 1;
		q__3.r = a[i__6].r * work[i__7].r - a[i__6].i * work[i__7].i, 
			q__3.i = a[i__6].r * work[i__7].i + a[i__6].i * work[
			i__7].r;
		q__2.r = a[i__5].r - q__3.r, q__2.i = a[i__5].i - q__3.i;
		i__8 = ii - *k - i__ + 1;
		i__9 = a_subscr(jj, i__);
		q__4.r = work[i__8].r * a[i__9].r - work[i__8].i * a[i__9].i, 
			q__4.i = work[i__8].r * a[i__9].i + work[i__8].i * a[
			i__9].r;
		q__1.r = q__2.r - q__4.r, q__1.i = q__2.i - q__4.i;
		a[i__4].r = q__1.r, a[i__4].i = q__1.i;
/* L70: */
	    }
/* L80: */
	}

	i__2 = a_subscr(*k + i__, i__);
	q__1.r = -wa.r, q__1.i = -wa.i;
	a[i__2].r = q__1.r, a[i__2].i = q__1.i;
	i__2 = *n;
	for (j = *k + i__ + 1; j <= i__2; ++j) {
	    i__3 = a_subscr(j, i__);
	    a[i__3].r = 0.f, a[i__3].i = 0.f;
/* L90: */
	}
/* L100: */
    }

/*     Store full symmetric matrix */

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n;
	for (i__ = j + 1; i__ <= i__2; ++i__) {
	    i__3 = a_subscr(j, i__);
	    i__4 = a_subscr(i__, j);
	    a[i__3].r = a[i__4].r, a[i__3].i = a[i__4].i;
/* L110: */
	}
/* L120: */
    }
    return 0;

/*     End of CLAGSY */

} /* clagsy_ */

#undef a_ref
#undef a_subscr


