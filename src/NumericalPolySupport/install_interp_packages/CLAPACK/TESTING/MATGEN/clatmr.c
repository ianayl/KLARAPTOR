#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__0 = 0;
static integer c__1 = 1;

/* Subroutine */ int clatmr_(integer *m, integer *n, char *dist, integer *
	iseed, char *sym, complex *d__, integer *mode, real *cond, complex *
	dmax__, char *rsign, char *grade, complex *dl, integer *model, real *
	condl, complex *dr, integer *moder, real *condr, char *pivtng, 
	integer *ipivot, integer *kl, integer *ku, real *sparse, real *anorm, 
	char *pack, complex *a, integer *lda, integer *iwork, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
    real r__1, r__2;
    complex q__1, q__2;

    /* Builtin functions */
    double c_abs(complex *);
    void r_cnjg(complex *, complex *);

    /* Local variables */
    static integer isub, jsub;
    static real temp;
    static integer isym, i__, j, k, ipack;
    extern logical lsame_(char *, char *);
    static real tempa[1];
    static complex ctemp;
    static integer iisub, idist, jjsub, mnmin;
    static logical dzero;
    static integer mnsub;
    static real onorm;
    static integer mxsub, npvts;
    extern /* Subroutine */ int clatm1_(integer *, real *, integer *, integer 
	    *, integer *, complex *, integer *, integer *);
    extern /* Complex */ VOID clatm2_(complex *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    complex *, integer *, complex *, complex *, integer *, integer *, 
	    real *), clatm3_(complex *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, complex *, integer *, complex *, complex *, integer *, 
	    integer *, real *);
    static complex calpha;
    extern doublereal clangb_(char *, integer *, integer *, integer *, 
	    complex *, integer *, real *), clange_(char *, integer *, 
	    integer *, complex *, integer *, real *);
    static integer igrade;
    extern doublereal clansb_(char *, char *, integer *, integer *, complex *,
	     integer *, real *);
    extern /* Subroutine */ int csscal_(integer *, real *, complex *, integer 
	    *);
    static logical fulbnd;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static logical badpvt;
    extern doublereal clansp_(char *, char *, integer *, complex *, real *), clansy_(char *, char *, integer *, complex *, 
	    integer *, real *);
    static integer irsign, ipvtng, kll, kuu;


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

       CLATMR generates random matrices of various types for testing   
       LAPACK programs.   

       CLATMR operates by applying the following sequence of   
       operations:   

         Generate a matrix A with random entries of distribution DIST   
            which is symmetric if SYM='S', Hermitian if SYM='H', and   
            nonsymmetric if SYM='N'.   

         Set the diagonal to D, where D may be input or   
            computed according to MODE, COND, DMAX and RSIGN   
            as described below.   

         Grade the matrix, if desired, from the left and/or right   
            as specified by GRADE. The inputs DL, MODEL, CONDL, DR,   
            MODER and CONDR also determine the grading as described   
            below.   

         Permute, if desired, the rows and/or columns as specified by   
            PIVTNG and IPIVOT.   

         Set random entries to zero, if desired, to get a random sparse   
            matrix as specified by SPARSE.   

         Make A a band matrix, if desired, by zeroing out the matrix   
            outside a band of lower bandwidth KL and upper bandwidth KU.   

         Scale A, if desired, to have maximum entry ANORM.   

         Pack the matrix if desired. Options specified by PACK are:   
            no packing   
            zero out upper half (if symmetric or Hermitian)   
            zero out lower half (if symmetric or Hermitian)   
            store the upper half columnwise (if symmetric or Hermitian   
                or square upper triangular)   
            store the lower half columnwise (if symmetric or Hermitian   
                or square lower triangular)   
                same as upper half rowwise if symmetric   
                same as conjugate upper half rowwise if Hermitian   
            store the lower triangle in banded format   
                (if symmetric or Hermitian)   
            store the upper triangle in banded format   
                (if symmetric or Hermitian)   
            store the entire matrix in banded format   

       Note: If two calls to CLATMR differ only in the PACK parameter,   
             they will generate mathematically equivalent matrices.   

             If two calls to CLATMR both have full bandwidth (KL = M-1   
             and KU = N-1), and differ only in the PIVTNG and PACK   
             parameters, then the matrices generated will differ only   
             in the order of the rows and/or columns, and otherwise   
             contain the same data. This consistency cannot be and   
             is not maintained with less than full bandwidth.   

    Arguments   
    =========   

    M      - INTEGER   
             Number of rows of A. Not modified.   

    N      - INTEGER   
             Number of columns of A. Not modified.   

    DIST   - CHARACTER*1   
             On entry, DIST specifies the type of distribution to be used   
             to generate a random matrix .   
             'U' => real and imaginary parts are independent   
                    UNIFORM( 0, 1 )  ( 'U' for uniform )   
             'S' => real and imaginary parts are independent   
                    UNIFORM( -1, 1 ) ( 'S' for symmetric )   
             'N' => real and imaginary parts are independent   
                    NORMAL( 0, 1 )   ( 'N' for normal )   
             'D' => uniform on interior of unit disk ( 'D' for disk )   
             Not modified.   

    ISEED  - INTEGER array, dimension (4)   
             On entry ISEED specifies the seed of the random number   
             generator. They should lie between 0 and 4095 inclusive,   
             and ISEED(4) should be odd. The random number generator   
             uses a linear congruential sequence limited to small   
             integers, and so should produce machine independent   
             random numbers. The values of ISEED are changed on   
             exit, and can be used in the next call to CLATMR   
             to continue the same random number sequence.   
             Changed on exit.   

    SYM    - CHARACTER*1   
             If SYM='S', generated matrix is symmetric.   
             If SYM='H', generated matrix is Hermitian.   
             If SYM='N', generated matrix is nonsymmetric.   
             Not modified.   

    D      - COMPLEX array, dimension (min(M,N))   
             On entry this array specifies the diagonal entries   
             of the diagonal of A.  D may either be specified   
             on entry, or set according to MODE and COND as described   
             below. If the matrix is Hermitian, the real part of D   
             will be taken. May be changed on exit if MODE is nonzero.   

    MODE   - INTEGER   
             On entry describes how D is to be used:   
             MODE = 0 means use D as input   
             MODE = 1 sets D(1)=1 and D(2:N)=1.0/COND   
             MODE = 2 sets D(1:N-1)=1 and D(N)=1.0/COND   
             MODE = 3 sets D(I)=COND**(-(I-1)/(N-1))   
             MODE = 4 sets D(i)=1 - (i-1)/(N-1)*(1 - 1/COND)   
             MODE = 5 sets D to random numbers in the range   
                      ( 1/COND , 1 ) such that their logarithms   
                      are uniformly distributed.   
             MODE = 6 set D to random numbers from same distribution   
                      as the rest of the matrix.   
             MODE < 0 has the same meaning as ABS(MODE), except that   
                the order of the elements of D is reversed.   
             Thus if MODE is positive, D has entries ranging from   
                1 to 1/COND, if negative, from 1/COND to 1,   
             Not modified.   

    COND   - REAL   
             On entry, used as described under MODE above.   
             If used, it must be >= 1. Not modified.   

    DMAX   - COMPLEX   
             If MODE neither -6, 0 nor 6, the diagonal is scaled by   
             DMAX / max(abs(D(i))), so that maximum absolute entry   
             of diagonal is abs(DMAX). If DMAX is complex (or zero),   
             diagonal will be scaled by a complex number (or zero).   

    RSIGN  - CHARACTER*1   
             If MODE neither -6, 0 nor 6, specifies sign of diagonal   
             as follows:   
             'T' => diagonal entries are multiplied by a random complex   
                    number uniformly distributed with absolute value 1   
             'F' => diagonal unchanged   
             Not modified.   

    GRADE  - CHARACTER*1   
             Specifies grading of matrix as follows:   
             'N'  => no grading   
             'L'  => matrix premultiplied by diag( DL )   
                     (only if matrix nonsymmetric)   
             'R'  => matrix postmultiplied by diag( DR )   
                     (only if matrix nonsymmetric)   
             'B'  => matrix premultiplied by diag( DL ) and   
                           postmultiplied by diag( DR )   
                     (only if matrix nonsymmetric)   
             'H'  => matrix premultiplied by diag( DL ) and   
                           postmultiplied by diag( CONJG(DL) )   
                     (only if matrix Hermitian or nonsymmetric)   
             'S'  => matrix premultiplied by diag( DL ) and   
                           postmultiplied by diag( DL )   
                     (only if matrix symmetric or nonsymmetric)   
             'E'  => matrix premultiplied by diag( DL ) and   
                           postmultiplied by inv( diag( DL ) )   
                           ( 'S' for similarity )   
                     (only if matrix nonsymmetric)   
                     Note: if GRADE='S', then M must equal N.   
             Not modified.   

    DL     - COMPLEX array, dimension (M)   
             If MODEL=0, then on entry this array specifies the diagonal   
             entries of a diagonal matrix used as described under GRADE   
             above. If MODEL is not zero, then DL will be set according   
             to MODEL and CONDL, analogous to the way D is set according   
             to MODE and COND (except there is no DMAX parameter for DL).   
             If GRADE='E', then DL cannot have zero entries.   
             Not referenced if GRADE = 'N' or 'R'. Changed on exit.   

    MODEL  - INTEGER   
             This specifies how the diagonal array DL is to be computed,   
             just as MODE specifies how D is to be computed.   
             Not modified.   

    CONDL  - REAL   
             When MODEL is not zero, this specifies the condition number   
             of the computed DL.  Not modified.   

    DR     - COMPLEX array, dimension (N)   
             If MODER=0, then on entry this array specifies the diagonal   
             entries of a diagonal matrix used as described under GRADE   
             above. If MODER is not zero, then DR will be set according   
             to MODER and CONDR, analogous to the way D is set according   
             to MODE and COND (except there is no DMAX parameter for DR).   
             Not referenced if GRADE = 'N', 'L', 'H' or 'S'.   
             Changed on exit.   

    MODER  - INTEGER   
             This specifies how the diagonal array DR is to be computed,   
             just as MODE specifies how D is to be computed.   
             Not modified.   

    CONDR  - REAL   
             When MODER is not zero, this specifies the condition number   
             of the computed DR.  Not modified.   

    PIVTNG - CHARACTER*1   
             On entry specifies pivoting permutations as follows:   
             'N' or ' ' => none.   
             'L' => left or row pivoting (matrix must be nonsymmetric).   
             'R' => right or column pivoting (matrix must be   
                    nonsymmetric).   
             'B' or 'F' => both or full pivoting, i.e., on both sides.   
                           In this case, M must equal N   

             If two calls to CLATMR both have full bandwidth (KL = M-1   
             and KU = N-1), and differ only in the PIVTNG and PACK   
             parameters, then the matrices generated will differ only   
             in the order of the rows and/or columns, and otherwise   
             contain the same data. This consistency cannot be   
             maintained with less than full bandwidth.   

    IPIVOT - INTEGER array, dimension (N or M)   
             This array specifies the permutation used.  After the   
             basic matrix is generated, the rows, columns, or both   
             are permuted.   If, say, row pivoting is selected, CLATMR   
             starts with the *last* row and interchanges the M-th and   
             IPIVOT(M)-th rows, then moves to the next-to-last row,   
             interchanging the (M-1)-th and the IPIVOT(M-1)-th rows,   
             and so on.  In terms of "2-cycles", the permutation is   
             (1 IPIVOT(1)) (2 IPIVOT(2)) ... (M IPIVOT(M))   
             where the rightmost cycle is applied first.  This is the   
             *inverse* of the effect of pivoting in LINPACK.  The idea   
             is that factoring (with pivoting) an identity matrix   
             which has been inverse-pivoted in this way should   
             result in a pivot vector identical to IPIVOT.   
             Not referenced if PIVTNG = 'N'. Not modified.   

    SPARSE - REAL   
             On entry specifies the sparsity of the matrix if a sparse   
             matrix is to be generated. SPARSE should lie between   
             0 and 1. To generate a sparse matrix, for each matrix entry   
             a uniform ( 0, 1 ) random number x is generated and   
             compared to SPARSE; if x is larger the matrix entry   
             is unchanged and if x is smaller the entry is set   
             to zero. Thus on the average a fraction SPARSE of the   
             entries will be set to zero.   
             Not modified.   

    KL     - INTEGER   
             On entry specifies the lower bandwidth of the  matrix. For   
             example, KL=0 implies upper triangular, KL=1 implies upper   
             Hessenberg, and KL at least M-1 implies the matrix is not   
             banded. Must equal KU if matrix is symmetric or Hermitian.   
             Not modified.   

    KU     - INTEGER   
             On entry specifies the upper bandwidth of the  matrix. For   
             example, KU=0 implies lower triangular, KU=1 implies lower   
             Hessenberg, and KU at least N-1 implies the matrix is not   
             banded. Must equal KL if matrix is symmetric or Hermitian.   
             Not modified.   

    ANORM  - REAL   
             On entry specifies maximum entry of output matrix   
             (output matrix will by multiplied by a constant so that   
             its largest absolute entry equal ANORM)   
             if ANORM is nonnegative. If ANORM is negative no scaling   
             is done. Not modified.   

    PACK   - CHARACTER*1   
             On entry specifies packing of matrix as follows:   
             'N' => no packing   
             'U' => zero out all subdiagonal entries   
                    (if symmetric or Hermitian)   
             'L' => zero out all superdiagonal entries   
                    (if symmetric or Hermitian)   
             'C' => store the upper triangle columnwise   
                    (only if matrix symmetric or Hermitian or   
                     square upper triangular)   
             'R' => store the lower triangle columnwise   
                    (only if matrix symmetric or Hermitian or   
                     square lower triangular)   
                    (same as upper half rowwise if symmetric)   
                    (same as conjugate upper half rowwise if Hermitian)   
             'B' => store the lower triangle in band storage scheme   
                    (only if matrix symmetric or Hermitian)   
             'Q' => store the upper triangle in band storage scheme   
                    (only if matrix symmetric or Hermitian)   
             'Z' => store the entire matrix in band storage scheme   
                        (pivoting can be provided for by using this   
                        option to store A in the trailing rows of   
                        the allocated storage)   

             Using these options, the various LAPACK packed and banded   
             storage schemes can be obtained:   
             GB               - use 'Z'   
             PB, HB or TB     - use 'B' or 'Q'   
             PP, HP or TP     - use 'C' or 'R'   

             If two calls to CLATMR differ only in the PACK parameter,   
             they will generate mathematically equivalent matrices.   
             Not modified.   

    A      - COMPLEX array, dimension (LDA,N)   
             On exit A is the desired test matrix. Only those   
             entries of A which are significant on output   
             will be referenced (even if A is in packed or band   
             storage format). The 'unoccupied corners' of A in   
             band format will be zeroed out.   

    LDA    - INTEGER   
             on entry LDA specifies the first dimension of A as   
             declared in the calling program.   
             If PACK='N', 'U' or 'L', LDA must be at least max ( 1, M ).   
             If PACK='C' or 'R', LDA must be at least 1.   
             If PACK='B', or 'Q', LDA must be MIN ( KU+1, N )   
             If PACK='Z', LDA must be at least KUU+KLL+1, where   
             KUU = MIN ( KU, N-1 ) and KLL = MIN ( KL, N-1 )   
             Not modified.   

    IWORK  - INTEGER array, dimension (N or M)   
             Workspace. Not referenced if PIVTNG = 'N'. Changed on exit.   

    INFO   - INTEGER   
             Error parameter on exit:   
               0 => normal return   
              -1 => M negative or unequal to N and SYM='S' or 'H'   
              -2 => N negative   
              -3 => DIST illegal string   
              -5 => SYM illegal string   
              -7 => MODE not in range -6 to 6   
              -8 => COND less than 1.0, and MODE neither -6, 0 nor 6   
             -10 => MODE neither -6, 0 nor 6 and RSIGN illegal string   
             -11 => GRADE illegal string, or GRADE='E' and   
                    M not equal to N, or GRADE='L', 'R', 'B', 'S' or 'E'   
                    and SYM = 'H', or GRADE='L', 'R', 'B', 'H' or 'E'   
                    and SYM = 'S'   
             -12 => GRADE = 'E' and DL contains zero   
             -13 => MODEL not in range -6 to 6 and GRADE= 'L', 'B', 'H',   
                    'S' or 'E'   
             -14 => CONDL less than 1.0, GRADE='L', 'B', 'H', 'S' or 'E',   
                    and MODEL neither -6, 0 nor 6   
             -16 => MODER not in range -6 to 6 and GRADE= 'R' or 'B'   
             -17 => CONDR less than 1.0, GRADE='R' or 'B', and   
                    MODER neither -6, 0 nor 6   
             -18 => PIVTNG illegal string, or PIVTNG='B' or 'F' and   
                    M not equal to N, or PIVTNG='L' or 'R' and SYM='S'   
                    or 'H'   
             -19 => IPIVOT contains out of range number and   
                    PIVTNG not equal to 'N'   
             -20 => KL negative   
             -21 => KU negative, or SYM='S' or 'H' and KU not equal to KL   
             -22 => SPARSE not in range 0. to 1.   
             -24 => PACK illegal string, or PACK='U', 'L', 'B' or 'Q'   
                    and SYM='N', or PACK='C' and SYM='N' and either KL   
                    not equal to 0 or N not equal to M, or PACK='R' and   
                    SYM='N', and either KU not equal to 0 or N not equal   
                    to M   
             -26 => LDA too small   
               1 => Error return from CLATM1 (computing D)   
               2 => Cannot scale diagonal to DMAX (max. entry is 0)   
               3 => Error return from CLATM1 (computing DL)   
               4 => Error return from CLATM1 (computing DR)   
               5 => ANORM is positive, but matrix constructed prior to   
                    attempting to scale it to have norm ANORM, is zero   

    =====================================================================   


       1)      Decode and Test the input parameters.   
               Initialize flags & seed.   

       Parameter adjustments */
    --iseed;
    --d__;
    --dl;
    --dr;
    --ipivot;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --iwork;

    /* Function Body */
    *info = 0;

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Decode DIST */

    if (lsame_(dist, "U")) {
	idist = 1;
    } else if (lsame_(dist, "S")) {
	idist = 2;
    } else if (lsame_(dist, "N")) {
	idist = 3;
    } else if (lsame_(dist, "D")) {
	idist = 4;
    } else {
	idist = -1;
    }

/*     Decode SYM */

    if (lsame_(sym, "H")) {
	isym = 0;
    } else if (lsame_(sym, "N")) {
	isym = 1;
    } else if (lsame_(sym, "S")) {
	isym = 2;
    } else {
	isym = -1;
    }

/*     Decode RSIGN */

    if (lsame_(rsign, "F")) {
	irsign = 0;
    } else if (lsame_(rsign, "T")) {
	irsign = 1;
    } else {
	irsign = -1;
    }

/*     Decode PIVTNG */

    if (lsame_(pivtng, "N")) {
	ipvtng = 0;
    } else if (lsame_(pivtng, " ")) {
	ipvtng = 0;
    } else if (lsame_(pivtng, "L")) {
	ipvtng = 1;
	npvts = *m;
    } else if (lsame_(pivtng, "R")) {
	ipvtng = 2;
	npvts = *n;
    } else if (lsame_(pivtng, "B")) {
	ipvtng = 3;
	npvts = min(*n,*m);
    } else if (lsame_(pivtng, "F")) {
	ipvtng = 3;
	npvts = min(*n,*m);
    } else {
	ipvtng = -1;
    }

/*     Decode GRADE */

    if (lsame_(grade, "N")) {
	igrade = 0;
    } else if (lsame_(grade, "L")) {
	igrade = 1;
    } else if (lsame_(grade, "R")) {
	igrade = 2;
    } else if (lsame_(grade, "B")) {
	igrade = 3;
    } else if (lsame_(grade, "E")) {
	igrade = 4;
    } else if (lsame_(grade, "H")) {
	igrade = 5;
    } else if (lsame_(grade, "S")) {
	igrade = 6;
    } else {
	igrade = -1;
    }

/*     Decode PACK */

    if (lsame_(pack, "N")) {
	ipack = 0;
    } else if (lsame_(pack, "U")) {
	ipack = 1;
    } else if (lsame_(pack, "L")) {
	ipack = 2;
    } else if (lsame_(pack, "C")) {
	ipack = 3;
    } else if (lsame_(pack, "R")) {
	ipack = 4;
    } else if (lsame_(pack, "B")) {
	ipack = 5;
    } else if (lsame_(pack, "Q")) {
	ipack = 6;
    } else if (lsame_(pack, "Z")) {
	ipack = 7;
    } else {
	ipack = -1;
    }

/*     Set certain internal parameters */

    mnmin = min(*m,*n);
/* Computing MIN */
    i__1 = *kl, i__2 = *m - 1;
    kll = min(i__1,i__2);
/* Computing MIN */
    i__1 = *ku, i__2 = *n - 1;
    kuu = min(i__1,i__2);

/*     If inv(DL) is used, check to see if DL has a zero entry. */

    dzero = FALSE_;
    if (igrade == 4 && *model == 0) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__;
	    if (dl[i__2].r == 0.f && dl[i__2].i == 0.f) {
		dzero = TRUE_;
	    }
/* L10: */
	}
    }

/*     Check values in IPIVOT */

    badpvt = FALSE_;
    if (ipvtng > 0) {
	i__1 = npvts;
	for (j = 1; j <= i__1; ++j) {
	    if (ipivot[j] <= 0 || ipivot[j] > npvts) {
		badpvt = TRUE_;
	    }
/* L20: */
	}
    }

/*     Set INFO if an error */

    if (*m < 0) {
	*info = -1;
    } else if (*m != *n && (isym == 0 || isym == 2)) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (idist == -1) {
	*info = -3;
    } else if (isym == -1) {
	*info = -5;
    } else if (*mode < -6 || *mode > 6) {
	*info = -7;
    } else if (*mode != -6 && *mode != 0 && *mode != 6 && *cond < 1.f) {
	*info = -8;
    } else if (*mode != -6 && *mode != 0 && *mode != 6 && irsign == -1) {
	*info = -10;
    } else if (igrade == -1 || igrade == 4 && *m != *n || (igrade == 1 || 
	    igrade == 2 || igrade == 3 || igrade == 4 || igrade == 6) && isym 
	    == 0 || (igrade == 1 || igrade == 2 || igrade == 3 || igrade == 4 
	    || igrade == 5) && isym == 2) {
	*info = -11;
    } else if (igrade == 4 && dzero) {
	*info = -12;
    } else if ((igrade == 1 || igrade == 3 || igrade == 4 || igrade == 5 || 
	    igrade == 6) && (*model < -6 || *model > 6)) {
	*info = -13;
    } else if ((igrade == 1 || igrade == 3 || igrade == 4 || igrade == 5 || 
	    igrade == 6) && (*model != -6 && *model != 0 && *model != 6) && *
	    condl < 1.f) {
	*info = -14;
    } else if ((igrade == 2 || igrade == 3) && (*moder < -6 || *moder > 6)) {
	*info = -16;
    } else if ((igrade == 2 || igrade == 3) && (*moder != -6 && *moder != 0 &&
	     *moder != 6) && *condr < 1.f) {
	*info = -17;
    } else if (ipvtng == -1 || ipvtng == 3 && *m != *n || (ipvtng == 1 || 
	    ipvtng == 2) && (isym == 0 || isym == 2)) {
	*info = -18;
    } else if (ipvtng != 0 && badpvt) {
	*info = -19;
    } else if (*kl < 0) {
	*info = -20;
    } else if (*ku < 0 || (isym == 0 || isym == 2) && *kl != *ku) {
	*info = -21;
    } else if (*sparse < 0.f || *sparse > 1.f) {
	*info = -22;
    } else if (ipack == -1 || (ipack == 1 || ipack == 2 || ipack == 5 || 
	    ipack == 6) && isym == 1 || ipack == 3 && isym == 1 && (*kl != 0 
	    || *m != *n) || ipack == 4 && isym == 1 && (*ku != 0 || *m != *n))
	     {
	*info = -24;
    } else if ((ipack == 0 || ipack == 1 || ipack == 2) && *lda < max(1,*m) ||
	     (ipack == 3 || ipack == 4) && *lda < 1 || (ipack == 5 || ipack ==
	     6) && *lda < kuu + 1 || ipack == 7 && *lda < kll + kuu + 1) {
	*info = -26;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CLATMR", &i__1);
	return 0;
    }

/*     Decide if we can pivot consistently */

    fulbnd = FALSE_;
    if (kuu == *n - 1 && kll == *m - 1) {
	fulbnd = TRUE_;
    }

/*     Initialize random number generator */

    for (i__ = 1; i__ <= 4; ++i__) {
	iseed[i__] = (i__1 = iseed[i__], abs(i__1)) % 4096;
/* L30: */
    }

    iseed[4] = (iseed[4] / 2 << 1) + 1;

/*     2)      Set up D, DL, and DR, if indicated.   

               Compute D according to COND and MODE */

    clatm1_(mode, cond, &irsign, &idist, &iseed[1], &d__[1], &mnmin, info);
    if (*info != 0) {
	*info = 1;
	return 0;
    }
    if (*mode != 0 && *mode != -6 && *mode != 6) {

/*        Scale by DMAX */

	temp = c_abs(&d__[1]);
	i__1 = mnmin;
	for (i__ = 2; i__ <= i__1; ++i__) {
/* Computing MAX */
	    r__1 = temp, r__2 = c_abs(&d__[i__]);
	    temp = dmax(r__1,r__2);
/* L40: */
	}
	if (temp == 0.f && (dmax__->r != 0.f || dmax__->i != 0.f)) {
	    *info = 2;
	    return 0;
	}
	if (temp != 0.f) {
	    q__1.r = dmax__->r / temp, q__1.i = dmax__->i / temp;
	    calpha.r = q__1.r, calpha.i = q__1.i;
	} else {
	    calpha.r = 1.f, calpha.i = 0.f;
	}
	i__1 = mnmin;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__;
	    i__3 = i__;
	    q__1.r = calpha.r * d__[i__3].r - calpha.i * d__[i__3].i, q__1.i =
		     calpha.r * d__[i__3].i + calpha.i * d__[i__3].r;
	    d__[i__2].r = q__1.r, d__[i__2].i = q__1.i;
/* L50: */
	}

    }

/*     If matrix Hermitian, make D real */

    if (isym == 0) {
	i__1 = mnmin;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i__2 = i__;
	    i__3 = i__;
	    r__1 = d__[i__3].r;
	    d__[i__2].r = r__1, d__[i__2].i = 0.f;
/* L60: */
	}
    }

/*     Compute DL if grading set */

    if (igrade == 1 || igrade == 3 || igrade == 4 || igrade == 5 || igrade == 
	    6) {
	clatm1_(model, condl, &c__0, &idist, &iseed[1], &dl[1], m, info);
	if (*info != 0) {
	    *info = 3;
	    return 0;
	}
    }

/*     Compute DR if grading set */

    if (igrade == 2 || igrade == 3) {
	clatm1_(moder, condr, &c__0, &idist, &iseed[1], &dr[1], n, info);
	if (*info != 0) {
	    *info = 4;
	    return 0;
	}
    }

/*     3)     Generate IWORK if pivoting */

    if (ipvtng > 0) {
	i__1 = npvts;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    iwork[i__] = i__;
/* L70: */
	}
	if (fulbnd) {
	    i__1 = npvts;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		k = ipivot[i__];
		j = iwork[i__];
		iwork[i__] = iwork[k];
		iwork[k] = j;
/* L80: */
	    }
	} else {
	    for (i__ = npvts; i__ >= 1; --i__) {
		k = ipivot[i__];
		j = iwork[i__];
		iwork[i__] = iwork[k];
		iwork[k] = j;
/* L90: */
	    }
	}
    }

/*     4)      Generate matrices for each kind of PACKing   
               Always sweep matrix columnwise (if symmetric, upper   
               half only) so that matrix generated does not depend   
               on PACK */

    if (fulbnd) {

/*        Use CLATM3 so matrices generated with differing PIVOTing only   
          differ only in the order of their rows and/or columns. */

	if (ipack == 0) {
	    if (isym == 0) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
				idist, &iseed[1], &d__[1], &igrade, &dl[1], &
				dr[1], &ipvtng, &iwork[1], sparse);
			ctemp.r = q__1.r, ctemp.i = q__1.i;
			i__3 = a_subscr(isub, jsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
			i__3 = a_subscr(jsub, isub);
			r_cnjg(&q__1, &ctemp);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
/* L100: */
		    }
/* L110: */
		}
	    } else if (isym == 1) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
				idist, &iseed[1], &d__[1], &igrade, &dl[1], &
				dr[1], &ipvtng, &iwork[1], sparse);
			ctemp.r = q__1.r, ctemp.i = q__1.i;
			i__3 = a_subscr(isub, jsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
/* L120: */
		    }
/* L130: */
		}
	    } else if (isym == 2) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
				idist, &iseed[1], &d__[1], &igrade, &dl[1], &
				dr[1], &ipvtng, &iwork[1], sparse);
			ctemp.r = q__1.r, ctemp.i = q__1.i;
			i__3 = a_subscr(isub, jsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
			i__3 = a_subscr(jsub, isub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
/* L140: */
		    }
/* L150: */
		}
	    }

	} else if (ipack == 1) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
			    idist, &iseed[1], &d__[1], &igrade, &dl[1], &dr[1]
			    , &ipvtng, &iwork[1], sparse);
		    ctemp.r = q__1.r, ctemp.i = q__1.i;
		    mnsub = min(isub,jsub);
		    mxsub = max(isub,jsub);
		    if (mxsub == isub && isym == 0) {
			i__3 = a_subscr(mnsub, mxsub);
			r_cnjg(&q__1, &ctemp);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
		    } else {
			i__3 = a_subscr(mnsub, mxsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
		    }
		    if (mnsub != mxsub) {
			i__3 = a_subscr(mxsub, mnsub);
			a[i__3].r = 0.f, a[i__3].i = 0.f;
		    }
/* L160: */
		}
/* L170: */
	    }

	} else if (ipack == 2) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
			    idist, &iseed[1], &d__[1], &igrade, &dl[1], &dr[1]
			    , &ipvtng, &iwork[1], sparse);
		    ctemp.r = q__1.r, ctemp.i = q__1.i;
		    mnsub = min(isub,jsub);
		    mxsub = max(isub,jsub);
		    if (mxsub == jsub && isym == 0) {
			i__3 = a_subscr(mxsub, mnsub);
			r_cnjg(&q__1, &ctemp);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
		    } else {
			i__3 = a_subscr(mxsub, mnsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
		    }
		    if (mnsub != mxsub) {
			i__3 = a_subscr(mnsub, mxsub);
			a[i__3].r = 0.f, a[i__3].i = 0.f;
		    }
/* L180: */
		}
/* L190: */
	    }

	} else if (ipack == 3) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
			    idist, &iseed[1], &d__[1], &igrade, &dl[1], &dr[1]
			    , &ipvtng, &iwork[1], sparse);
		    ctemp.r = q__1.r, ctemp.i = q__1.i;

/*                 Compute K = location of (ISUB,JSUB) entry in packed   
                   array */

		    mnsub = min(isub,jsub);
		    mxsub = max(isub,jsub);
		    k = mxsub * (mxsub - 1) / 2 + mnsub;

/*                 Convert K to (IISUB,JJSUB) location */

		    jjsub = (k - 1) / *lda + 1;
		    iisub = k - *lda * (jjsub - 1);

		    if (mxsub == isub && isym == 0) {
			i__3 = a_subscr(iisub, jjsub);
			r_cnjg(&q__1, &ctemp);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
		    } else {
			i__3 = a_subscr(iisub, jjsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
		    }
/* L200: */
		}
/* L210: */
	    }

	} else if (ipack == 4) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
			    idist, &iseed[1], &d__[1], &igrade, &dl[1], &dr[1]
			    , &ipvtng, &iwork[1], sparse);
		    ctemp.r = q__1.r, ctemp.i = q__1.i;

/*                 Compute K = location of (I,J) entry in packed array */

		    mnsub = min(isub,jsub);
		    mxsub = max(isub,jsub);
		    if (mnsub == 1) {
			k = mxsub;
		    } else {
			k = *n * (*n + 1) / 2 - (*n - mnsub + 1) * (*n - 
				mnsub + 2) / 2 + mxsub - mnsub + 1;
		    }

/*                 Convert K to (IISUB,JJSUB) location */

		    jjsub = (k - 1) / *lda + 1;
		    iisub = k - *lda * (jjsub - 1);

		    if (mxsub == jsub && isym == 0) {
			i__3 = a_subscr(iisub, jjsub);
			r_cnjg(&q__1, &ctemp);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
		    } else {
			i__3 = a_subscr(iisub, jjsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
		    }
/* L220: */
		}
/* L230: */
	    }

	} else if (ipack == 5) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = j - kuu; i__ <= i__2; ++i__) {
		    if (i__ < 1) {
			i__3 = a_subscr(j - i__ + 1, i__ + *n);
			a[i__3].r = 0.f, a[i__3].i = 0.f;
		    } else {
			clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
				idist, &iseed[1], &d__[1], &igrade, &dl[1], &
				dr[1], &ipvtng, &iwork[1], sparse);
			ctemp.r = q__1.r, ctemp.i = q__1.i;
			mnsub = min(isub,jsub);
			mxsub = max(isub,jsub);
			if (mxsub == jsub && isym == 0) {
			    i__3 = a_subscr(mxsub - mnsub + 1, mnsub);
			    r_cnjg(&q__1, &ctemp);
			    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			} else {
			    i__3 = a_subscr(mxsub - mnsub + 1, mnsub);
			    a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
			}
		    }
/* L240: */
		}
/* L250: */
	    }

	} else if (ipack == 6) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = j - kuu; i__ <= i__2; ++i__) {
		    clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
			    idist, &iseed[1], &d__[1], &igrade, &dl[1], &dr[1]
			    , &ipvtng, &iwork[1], sparse);
		    ctemp.r = q__1.r, ctemp.i = q__1.i;
		    mnsub = min(isub,jsub);
		    mxsub = max(isub,jsub);
		    if (mxsub == isub && isym == 0) {
			i__3 = a_subscr(mnsub - mxsub + kuu + 1, mxsub);
			r_cnjg(&q__1, &ctemp);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
		    } else {
			i__3 = a_subscr(mnsub - mxsub + kuu + 1, mxsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
		    }
/* L260: */
		}
/* L270: */
	    }

	} else if (ipack == 7) {

	    if (isym != 1) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j;
		    for (i__ = j - kuu; i__ <= i__2; ++i__) {
			clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
				idist, &iseed[1], &d__[1], &igrade, &dl[1], &
				dr[1], &ipvtng, &iwork[1], sparse);
			ctemp.r = q__1.r, ctemp.i = q__1.i;
			mnsub = min(isub,jsub);
			mxsub = max(isub,jsub);
			if (i__ < 1) {
			    i__3 = a_subscr(j - i__ + 1 + kuu, i__ + *n);
			    a[i__3].r = 0.f, a[i__3].i = 0.f;
			}
			if (mxsub == isub && isym == 0) {
			    i__3 = a_subscr(mnsub - mxsub + kuu + 1, mxsub);
			    r_cnjg(&q__1, &ctemp);
			    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			} else {
			    i__3 = a_subscr(mnsub - mxsub + kuu + 1, mxsub);
			    a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
			}
			if (i__ >= 1 && mnsub != mxsub) {
			    if (mnsub == isub && isym == 0) {
				i__3 = a_subscr(mxsub - mnsub + 1 + kuu, 
					mnsub);
				r_cnjg(&q__1, &ctemp);
				a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			    } else {
				i__3 = a_subscr(mxsub - mnsub + 1 + kuu, 
					mnsub);
				a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
			    }
			}
/* L280: */
		    }
/* L290: */
		}
	    } else if (isym == 1) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j + kll;
		    for (i__ = j - kuu; i__ <= i__2; ++i__) {
			clatm3_(&q__1, m, n, &i__, &j, &isub, &jsub, kl, ku, &
				idist, &iseed[1], &d__[1], &igrade, &dl[1], &
				dr[1], &ipvtng, &iwork[1], sparse);
			ctemp.r = q__1.r, ctemp.i = q__1.i;
			i__3 = a_subscr(isub - jsub + kuu + 1, jsub);
			a[i__3].r = ctemp.r, a[i__3].i = ctemp.i;
/* L300: */
		    }
/* L310: */
		}
	    }

	}

    } else {

/*        Use CLATM2 */

	if (ipack == 0) {
	    if (isym == 0) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			i__3 = a_subscr(i__, j);
			clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			i__3 = a_subscr(j, i__);
			r_cnjg(&q__1, &a_ref(i__, j));
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
/* L320: */
		    }
/* L330: */
		}
	    } else if (isym == 1) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			i__3 = a_subscr(i__, j);
			clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
/* L340: */
		    }
/* L350: */
		}
	    } else if (isym == 2) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			i__3 = a_subscr(i__, j);
			clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			i__3 = a_subscr(j, i__);
			i__4 = a_subscr(i__, j);
			a[i__3].r = a[i__4].r, a[i__3].i = a[i__4].i;
/* L360: */
		    }
/* L370: */
		}
	    }

	} else if (ipack == 1) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    i__3 = a_subscr(i__, j);
		    clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[1], 
			    &d__[1], &igrade, &dl[1], &dr[1], &ipvtng, &iwork[
			    1], sparse);
		    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
		    if (i__ != j) {
			i__3 = a_subscr(j, i__);
			a[i__3].r = 0.f, a[i__3].i = 0.f;
		    }
/* L380: */
		}
/* L390: */
	    }

	} else if (ipack == 2) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    if (isym == 0) {
			i__3 = a_subscr(j, i__);
			clatm2_(&q__2, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			r_cnjg(&q__1, &q__2);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
		    } else {
			i__3 = a_subscr(j, i__);
			clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
		    }
		    if (i__ != j) {
			i__3 = a_subscr(i__, j);
			a[i__3].r = 0.f, a[i__3].i = 0.f;
		    }
/* L400: */
		}
/* L410: */
	    }

	} else if (ipack == 3) {

	    isub = 0;
	    jsub = 1;
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    ++isub;
		    if (isub > *lda) {
			isub = 1;
			++jsub;
		    }
		    i__3 = a_subscr(isub, jsub);
		    clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[1], 
			    &d__[1], &igrade, &dl[1], &dr[1], &ipvtng, &iwork[
			    1], sparse);
		    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
/* L420: */
		}
/* L430: */
	    }

	} else if (ipack == 4) {

	    if (isym == 0 || isym == 2) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j;
		    for (i__ = 1; i__ <= i__2; ++i__) {

/*                    Compute K = location of (I,J) entry in packed array */

			if (i__ == 1) {
			    k = j;
			} else {
			    k = *n * (*n + 1) / 2 - (*n - i__ + 1) * (*n - 
				    i__ + 2) / 2 + j - i__ + 1;
			}

/*                    Convert K to (ISUB,JSUB) location */

			jsub = (k - 1) / *lda + 1;
			isub = k - *lda * (jsub - 1);

			i__3 = a_subscr(isub, jsub);
			clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			if (isym == 0) {
			    i__3 = a_subscr(isub, jsub);
			    r_cnjg(&q__1, &a_ref(isub, jsub));
			    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			}
/* L440: */
		    }
/* L450: */
		}
	    } else {
		isub = 0;
		jsub = 1;
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = j; i__ <= i__2; ++i__) {
			++isub;
			if (isub > *lda) {
			    isub = 1;
			    ++jsub;
			}
			i__3 = a_subscr(isub, jsub);
			clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
/* L460: */
		    }
/* L470: */
		}
	    }

	} else if (ipack == 5) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = j - kuu; i__ <= i__2; ++i__) {
		    if (i__ < 1) {
			i__3 = a_subscr(j - i__ + 1, i__ + *n);
			a[i__3].r = 0.f, a[i__3].i = 0.f;
		    } else {
			if (isym == 0) {
			    i__3 = a_subscr(j - i__ + 1, i__);
			    clatm2_(&q__2, m, n, &i__, &j, kl, ku, &idist, &
				    iseed[1], &d__[1], &igrade, &dl[1], &dr[1]
				    , &ipvtng, &iwork[1], sparse);
			    r_cnjg(&q__1, &q__2);
			    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			} else {
			    i__3 = a_subscr(j - i__ + 1, i__);
			    clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &
				    iseed[1], &d__[1], &igrade, &dl[1], &dr[1]
				    , &ipvtng, &iwork[1], sparse);
			    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			}
		    }
/* L480: */
		}
/* L490: */
	    }

	} else if (ipack == 6) {

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = j;
		for (i__ = j - kuu; i__ <= i__2; ++i__) {
		    i__3 = a_subscr(i__ - j + kuu + 1, j);
		    clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[1], 
			    &d__[1], &igrade, &dl[1], &dr[1], &ipvtng, &iwork[
			    1], sparse);
		    a[i__3].r = q__1.r, a[i__3].i = q__1.i;
/* L500: */
		}
/* L510: */
	    }

	} else if (ipack == 7) {

	    if (isym != 1) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j;
		    for (i__ = j - kuu; i__ <= i__2; ++i__) {
			i__3 = a_subscr(i__ - j + kuu + 1, j);
			clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			if (i__ < 1) {
			    i__3 = a_subscr(j - i__ + 1 + kuu, i__ + *n);
			    a[i__3].r = 0.f, a[i__3].i = 0.f;
			}
			if (i__ >= 1 && i__ != j) {
			    if (isym == 0) {
				i__3 = a_subscr(j - i__ + 1 + kuu, i__);
				r_cnjg(&q__1, &a_ref(i__ - j + kuu + 1, j));
				a[i__3].r = q__1.r, a[i__3].i = q__1.i;
			    } else {
				i__3 = a_subscr(j - i__ + 1 + kuu, i__);
				i__4 = a_subscr(i__ - j + kuu + 1, j);
				a[i__3].r = a[i__4].r, a[i__3].i = a[i__4].i;
			    }
			}
/* L520: */
		    }
/* L530: */
		}
	    } else if (isym == 1) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = j + kll;
		    for (i__ = j - kuu; i__ <= i__2; ++i__) {
			i__3 = a_subscr(i__ - j + kuu + 1, j);
			clatm2_(&q__1, m, n, &i__, &j, kl, ku, &idist, &iseed[
				1], &d__[1], &igrade, &dl[1], &dr[1], &ipvtng,
				 &iwork[1], sparse);
			a[i__3].r = q__1.r, a[i__3].i = q__1.i;
/* L540: */
		    }
/* L550: */
		}
	    }

	}

    }

/*     5)      Scaling the norm */

    if (ipack == 0) {
	onorm = clange_("M", m, n, &a[a_offset], lda, tempa);
    } else if (ipack == 1) {
	onorm = clansy_("M", "U", n, &a[a_offset], lda, tempa);
    } else if (ipack == 2) {
	onorm = clansy_("M", "L", n, &a[a_offset], lda, tempa);
    } else if (ipack == 3) {
	onorm = clansp_("M", "U", n, &a[a_offset], tempa);
    } else if (ipack == 4) {
	onorm = clansp_("M", "L", n, &a[a_offset], tempa);
    } else if (ipack == 5) {
	onorm = clansb_("M", "L", n, &kll, &a[a_offset], lda, tempa);
    } else if (ipack == 6) {
	onorm = clansb_("M", "U", n, &kuu, &a[a_offset], lda, tempa);
    } else if (ipack == 7) {
	onorm = clangb_("M", n, &kll, &kuu, &a[a_offset], lda, tempa);
    }

    if (*anorm >= 0.f) {

	if (*anorm > 0.f && onorm == 0.f) {

/*           Desired scaling impossible */

	    *info = 5;
	    return 0;

	} else if (*anorm > 1.f && onorm < 1.f || *anorm < 1.f && onorm > 1.f)
		 {

/*           Scale carefully to avoid over / underflow */

	    if (ipack <= 2) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    r__1 = 1.f / onorm;
		    csscal_(m, &r__1, &a_ref(1, j), &c__1);
		    csscal_(m, anorm, &a_ref(1, j), &c__1);
/* L560: */
		}

	    } else if (ipack == 3 || ipack == 4) {

		i__1 = *n * (*n + 1) / 2;
		r__1 = 1.f / onorm;
		csscal_(&i__1, &r__1, &a[a_offset], &c__1);
		i__1 = *n * (*n + 1) / 2;
		csscal_(&i__1, anorm, &a[a_offset], &c__1);

	    } else if (ipack >= 5) {

		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = kll + kuu + 1;
		    r__1 = 1.f / onorm;
		    csscal_(&i__2, &r__1, &a_ref(1, j), &c__1);
		    i__2 = kll + kuu + 1;
		    csscal_(&i__2, anorm, &a_ref(1, j), &c__1);
/* L570: */
		}

	    }

	} else {

/*           Scale straightforwardly */

	    if (ipack <= 2) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    r__1 = *anorm / onorm;
		    csscal_(m, &r__1, &a_ref(1, j), &c__1);
/* L580: */
		}

	    } else if (ipack == 3 || ipack == 4) {

		i__1 = *n * (*n + 1) / 2;
		r__1 = *anorm / onorm;
		csscal_(&i__1, &r__1, &a[a_offset], &c__1);

	    } else if (ipack >= 5) {

		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = kll + kuu + 1;
		    r__1 = *anorm / onorm;
		    csscal_(&i__2, &r__1, &a_ref(1, j), &c__1);
/* L590: */
		}
	    }

	}

    }

/*     End of CLATMR */

    return 0;
} /* clatmr_ */

#undef a_ref
#undef a_subscr


