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

struct {
    real opcnt[6], timng[6];
} lstime_;

#define lstime_1 lstime_

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static integer c__0 = 0;
static real c_b31 = 0.f;
static integer c__2 = 2;
static real c_b67 = 1.f;

/* Subroutine */ int sgelsy_(integer *m, integer *n, integer *nrhs, real *a, 
	integer *lda, real *b, integer *ldb, integer *jpvt, real *rcond, 
	integer *rank, real *work, integer *lwork, integer *info)
{
    /* Initialized data */

    static integer gelsy = 1;
    static integer geqp3 = 2;
    static integer ormqr = 4;
    static integer ormrz = 6;
    static integer trsm = 5;
    static integer tzrzf = 3;

    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2;
    real r__1, r__2;

    /* Local variables */
    static real anrm, bnrm, smin, smax;
    static integer i__, j, iascl, ibscl, ismin;
    extern doublereal sopla_(char *, integer *, integer *, integer *, integer 
	    *, integer *);
    static integer ismax;
    static real c1, c2;
    extern /* Subroutine */ int scopy_(integer *, real *, integer *, real *, 
	    integer *);
    static real wsize, s1, s2, t1, t2;
    extern /* Subroutine */ int strsm_(char *, char *, char *, char *, 
	    integer *, integer *, real *, real *, integer *, real *, integer *
	    ), slaic1_(integer *, integer *, 
	    real *, real *, real *, real *, real *, real *, real *);
    extern doublereal sopbl3_(char *, integer *, integer *, integer *)
	    ;
    extern /* Subroutine */ int sgeqp3_(integer *, integer *, real *, integer 
	    *, integer *, real *, real *, integer *, integer *);
    static integer nb;
    extern /* Subroutine */ int slabad_(real *, real *);
    static integer mn;
    extern doublereal slamch_(char *), slange_(char *, integer *, 
	    integer *, real *, integer *, real *), second_(void);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    static real bignum;
    extern /* Subroutine */ int slascl_(char *, integer *, integer *, real *, 
	    real *, integer *, integer *, real *, integer *, integer *), slaset_(char *, integer *, integer *, real *, real *, 
	    real *, integer *);
    static integer nb1, nb2, nb3, nb4;
    static real sminpr, smaxpr, smlnum;
    static integer lwkopt;
    static logical lquery;
    extern /* Subroutine */ int sormqr_(char *, char *, integer *, integer *, 
	    integer *, real *, integer *, real *, real *, integer *, real *, 
	    integer *, integer *), sormrz_(char *, char *, 
	    integer *, integer *, integer *, integer *, real *, integer *, 
	    real *, real *, integer *, real *, integer *, integer *), stzrzf_(integer *, integer *, real *, integer *, real *, 
	    real *, integer *, integer *);


#define a_ref(a_1,a_2) a[(a_2)*a_dim1 + a_1]
#define b_ref(a_1,a_2) b[(a_2)*b_dim1 + a_1]


/*  -- LAPACK driver routine (instrumented to count ops, version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   

       Common block to return operation counts and timings   

    Purpose   
    =======   

    SGELSY computes the minimum-norm solution to a real linear least   
    squares problem:   
        min || A * X - B ||   
    using a complete orthogonal factorization of A.  A is an M-by-N   
    matrix which may be rank-deficient.   

    Several right hand side vectors b and solution vectors x can be   
    handled in a single call; they are stored as the columns of the   
    M-by-NRHS right hand side matrix B and the N-by-NRHS solution   
    matrix X.   

    The routine first computes a QR factorization with column pivoting:   
        A * P = Q * [ R11 R12 ]   
                    [  0  R22 ]   
    with R11 defined as the largest leading submatrix whose estimated   
    condition number is less than 1/RCOND.  The order of R11, RANK,   
    is the effective rank of A.   

    Then, R22 is considered to be negligible, and R12 is annihilated   
    by orthogonal transformations from the right, arriving at the   
    complete orthogonal factorization:   
       A * P = Q * [ T11 0 ] * Z   
                   [  0  0 ]   
    The minimum-norm solution is then   
       X = P * Z' [ inv(T11)*Q1'*B ]   
                  [        0       ]   
    where Q1 consists of the first RANK columns of Q.   

    This routine is basically identical to the original xGELSX except   
    three differences:   
      o The call to the subroutine xGEQPF has been substituted by the   
        the call to the subroutine xGEQP3. This subroutine is a Blas-3   
        version of the QR factorization with column pivoting.   
      o Matrix B (the right hand side) is updated with Blas-3.   
      o The permutation of matrix B (the right hand side) is faster and   
        more simple.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of right hand sides, i.e., the number of   
            columns of matrices B and X. NRHS >= 0.   

    A       (input/output) REAL array, dimension (LDA,N)   
            On entry, the M-by-N matrix A.   
            On exit, A has been overwritten by details of its   
            complete orthogonal factorization.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    B       (input/output) REAL array, dimension (LDB,NRHS)   
            On entry, the M-by-NRHS right hand side matrix B.   
            On exit, the N-by-NRHS solution matrix X.   

    LDB     (input) INTEGER   
            The leading dimension of the array B. LDB >= max(1,M,N).   

    JPVT    (input/output) INTEGER array, dimension (N)   
            On entry, if JPVT(i) .ne. 0, the i-th column of A is permuted   
            to the front of AP, otherwise column i is a free column.   
            On exit, if JPVT(i) = k, then the i-th column of AP   
            was the k-th column of A.   

    RCOND   (input) REAL   
            RCOND is used to determine the effective rank of A, which   
            is defined as the order of the largest leading triangular   
            submatrix R11 in the QR factorization with pivoting of A,   
            whose estimated condition number < 1/RCOND.   

    RANK    (output) INTEGER   
            The effective rank of A, i.e., the order of the submatrix   
            R11.  This is the same as the order of the submatrix T11   
            in the complete orthogonal factorization of A.   

    WORK    (workspace/output) REAL array, dimension (LWORK)   
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.   
            The unblocked strategy requires that:   
               LWORK >= MAX( MN+3*N+1, 2*MN+NRHS ),   
            where MN = min( M, N ).   
            The block algorithm requires that:   
               LWORK >= MAX( MN+2*N+NB*(N+1), 2*MN+NB*NRHS ),   
            where NB is an upper bound on the blocksize returned   
            by ILAENV for the routines SGEQP3, STZRZF, STZRQF, SORMQR,   
            and SORMRZ.   

            If LWORK = -1, then a workspace query is assumed; the routine   
            only calculates the optimal size of the WORK array, returns   
            this value as the first entry of the WORK array, and no error   
            message related to LWORK is issued by XERBLA.   

    INFO    (output) INTEGER   
            = 0: successful exit   
            < 0: If INFO = -i, the i-th argument had an illegal value.   

    Further Details   
    ===============   

    Based on contributions by   
      A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA   
      E. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain   
      G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain   

    =====================================================================   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    --jpvt;
    --work;

    /* Function Body */

    mn = min(*m,*n);
    ismin = mn + 1;
    ismax = (mn << 1) + 1;

/*     Test the input arguments. */

    *info = 0;
    nb1 = ilaenv_(&c__1, "SGEQRF", " ", m, n, &c_n1, &c_n1, (ftnlen)6, (
	    ftnlen)1);
    nb2 = ilaenv_(&c__1, "SGERQF", " ", m, n, &c_n1, &c_n1, (ftnlen)6, (
	    ftnlen)1);
    nb3 = ilaenv_(&c__1, "SORMQR", " ", m, n, nrhs, &c_n1, (ftnlen)6, (ftnlen)
	    1);
    nb4 = ilaenv_(&c__1, "SORMRQ", " ", m, n, nrhs, &c_n1, (ftnlen)6, (ftnlen)
	    1);
/* Computing MAX */
    i__1 = max(nb1,nb2), i__1 = max(i__1,nb3);
    nb = max(i__1,nb4);
/* Computing MAX */
    i__1 = 1, i__2 = mn + (*n << 1) + nb * (*n + 1), i__1 = max(i__1,i__2), 
	    i__2 = (mn << 1) + nb * *nrhs;
    lwkopt = max(i__1,i__2);
    work[1] = (real) lwkopt;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*lda < max(1,*m)) {
	*info = -5;
    } else /* if(complicated condition) */ {
/* Computing MAX */
	i__1 = max(1,*m);
	if (*ldb < max(i__1,*n)) {
	    *info = -7;
	} else /* if(complicated condition) */ {
/* Computing MAX */
	    i__1 = 1, i__2 = mn + *n * 3 + 1, i__1 = max(i__1,i__2), i__2 = (
		    mn << 1) + *nrhs;
	    if (*lwork < max(i__1,i__2) && ! lquery) {
		*info = -12;
	    }
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("SGELSY", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible   

   Computing MIN */
    i__1 = min(*m,*n);
    if (min(i__1,*nrhs) == 0) {
	*rank = 0;
	return 0;
    }

/*     Get machine parameters */

    lstime_1.opcnt[gelsy - 1] += 2.f;
    smlnum = slamch_("S") / slamch_("P");
    bignum = 1.f / smlnum;
    slabad_(&smlnum, &bignum);

/*     Scale A, B if max entries outside range [SMLNUM,BIGNUM] */

    anrm = slange_("M", m, n, &a[a_offset], lda, &work[1]);
    iascl = 0;
    if (anrm > 0.f && anrm < smlnum) {

/*        Scale matrix norm up to SMLNUM */

	lstime_1.opcnt[gelsy - 1] += (real) (*m * *n);
	slascl_("G", &c__0, &c__0, &anrm, &smlnum, m, n, &a[a_offset], lda, 
		info);
	iascl = 1;
    } else if (anrm > bignum) {

/*        Scale matrix norm down to BIGNUM */

	lstime_1.opcnt[gelsy - 1] += (real) (*m * *n);
	slascl_("G", &c__0, &c__0, &anrm, &bignum, m, n, &a[a_offset], lda, 
		info);
	iascl = 2;
    } else if (anrm == 0.f) {

/*        Matrix all zero. Return zero solution. */

	i__1 = max(*m,*n);
	slaset_("F", &i__1, nrhs, &c_b31, &c_b31, &b[b_offset], ldb);
	*rank = 0;
	goto L70;
    }

    bnrm = slange_("M", m, nrhs, &b[b_offset], ldb, &work[1]);
    ibscl = 0;
    if (bnrm > 0.f && bnrm < smlnum) {

/*        Scale matrix norm up to SMLNUM */

	lstime_1.opcnt[gelsy - 1] += (real) (*m * *nrhs);
	slascl_("G", &c__0, &c__0, &bnrm, &smlnum, m, nrhs, &b[b_offset], ldb,
		 info);
	ibscl = 1;
    } else if (bnrm > bignum) {

/*        Scale matrix norm down to BIGNUM */

	lstime_1.opcnt[gelsy - 1] += (real) (*m * *nrhs);
	slascl_("G", &c__0, &c__0, &bnrm, &bignum, m, nrhs, &b[b_offset], ldb,
		 info);
	ibscl = 2;
    }

/*     Compute QR factorization with column pivoting of A:   
          A * P = Q * R */

    lstime_1.opcnt[geqp3 - 1] += sopla_("SGEQPF", m, n, &c__0, &c__0, &c__0);
    t1 = second_();
    i__1 = *lwork - mn;
    sgeqp3_(m, n, &a[a_offset], lda, &jpvt[1], &work[1], &work[mn + 1], &i__1,
	     info);
    t2 = second_();
    lstime_1.timng[geqp3 - 1] += t2 - t1;
    wsize = mn + work[mn + 1];

/*     workspace: MN+2*N+NB*(N+1).   
       Details of Householder rotations stored in WORK(1:MN).   

       Determine RANK using incremental condition estimation */

    work[ismin] = 1.f;
    work[ismax] = 1.f;
    smax = (r__1 = a_ref(1, 1), dabs(r__1));
    smin = smax;
    if ((r__1 = a_ref(1, 1), dabs(r__1)) == 0.f) {
	*rank = 0;
	i__1 = max(*m,*n);
	slaset_("F", &i__1, nrhs, &c_b31, &c_b31, &b[b_offset], ldb);
	goto L70;
    } else {
	*rank = 1;
    }

L10:
    if (*rank < mn) {
	i__ = *rank + 1;
	latime_1.ops = 0.f;
	slaic1_(&c__2, rank, &work[ismin], &smin, &a_ref(1, i__), &a_ref(i__, 
		i__), &sminpr, &s1, &c1);
	slaic1_(&c__1, rank, &work[ismax], &smax, &a_ref(1, i__), &a_ref(i__, 
		i__), &smaxpr, &s2, &c2);
	lstime_1.opcnt[gelsy - 1] = lstime_1.opcnt[gelsy - 1] + latime_1.ops 
		+ 1.f;

	if (smaxpr * *rcond <= sminpr) {
	    lstime_1.opcnt[gelsy - 1] += (real) (*rank << 1);
	    i__1 = *rank;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		work[ismin + i__ - 1] = s1 * work[ismin + i__ - 1];
		work[ismax + i__ - 1] = s2 * work[ismax + i__ - 1];
/* L20: */
	    }
	    work[ismin + *rank] = c1;
	    work[ismax + *rank] = c2;
	    smin = sminpr;
	    smax = smaxpr;
	    ++(*rank);
	    goto L10;
	}
    }

/*     workspace: 3*MN.   

       Logically partition R = [ R11 R12 ]   
                               [  0  R22 ]   
       where R11 = R(1:RANK,1:RANK)   

       [R11,R12] = [ T11, 0 ] * Y */

    if (*rank < *n) {
	lstime_1.opcnt[tzrzf - 1] += sopla_("STZRQF", rank, n, &c__0, &c__0, &
		c__0);
	t1 = second_();
	i__1 = *lwork - (mn << 1);
	stzrzf_(rank, n, &a[a_offset], lda, &work[mn + 1], &work[(mn << 1) + 
		1], &i__1, info);
	t2 = second_();
	lstime_1.timng[tzrzf - 1] += t2 - t1;
    }

/*     workspace: 2*MN.   
       Details of Householder rotations stored in WORK(MN+1:2*MN)   

       B(1:M,1:NRHS) := Q' * B(1:M,1:NRHS) */

    lstime_1.opcnt[ormqr - 1] += sopla_("SORMQR", m, nrhs, &mn, &c__0, &c__0);
    t1 = second_();
    i__1 = *lwork - (mn << 1);
    sormqr_("Left", "Transpose", m, nrhs, &mn, &a[a_offset], lda, &work[1], &
	    b[b_offset], ldb, &work[(mn << 1) + 1], &i__1, info);
    t2 = second_();
    lstime_1.timng[ormqr - 1] += t2 - t1;
/* Computing MAX */
    r__1 = wsize, r__2 = (mn << 1) + work[(mn << 1) + 1];
    wsize = dmax(r__1,r__2);

/*     workspace: 2*MN+NB*NRHS.   

       B(1:RANK,1:NRHS) := inv(T11) * B(1:RANK,1:NRHS) */

    lstime_1.opcnt[trsm - 1] += sopbl3_("STRSM ", rank, nrhs, &c__0);
    t1 = second_();
    strsm_("Left", "Upper", "No transpose", "Non-unit", rank, nrhs, &c_b67, &
	    a[a_offset], lda, &b[b_offset], ldb);
    t2 = second_();
    lstime_1.timng[trsm - 1] += t2 - t1;

    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n;
	for (i__ = *rank + 1; i__ <= i__2; ++i__) {
	    b_ref(i__, j) = 0.f;
/* L30: */
	}
/* L40: */
    }

/*     B(1:N,1:NRHS) := Y' * B(1:N,1:NRHS) */

    if (*rank < *n) {
	nb = ilaenv_(&c__1, "SORMRQ", "LT", n, nrhs, rank, &c_n1, (ftnlen)6, (
		ftnlen)2);
	lstime_1.opcnt[ormrz - 1] += sopla_("SORMRQ", n, nrhs, rank, &c__0, &
		nb);
	t1 = second_();
	i__1 = *n - *rank;
	i__2 = *lwork - (mn << 1);
	sormrz_("Left", "Transpose", n, nrhs, rank, &i__1, &a[a_offset], lda, 
		&work[mn + 1], &b[b_offset], ldb, &work[(mn << 1) + 1], &i__2,
		 info);
	t2 = second_();
	lstime_1.timng[ormrz - 1] += t2 - t1;
    }

/*     workspace: 2*MN+NRHS.   

       B(1:N,1:NRHS) := P * B(1:N,1:NRHS) */

    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    work[jpvt[i__]] = b_ref(i__, j);
/* L50: */
	}
	scopy_(n, &work[1], &c__1, &b_ref(1, j), &c__1);
/* L60: */
    }

/*     workspace: N.   

       Undo scaling */

    if (iascl == 1) {
	lstime_1.opcnt[gelsy - 1] += (real) (*n * *nrhs + *rank * *rank);
	slascl_("G", &c__0, &c__0, &anrm, &smlnum, n, nrhs, &b[b_offset], ldb,
		 info);
	slascl_("U", &c__0, &c__0, &smlnum, &anrm, rank, rank, &a[a_offset], 
		lda, info);
    } else if (iascl == 2) {
	lstime_1.opcnt[gelsy - 1] += (real) (*n * *nrhs + *rank * *rank);
	slascl_("G", &c__0, &c__0, &anrm, &bignum, n, nrhs, &b[b_offset], ldb,
		 info);
	slascl_("U", &c__0, &c__0, &bignum, &anrm, rank, rank, &a[a_offset], 
		lda, info);
    }
    if (ibscl == 1) {
	lstime_1.opcnt[gelsy - 1] += (real) (*n * *nrhs);
	slascl_("G", &c__0, &c__0, &smlnum, &bnrm, n, nrhs, &b[b_offset], ldb,
		 info);
    } else if (ibscl == 2) {
	lstime_1.opcnt[gelsy - 1] += (real) (*n * *nrhs);
	slascl_("G", &c__0, &c__0, &bignum, &bnrm, n, nrhs, &b[b_offset], ldb,
		 info);
    }

L70:
    work[1] = (real) lwkopt;

    return 0;

/*     End of SGELSY */

} /* sgelsy_ */

#undef b_ref
#undef a_ref


