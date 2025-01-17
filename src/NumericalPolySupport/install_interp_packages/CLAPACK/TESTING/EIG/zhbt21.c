#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublecomplex c_b1 = {0.,0.};
static doublecomplex c_b2 = {1.,0.};
static integer c__1 = 1;

/* Subroutine */ int zhbt21_(char *uplo, integer *n, integer *ka, integer *ks,
	 doublecomplex *a, integer *lda, doublereal *d__, doublereal *e, 
	doublecomplex *u, integer *ldu, doublecomplex *work, doublereal *
	rwork, doublereal *result)
{
    /* System generated locals */
    integer a_dim1, a_offset, u_dim1, u_offset, i__1, i__2, i__3, i__4;
    doublereal d__1, d__2;
    doublecomplex z__1, z__2;

    /* Local variables */
    static doublereal unfl;
    extern /* Subroutine */ int zhpr_(char *, integer *, doublereal *, 
	    doublecomplex *, integer *, doublecomplex *), zhpr2_(char 
	    *, integer *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *);
    static integer j;
    extern logical lsame_(char *, char *);
    static doublereal anorm;
    extern /* Subroutine */ int zgemm_(char *, char *, integer *, integer *, 
	    integer *, doublecomplex *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, doublecomplex *, 
	    integer *);
    static char cuplo[1];
    static logical lower;
    static doublereal wnorm;
    static integer jc;
    extern doublereal dlamch_(char *);
    static integer jr;
    extern doublereal zlanhb_(char *, char *, integer *, integer *, 
	    doublecomplex *, integer *, doublereal *), 
	    zlange_(char *, integer *, integer *, doublecomplex *, integer *, 
	    doublereal *), zlanhp_(char *, char *, integer *, 
	    doublecomplex *, doublereal *);
    static integer ika;
    static doublereal ulp;


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define u_subscr(a_1,a_2) (a_2)*u_dim1 + a_1
#define u_ref(a_1,a_2) u[u_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    ZHBT21  generally checks a decomposition of the form   

            A = U S U*   

    where * means conjugate transpose, A is hermitian banded, U is   
    unitary, and S is diagonal (if KS=0) or symmetric   
    tridiagonal (if KS=1).   

    Specifically:   

            RESULT(1) = | A - U S U* | / ( |A| n ulp ) *and*   
            RESULT(2) = | I - UU* | / ( n ulp )   

    Arguments   
    =========   

    UPLO    (input) CHARACTER   
            If UPLO='U', the upper triangle of A and V will be used and   
            the (strictly) lower triangle will not be referenced.   
            If UPLO='L', the lower triangle of A and V will be used and   
            the (strictly) upper triangle will not be referenced.   

    N       (input) INTEGER   
            The size of the matrix.  If it is zero, ZHBT21 does nothing.   
            It must be at least zero.   

    KA      (input) INTEGER   
            The bandwidth of the matrix A.  It must be at least zero.  If   
            it is larger than N-1, then max( 0, N-1 ) will be used.   

    KS      (input) INTEGER   
            The bandwidth of the matrix S.  It may only be zero or one.   
            If zero, then S is diagonal, and E is not referenced.  If   
            one, then S is symmetric tri-diagonal.   

    A       (input) COMPLEX*16 array, dimension (LDA, N)   
            The original (unfactored) matrix.  It is assumed to be   
            hermitian, and only the upper (UPLO='U') or only the lower   
            (UPLO='L') will be referenced.   

    LDA     (input) INTEGER   
            The leading dimension of A.  It must be at least 1   
            and at least min( KA, N-1 ).   

    D       (input) DOUBLE PRECISION array, dimension (N)   
            The diagonal of the (symmetric tri-) diagonal matrix S.   

    E       (input) DOUBLE PRECISION array, dimension (N-1)   
            The off-diagonal of the (symmetric tri-) diagonal matrix S.   
            E(1) is the (1,2) and (2,1) element, E(2) is the (2,3) and   
            (3,2) element, etc.   
            Not referenced if KS=0.   

    U       (input) COMPLEX*16 array, dimension (LDU, N)   
            The unitary matrix in the decomposition, expressed as a   
            dense matrix (i.e., not as a product of Householder   
            transformations, Givens transformations, etc.)   

    LDU     (input) INTEGER   
            The leading dimension of U.  LDU must be at least N and   
            at least 1.   

    WORK    (workspace) COMPLEX*16 array, dimension (N**2)   

    RWORK   (workspace) DOUBLE PRECISION array, dimension (N)   

    RESULT  (output) DOUBLE PRECISION array, dimension (2)   
            The values computed by the two tests described above.  The   
            values are currently limited to 1/ulp, to avoid overflow.   

    =====================================================================   


       Constants   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --d__;
    --e;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1 * 1;
    u -= u_offset;
    --work;
    --rwork;
    --result;

    /* Function Body */
    result[1] = 0.;
    result[2] = 0.;
    if (*n <= 0) {
	return 0;
    }

/* Computing MAX   
   Computing MIN */
    i__3 = *n - 1;
    i__1 = 0, i__2 = min(i__3,*ka);
    ika = max(i__1,i__2);

    if (lsame_(uplo, "U")) {
	lower = FALSE_;
	*(unsigned char *)cuplo = 'U';
    } else {
	lower = TRUE_;
	*(unsigned char *)cuplo = 'L';
    }

    unfl = dlamch_("Safe minimum");
    ulp = dlamch_("Epsilon") * dlamch_("Base");

/*     Some Error Checks   

       Do Test 1   

       Norm of A:   

   Computing MAX */
    d__1 = zlanhb_("1", cuplo, n, &ika, &a[a_offset], lda, &rwork[1]);
    anorm = max(d__1,unfl);

/*     Compute error matrix:    Error = A - U S U*   

       Copy A from SB to SP storage format. */

    j = 0;
    i__1 = *n;
    for (jc = 1; jc <= i__1; ++jc) {
	if (lower) {
/* Computing MIN */
	    i__3 = ika + 1, i__4 = *n + 1 - jc;
	    i__2 = min(i__3,i__4);
	    for (jr = 1; jr <= i__2; ++jr) {
		++j;
		i__3 = j;
		i__4 = a_subscr(jr, jc);
		work[i__3].r = a[i__4].r, work[i__3].i = a[i__4].i;
/* L10: */
	    }
	    i__2 = *n + 1 - jc;
	    for (jr = ika + 2; jr <= i__2; ++jr) {
		++j;
		i__3 = j;
		work[i__3].r = 0., work[i__3].i = 0.;
/* L20: */
	    }
	} else {
	    i__2 = jc;
	    for (jr = ika + 2; jr <= i__2; ++jr) {
		++j;
		i__3 = j;
		work[i__3].r = 0., work[i__3].i = 0.;
/* L30: */
	    }
/* Computing MIN */
	    i__2 = ika, i__3 = jc - 1;
	    for (jr = min(i__2,i__3); jr >= 0; --jr) {
		++j;
		i__2 = j;
		i__3 = a_subscr(ika + 1 - jr, jc);
		work[i__2].r = a[i__3].r, work[i__2].i = a[i__3].i;
/* L40: */
	    }
	}
/* L50: */
    }

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	d__1 = -d__[j];
	zhpr_(cuplo, n, &d__1, &u_ref(1, j), &c__1, &work[1]);
/* L60: */
    }

    if (*n > 1 && *ks == 1) {
	i__1 = *n - 1;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = j;
	    z__2.r = e[i__2], z__2.i = 0.;
	    z__1.r = -z__2.r, z__1.i = -z__2.i;
	    zhpr2_(cuplo, n, &z__1, &u_ref(1, j), &c__1, &u_ref(1, j + 1), &
		    c__1, &work[1]);
/* L70: */
	}
    }
    wnorm = zlanhp_("1", cuplo, n, &work[1], &rwork[1]);

    if (anorm > wnorm) {
	result[1] = wnorm / anorm / (*n * ulp);
    } else {
	if (anorm < 1.) {
/* Computing MIN */
	    d__1 = wnorm, d__2 = *n * anorm;
	    result[1] = min(d__1,d__2) / anorm / (*n * ulp);
	} else {
/* Computing MIN */
	    d__1 = wnorm / anorm, d__2 = (doublereal) (*n);
	    result[1] = min(d__1,d__2) / (*n * ulp);
	}
    }

/*     Do Test 2   

       Compute  UU* - I */

    zgemm_("N", "C", n, n, n, &c_b2, &u[u_offset], ldu, &u[u_offset], ldu, &
	    c_b1, &work[1], n);

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = (*n + 1) * (j - 1) + 1;
	i__3 = (*n + 1) * (j - 1) + 1;
	z__1.r = work[i__3].r - 1., z__1.i = work[i__3].i + 0.;
	work[i__2].r = z__1.r, work[i__2].i = z__1.i;
/* L80: */
    }

/* Computing MIN */
    d__1 = zlange_("1", n, n, &work[1], n, &rwork[1]), d__2 = (
	    doublereal) (*n);
    result[2] = min(d__1,d__2) / (*n * ulp);

    return 0;

/*     End of ZHBT21 */

} /* zhbt21_ */

#undef u_ref
#undef u_subscr
#undef a_ref
#undef a_subscr


