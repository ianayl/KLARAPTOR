#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer m, n, mplusn, k;
    logical fs;
} mn_;

#define mn_1 mn_

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static integer c_n1 = -1;
static doublereal c_b26 = 0.;
static integer c__3 = 3;
static integer c__5 = 5;

/* Subroutine */ int ddrgsx_(integer *nsize, integer *ncmax, doublereal *
	thresh, integer *nin, integer *nout, doublereal *a, integer *lda, 
	doublereal *b, doublereal *ai, doublereal *bi, doublereal *z__, 
	doublereal *q, doublereal *alphar, doublereal *alphai, doublereal *
	beta, doublereal *c__, integer *ldc, doublereal *s, doublereal *work, 
	integer *lwork, integer *iwork, integer *liwork, logical *bwork, 
	integer *info)
{
    /* Format strings */
    static char fmt_9999[] = "(\002 DDRGSX: \002,a,\002 returned INFO=\002,i"
	    "6,\002.\002,/9x,\002N=\002,i6,\002, JTYPE=\002,i6,\002)\002)";
    static char fmt_9997[] = "(\002 DDRGSX: DGET53 returned INFO=\002,i1,"
	    "\002 for eigenvalue \002,i6,\002.\002,/9x,\002N=\002,i6,\002, JT"
	    "YPE=\002,i6,\002)\002)";
    static char fmt_9996[] = "(\002 DDRGSX: S not in Schur form at eigenvalu"
	    "e \002,i6,\002.\002,/9x,\002N=\002,i6,\002, JTYPE=\002,i6,\002"
	    ")\002)";
    static char fmt_9995[] = "(/1x,a3,\002 -- Real Expert Generalized Schur "
	    "form\002,\002 problem driver\002)";
    static char fmt_9993[] = "(\002 Matrix types: \002,/\002  1:  A is a blo"
	    "ck diagonal matrix of Jordan blocks \002,\002and B is the identi"
	    "ty \002,/\002      matrix, \002,/\002  2:  A and B are upper tri"
	    "angular matrices, \002,/\002  3:  A and B are as type 2, but eac"
	    "h second diagonal \002,\002block in A_11 and \002,/\002      eac"
	    "h third diaongal block in A_22 are 2x2 blocks,\002,/\002  4:  A "
	    "and B are block diagonal matrices, \002,/\002  5:  (A,B) has pot"
	    "entially close or common \002,\002eigenvalues.\002,/)";
    static char fmt_9992[] = "(/\002 Tests performed:  (S is Schur, T is tri"
	    "angular, \002,\002Q and Z are \002,a,\002,\002,/19x,\002 a is al"
	    "pha, b is beta, and \002,a,\002 means \002,a,\002.)\002,/\002  1"
	    " = | A - Q S Z\002,a,\002 | / ( |A| n ulp )      2 = | B - Q T "
	    "Z\002,a,\002 | / ( |B| n ulp )\002,/\002  3 = | I - QQ\002,a,"
	    "\002 | / ( n ulp )             4 = | I - ZZ\002,a,\002 | / ( n u"
	    "lp )\002,/\002  5 = 1/ULP  if A is not in \002,\002Schur form "
	    "S\002,/\002  6 = difference between (alpha,beta)\002,\002 and di"
	    "agonals of (S,T)\002,/\002  7 = 1/ULP  if SDIM is not the correc"
	    "t number of \002,\002selected eigenvalues\002,/\002  8 = 1/ULP  "
	    "if DIFEST/DIFTRU > 10*THRESH or \002,\002DIFTRU/DIFEST > 10*THRE"
	    "SH\002,/\002  9 = 1/ULP  if DIFEST <> 0 or DIFTRU > ULP*norm(A,B"
	    ") \002,\002when reordering fails\002,/\002 10 = 1/ULP  if PLEST/"
	    "PLTRU > THRESH or \002,\002PLTRU/PLEST > THRESH\002,/\002    ( T"
	    "est 10 is only for input examples )\002,/)";
    static char fmt_9991[] = "(\002 Matrix order=\002,i2,\002, type=\002,i2"
	    ",\002, a=\002,d10.4,\002, order(A_11)=\002,i2,\002, result \002,"
	    "i2,\002 is \002,0p,f8.2)";
    static char fmt_9990[] = "(\002 Matrix order=\002,i2,\002, type=\002,i2"
	    ",\002, a=\002,d10.4,\002, order(A_11)=\002,i2,\002, result \002,"
	    "i2,\002 is \002,0p,d10.4)";
    static char fmt_9998[] = "(\002 DDRGSX: \002,a,\002 returned INFO=\002,i"
	    "6,\002.\002,/9x,\002N=\002,i6,\002, Input Example #\002,i2,\002"
	    ")\002)";
    static char fmt_9994[] = "(\002Input Example\002)";
    static char fmt_9989[] = "(\002 Input example #\002,i2,\002, matrix orde"
	    "r=\002,i4,\002,\002,\002 result \002,i2,\002 is\002,0p,f8.2)";
    static char fmt_9988[] = "(\002 Input example #\002,i2,\002, matrix orde"
	    "r=\002,i4,\002,\002,\002 result \002,i2,\002 is\002,1p,d10.3)";

    /* System generated locals */
    integer a_dim1, a_offset, ai_dim1, ai_offset, b_dim1, b_offset, bi_dim1, 
	    bi_offset, c_dim1, c_offset, q_dim1, q_offset, z_dim1, z_offset, 
	    i__1, i__2, i__3, i__4;
    doublereal d__1, d__2, d__3, d__4, d__5, d__6, d__7, d__8, d__9, d__10;

    /* Builtin functions */
    double sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void),
	     s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);

    /* Local variables */
    static doublereal temp1, temp2;
    static integer i__, j;
    extern /* Subroutine */ int dget51_(integer *, integer *, doublereal *, 
	    integer *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *), dget53_(
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *);
    static doublereal abnrm;
    static integer ifunc, iinfo, linfo;
    static char sense[1];
    static integer nerrs, i1, ntest;
    extern /* Subroutine */ int dlakf2_(integer *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     integer *);
    static doublereal pltru;
    extern /* Subroutine */ int dlatm5_(integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, integer *, integer *), dlabad_(
	    doublereal *, doublereal *);
    static logical ilabad;
    static doublereal thrsh2;
    extern doublereal dlamch_(char *);
    static integer mm;
    extern doublereal dlange_(char *, integer *, integer *, doublereal *, 
	    integer *, doublereal *);
    static integer bdspac;
    static doublereal pl[2];
    extern /* Subroutine */ int dgesvd_(char *, char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, integer *), dlacpy_(char *, integer *, integer *, doublereal 
	    *, integer *, doublereal *, integer *);
    static doublereal difest[2];
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int dlaset_(char *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *);
    static doublereal bignum;
    extern /* Subroutine */ int dggesx_(char *, char *, char *, L_fp, char *, 
	    integer *, doublereal *, integer *, doublereal *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, logical *, integer 
	    *), alasvm_(char *, integer *, 
	    integer *, integer *, integer *), xerbla_(char *, integer 
	    *);
    static doublereal weight, diftru;
    extern logical dlctsx_();
    static integer minwrk, maxwrk;
    static doublereal smlnum;
    static integer mn2, nptknt;
    static doublereal ulpinv, result[10];
    static integer ntestt, prtype, qba, qbb;
    static doublereal ulp;

    /* Fortran I/O blocks */
    static cilist io___22 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___32 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_9993, 0 };
    static cilist io___37 = { 0, 0, 0, fmt_9992, 0 };
    static cilist io___39 = { 0, 0, 0, fmt_9991, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_9990, 0 };
    static cilist io___42 = { 0, 0, 1, 0, 0 };
    static cilist io___43 = { 0, 0, 1, 0, 0 };
    static cilist io___44 = { 0, 0, 0, 0, 0 };
    static cilist io___45 = { 0, 0, 0, 0, 0 };
    static cilist io___46 = { 0, 0, 0, 0, 0 };
    static cilist io___48 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___49 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___50 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___51 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___52 = { 0, 0, 0, fmt_9994, 0 };
    static cilist io___53 = { 0, 0, 0, fmt_9992, 0 };
    static cilist io___54 = { 0, 0, 0, fmt_9989, 0 };
    static cilist io___55 = { 0, 0, 0, fmt_9988, 0 };



#define ai_ref(a_1,a_2) ai[(a_2)*ai_dim1 + a_1]
#define bi_ref(a_1,a_2) bi[(a_2)*bi_dim1 + a_1]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1999   


    Purpose   
    =======   

    DDRGSX checks the nonsymmetric generalized eigenvalue (Schur form)   
    problem expert driver DGGESX.   

    DGGESX factors A and B as Q S Z' and Q T Z', where ' means   
    transpose, T is upper triangular, S is in generalized Schur form   
    (block upper triangular, with 1x1 and 2x2 blocks on the diagonal,   
    the 2x2 blocks corresponding to complex conjugate pairs of   
    generalized eigenvalues), and Q and Z are orthogonal.  It also   
    computes the generalized eigenvalues (alpha(1),beta(1)), ...,   
    (alpha(n),beta(n)). Thus, w(j) = alpha(j)/beta(j) is a root of the   
    characteristic equation   

        det( A - w(j) B ) = 0   

    Optionally it also reorders the eigenvalues so that a selected   
    cluster of eigenvalues appears in the leading diagonal block of the   
    Schur forms; computes a reciprocal condition number for the average   
    of the selected eigenvalues; and computes a reciprocal condition   
    number for the right and left deflating subspaces corresponding to   
    the selected eigenvalues.   

    When DDRGSX is called with NSIZE > 0, five (5) types of built-in   
    matrix pairs are used to test the routine DGGESX.   

    When DDRGSX is called with NSIZE = 0, it reads in test matrix data   
    to test DGGESX.   

    For each matrix pair, the following tests will be performed and   
    compared with the threshhold THRESH except for the tests (7) and (9):   

    (1)   | A - Q S Z' | / ( |A| n ulp )   

    (2)   | B - Q T Z' | / ( |B| n ulp )   

    (3)   | I - QQ' | / ( n ulp )   

    (4)   | I - ZZ' | / ( n ulp )   

    (5)   if A is in Schur form (i.e. quasi-triangular form)   

    (6)   maximum over j of D(j)  where:   

          if alpha(j) is real:   
                        |alpha(j) - S(j,j)|        |beta(j) - T(j,j)|   
              D(j) = ------------------------ + -----------------------   
                     max(|alpha(j)|,|S(j,j)|)   max(|beta(j)|,|T(j,j)|)   

          if alpha(j) is complex:   
                                    | det( s S - w T ) |   
              D(j) = ---------------------------------------------------   
                     ulp max( s norm(S), |w| norm(T) )*norm( s S - w T )   

              and S and T are here the 2 x 2 diagonal blocks of S and T   
              corresponding to the j-th and j+1-th eigenvalues.   

    (7)   if sorting worked and SDIM is the number of eigenvalues   
          which were selected.   

    (8)   the estimated value DIF does not differ from the true values of   
          Difu and Difl more than a factor 10*THRESH. If the estimate DIF   
          equals zero the corresponding true values of Difu and Difl   
          should be less than EPS*norm(A, B). If the true value of Difu   
          and Difl equal zero, the estimate DIF should be less than   
          EPS*norm(A, B).   

    (9)   If INFO = N+3 is returned by DGGESX, the reordering "failed"   
          and we check that DIF = PL = PR = 0 and that the true value of   
          Difu and Difl is < EPS*norm(A, B). We count the events when   
          INFO=N+3.   

    For read-in test matrices, the above tests are run except that the   
    exact value for DIF (and PL) is input data.  Additionally, there is   
    one more test run for read-in test matrices:   

    (10)  the estimated value PL does not differ from the true value of   
          PLTRU more than a factor THRESH. If the estimate PL equals   
          zero the corresponding true value of PLTRU should be less than   
          EPS*norm(A, B). If the true value of PLTRU equal zero, the   
          estimate PL should be less than EPS*norm(A, B).   

    Note that for the built-in tests, a total of 10*NSIZE*(NSIZE-1)   
    matrix pairs are generated and tested. NSIZE should be kept small.   

    SVD (routine DGESVD) is used for computing the true value of DIF_u   
    and DIF_l when testing the built-in test problems.   

    Built-in Test Matrices   
    ======================   

    All built-in test matrices are the 2 by 2 block of triangular   
    matrices   

             A = [ A11 A12 ]    and      B = [ B11 B12 ]   
                 [     A22 ]                 [     B22 ]   

    where for different type of A11 and A22 are given as the following.   
    A12 and B12 are chosen so that the generalized Sylvester equation   

             A11*R - L*A22 = -A12   
             B11*R - L*B22 = -B12   

    have prescribed solution R and L.   

    Type 1:  A11 = J_m(1,-1) and A_22 = J_k(1-a,1).   
             B11 = I_m, B22 = I_k   
             where J_k(a,b) is the k-by-k Jordan block with ``a'' on   
             diagonal and ``b'' on superdiagonal.   

    Type 2:  A11 = (a_ij) = ( 2(.5-sin(i)) ) and   
             B11 = (b_ij) = ( 2(.5-sin(ij)) ) for i=1,...,m, j=i,...,m   
             A22 = (a_ij) = ( 2(.5-sin(i+j)) ) and   
             B22 = (b_ij) = ( 2(.5-sin(ij)) ) for i=m+1,...,k, j=i,...,k   

    Type 3:  A11, A22 and B11, B22 are chosen as for Type 2, but each   
             second diagonal block in A_11 and each third diagonal block   
             in A_22 are made as 2 by 2 blocks.   

    Type 4:  A11 = ( 20(.5 - sin(ij)) ) and B22 = ( 2(.5 - sin(i+j)) )   
                for i=1,...,m,  j=1,...,m and   
             A22 = ( 20(.5 - sin(i+j)) ) and B22 = ( 2(.5 - sin(ij)) )   
                for i=m+1,...,k,  j=m+1,...,k   

    Type 5:  (A,B) and have potentially close or common eigenvalues and   
             very large departure from block diagonality A_11 is chosen   
             as the m x m leading submatrix of A_1:   
                     |  1  b                            |   
                     | -b  1                            |   
                     |        1+d  b                    |   
                     |         -b 1+d                   |   
              A_1 =  |                  d  1            |   
                     |                 -1  d            |   
                     |                        -d  1     |   
                     |                        -1 -d     |   
                     |                               1  |   
             and A_22 is chosen as the k x k leading submatrix of A_2:   
                     | -1  b                            |   
                     | -b -1                            |   
                     |       1-d  b                     |   
                     |       -b  1-d                    |   
              A_2 =  |                 d 1+b            |   
                     |               -1-b d             |   
                     |                       -d  1+b    |   
                     |                      -1+b  -d    |   
                     |                              1-d |   
             and matrix B are chosen as identity matrices (see DLATM5).   


    Arguments   
    =========   

    NSIZE   (input) INTEGER   
            The maximum size of the matrices to use. NSIZE >= 0.   
            If NSIZE = 0, no built-in tests matrices are used, but   
            read-in test matrices are used to test DGGESX.   

    NCMAX   (input) INTEGER   
            Maximum allowable NMAX for generating Kroneker matrix   
            in call to DLAKF2   

    THRESH  (input) DOUBLE PRECISION   
            A test will count as "failed" if the "error", computed as   
            described above, exceeds THRESH.  Note that the error   
            is scaled to be O(1), so THRESH should be a reasonably   
            small multiple of 1, e.g., 10 or 100.  In particular,   
            it should not depend on the precision (single vs. double)   
            or the size of the matrix.  THRESH >= 0.   

    NIN     (input) INTEGER   
            The FORTRAN unit number for reading in the data file of   
            problems to solve.   

    NOUT    (input) INTEGER   
            The FORTRAN unit number for printing out error messages   
            (e.g., if a routine returns IINFO not equal to 0.)   

    A       (workspace) DOUBLE PRECISION array, dimension (LDA, NSIZE)   
            Used to store the matrix whose eigenvalues are to be   
            computed.  On exit, A contains the last matrix actually used.   

    LDA     (input) INTEGER   
            The leading dimension of A, B, AI, BI, Z and Q,   
            LDA >= max( 1, NSIZE ). For the read-in test,   
            LDA >= max( 1, N ), N is the size of the test matrices.   

    B       (workspace) DOUBLE PRECISION array, dimension (LDA, NSIZE)   
            Used to store the matrix whose eigenvalues are to be   
            computed.  On exit, B contains the last matrix actually used.   

    AI      (workspace) DOUBLE PRECISION array, dimension (LDA, NSIZE)   
            Copy of A, modified by DGGESX.   

    BI      (workspace) DOUBLE PRECISION array, dimension (LDA, NSIZE)   
            Copy of B, modified by DGGESX.   

    Z       (workspace) DOUBLE PRECISION array, dimension (LDA, NSIZE)   
            Z holds the left Schur vectors computed by DGGESX.   

    Q       (workspace) DOUBLE PRECISION array, dimension (LDA, NSIZE)   
            Q holds the right Schur vectors computed by DGGESX.   

    ALPHAR  (workspace) DOUBLE PRECISION array, dimension (NSIZE)   
    ALPHAI  (workspace) DOUBLE PRECISION array, dimension (NSIZE)   
    BETA    (workspace) DOUBLE PRECISION array, dimension (NSIZE)   
            On exit, (ALPHAR + ALPHAI*i)/BETA are the eigenvalues.   

    C       (workspace) DOUBLE PRECISION array, dimension (LDC, LDC)   
            Store the matrix generated by subroutine DLAKF2, this is the   
            matrix formed by Kronecker products used for estimating   
            DIF.   

    LDC     (input) INTEGER   
            The leading dimension of C. LDC >= max(1, LDA*LDA/2 ).   

    S       (workspace) DOUBLE PRECISION array, dimension (LDC)   
            Singular values of C   

    WORK    (workspace) DOUBLE PRECISION array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.   
            LWORK >= MAX( 5*NSIZE*NSIZE/2 - 2, 10*(NSIZE+1) )   

    IWORK   (workspace) INTEGER array, dimension (LIWORK)   

    LIWORK  (input) INTEGER   
            The dimension of the array IWORK. LIWORK >= NSIZE + 6.   

    BWORK   (workspace) LOGICAL array, dimension (LDA)   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value.   
            > 0:  A routine returned an error code.   

    =====================================================================   


       Check for errors   

       Parameter adjustments */
    q_dim1 = *lda;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;
    z_dim1 = *lda;
    z_offset = 1 + z_dim1 * 1;
    z__ -= z_offset;
    bi_dim1 = *lda;
    bi_offset = 1 + bi_dim1 * 1;
    bi -= bi_offset;
    ai_dim1 = *lda;
    ai_offset = 1 + ai_dim1 * 1;
    ai -= ai_offset;
    b_dim1 = *lda;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --alphar;
    --alphai;
    --beta;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1 * 1;
    c__ -= c_offset;
    --s;
    --work;
    --iwork;
    --bwork;

    /* Function Body */
    if (*nsize < 0) {
	*info = -1;
    } else if (*thresh < 0.) {
	*info = -2;
    } else if (*nin <= 0) {
	*info = -3;
    } else if (*nout <= 0) {
	*info = -4;
    } else if (*lda < 1 || *lda < *nsize) {
	*info = -6;
    } else if (*ldc < 1 || *ldc < *nsize * *nsize / 2) {
	*info = -17;
    } else if (*liwork < *nsize + 6) {
	*info = -21;
    }

/*     Compute workspace   
        (Note: Comments in the code beginning "Workspace:" describe the   
         minimal amount of workspace needed at that point in the code,   
         as well as the preferred amount for good performance.   
         NB refers to the optimal block size for the immediately   
         following subroutine, as returned by ILAENV.) */

    minwrk = 1;
    if (*info == 0 && *lwork >= 1) {
/* Computing MAX */
	i__1 = (*nsize + 1) * 10, i__2 = *nsize * 5 * *nsize / 2;
	minwrk = max(i__1,i__2);

/*        workspace for sggesx */

	maxwrk = (*nsize + 1) * 9 + *nsize * ilaenv_(&c__1, "DGEQRF", " ", 
		nsize, &c__1, nsize, &c__0, (ftnlen)6, (ftnlen)1);
/* Computing MAX */
	i__1 = maxwrk, i__2 = (*nsize + 1) * 9 + *nsize * ilaenv_(&c__1, 
		"DORGQR", " ", nsize, &c__1, nsize, &c_n1, (ftnlen)6, (ftnlen)
		1);
	maxwrk = max(i__1,i__2);

/*        workspace for dgesvd */

	bdspac = *nsize * 5 * *nsize / 2;
/* Computing MAX */
	i__3 = *nsize * *nsize / 2;
	i__4 = *nsize * *nsize / 2;
	i__1 = maxwrk, i__2 = *nsize * 3 * *nsize / 2 + *nsize * *nsize * 
		ilaenv_(&c__1, "DGEBRD", " ", &i__3, &i__4, &c_n1, &c_n1, (
		ftnlen)6, (ftnlen)1);
	maxwrk = max(i__1,i__2);
	maxwrk = max(maxwrk,bdspac);

	maxwrk = max(maxwrk,minwrk);

	work[1] = (doublereal) maxwrk;
    }

    if (*lwork < minwrk) {
	*info = -19;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DDRGSX", &i__1);
	return 0;
    }

/*     Important constants */

    ulp = dlamch_("P");
    ulpinv = 1. / ulp;
    smlnum = dlamch_("S") / ulp;
    bignum = 1. / smlnum;
    dlabad_(&smlnum, &bignum);
    thrsh2 = *thresh * 10.;
    ntestt = 0;
    nerrs = 0;

/*     Go to the tests for read-in matrix pairs */

    ifunc = 0;
    if (*nsize == 0) {
	goto L70;
    }

/*     Test the built-in matrix pairs.   
       Loop over different functions (IFUNC) of DGGESX, types (PRTYPE)   
       of test matrices, different size (M+N) */

    prtype = 0;
    qba = 3;
    qbb = 4;
    weight = sqrt(ulp);

    for (ifunc = 0; ifunc <= 3; ++ifunc) {
	for (prtype = 1; prtype <= 5; ++prtype) {
	    i__1 = *nsize - 1;
	    for (mn_1.m = 1; mn_1.m <= i__1; ++mn_1.m) {
		i__2 = *nsize - mn_1.m;
		for (mn_1.n = 1; mn_1.n <= i__2; ++mn_1.n) {

		    weight = 1. / weight;
		    mn_1.mplusn = mn_1.m + mn_1.n;

/*                 Generate test matrices */

		    mn_1.fs = TRUE_;
		    mn_1.k = 0;

		    dlaset_("Full", &mn_1.mplusn, &mn_1.mplusn, &c_b26, &
			    c_b26, &ai[ai_offset], lda);
		    dlaset_("Full", &mn_1.mplusn, &mn_1.mplusn, &c_b26, &
			    c_b26, &bi[bi_offset], lda);

		    dlatm5_(&prtype, &mn_1.m, &mn_1.n, &ai[ai_offset], lda, &
			    ai_ref(mn_1.m + 1, mn_1.m + 1), lda, &ai_ref(1, 
			    mn_1.m + 1), lda, &bi[bi_offset], lda, &bi_ref(
			    mn_1.m + 1, mn_1.m + 1), lda, &bi_ref(1, mn_1.m + 
			    1), lda, &q[q_offset], lda, &z__[z_offset], lda, &
			    weight, &qba, &qbb);

/*                 Compute the Schur factorization and swapping the   
                   m-by-m (1,1)-blocks with n-by-n (2,2)-blocks.   
                   Swapping is accomplished via the function DLCTSX   
                   which is supplied below. */

		    if (ifunc == 0) {
			*(unsigned char *)sense = 'N';
		    } else if (ifunc == 1) {
			*(unsigned char *)sense = 'E';
		    } else if (ifunc == 2) {
			*(unsigned char *)sense = 'V';
		    } else if (ifunc == 3) {
			*(unsigned char *)sense = 'B';
		    }

		    dlacpy_("Full", &mn_1.mplusn, &mn_1.mplusn, &ai[ai_offset]
			    , lda, &a[a_offset], lda);
		    dlacpy_("Full", &mn_1.mplusn, &mn_1.mplusn, &bi[bi_offset]
			    , lda, &b[b_offset], lda);

		    dggesx_("V", "V", "S", (L_fp)dlctsx_, sense, &mn_1.mplusn,
			     &ai[ai_offset], lda, &bi[bi_offset], lda, &mm, &
			    alphar[1], &alphai[1], &beta[1], &q[q_offset], 
			    lda, &z__[z_offset], lda, pl, difest, &work[1], 
			    lwork, &iwork[1], liwork, &bwork[1], &linfo);

		    if (linfo != 0 && linfo != mn_1.mplusn + 2) {
			result[0] = ulpinv;
			io___22.ciunit = *nout;
			s_wsfe(&io___22);
			do_fio(&c__1, "DGGESX", (ftnlen)6);
			do_fio(&c__1, (char *)&linfo, (ftnlen)sizeof(integer))
				;
			do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&prtype, (ftnlen)sizeof(integer)
				);
			e_wsfe();
			*info = linfo;
			goto L30;
		    }

/*                 Compute the norm(A, B) */

		    dlacpy_("Full", &mn_1.mplusn, &mn_1.mplusn, &ai[ai_offset]
			    , lda, &work[1], &mn_1.mplusn);
		    dlacpy_("Full", &mn_1.mplusn, &mn_1.mplusn, &bi[bi_offset]
			    , lda, &work[mn_1.mplusn * mn_1.mplusn + 1], &
			    mn_1.mplusn);
		    i__3 = mn_1.mplusn << 1;
		    abnrm = dlange_("Fro", &mn_1.mplusn, &i__3, &work[1], &
			    mn_1.mplusn, &work[1]);

/*                 Do tests (1) to (4) */

		    dget51_(&c__1, &mn_1.mplusn, &a[a_offset], lda, &ai[
			    ai_offset], lda, &q[q_offset], lda, &z__[z_offset]
			    , lda, &work[1], result);
		    dget51_(&c__1, &mn_1.mplusn, &b[b_offset], lda, &bi[
			    bi_offset], lda, &q[q_offset], lda, &z__[z_offset]
			    , lda, &work[1], &result[1]);
		    dget51_(&c__3, &mn_1.mplusn, &b[b_offset], lda, &bi[
			    bi_offset], lda, &q[q_offset], lda, &q[q_offset], 
			    lda, &work[1], &result[2]);
		    dget51_(&c__3, &mn_1.mplusn, &b[b_offset], lda, &bi[
			    bi_offset], lda, &z__[z_offset], lda, &z__[
			    z_offset], lda, &work[1], &result[3]);
		    ntest = 4;

/*                 Do tests (5) and (6): check Schur form of A and   
                   compare eigenvalues with diagonals. */

		    temp1 = 0.;
		    result[4] = 0.;
		    result[5] = 0.;

		    i__3 = mn_1.mplusn;
		    for (j = 1; j <= i__3; ++j) {
			ilabad = FALSE_;
			if (alphai[j] == 0.) {
/* Computing MAX */
			    d__7 = smlnum, d__8 = (d__2 = alphar[j], abs(d__2)
				    ), d__7 = max(d__7,d__8), d__8 = (d__3 = 
				    ai_ref(j, j), abs(d__3));
/* Computing MAX */
			    d__9 = smlnum, d__10 = (d__5 = beta[j], abs(d__5))
				    , d__9 = max(d__9,d__10), d__10 = (d__6 = 
				    bi_ref(j, j), abs(d__6));
			    temp2 = ((d__1 = alphar[j] - ai_ref(j, j), abs(
				    d__1)) / max(d__7,d__8) + (d__4 = beta[j] 
				    - bi_ref(j, j), abs(d__4)) / max(d__9,
				    d__10)) / ulp;
			    if (j < mn_1.mplusn) {
				if (ai_ref(j + 1, j) != 0.) {
				    ilabad = TRUE_;
				    result[4] = ulpinv;
				}
			    }
			    if (j > 1) {
				if (ai_ref(j, j - 1) != 0.) {
				    ilabad = TRUE_;
				    result[4] = ulpinv;
				}
			    }
			} else {
			    if (alphai[j] > 0.) {
				i1 = j;
			    } else {
				i1 = j - 1;
			    }
			    if (i1 <= 0 || i1 >= mn_1.mplusn) {
				ilabad = TRUE_;
			    } else if (i1 < mn_1.mplusn - 1) {
				if (ai_ref(i1 + 2, i1 + 1) != 0.) {
				    ilabad = TRUE_;
				    result[4] = ulpinv;
				}
			    } else if (i1 > 1) {
				if (ai_ref(i1, i1 - 1) != 0.) {
				    ilabad = TRUE_;
				    result[4] = ulpinv;
				}
			    }
			    if (! ilabad) {
				dget53_(&ai_ref(i1, i1), lda, &bi_ref(i1, i1),
					 lda, &beta[j], &alphar[j], &alphai[j]
					, &temp2, &iinfo);
				if (iinfo >= 3) {
				    io___31.ciunit = *nout;
				    s_wsfe(&io___31);
				    do_fio(&c__1, (char *)&iinfo, (ftnlen)
					    sizeof(integer));
				    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(
					    integer));
				    do_fio(&c__1, (char *)&mn_1.mplusn, (
					    ftnlen)sizeof(integer));
				    do_fio(&c__1, (char *)&prtype, (ftnlen)
					    sizeof(integer));
				    e_wsfe();
				    *info = abs(iinfo);
				}
			    } else {
				temp2 = ulpinv;
			    }
			}
			temp1 = max(temp1,temp2);
			if (ilabad) {
			    io___32.ciunit = *nout;
			    s_wsfe(&io___32);
			    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)
				    sizeof(integer));
			    do_fio(&c__1, (char *)&prtype, (ftnlen)sizeof(
				    integer));
			    e_wsfe();
			}
/* L10: */
		    }
		    result[5] = temp1;
		    ntest += 2;

/*                 Test (7) (if sorting worked) */

		    result[6] = 0.;
		    if (linfo == mn_1.mplusn + 3) {
			result[6] = ulpinv;
		    } else if (mm != mn_1.n) {
			result[6] = ulpinv;
		    }
		    ++ntest;

/*                 Test (8): compare the estimated value DIF and its   
                   value. first, compute the exact DIF. */

		    result[7] = 0.;
		    mn2 = mm * (mn_1.mplusn - mm) << 1;
		    if (ifunc >= 2 && mn2 <= *ncmax * *ncmax) {

/*                    Note: for either following two causes, there are   
                      almost same number of test cases fail the test. */

			i__3 = mn_1.mplusn - mm;
			dlakf2_(&mm, &i__3, &ai[ai_offset], lda, &ai_ref(mm + 
				1, mm + 1), &bi[bi_offset], &bi_ref(mm + 1, 
				mm + 1), &c__[c_offset], ldc);

			i__3 = *lwork - 2;
			dgesvd_("N", "N", &mn2, &mn2, &c__[c_offset], ldc, &s[
				1], &work[1], &c__1, &work[2], &c__1, &work[3]
				, &i__3, info);
			diftru = s[mn2];

			if (difest[1] == 0.) {
			    if (diftru > abnrm * ulp) {
				result[7] = ulpinv;
			    }
			} else if (diftru == 0.) {
			    if (difest[1] > abnrm * ulp) {
				result[7] = ulpinv;
			    }
			} else if (diftru > thrsh2 * difest[1] || diftru * 
				thrsh2 < difest[1]) {
/* Computing MAX */
			    d__1 = diftru / difest[1], d__2 = difest[1] / 
				    diftru;
			    result[7] = max(d__1,d__2);
			}
			++ntest;
		    }

/*                 Test (9) */

		    result[8] = 0.;
		    if (linfo == mn_1.mplusn + 2) {
			if (diftru > abnrm * ulp) {
			    result[8] = ulpinv;
			}
			if (ifunc > 1 && difest[1] != 0.) {
			    result[8] = ulpinv;
			}
			if (ifunc == 1 && pl[0] != 0.) {
			    result[8] = ulpinv;
			}
			++ntest;
		    }

		    ntestt += ntest;

/*                 Print out tests which fail. */

		    for (j = 1; j <= 9; ++j) {
			if (result[j - 1] >= *thresh) {

/*                       If this is the first test to fail,   
                         print a header to the data file. */

			    if (nerrs == 0) {
				io___35.ciunit = *nout;
				s_wsfe(&io___35);
				do_fio(&c__1, "SGX", (ftnlen)3);
				e_wsfe();

/*                          Matrix types */

				io___36.ciunit = *nout;
				s_wsfe(&io___36);
				e_wsfe();

/*                          Tests performed */

				io___37.ciunit = *nout;
				s_wsfe(&io___37);
				do_fio(&c__1, "orthogonal", (ftnlen)10);
				do_fio(&c__1, "'", (ftnlen)1);
				do_fio(&c__1, "transpose", (ftnlen)9);
				for (i__ = 1; i__ <= 4; ++i__) {
				    do_fio(&c__1, "'", (ftnlen)1);
				}
				e_wsfe();

			    }
			    ++nerrs;
			    if (result[j - 1] < 1e4) {
				io___39.ciunit = *nout;
				s_wsfe(&io___39);
				do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)
					sizeof(integer));
				do_fio(&c__1, (char *)&prtype, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&weight, (ftnlen)sizeof(
					doublereal));
				do_fio(&c__1, (char *)&mn_1.m, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&j, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&result[j - 1], (ftnlen)
					sizeof(doublereal));
				e_wsfe();
			    } else {
				io___40.ciunit = *nout;
				s_wsfe(&io___40);
				do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)
					sizeof(integer));
				do_fio(&c__1, (char *)&prtype, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&weight, (ftnlen)sizeof(
					doublereal));
				do_fio(&c__1, (char *)&mn_1.m, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&j, (ftnlen)sizeof(
					integer));
				do_fio(&c__1, (char *)&result[j - 1], (ftnlen)
					sizeof(doublereal));
				e_wsfe();
			    }
			}
/* L20: */
		    }

L30:
		    ;
		}
/* L40: */
	    }
/* L50: */
	}
/* L60: */
    }

    goto L150;

L70:

/*     Read in data from file to check accuracy of condition estimation   
       Read input data until N=0 */

    nptknt = 0;

L80:
    io___42.ciunit = *nin;
    i__1 = s_rsle(&io___42);
    if (i__1 != 0) {
	goto L140;
    }
    i__1 = do_lio(&c__3, &c__1, (char *)&mn_1.mplusn, (ftnlen)sizeof(integer))
	    ;
    if (i__1 != 0) {
	goto L140;
    }
    i__1 = e_rsle();
    if (i__1 != 0) {
	goto L140;
    }
    if (mn_1.mplusn == 0) {
	goto L140;
    }
    io___43.ciunit = *nin;
    i__1 = s_rsle(&io___43);
    if (i__1 != 0) {
	goto L140;
    }
    i__1 = do_lio(&c__3, &c__1, (char *)&mn_1.n, (ftnlen)sizeof(integer));
    if (i__1 != 0) {
	goto L140;
    }
    i__1 = e_rsle();
    if (i__1 != 0) {
	goto L140;
    }
    i__1 = mn_1.mplusn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___44.ciunit = *nin;
	s_rsle(&io___44);
	i__2 = mn_1.mplusn;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__5, &c__1, (char *)&ai_ref(i__, j), (ftnlen)sizeof(
		    doublereal));
	}
	e_rsle();
/* L90: */
    }
    i__1 = mn_1.mplusn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___45.ciunit = *nin;
	s_rsle(&io___45);
	i__2 = mn_1.mplusn;
	for (j = 1; j <= i__2; ++j) {
	    do_lio(&c__5, &c__1, (char *)&bi_ref(i__, j), (ftnlen)sizeof(
		    doublereal));
	}
	e_rsle();
/* L100: */
    }
    io___46.ciunit = *nin;
    s_rsle(&io___46);
    do_lio(&c__5, &c__1, (char *)&pltru, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&diftru, (ftnlen)sizeof(doublereal));
    e_rsle();

    ++nptknt;
    mn_1.fs = TRUE_;
    mn_1.k = 0;
    mn_1.m = mn_1.mplusn - mn_1.n;

    dlacpy_("Full", &mn_1.mplusn, &mn_1.mplusn, &ai[ai_offset], lda, &a[
	    a_offset], lda);
    dlacpy_("Full", &mn_1.mplusn, &mn_1.mplusn, &bi[bi_offset], lda, &b[
	    b_offset], lda);

/*     Compute the Schur factorization while swaping the   
       m-by-m (1,1)-blocks with n-by-n (2,2)-blocks. */

    dggesx_("V", "V", "S", (L_fp)dlctsx_, "B", &mn_1.mplusn, &ai[ai_offset], 
	    lda, &bi[bi_offset], lda, &mm, &alphar[1], &alphai[1], &beta[1], &
	    q[q_offset], lda, &z__[z_offset], lda, pl, difest, &work[1], 
	    lwork, &iwork[1], liwork, &bwork[1], &linfo);

    if (linfo != 0 && linfo != mn_1.mplusn + 2) {
	result[0] = ulpinv;
	io___48.ciunit = *nout;
	s_wsfe(&io___48);
	do_fio(&c__1, "DGGESX", (ftnlen)6);
	do_fio(&c__1, (char *)&linfo, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nptknt, (ftnlen)sizeof(integer));
	e_wsfe();
	goto L130;
    }

/*     Compute the norm(A, B)   
          (should this be norm of (A,B) or (AI,BI)?) */

    dlacpy_("Full", &mn_1.mplusn, &mn_1.mplusn, &ai[ai_offset], lda, &work[1],
	     &mn_1.mplusn);
    dlacpy_("Full", &mn_1.mplusn, &mn_1.mplusn, &bi[bi_offset], lda, &work[
	    mn_1.mplusn * mn_1.mplusn + 1], &mn_1.mplusn);
    i__1 = mn_1.mplusn << 1;
    abnrm = dlange_("Fro", &mn_1.mplusn, &i__1, &work[1], &mn_1.mplusn, &work[
	    1]);

/*     Do tests (1) to (4) */

    dget51_(&c__1, &mn_1.mplusn, &a[a_offset], lda, &ai[ai_offset], lda, &q[
	    q_offset], lda, &z__[z_offset], lda, &work[1], result);
    dget51_(&c__1, &mn_1.mplusn, &b[b_offset], lda, &bi[bi_offset], lda, &q[
	    q_offset], lda, &z__[z_offset], lda, &work[1], &result[1]);
    dget51_(&c__3, &mn_1.mplusn, &b[b_offset], lda, &bi[bi_offset], lda, &q[
	    q_offset], lda, &q[q_offset], lda, &work[1], &result[2]);
    dget51_(&c__3, &mn_1.mplusn, &b[b_offset], lda, &bi[bi_offset], lda, &z__[
	    z_offset], lda, &z__[z_offset], lda, &work[1], &result[3]);

/*     Do tests (5) and (6): check Schur form of A and compare   
       eigenvalues with diagonals. */

    ntest = 6;
    temp1 = 0.;
    result[4] = 0.;
    result[5] = 0.;

    i__1 = mn_1.mplusn;
    for (j = 1; j <= i__1; ++j) {
	ilabad = FALSE_;
	if (alphai[j] == 0.) {
/* Computing MAX */
	    d__7 = smlnum, d__8 = (d__2 = alphar[j], abs(d__2)), d__7 = max(
		    d__7,d__8), d__8 = (d__3 = ai_ref(j, j), abs(d__3));
/* Computing MAX */
	    d__9 = smlnum, d__10 = (d__5 = beta[j], abs(d__5)), d__9 = max(
		    d__9,d__10), d__10 = (d__6 = bi_ref(j, j), abs(d__6));
	    temp2 = ((d__1 = alphar[j] - ai_ref(j, j), abs(d__1)) / max(d__7,
		    d__8) + (d__4 = beta[j] - bi_ref(j, j), abs(d__4)) / max(
		    d__9,d__10)) / ulp;
	    if (j < mn_1.mplusn) {
		if (ai_ref(j + 1, j) != 0.) {
		    ilabad = TRUE_;
		    result[4] = ulpinv;
		}
	    }
	    if (j > 1) {
		if (ai_ref(j, j - 1) != 0.) {
		    ilabad = TRUE_;
		    result[4] = ulpinv;
		}
	    }
	} else {
	    if (alphai[j] > 0.) {
		i1 = j;
	    } else {
		i1 = j - 1;
	    }
	    if (i1 <= 0 || i1 >= mn_1.mplusn) {
		ilabad = TRUE_;
	    } else if (i1 < mn_1.mplusn - 1) {
		if (ai_ref(i1 + 2, i1 + 1) != 0.) {
		    ilabad = TRUE_;
		    result[4] = ulpinv;
		}
	    } else if (i1 > 1) {
		if (ai_ref(i1, i1 - 1) != 0.) {
		    ilabad = TRUE_;
		    result[4] = ulpinv;
		}
	    }
	    if (! ilabad) {
		dget53_(&ai_ref(i1, i1), lda, &bi_ref(i1, i1), lda, &beta[j], 
			&alphar[j], &alphai[j], &temp2, &iinfo);
		if (iinfo >= 3) {
		    io___49.ciunit = *nout;
		    s_wsfe(&io___49);
		    do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)sizeof(
			    integer));
		    do_fio(&c__1, (char *)&nptknt, (ftnlen)sizeof(integer));
		    e_wsfe();
		    *info = abs(iinfo);
		}
	    } else {
		temp2 = ulpinv;
	    }
	}
	temp1 = max(temp1,temp2);
	if (ilabad) {
	    io___50.ciunit = *nout;
	    s_wsfe(&io___50);
	    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&nptknt, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
/* L110: */
    }
    result[5] = temp1;

/*     Test (7) (if sorting worked)  <--------- need to be checked. */

    ntest = 7;
    result[6] = 0.;
    if (linfo == mn_1.mplusn + 3) {
	result[6] = ulpinv;
    }

/*     Test (8): compare the estimated value of DIF and its true value. */

    ntest = 8;
    result[7] = 0.;
    if (difest[1] == 0.) {
	if (diftru > abnrm * ulp) {
	    result[7] = ulpinv;
	}
    } else if (diftru == 0.) {
	if (difest[1] > abnrm * ulp) {
	    result[7] = ulpinv;
	}
    } else if (diftru > thrsh2 * difest[1] || diftru * thrsh2 < difest[1]) {
/* Computing MAX */
	d__1 = diftru / difest[1], d__2 = difest[1] / diftru;
	result[7] = max(d__1,d__2);
    }

/*     Test (9) */

    ntest = 9;
    result[8] = 0.;
    if (linfo == mn_1.mplusn + 2) {
	if (diftru > abnrm * ulp) {
	    result[8] = ulpinv;
	}
	if (ifunc > 1 && difest[1] != 0.) {
	    result[8] = ulpinv;
	}
	if (ifunc == 1 && pl[0] != 0.) {
	    result[8] = ulpinv;
	}
    }

/*     Test (10): compare the estimated value of PL and it true value. */

    ntest = 10;
    result[9] = 0.;
    if (pl[0] == 0.) {
	if (pltru > abnrm * ulp) {
	    result[9] = ulpinv;
	}
    } else if (pltru == 0.) {
	if (pl[0] > abnrm * ulp) {
	    result[9] = ulpinv;
	}
    } else if (pltru > *thresh * pl[0] || pltru * *thresh < pl[0]) {
	result[9] = ulpinv;
    }

    ntestt += ntest;

/*     Print out tests which fail. */

    i__1 = ntest;
    for (j = 1; j <= i__1; ++j) {
	if (result[j - 1] >= *thresh) {

/*           If this is the first test to fail,   
             print a header to the data file. */

	    if (nerrs == 0) {
		io___51.ciunit = *nout;
		s_wsfe(&io___51);
		do_fio(&c__1, "SGX", (ftnlen)3);
		e_wsfe();

/*              Matrix types */

		io___52.ciunit = *nout;
		s_wsfe(&io___52);
		e_wsfe();

/*              Tests performed */

		io___53.ciunit = *nout;
		s_wsfe(&io___53);
		do_fio(&c__1, "orthogonal", (ftnlen)10);
		do_fio(&c__1, "'", (ftnlen)1);
		do_fio(&c__1, "transpose", (ftnlen)9);
		for (i__ = 1; i__ <= 4; ++i__) {
		    do_fio(&c__1, "'", (ftnlen)1);
		}
		e_wsfe();

	    }
	    ++nerrs;
	    if (result[j - 1] < 1e4) {
		io___54.ciunit = *nout;
		s_wsfe(&io___54);
		do_fio(&c__1, (char *)&nptknt, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&result[j - 1], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    } else {
		io___55.ciunit = *nout;
		s_wsfe(&io___55);
		do_fio(&c__1, (char *)&nptknt, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&mn_1.mplusn, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&result[j - 1], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    }
	}

/* L120: */
    }

L130:
    goto L80;
L140:

L150:

/*     Summary */

    alasvm_("SGX", nout, &nerrs, &ntestt, &c__0);

    work[1] = (doublereal) maxwrk;

    return 0;









/*     End of DDRGSX */

} /* ddrgsx_ */

#undef bi_ref
#undef ai_ref


