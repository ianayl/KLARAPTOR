#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    char srnamt[6];
} srnamc_;

#define srnamc_1 srnamc_

/* Table of constant values */

static complex c_b1 = {-1e10f,-1e10f};
static integer c__2 = 2;
static complex c_b20 = {-1.f,0.f};
static complex c_b21 = {1.f,0.f};

/* Subroutine */ int cqrt03_(integer *m, integer *n, integer *k, complex *af, 
	complex *c__, complex *cc, complex *q, integer *lda, complex *tau, 
	complex *work, integer *lwork, real *rwork, real *result)
{
    /* Initialized data */

    static integer iseed[4] = { 1988,1989,1990,1991 };

    /* System generated locals */
    integer af_dim1, af_offset, c_dim1, c_offset, cc_dim1, cc_offset, q_dim1, 
	    q_offset, i__1;

    /* Builtin functions   
       Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static char side[1];
    static integer info, j;
    extern /* Subroutine */ int cgemm_(char *, char *, integer *, integer *, 
	    integer *, complex *, complex *, integer *, complex *, integer *, 
	    complex *, complex *, integer *);
    static integer iside;
    extern logical lsame_(char *, char *);
    static real resid, cnorm;
    static char trans[1];
    static integer mc, nc;
    extern doublereal clange_(char *, integer *, integer *, complex *, 
	    integer *, real *), slamch_(char *);
    extern /* Subroutine */ int clacpy_(char *, integer *, integer *, complex 
	    *, integer *, complex *, integer *), claset_(char *, 
	    integer *, integer *, complex *, complex *, complex *, integer *), clarnv_(integer *, integer *, integer *, complex *), 
	    cungqr_(integer *, integer *, integer *, complex *, integer *, 
	    complex *, complex *, integer *, integer *);
    static integer itrans;
    extern /* Subroutine */ int cunmqr_(char *, char *, integer *, integer *, 
	    integer *, complex *, integer *, complex *, complex *, integer *, 
	    complex *, integer *, integer *);
    static real eps;


#define c___subscr(a_1,a_2) (a_2)*c_dim1 + a_1
#define c___ref(a_1,a_2) c__[c___subscr(a_1,a_2)]
#define q_subscr(a_1,a_2) (a_2)*q_dim1 + a_1
#define q_ref(a_1,a_2) q[q_subscr(a_1,a_2)]
#define af_subscr(a_1,a_2) (a_2)*af_dim1 + a_1
#define af_ref(a_1,a_2) af[af_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    CQRT03 tests CUNMQR, which computes Q*C, Q'*C, C*Q or C*Q'.   

    CQRT03 compares the results of a call to CUNMQR with the results of   
    forming Q explicitly by a call to CUNGQR and then performing matrix   
    multiplication by a call to CGEMM.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The order of the orthogonal matrix Q.  M >= 0.   

    N       (input) INTEGER   
            The number of rows or columns of the matrix C; C is m-by-n if   
            Q is applied from the left, or n-by-m if Q is applied from   
            the right.  N >= 0.   

    K       (input) INTEGER   
            The number of elementary reflectors whose product defines the   
            orthogonal matrix Q.  M >= K >= 0.   

    AF      (input) COMPLEX array, dimension (LDA,N)   
            Details of the QR factorization of an m-by-n matrix, as   
            returnedby CGEQRF. See CGEQRF for further details.   

    C       (workspace) COMPLEX array, dimension (LDA,N)   

    CC      (workspace) COMPLEX array, dimension (LDA,N)   

    Q       (workspace) COMPLEX array, dimension (LDA,M)   

    LDA     (input) INTEGER   
            The leading dimension of the arrays AF, C, CC, and Q.   

    TAU     (input) COMPLEX array, dimension (min(M,N))   
            The scalar factors of the elementary reflectors corresponding   
            to the QR factorization in AF.   

    WORK    (workspace) COMPLEX array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The length of WORK.  LWORK must be at least M, and should be   
            M*NB, where NB is the blocksize for this environment.   

    RWORK   (workspace) REAL array, dimension (M)   

    RESULT  (output) REAL array, dimension (4)   
            The test ratios compare two techniques for multiplying a   
            random matrix C by an m-by-m orthogonal matrix Q.   
            RESULT(1) = norm( Q*C - Q*C )  / ( M * norm(C) * EPS )   
            RESULT(2) = norm( C*Q - C*Q )  / ( M * norm(C) * EPS )   
            RESULT(3) = norm( Q'*C - Q'*C )/ ( M * norm(C) * EPS )   
            RESULT(4) = norm( C*Q' - C*Q' )/ ( M * norm(C) * EPS )   

    =====================================================================   

       Parameter adjustments */
    q_dim1 = *lda;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;
    cc_dim1 = *lda;
    cc_offset = 1 + cc_dim1 * 1;
    cc -= cc_offset;
    c_dim1 = *lda;
    c_offset = 1 + c_dim1 * 1;
    c__ -= c_offset;
    af_dim1 = *lda;
    af_offset = 1 + af_dim1 * 1;
    af -= af_offset;
    --tau;
    --work;
    --rwork;
    --result;

    /* Function Body */

    eps = slamch_("Epsilon");

/*     Copy the first k columns of the factorization to the array Q */

    claset_("Full", m, m, &c_b1, &c_b1, &q[q_offset], lda);
    i__1 = *m - 1;
    clacpy_("Lower", &i__1, k, &af_ref(2, 1), lda, &q_ref(2, 1), lda);

/*     Generate the m-by-m matrix Q */

    s_copy(srnamc_1.srnamt, "CUNGQR", (ftnlen)6, (ftnlen)6);
    cungqr_(m, m, k, &q[q_offset], lda, &tau[1], &work[1], lwork, &info);

    for (iside = 1; iside <= 2; ++iside) {
	if (iside == 1) {
	    *(unsigned char *)side = 'L';
	    mc = *m;
	    nc = *n;
	} else {
	    *(unsigned char *)side = 'R';
	    mc = *n;
	    nc = *m;
	}

/*        Generate MC by NC matrix C */

	i__1 = nc;
	for (j = 1; j <= i__1; ++j) {
	    clarnv_(&c__2, iseed, &mc, &c___ref(1, j));
/* L10: */
	}
	cnorm = clange_("1", &mc, &nc, &c__[c_offset], lda, &rwork[1]);
	if (cnorm == 0.f) {
	    cnorm = 1.f;
	}

	for (itrans = 1; itrans <= 2; ++itrans) {
	    if (itrans == 1) {
		*(unsigned char *)trans = 'N';
	    } else {
		*(unsigned char *)trans = 'C';
	    }

/*           Copy C */

	    clacpy_("Full", &mc, &nc, &c__[c_offset], lda, &cc[cc_offset], 
		    lda);

/*           Apply Q or Q' to C */

	    s_copy(srnamc_1.srnamt, "CUNMQR", (ftnlen)6, (ftnlen)6);
	    cunmqr_(side, trans, &mc, &nc, k, &af[af_offset], lda, &tau[1], &
		    cc[cc_offset], lda, &work[1], lwork, &info);

/*           Form explicit product and subtract */

	    if (lsame_(side, "L")) {
		cgemm_(trans, "No transpose", &mc, &nc, &mc, &c_b20, &q[
			q_offset], lda, &c__[c_offset], lda, &c_b21, &cc[
			cc_offset], lda);
	    } else {
		cgemm_("No transpose", trans, &mc, &nc, &nc, &c_b20, &c__[
			c_offset], lda, &q[q_offset], lda, &c_b21, &cc[
			cc_offset], lda);
	    }

/*           Compute error in the difference */

	    resid = clange_("1", &mc, &nc, &cc[cc_offset], lda, &rwork[1]);
	    result[(iside - 1 << 1) + itrans] = resid / ((real) max(1,*m) * 
		    cnorm * eps);

/* L20: */
	}
/* L30: */
    }

    return 0;

/*     End of CQRT03 */

} /* cqrt03_ */

#undef af_ref
#undef af_subscr
#undef q_ref
#undef q_subscr
#undef c___ref
#undef c___subscr


