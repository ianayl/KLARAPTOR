#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__8 = 8;
static complex c_b6 = {0.f,0.f};
static integer c__1 = 1;
static complex c_b15 = {-1.f,0.f};

doublereal crzt01_(integer *m, integer *n, complex *a, complex *af, integer *
	lda, complex *tau, complex *work, integer *lwork)
{
    /* System generated locals */
    integer a_dim1, a_offset, af_dim1, af_offset, i__1, i__2, i__3, i__4;
    real ret_val;

    /* Local variables */
    static integer info, i__, j;
    static real norma;
    extern /* Subroutine */ int caxpy_(integer *, complex *, complex *, 
	    integer *, complex *, integer *);
    static real rwork[1];
    extern doublereal clange_(char *, integer *, integer *, complex *, 
	    integer *, real *), slamch_(char *);
    extern /* Subroutine */ int claset_(char *, integer *, integer *, complex 
	    *, complex *, complex *, integer *), xerbla_(char *, 
	    integer *), cunmrz_(char *, char *, integer *, integer *, 
	    integer *, integer *, complex *, integer *, complex *, complex *, 
	    integer *, complex *, integer *, integer *);


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define af_subscr(a_1,a_2) (a_2)*af_dim1 + a_1
#define af_ref(a_1,a_2) af[af_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    CRZT01 returns   
         || A - R*Q || / ( M * eps * ||A|| )   
    for an upper trapezoidal A that was factored with CTZRZF.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrices A and AF.   

    N       (input) INTEGER   
            The number of columns of the matrices A and AF.   

    A       (input) COMPLEX array, dimension (LDA,N)   
            The original upper trapezoidal M by N matrix A.   

    AF      (input) COMPLEX array, dimension (LDA,N)   
            The output of CTZRZF for input matrix A.   
            The lower triangle is not referenced.   

    LDA     (input) INTEGER   
            The leading dimension of the arrays A and AF.   

    TAU     (input) COMPLEX array, dimension (M)   
            Details of the  Householder transformations as returned by   
            CTZRZF.   

    WORK    (workspace) COMPLEX array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The length of the array WORK.  LWORK >= m*n + m.   

    =====================================================================   


       Parameter adjustments */
    af_dim1 = *lda;
    af_offset = 1 + af_dim1 * 1;
    af -= af_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    ret_val = 0.f;

    if (*lwork < *m * *n + *m) {
	xerbla_("CRZT01", &c__8);
	return ret_val;
    }

/*     Quick return if possible */

    if (*m <= 0 || *n <= 0) {
	return ret_val;
    }

    norma = clange_("One-norm", m, n, &a[a_offset], lda, rwork);

/*     Copy upper triangle R */

    claset_("Full", m, n, &c_b6, &c_b6, &work[1], m);
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = (j - 1) * *m + i__;
	    i__4 = af_subscr(i__, j);
	    work[i__3].r = af[i__4].r, work[i__3].i = af[i__4].i;
/* L10: */
	}
/* L20: */
    }

/*     R = R * P(1) * ... *P(m) */

    i__1 = *n - *m;
    i__2 = *lwork - *m * *n;
    cunmrz_("Right", "No tranpose", m, n, m, &i__1, &af[af_offset], lda, &tau[
	    1], &work[1], m, &work[*m * *n + 1], &i__2, &info);

/*     R = R - A */

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	caxpy_(m, &c_b15, &a_ref(1, i__), &c__1, &work[(i__ - 1) * *m + 1], &
		c__1);
/* L30: */
    }

    ret_val = clange_("One-norm", m, n, &work[1], m, rwork);

    ret_val /= slamch_("Epsilon") * (real) max(*m,*n);
    if (norma != 0.f) {
	ret_val /= norma;
    }

    return ret_val;

/*     End of CRZT01 */

} /* crzt01_ */

#undef af_ref
#undef af_subscr
#undef a_ref
#undef a_subscr


