#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static doublereal c_b17 = 0.;
static integer c__2 = 2;
static doublereal c_b23 = 1.;
static integer c__3 = 3;
static integer c__4 = 4;
static logical c_true = TRUE_;
static logical c_false = FALSE_;

/* Subroutine */ int ddrgev_(integer *nsizes, integer *nn, integer *ntypes, 
	logical *dotype, integer *iseed, doublereal *thresh, integer *nounit, 
	doublereal *a, integer *lda, doublereal *b, doublereal *s, doublereal 
	*t, doublereal *q, integer *ldq, doublereal *z__, doublereal *qe, 
	integer *ldqe, doublereal *alphar, doublereal *alphai, doublereal *
	beta, doublereal *alphr1, doublereal *alphi1, doublereal *beta1, 
	doublereal *work, integer *lwork, doublereal *result, integer *info)
{
    /* Initialized data */

    static integer kclass[26] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,
	    2,2,2,3 };
    static integer kbmagn[26] = { 1,1,1,1,1,1,1,1,3,2,3,2,2,3,1,1,1,1,1,1,1,3,
	    2,3,2,1 };
    static integer ktrian[26] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
	    1,1,1,1 };
    static integer iasign[26] = { 0,0,0,0,0,0,2,0,2,2,0,0,2,2,2,0,2,0,0,0,2,2,
	    2,2,2,0 };
    static integer ibsign[26] = { 0,0,0,0,0,0,0,2,0,0,2,2,0,0,2,0,2,0,0,0,0,0,
	    0,0,0,0 };
    static integer kz1[6] = { 0,1,2,1,3,3 };
    static integer kz2[6] = { 0,0,1,2,1,1 };
    static integer kadd[6] = { 0,0,0,0,3,2 };
    static integer katype[26] = { 0,1,0,1,2,3,4,1,4,4,1,1,4,4,4,2,4,5,8,7,9,4,
	    4,4,4,0 };
    static integer kbtype[26] = { 0,0,1,1,2,-3,1,4,1,1,4,4,1,1,-4,2,-4,8,8,8,
	    8,8,8,8,8,0 };
    static integer kazero[26] = { 1,1,1,1,1,1,2,1,2,2,1,1,2,2,3,1,3,5,5,5,5,3,
	    3,3,3,1 };
    static integer kbzero[26] = { 1,1,1,1,1,1,1,2,1,1,2,2,1,1,4,1,4,6,6,6,6,4,
	    4,4,4,1 };
    static integer kamagn[26] = { 1,1,1,1,1,1,1,1,2,3,2,3,2,3,1,1,1,1,1,1,1,2,
	    3,3,2,1 };

    /* Format strings */
    static char fmt_9999[] = "(\002 DDRGEV: \002,a,\002 returned INFO=\002,i"
	    "6,\002.\002,/3x,\002N=\002,i6,\002, JTYPE=\002,i6,\002, ISEED="
	    "(\002,4(i4,\002,\002),i5,\002)\002)";
    static char fmt_9998[] = "(\002 DDRGEV: \002,a,\002 Eigenvectors from"
	    " \002,a,\002 incorrectly \002,\002normalized.\002,/\002 Bits of "
	    "error=\002,0p,g10.3,\002,\002,3x,\002N=\002,i4,\002, JTYPE=\002,"
	    "i3,\002, ISEED=(\002,4(i4,\002,\002),i5,\002)\002)";
    static char fmt_9997[] = "(/1x,a3,\002 -- Real Generalized eigenvalue pr"
	    "oblem driver\002)";
    static char fmt_9996[] = "(\002 Matrix types (see DDRGEV for details):"
	    " \002)";
    static char fmt_9995[] = "(\002 Special Matrices:\002,23x,\002(J'=transp"
	    "osed Jordan block)\002,/\002   1=(0,0)  2=(I,0)  3=(0,I)  4=(I,I"
	    ")  5=(J',J')  \002,\0026=(diag(J',I), diag(I,J'))\002,/\002 Diag"
	    "onal Matrices:  ( \002,\002D=diag(0,1,2,...) )\002,/\002   7=(D,"
	    "I)   9=(large*D, small*I\002,\002)  11=(large*I, small*D)  13=(l"
	    "arge*D, large*I)\002,/\002   8=(I,D)  10=(small*D, large*I)  12="
	    "(small*I, large*D) \002,\002 14=(small*D, small*I)\002,/\002  15"
	    "=(D, reversed D)\002)";
    static char fmt_9994[] = "(\002 Matrices Rotated by Random \002,a,\002 M"
	    "atrices U, V:\002,/\002  16=Transposed Jordan Blocks            "
	    " 19=geometric \002,\002alpha, beta=0,1\002,/\002  17=arithm. alp"
	    "ha&beta             \002,\002      20=arithmetic alpha, beta=0,"
	    "1\002,/\002  18=clustered \002,\002alpha, beta=0,1            21"
	    "=random alpha, beta=0,1\002,/\002 Large & Small Matrices:\002,"
	    "/\002  22=(large, small)   \002,\00223=(small,large)    24=(smal"
	    "l,small)    25=(large,large)\002,/\002  26=random O(1) matrices"
	    ".\002)";
    static char fmt_9993[] = "(/\002 Tests performed:    \002,/\002 1 = max "
	    "| ( b A - a B )'*l | / const.,\002,/\002 2 = | |VR(i)| - 1 | / u"
	    "lp,\002,/\002 3 = max | ( b A - a B )*r | / const.\002,/\002 4 ="
	    " | |VL(i)| - 1 | / ulp,\002,/\002 5 = 0 if W same no matter if r"
	    " or l computed,\002,/\002 6 = 0 if l same no matter if l compute"
	    "d,\002,/\002 7 = 0 if r same no matter if r computed,\002,/1x)";
    static char fmt_9992[] = "(\002 Matrix order=\002,i5,\002, type=\002,i2"
	    ",\002, seed=\002,4(i4,\002,\002),\002 result \002,i2,\002 is\002"
	    ",0p,f8.2)";
    static char fmt_9991[] = "(\002 Matrix order=\002,i5,\002, type=\002,i2"
	    ",\002, seed=\002,4(i4,\002,\002),\002 result \002,i2,\002 is\002"
	    ",1p,d10.3)";

    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, q_dim1, q_offset, qe_dim1, 
	    qe_offset, s_dim1, s_offset, t_dim1, t_offset, z_dim1, z_offset, 
	    i__1, i__2, i__3, i__4;
    doublereal d__1;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer iadd, ierr, nmax, i__, j, n;
    static logical badnn;
    extern /* Subroutine */ int dget52_(logical *, integer *, doublereal *, 
	    integer *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), dggev_(char *, char *, integer *, doublereal *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, integer *);
    static doublereal rmagn[4];
    static integer nmats, jsize, nerrs, jtype, n1;
    extern /* Subroutine */ int dlatm4_(integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    integer *, integer *, doublereal *, integer *), dorm2r_(char *, 
	    char *, integer *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *), dlabad_(doublereal *, doublereal *);
    static integer jc, in;
    extern doublereal dlamch_(char *);
    static integer jr;
    extern /* Subroutine */ int dlarfg_(integer *, doublereal *, doublereal *,
	     integer *, doublereal *);
    extern doublereal dlarnd_(integer *, integer *);
    static doublereal safmin;
    static integer ioldsd[4];
    static doublereal safmax;
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    extern /* Subroutine */ int dlacpy_(char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, integer *), 
	    alasvm_(char *, integer *, integer *, integer *, integer *), dlaset_(char *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, integer *), xerbla_(char *, 
	    integer *);
    static integer minwrk, maxwrk;
    static doublereal ulpinv;
    static integer mtypes, ntestt;
    static doublereal ulp;

    /* Fortran I/O blocks */
    static cilist io___38 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___41 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___42 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___44 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___45 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___46 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___47 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___48 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___49 = { 0, 0, 0, fmt_9994, 0 };
    static cilist io___50 = { 0, 0, 0, fmt_9993, 0 };
    static cilist io___51 = { 0, 0, 0, fmt_9992, 0 };
    static cilist io___52 = { 0, 0, 0, fmt_9991, 0 };



#define a_ref(a_1,a_2) a[(a_2)*a_dim1 + a_1]
#define b_ref(a_1,a_2) b[(a_2)*b_dim1 + a_1]
#define q_ref(a_1,a_2) q[(a_2)*q_dim1 + a_1]
#define z___ref(a_1,a_2) z__[(a_2)*z_dim1 + a_1]
#define qe_ref(a_1,a_2) qe[(a_2)*qe_dim1 + a_1]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    DDRGEV checks the nonsymmetric generalized eigenvalue problem driver   
    routine DGGEV.   

    DGGEV computes for a pair of n-by-n nonsymmetric matrices (A,B) the   
    generalized eigenvalues and, optionally, the left and right   
    eigenvectors.   

    A generalized eigenvalue for a pair of matrices (A,B) is a scalar w   
    or a ratio  alpha/beta = w, such that A - w*B is singular.  It is   
    usually represented as the pair (alpha,beta), as there is reasonalbe   
    interpretation for beta=0, and even for both being zero.   

    A right generalized eigenvector corresponding to a generalized   
    eigenvalue  w  for a pair of matrices (A,B) is a vector r  such that   
    (A - wB) * r = 0.  A left generalized eigenvector is a vector l such   
    that l**H * (A - wB) = 0, where l**H is the conjugate-transpose of l.   

    When DDRGEV is called, a number of matrix "sizes" ("n's") and a   
    number of matrix "types" are specified.  For each size ("n")   
    and each type of matrix, a pair of matrices (A, B) will be generated   
    and used for testing.  For each matrix pair, the following tests   
    will be performed and compared with the threshhold THRESH.   

    Results from DGGEV:   

    (1)  max over all left eigenvalue/-vector pairs (alpha/beta,l) of   

         | VL**H * (beta A - alpha B) |/( ulp max(|beta A|, |alpha B|) )   

         where VL**H is the conjugate-transpose of VL.   

    (2)  | |VL(i)| - 1 | / ulp and whether largest component real   

         VL(i) denotes the i-th column of VL.   

    (3)  max over all left eigenvalue/-vector pairs (alpha/beta,r) of   

         | (beta A - alpha B) * VR | / ( ulp max(|beta A|, |alpha B|) )   

    (4)  | |VR(i)| - 1 | / ulp and whether largest component real   

         VR(i) denotes the i-th column of VR.   

    (5)  W(full) = W(partial)   
         W(full) denotes the eigenvalues computed when both l and r   
         are also computed, and W(partial) denotes the eigenvalues   
         computed when only W, only W and r, or only W and l are   
         computed.   

    (6)  VL(full) = VL(partial)   
         VL(full) denotes the left eigenvectors computed when both l   
         and r are computed, and VL(partial) denotes the result   
         when only l is computed.   

    (7)  VR(full) = VR(partial)   
         VR(full) denotes the right eigenvectors computed when both l   
         and r are also computed, and VR(partial) denotes the result   
         when only l is computed.   


    Test Matrices   
    ---- --------   

    The sizes of the test matrices are specified by an array   
    NN(1:NSIZES); the value of each element NN(j) specifies one size.   
    The "types" are specified by a logical array DOTYPE( 1:NTYPES ); if   
    DOTYPE(j) is .TRUE., then matrix type "j" will be generated.   
    Currently, the list of possible types is:   

    (1)  ( 0, 0 )         (a pair of zero matrices)   

    (2)  ( I, 0 )         (an identity and a zero matrix)   

    (3)  ( 0, I )         (an identity and a zero matrix)   

    (4)  ( I, I )         (a pair of identity matrices)   

            t   t   
    (5)  ( J , J  )       (a pair of transposed Jordan blocks)   

                                        t                ( I   0  )   
    (6)  ( X, Y )         where  X = ( J   0  )  and Y = (      t )   
                                     ( 0   I  )          ( 0   J  )   
                          and I is a k x k identity and J a (k+1)x(k+1)   
                          Jordan block; k=(N-1)/2   

    (7)  ( D, I )         where D is diag( 0, 1,..., N-1 ) (a diagonal   
                          matrix with those diagonal entries.)   
    (8)  ( I, D )   

    (9)  ( big*D, small*I ) where "big" is near overflow and small=1/big   

    (10) ( small*D, big*I )   

    (11) ( big*I, small*D )   

    (12) ( small*I, big*D )   

    (13) ( big*D, big*I )   

    (14) ( small*D, small*I )   

    (15) ( D1, D2 )        where D1 is diag( 0, 0, 1, ..., N-3, 0 ) and   
                           D2 is diag( 0, N-3, N-4,..., 1, 0, 0 )   
              t   t   
    (16) Q ( J , J ) Z     where Q and Z are random orthogonal matrices.   

    (17) Q ( T1, T2 ) Z    where T1 and T2 are upper triangular matrices   
                           with random O(1) entries above the diagonal   
                           and diagonal entries diag(T1) =   
                           ( 0, 0, 1, ..., N-3, 0 ) and diag(T2) =   
                           ( 0, N-3, N-4,..., 1, 0, 0 )   

    (18) Q ( T1, T2 ) Z    diag(T1) = ( 0, 0, 1, 1, s, ..., s, 0 )   
                           diag(T2) = ( 0, 1, 0, 1,..., 1, 0 )   
                           s = machine precision.   

    (19) Q ( T1, T2 ) Z    diag(T1)=( 0,0,1,1, 1-d, ..., 1-(N-5)*d=s, 0 )   
                           diag(T2) = ( 0, 1, 0, 1, ..., 1, 0 )   

                                                           N-5   
    (20) Q ( T1, T2 ) Z    diag(T1)=( 0, 0, 1, 1, a, ..., a   =s, 0 )   
                           diag(T2) = ( 0, 1, 0, 1, ..., 1, 0, 0 )   

    (21) Q ( T1, T2 ) Z    diag(T1)=( 0, 0, 1, r1, r2, ..., r(N-4), 0 )   
                           diag(T2) = ( 0, 1, 0, 1, ..., 1, 0, 0 )   
                           where r1,..., r(N-4) are random.   

    (22) Q ( big*T1, small*T2 ) Z    diag(T1) = ( 0, 0, 1, ..., N-3, 0 )   
                                     diag(T2) = ( 0, 1, ..., 1, 0, 0 )   

    (23) Q ( small*T1, big*T2 ) Z    diag(T1) = ( 0, 0, 1, ..., N-3, 0 )   
                                     diag(T2) = ( 0, 1, ..., 1, 0, 0 )   

    (24) Q ( small*T1, small*T2 ) Z  diag(T1) = ( 0, 0, 1, ..., N-3, 0 )   
                                     diag(T2) = ( 0, 1, ..., 1, 0, 0 )   

    (25) Q ( big*T1, big*T2 ) Z      diag(T1) = ( 0, 0, 1, ..., N-3, 0 )   
                                     diag(T2) = ( 0, 1, ..., 1, 0, 0 )   

    (26) Q ( T1, T2 ) Z     where T1 and T2 are random upper-triangular   
                            matrices.   


    Arguments   
    =========   

    NSIZES  (input) INTEGER   
            The number of sizes of matrices to use.  If it is zero,   
            DDRGES does nothing.  NSIZES >= 0.   

    NN      (input) INTEGER array, dimension (NSIZES)   
            An array containing the sizes to be used for the matrices.   
            Zero values will be skipped.  NN >= 0.   

    NTYPES  (input) INTEGER   
            The number of elements in DOTYPE.   If it is zero, DDRGES   
            does nothing.  It must be at least zero.  If it is MAXTYP+1   
            and NSIZES is 1, then an additional type, MAXTYP+1 is   
            defined, which is to use whatever matrix is in A.  This   
            is only useful if DOTYPE(1:MAXTYP) is .FALSE. and   
            DOTYPE(MAXTYP+1) is .TRUE. .   

    DOTYPE  (input) LOGICAL array, dimension (NTYPES)   
            If DOTYPE(j) is .TRUE., then for each size in NN a   
            matrix of that size and of type j will be generated.   
            If NTYPES is smaller than the maximum number of types   
            defined (PARAMETER MAXTYP), then types NTYPES+1 through   
            MAXTYP will not be generated. If NTYPES is larger   
            than MAXTYP, DOTYPE(MAXTYP+1) through DOTYPE(NTYPES)   
            will be ignored.   

    ISEED   (input/output) INTEGER array, dimension (4)   
            On entry ISEED specifies the seed of the random number   
            generator. The array elements should be between 0 and 4095;   
            if not they will be reduced mod 4096. Also, ISEED(4) must   
            be odd.  The random number generator uses a linear   
            congruential sequence limited to small integers, and so   
            should produce machine independent random numbers. The   
            values of ISEED are changed on exit, and can be used in the   
            next call to DDRGES to continue the same random number   
            sequence.   

    THRESH  (input) DOUBLE PRECISION   
            A test will count as "failed" if the "error", computed as   
            described above, exceeds THRESH.  Note that the error is   
            scaled to be O(1), so THRESH should be a reasonably small   
            multiple of 1, e.g., 10 or 100.  In particular, it should   
            not depend on the precision (single vs. double) or the size   
            of the matrix.  It must be at least zero.   

    NOUNIT  (input) INTEGER   
            The FORTRAN unit number for printing out error messages   
            (e.g., if a routine returns IERR not equal to 0.)   

    A       (input/workspace) DOUBLE PRECISION array,   
                                         dimension(LDA, max(NN))   
            Used to hold the original A matrix.  Used as input only   
            if NTYPES=MAXTYP+1, DOTYPE(1:MAXTYP)=.FALSE., and   
            DOTYPE(MAXTYP+1)=.TRUE.   

    LDA     (input) INTEGER   
            The leading dimension of A, B, S, and T.   
            It must be at least 1 and at least max( NN ).   

    B       (input/workspace) DOUBLE PRECISION array,   
                                         dimension(LDA, max(NN))   
            Used to hold the original B matrix.  Used as input only   
            if NTYPES=MAXTYP+1, DOTYPE(1:MAXTYP)=.FALSE., and   
            DOTYPE(MAXTYP+1)=.TRUE.   

    S       (workspace) DOUBLE PRECISION array,   
                                   dimension (LDA, max(NN))   
            The Schur form matrix computed from A by DGGES.  On exit, S   
            contains the Schur form matrix corresponding to the matrix   
            in A.   

    T       (workspace) DOUBLE PRECISION array,   
                                   dimension (LDA, max(NN))   
            The upper triangular matrix computed from B by DGGES.   

    Q       (workspace) DOUBLE PRECISION array,   
                                   dimension (LDQ, max(NN))   
            The (left) eigenvectors matrix computed by DGGEV.   

    LDQ     (input) INTEGER   
            The leading dimension of Q and Z. It must   
            be at least 1 and at least max( NN ).   

    Z       (workspace) DOUBLE PRECISION array, dimension( LDQ, max(NN) )   
            The (right) orthogonal matrix computed by DGGES.   

    QE      (workspace) DOUBLE PRECISION array, dimension( LDQ, max(NN) )   
            QE holds the computed right or left eigenvectors.   

    LDQE    (input) INTEGER   
            The leading dimension of QE. LDQE >= max(1,max(NN)).   

    ALPHAR  (workspace) DOUBLE PRECISION array, dimension (max(NN))   
    ALPHAI  (workspace) DOUBLE PRECISION array, dimension (max(NN))   
    BETA    (workspace) DOUBLE PRECISION array, dimension (max(NN))   
            The generalized eigenvalues of (A,B) computed by DGGEV.   
            ( ALPHAR(k)+ALPHAI(k)*i ) / BETA(k) is the k-th   
            generalized eigenvalue of A and B.   

    ALPHR1  (workspace) DOUBLE PRECISION array, dimension (max(NN))   
    ALPHI1  (workspace) DOUBLE PRECISION array, dimension (max(NN))   
    BETA1   (workspace) DOUBLE PRECISION array, dimension (max(NN))   
            Like ALPHAR, ALPHAI, BETA, these arrays contain the   
            eigenvalues of A and B, but those computed when DGGEV only   
            computes a partial eigendecomposition, i.e. not the   
            eigenvalues and left and right eigenvectors.   

    WORK    (workspace) DOUBLE PRECISION array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The number of entries in WORK.  LWORK >= MAX( 8*N, N*(N+1) ).   

    RESULT  (output) DOUBLE PRECISION array, dimension (2)   
            The values computed by the tests described above.   
            The values are currently limited to 1/ulp, to avoid overflow.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value.   
            > 0:  A routine returned an error code.  INFO is the   
                  absolute value of the INFO value returned.   

    =====================================================================   

       Parameter adjustments */
    --nn;
    --dotype;
    --iseed;
    t_dim1 = *lda;
    t_offset = 1 + t_dim1 * 1;
    t -= t_offset;
    s_dim1 = *lda;
    s_offset = 1 + s_dim1 * 1;
    s -= s_offset;
    b_dim1 = *lda;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    z_dim1 = *ldq;
    z_offset = 1 + z_dim1 * 1;
    z__ -= z_offset;
    q_dim1 = *ldq;
    q_offset = 1 + q_dim1 * 1;
    q -= q_offset;
    qe_dim1 = *ldqe;
    qe_offset = 1 + qe_dim1 * 1;
    qe -= qe_offset;
    --alphar;
    --alphai;
    --beta;
    --alphr1;
    --alphi1;
    --beta1;
    --work;
    --result;

    /* Function Body   

       Check for errors */

    *info = 0;

    badnn = FALSE_;
    nmax = 1;
    i__1 = *nsizes;
    for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	i__2 = nmax, i__3 = nn[j];
	nmax = max(i__2,i__3);
	if (nn[j] < 0) {
	    badnn = TRUE_;
	}
/* L10: */
    }

    if (*nsizes < 0) {
	*info = -1;
    } else if (badnn) {
	*info = -2;
    } else if (*ntypes < 0) {
	*info = -3;
    } else if (*thresh < 0.) {
	*info = -6;
    } else if (*lda <= 1 || *lda < nmax) {
	*info = -9;
    } else if (*ldq <= 1 || *ldq < nmax) {
	*info = -14;
    } else if (*ldqe <= 1 || *ldqe < nmax) {
	*info = -17;
    }

/*     Compute workspace   
        (Note: Comments in the code beginning "Workspace:" describe the   
         minimal amount of workspace needed at that point in the code,   
         as well as the preferred amount for good performance.   
         NB refers to the optimal block size for the immediately   
         following subroutine, as returned by ILAENV. */

    minwrk = 1;
    if (*info == 0 && *lwork >= 1) {
/* Computing MAX */
	i__1 = 1, i__2 = nmax << 3, i__1 = max(i__1,i__2), i__2 = nmax * (
		nmax + 1);
	minwrk = max(i__1,i__2);
	maxwrk = nmax * 7 + nmax * ilaenv_(&c__1, "DGEQRF", " ", &nmax, &c__1,
		 &nmax, &c__0, (ftnlen)6, (ftnlen)1);
/* Computing MAX */
	i__1 = maxwrk, i__2 = nmax * (nmax + 1);
	maxwrk = max(i__1,i__2);
	work[1] = (doublereal) maxwrk;
    }

    if (*lwork < minwrk) {
	*info = -25;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DDRGEV", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*nsizes == 0 || *ntypes == 0) {
	return 0;
    }

    safmin = dlamch_("Safe minimum");
    ulp = dlamch_("Epsilon") * dlamch_("Base");
    safmin /= ulp;
    safmax = 1. / safmin;
    dlabad_(&safmin, &safmax);
    ulpinv = 1. / ulp;

/*     The values RMAGN(2:3) depend on N, see below. */

    rmagn[0] = 0.;
    rmagn[1] = 1.;

/*     Loop over sizes, types */

    ntestt = 0;
    nerrs = 0;
    nmats = 0;

    i__1 = *nsizes;
    for (jsize = 1; jsize <= i__1; ++jsize) {
	n = nn[jsize];
	n1 = max(1,n);
	rmagn[2] = safmax * ulp / (doublereal) n1;
	rmagn[3] = safmin * ulpinv * n1;

	if (*nsizes != 1) {
	    mtypes = min(26,*ntypes);
	} else {
	    mtypes = min(27,*ntypes);
	}

	i__2 = mtypes;
	for (jtype = 1; jtype <= i__2; ++jtype) {
	    if (! dotype[jtype]) {
		goto L210;
	    }
	    ++nmats;

/*           Save ISEED in case of an error. */

	    for (j = 1; j <= 4; ++j) {
		ioldsd[j - 1] = iseed[j];
/* L20: */
	    }

/*           Generate test matrices A and B   

             Description of control parameters:   

             KZLASS: =1 means w/o rotation, =2 means w/ rotation,   
                     =3 means random.   
             KATYPE: the "type" to be passed to DLATM4 for computing A.   
             KAZERO: the pattern of zeros on the diagonal for A:   
                     =1: ( xxx ), =2: (0, xxx ) =3: ( 0, 0, xxx, 0 ),   
                     =4: ( 0, xxx, 0, 0 ), =5: ( 0, 0, 1, xxx, 0 ),   
                     =6: ( 0, 1, 0, xxx, 0 ).  (xxx means a string of   
                     non-zero entries.)   
             KAMAGN: the magnitude of the matrix: =0: zero, =1: O(1),   
                     =2: large, =3: small.   
             IASIGN: 1 if the diagonal elements of A are to be   
                     multiplied by a random magnitude 1 number, =2 if   
                     randomly chosen diagonal blocks are to be rotated   
                     to form 2x2 blocks.   
             KBTYPE, KBZERO, KBMAGN, IBSIGN: the same, but for B.   
             KTRIAN: =0: don't fill in the upper triangle, =1: do.   
             KZ1, KZ2, KADD: used to implement KAZERO and KBZERO.   
             RMAGN: used to implement KAMAGN and KBMAGN. */

	    if (mtypes > 26) {
		goto L100;
	    }
	    ierr = 0;
	    if (kclass[jtype - 1] < 3) {

/*              Generate A (w/o rotation) */

		if ((i__3 = katype[jtype - 1], abs(i__3)) == 3) {
		    in = ((n - 1) / 2 << 1) + 1;
		    if (in != n) {
			dlaset_("Full", &n, &n, &c_b17, &c_b17, &a[a_offset], 
				lda);
		    }
		} else {
		    in = n;
		}
		dlatm4_(&katype[jtype - 1], &in, &kz1[kazero[jtype - 1] - 1], 
			&kz2[kazero[jtype - 1] - 1], &iasign[jtype - 1], &
			rmagn[kamagn[jtype - 1]], &ulp, &rmagn[ktrian[jtype - 
			1] * kamagn[jtype - 1]], &c__2, &iseed[1], &a[
			a_offset], lda);
		iadd = kadd[kazero[jtype - 1] - 1];
		if (iadd > 0 && iadd <= n) {
		    a_ref(iadd, iadd) = 1.;
		}

/*              Generate B (w/o rotation) */

		if ((i__3 = kbtype[jtype - 1], abs(i__3)) == 3) {
		    in = ((n - 1) / 2 << 1) + 1;
		    if (in != n) {
			dlaset_("Full", &n, &n, &c_b17, &c_b17, &b[b_offset], 
				lda);
		    }
		} else {
		    in = n;
		}
		dlatm4_(&kbtype[jtype - 1], &in, &kz1[kbzero[jtype - 1] - 1], 
			&kz2[kbzero[jtype - 1] - 1], &ibsign[jtype - 1], &
			rmagn[kbmagn[jtype - 1]], &c_b23, &rmagn[ktrian[jtype 
			- 1] * kbmagn[jtype - 1]], &c__2, &iseed[1], &b[
			b_offset], lda);
		iadd = kadd[kbzero[jtype - 1] - 1];
		if (iadd != 0 && iadd <= n) {
		    b_ref(iadd, iadd) = 1.;
		}

		if (kclass[jtype - 1] == 2 && n > 0) {

/*                 Include rotations   

                   Generate Q, Z as Householder transformations times   
                   a diagonal matrix. */

		    i__3 = n - 1;
		    for (jc = 1; jc <= i__3; ++jc) {
			i__4 = n;
			for (jr = jc; jr <= i__4; ++jr) {
			    q_ref(jr, jc) = dlarnd_(&c__3, &iseed[1]);
			    z___ref(jr, jc) = dlarnd_(&c__3, &iseed[1]);
/* L30: */
			}
			i__4 = n + 1 - jc;
			dlarfg_(&i__4, &q_ref(jc, jc), &q_ref(jc + 1, jc), &
				c__1, &work[jc]);
			work[(n << 1) + jc] = d_sign(&c_b23, &q_ref(jc, jc));
			q_ref(jc, jc) = 1.;
			i__4 = n + 1 - jc;
			dlarfg_(&i__4, &z___ref(jc, jc), &z___ref(jc + 1, jc),
				 &c__1, &work[n + jc]);
			work[n * 3 + jc] = d_sign(&c_b23, &z___ref(jc, jc));
			z___ref(jc, jc) = 1.;
/* L40: */
		    }
		    q_ref(n, n) = 1.;
		    work[n] = 0.;
		    d__1 = dlarnd_(&c__2, &iseed[1]);
		    work[n * 3] = d_sign(&c_b23, &d__1);
		    z___ref(n, n) = 1.;
		    work[n * 2] = 0.;
		    d__1 = dlarnd_(&c__2, &iseed[1]);
		    work[n * 4] = d_sign(&c_b23, &d__1);

/*                 Apply the diagonal matrices */

		    i__3 = n;
		    for (jc = 1; jc <= i__3; ++jc) {
			i__4 = n;
			for (jr = 1; jr <= i__4; ++jr) {
			    a_ref(jr, jc) = work[(n << 1) + jr] * work[n * 3 
				    + jc] * a_ref(jr, jc);
			    b_ref(jr, jc) = work[(n << 1) + jr] * work[n * 3 
				    + jc] * b_ref(jr, jc);
/* L50: */
			}
/* L60: */
		    }
		    i__3 = n - 1;
		    dorm2r_("L", "N", &n, &n, &i__3, &q[q_offset], ldq, &work[
			    1], &a[a_offset], lda, &work[(n << 1) + 1], &ierr);
		    if (ierr != 0) {
			goto L90;
		    }
		    i__3 = n - 1;
		    dorm2r_("R", "T", &n, &n, &i__3, &z__[z_offset], ldq, &
			    work[n + 1], &a[a_offset], lda, &work[(n << 1) + 
			    1], &ierr);
		    if (ierr != 0) {
			goto L90;
		    }
		    i__3 = n - 1;
		    dorm2r_("L", "N", &n, &n, &i__3, &q[q_offset], ldq, &work[
			    1], &b[b_offset], lda, &work[(n << 1) + 1], &ierr);
		    if (ierr != 0) {
			goto L90;
		    }
		    i__3 = n - 1;
		    dorm2r_("R", "T", &n, &n, &i__3, &z__[z_offset], ldq, &
			    work[n + 1], &b[b_offset], lda, &work[(n << 1) + 
			    1], &ierr);
		    if (ierr != 0) {
			goto L90;
		    }
		}
	    } else {

/*              Random matrices */

		i__3 = n;
		for (jc = 1; jc <= i__3; ++jc) {
		    i__4 = n;
		    for (jr = 1; jr <= i__4; ++jr) {
			a_ref(jr, jc) = rmagn[kamagn[jtype - 1]] * dlarnd_(&
				c__2, &iseed[1]);
			b_ref(jr, jc) = rmagn[kbmagn[jtype - 1]] * dlarnd_(&
				c__2, &iseed[1]);
/* L70: */
		    }
/* L80: */
		}
	    }

L90:

	    if (ierr != 0) {
		io___38.ciunit = *nounit;
		s_wsfe(&io___38);
		do_fio(&c__1, "Generator", (ftnlen)9);
		do_fio(&c__1, (char *)&ierr, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(ierr);
		return 0;
	    }

L100:

	    for (i__ = 1; i__ <= 7; ++i__) {
		result[i__] = -1.;
/* L110: */
	    }

/*           Call DGGEV to compute eigenvalues and eigenvectors. */

	    dlacpy_(" ", &n, &n, &a[a_offset], lda, &s[s_offset], lda);
	    dlacpy_(" ", &n, &n, &b[b_offset], lda, &t[t_offset], lda);
	    dggev_("V", "V", &n, &s[s_offset], lda, &t[t_offset], lda, &
		    alphar[1], &alphai[1], &beta[1], &q[q_offset], ldq, &z__[
		    z_offset], ldq, &work[1], lwork, &ierr);
	    if (ierr != 0 && ierr != n + 1) {
		result[1] = ulpinv;
		io___40.ciunit = *nounit;
		s_wsfe(&io___40);
		do_fio(&c__1, "DGGEV1", (ftnlen)6);
		do_fio(&c__1, (char *)&ierr, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(ierr);
		goto L190;
	    }

/*           Do the tests (1) and (2) */

	    dget52_(&c_true, &n, &a[a_offset], lda, &b[b_offset], lda, &q[
		    q_offset], ldq, &alphar[1], &alphai[1], &beta[1], &work[1]
		    , &result[1]);
	    if (result[2] > *thresh) {
		io___41.ciunit = *nounit;
		s_wsfe(&io___41);
		do_fio(&c__1, "Left", (ftnlen)4);
		do_fio(&c__1, "DGGEV1", (ftnlen)6);
		do_fio(&c__1, (char *)&result[2], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
	    }

/*           Do the tests (3) and (4) */

	    dget52_(&c_false, &n, &a[a_offset], lda, &b[b_offset], lda, &z__[
		    z_offset], ldq, &alphar[1], &alphai[1], &beta[1], &work[1]
		    , &result[3]);
	    if (result[4] > *thresh) {
		io___42.ciunit = *nounit;
		s_wsfe(&io___42);
		do_fio(&c__1, "Right", (ftnlen)5);
		do_fio(&c__1, "DGGEV1", (ftnlen)6);
		do_fio(&c__1, (char *)&result[4], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
	    }

/*           Do the test (5) */

	    dlacpy_(" ", &n, &n, &a[a_offset], lda, &s[s_offset], lda);
	    dlacpy_(" ", &n, &n, &b[b_offset], lda, &t[t_offset], lda);
	    dggev_("N", "N", &n, &s[s_offset], lda, &t[t_offset], lda, &
		    alphr1[1], &alphi1[1], &beta1[1], &q[q_offset], ldq, &z__[
		    z_offset], ldq, &work[1], lwork, &ierr);
	    if (ierr != 0 && ierr != n + 1) {
		result[1] = ulpinv;
		io___43.ciunit = *nounit;
		s_wsfe(&io___43);
		do_fio(&c__1, "DGGEV2", (ftnlen)6);
		do_fio(&c__1, (char *)&ierr, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(ierr);
		goto L190;
	    }

	    i__3 = n;
	    for (j = 1; j <= i__3; ++j) {
		if (alphar[j] != alphr1[j] || alphai[j] != alphi1[j] || beta[
			j] != beta1[j]) {
		    result[5] = ulpinv;
		}
/* L120: */
	    }

/*           Do the test (6): Compute eigenvalues and left eigenvectors,   
             and test them */

	    dlacpy_(" ", &n, &n, &a[a_offset], lda, &s[s_offset], lda);
	    dlacpy_(" ", &n, &n, &b[b_offset], lda, &t[t_offset], lda);
	    dggev_("V", "N", &n, &s[s_offset], lda, &t[t_offset], lda, &
		    alphr1[1], &alphi1[1], &beta1[1], &qe[qe_offset], ldqe, &
		    z__[z_offset], ldq, &work[1], lwork, &ierr);
	    if (ierr != 0 && ierr != n + 1) {
		result[1] = ulpinv;
		io___44.ciunit = *nounit;
		s_wsfe(&io___44);
		do_fio(&c__1, "DGGEV3", (ftnlen)6);
		do_fio(&c__1, (char *)&ierr, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(ierr);
		goto L190;
	    }

	    i__3 = n;
	    for (j = 1; j <= i__3; ++j) {
		if (alphar[j] != alphr1[j] || alphai[j] != alphi1[j] || beta[
			j] != beta1[j]) {
		    result[6] = ulpinv;
		}
/* L130: */
	    }

	    i__3 = n;
	    for (j = 1; j <= i__3; ++j) {
		i__4 = n;
		for (jc = 1; jc <= i__4; ++jc) {
		    if (q_ref(j, jc) != qe_ref(j, jc)) {
			result[6] = ulpinv;
		    }
/* L140: */
		}
/* L150: */
	    }

/*           DO the test (7): Compute eigenvalues and right eigenvectors,   
             and test them */

	    dlacpy_(" ", &n, &n, &a[a_offset], lda, &s[s_offset], lda);
	    dlacpy_(" ", &n, &n, &b[b_offset], lda, &t[t_offset], lda);
	    dggev_("N", "V", &n, &s[s_offset], lda, &t[t_offset], lda, &
		    alphr1[1], &alphi1[1], &beta1[1], &q[q_offset], ldq, &qe[
		    qe_offset], ldqe, &work[1], lwork, &ierr);
	    if (ierr != 0 && ierr != n + 1) {
		result[1] = ulpinv;
		io___45.ciunit = *nounit;
		s_wsfe(&io___45);
		do_fio(&c__1, "DGGEV4", (ftnlen)6);
		do_fio(&c__1, (char *)&ierr, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer));
		do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(integer));
		e_wsfe();
		*info = abs(ierr);
		goto L190;
	    }

	    i__3 = n;
	    for (j = 1; j <= i__3; ++j) {
		if (alphar[j] != alphr1[j] || alphai[j] != alphi1[j] || beta[
			j] != beta1[j]) {
		    result[7] = ulpinv;
		}
/* L160: */
	    }

	    i__3 = n;
	    for (j = 1; j <= i__3; ++j) {
		i__4 = n;
		for (jc = 1; jc <= i__4; ++jc) {
		    if (z___ref(j, jc) != qe_ref(j, jc)) {
			result[7] = ulpinv;
		    }
/* L170: */
		}
/* L180: */
	    }

/*           End of Loop -- Check for RESULT(j) > THRESH */

L190:

	    ntestt += 7;

/*           Print out tests which fail. */

	    for (jr = 1; jr <= 7; ++jr) {
		if (result[jr] >= *thresh) {

/*                 If this is the first test to fail,   
                   print a header to the data file. */

		    if (nerrs == 0) {
			io___46.ciunit = *nounit;
			s_wsfe(&io___46);
			do_fio(&c__1, "DGV", (ftnlen)3);
			e_wsfe();

/*                    Matrix types */

			io___47.ciunit = *nounit;
			s_wsfe(&io___47);
			e_wsfe();
			io___48.ciunit = *nounit;
			s_wsfe(&io___48);
			e_wsfe();
			io___49.ciunit = *nounit;
			s_wsfe(&io___49);
			do_fio(&c__1, "Orthogonal", (ftnlen)10);
			e_wsfe();

/*                    Tests performed */

			io___50.ciunit = *nounit;
			s_wsfe(&io___50);
			e_wsfe();

		    }
		    ++nerrs;
		    if (result[jr] < 1e4) {
			io___51.ciunit = *nounit;
			s_wsfe(&io___51);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&jr, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[jr], (ftnlen)sizeof(
				doublereal));
			e_wsfe();
		    } else {
			io___52.ciunit = *nounit;
			s_wsfe(&io___52);
			do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&jtype, (ftnlen)sizeof(integer))
				;
			do_fio(&c__4, (char *)&ioldsd[0], (ftnlen)sizeof(
				integer));
			do_fio(&c__1, (char *)&jr, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&result[jr], (ftnlen)sizeof(
				doublereal));
			e_wsfe();
		    }
		}
/* L200: */
	    }

L210:
	    ;
	}
/* L220: */
    }

/*     Summary */

    alasvm_("DGV", nounit, &nerrs, &ntestt, &c__0);

    work[1] = (doublereal) maxwrk;

    return 0;







/*     End of DDRGEV */

} /* ddrgev_ */

#undef qe_ref
#undef z___ref
#undef q_ref
#undef b_ref
#undef a_ref


