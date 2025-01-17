#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer iparms[100];
} claenv_;

#define claenv_1 claenv_

struct {
    real ops, itcnt;
} latime_;

#define latime_1 latime_

/* Table of constant values */

static integer c__1 = 1;
static integer c__3 = 3;
static integer c__12 = 12;
static integer c__0 = 0;
static integer c__400 = 400;
static integer c__420 = 420;
static integer c__4 = 4;
static integer c__6 = 6;
static integer c_b226 = 649241;
static integer c__10 = 10;

/* Main program */ MAIN__(void)
{
    /* Initialized data */

    static integer mxtype[4] = { 8,4,5,4 };
    static integer iseed[4] = { 0,0,0,1 };

    /* Format strings */
    static char fmt_9993[] = "(\002 Timing the Nonsymmetric Eigenvalue Probl"
	    "em routines\002,/\002    CGEHRD, CHSEQR, CTREVC, and CHSEIN\002)";
    static char fmt_9992[] = "(\002 Timing the Symmetric Eigenvalue Problem "
	    "routines\002,/\002    CHETRD, CSTEQR, and SSTERF\002)";
    static char fmt_9991[] = "(\002 Timing the Singular Value Decomposition "
	    "routines\002,/\002    CGEBRD, CBDSQR, and CUNGBR \002)";
    static char fmt_9990[] = "(\002 Timing the Generalized Eigenvalue Proble"
	    "m routines\002,/\002    CGGHRD, CHGEQZ, and CTGEVC \002)";
    static char fmt_9996[] = "(1x,a3,\002:  Unrecognized path name\002)";
    static char fmt_9985[] = "(/\002 LAPACK VERSION 3.0, released June 30, 1"
	    "999 \002)";
    static char fmt_9989[] = "(/\002 The following parameter values will be "
	    "used:\002)";
    static char fmt_9995[] = "(\002 *** Invalid input value: \002,a6,\002"
	    "=\002,i6,\002; must be >=\002,i6)";
    static char fmt_9994[] = "(\002 *** Invalid input value: \002,a6,\002"
	    "=\002,i6,\002; must be <=\002,i6)";
    static char fmt_9988[] = "(\002    Values of \002,a5,\002:  \002,10i6,/1"
	    "9x,10i6)";
    static char fmt_9987[] = "(/\002 Minimum time a subroutine will be timed"
	    " = \002,f8.2,\002 seconds\002,/)";
    static char fmt_9999[] = "(/\002 Execution not attempted due to input er"
	    "rors\002)";
    static char fmt_9986[] = "(\002 *** Error code from \002,a6,\002 = \002,"
	    "i4)";
    static char fmt_9998[] = "(//\002 End of timing run\002)";
    static char fmt_9997[] = "(\002 Total time used = \002,f12.2,\002 seco"
	    "nds\002,/)";

    /* System generated locals */
    integer i__1;
    real r__1;
    static complex equiv_0[1008000], equiv_1[2400], equiv_2[649241];
    static real equiv_3[489601];

    /* Builtin functions */
    integer s_rsfe(cilist *), do_fio(integer *, char *, ftnlen), e_rsfe(void),
	     s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer s_rsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_rsle(void);
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsle(cilist *), e_wsle(void);

    /* Local variables */
    static char line[80];
    static integer info;
    static char path[3];
    static integer mval[12], nval[12];
#define work (equiv_2)
#define a (equiv_0)
#define d__ (equiv_1)
    static integer i__;
    static logical fatal;
    extern /* Subroutine */ int ctim21_(char *, integer *, integer *, integer 
	    *, logical *, integer *, integer *, integer *, integer *, integer 
	    *, real *, integer *, integer *, complex *, real *, real *, 
	    complex *, real *, real *, complex *, real *, real *, complex *, 
	    real *, real *, complex *, real *, real *, integer *, real *, 
	    logical *, integer *, real *, integer *, integer *, integer *, 
	    real *, integer *, integer *, integer *, integer *, ftnlen), 
	    ctim22_(char *, integer *, integer *, integer *, logical *, 
	    integer *, integer *, integer *, real *, integer *, integer *, 
	    complex *, real *, real *, real *, complex *, real *, real *, 
	    complex *, real *, complex *, real *, real *, complex *, integer *
	    , real *, logical *, integer *, real *, integer *, integer *, 
	    integer *, real *, integer *, integer *, integer *, integer *, 
	    ftnlen);
    static integer nbval[10];
    extern /* Subroutine */ int ctim51_(char *, integer *, integer *, integer 
	    *, logical *, integer *, integer *, integer *, integer *, integer 
	    *, integer *, integer *, real *, integer *, integer *, complex *, 
	    real *, real *, complex *, real *, real *, complex *, real *, 
	    real *, complex *, real *, real *, complex *, real *, real *, 
	    complex *, real *, real *, complex *, real *, complex *, integer *
	    , real *, logical *, real *, integer *, integer *, integer *, 
	    real *, integer *, integer *, integer *, integer *, ftnlen), 
	    ctim26_(char *, integer *, integer *, integer *, integer *, 
	    logical *, integer *, integer *, integer *, real *, integer *, 
	    integer *, complex *, complex *, complex *, complex *, real *, 
	    complex *, real *, complex *, complex *, complex *, complex *, 
	    integer *, real *, integer *, logical *, real *, integer *, 
	    integer *, integer *, real *, integer *, integer *, integer *, 
	    integer *, ftnlen);
    static char vname[6];
    static integer nsval[10];
    static char c3[3];
    static real e2[400];
    static integer iwork[10];
    static real s1, s2;
#define rwork (equiv_3)
#define workr ((real *)equiv_2)
    static integer iwork2[20406];
#define ar ((real *)equiv_0)
#define rwork1 (equiv_3)
#define dr ((real *)equiv_1)
    static integer nn, ldaval[10];
    extern doublereal second_(void);
    static integer nbkval[10], nbmval[10];
    extern logical lsamen_(integer *, char *, char *);
    static integer mxbval[10];
    static real timmin;
    static integer nparms;
    static logical dotype[10], logwrk[400];
    static real opcnts[24000]	/* was [10][10][12][20] */, result[24000]	
	    /* was [10][10][12][20] */;
    static integer maxtyp, ntypes;
    static logical gep, nep, sep, svd;

    /* Fortran I/O blocks */
    static cilist io___17 = { 0, 5, 1, "(A3)", 0 };
    static cilist io___19 = { 0, 6, 0, fmt_9993, 0 };
    static cilist io___20 = { 0, 6, 0, fmt_9992, 0 };
    static cilist io___21 = { 0, 6, 0, fmt_9991, 0 };
    static cilist io___22 = { 0, 6, 0, fmt_9990, 0 };
    static cilist io___23 = { 0, 6, 0, fmt_9996, 0 };
    static cilist io___24 = { 0, 6, 0, fmt_9985, 0 };
    static cilist io___25 = { 0, 6, 0, fmt_9989, 0 };
    static cilist io___26 = { 0, 5, 0, 0, 0 };
    static cilist io___28 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___29 = { 0, 6, 0, fmt_9994, 0 };
    static cilist io___30 = { 0, 5, 0, 0, 0 };
    static cilist io___34 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___35 = { 0, 6, 0, fmt_9994, 0 };
    static cilist io___36 = { 0, 6, 0, fmt_9988, 0 };
    static cilist io___37 = { 0, 5, 0, 0, 0 };
    static cilist io___39 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___40 = { 0, 6, 0, fmt_9994, 0 };
    static cilist io___41 = { 0, 6, 0, fmt_9988, 0 };
    static cilist io___42 = { 0, 5, 0, 0, 0 };
    static cilist io___44 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___45 = { 0, 6, 0, fmt_9994, 0 };
    static cilist io___46 = { 0, 5, 0, 0, 0 };
    static cilist io___48 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___49 = { 0, 6, 0, fmt_9988, 0 };
    static cilist io___50 = { 0, 5, 0, 0, 0 };
    static cilist io___52 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___53 = { 0, 6, 0, fmt_9988, 0 };
    static cilist io___54 = { 0, 5, 0, 0, 0 };
    static cilist io___56 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___57 = { 0, 6, 0, fmt_9988, 0 };
    static cilist io___58 = { 0, 5, 0, 0, 0 };
    static cilist io___60 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___61 = { 0, 6, 0, fmt_9988, 0 };
    static cilist io___62 = { 0, 5, 0, 0, 0 };
    static cilist io___64 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___65 = { 0, 6, 0, fmt_9988, 0 };
    static cilist io___66 = { 0, 5, 0, 0, 0 };
    static cilist io___68 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___69 = { 0, 6, 0, fmt_9994, 0 };
    static cilist io___70 = { 0, 6, 0, fmt_9988, 0 };
    static cilist io___71 = { 0, 5, 0, 0, 0 };
    static cilist io___73 = { 0, 6, 0, fmt_9987, 0 };
    static cilist io___74 = { 0, 5, 0, 0, 0 };
    static cilist io___76 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___78 = { 0, 5, 0, 0, 0 };
    static cilist io___81 = { 0, 6, 0, fmt_9995, 0 };
    static cilist io___82 = { 0, 6, 0, fmt_9994, 0 };
    static cilist io___83 = { 0, 6, 0, fmt_9999, 0 };
    static cilist io___84 = { 0, 5, 1, "(A80)", 0 };
    static cilist io___92 = { 0, 6, 0, fmt_9986, 0 };
    static cilist io___94 = { 0, 6, 0, fmt_9986, 0 };
    static cilist io___95 = { 0, 6, 0, fmt_9986, 0 };
    static cilist io___96 = { 0, 6, 0, fmt_9986, 0 };
    static cilist io___97 = { 0, 6, 0, 0, 0 };
    static cilist io___98 = { 0, 6, 0, 0, 0 };
    static cilist io___99 = { 0, 6, 0, fmt_9996, 0 };
    static cilist io___100 = { 0, 6, 0, fmt_9998, 0 };
    static cilist io___102 = { 0, 6, 0, fmt_9997, 0 };



#define a_subscr(a_1,a_2) (a_2)*168000 + a_1 - 168001
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define d___subscr(a_1,a_2) (a_2)*400 + a_1 - 401
#define d___ref(a_1,a_2) d__[d___subscr(a_1,a_2)]
#define workr_ref(a_1,a_2) workr[(a_2)*649241 + a_1 - 649242]
#define ar_ref(a_1,a_2) ar[(a_2)*168000 + a_1 - 168001]
#define dr_ref(a_1,a_2) dr[(a_2)*400 + a_1 - 401]


/*  -- LAPACK timing routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   

    Purpose   
    =======   

    CTIMEE is the main timing program for the COMPLEX matrix   
    eigenvalue routines in LAPACK.   

    There are four sets of routines that can be timed:   

    NEP (Nonsymmetric Eigenvalue Problem):   
        Includes CGEHRD, CHSEQR, CTREVC, and CHSEIN   

    SEP (Hermitian Eigenvalue Problem):   
        Includes CHETRD, CSTEQR, and SSTERF   

    SVD (Singular Value Decomposition):   
        Includes CGEBRD, CUNGBR, CBDSQR, and CGESDD   

    GEP (Generalized nonsymmetric Eigenvalue Problem):   
        Includes CGGHRD, CHGEQZ, and CTGEVC   

    Each test path has a different input file.  The first line of the   
    input file should contain the characters NEP, SEP, SVD, or GEP in   
    columns 1-3.  The number of remaining lines depends on what is found   
    on the first line.   

   -----------------------------------------------------------------------   

    NEP input file:   

    line 2:  NN, INTEGER   
             Number of values of N.   

    line 3:  NVAL, INTEGER array, dimension (NN)   
             The values for the matrix dimension N.   

    line 4:  NPARM, INTEGER   
             Number of values of the parameters NB, NS, MAXB, and LDA.   

    line 5:  NBVAL, INTEGER array, dimension (NPARM)   
             The values for the blocksize NB.   

    line 6:  NSVAL, INTEGER array, dimension (NPARM)   
             The values for the number of shifts.   

    line 7:  MXBVAL, INTEGER array, dimension (NPARM)   
             The values for MAXB, used in determining whether multishift   
             will be used.   

    line 8:  LDAVAL, INTEGER array, dimension (NPARM)   
             The values for the leading dimension LDA.   

    line 9:  TIMMIN, REAL   
             The minimum time (in seconds) that a subroutine will be   
             timed.  If TIMMIN is zero, each routine should be timed only   
             once.   

    line 10: NTYPES, INTEGER   
             The number of matrix types to be used in the timing run.   
             If NTYPES >= MAXTYP, all the types are used.   

    If 0 < NTYPES < MAXTYP, then line 11 specifies NTYPES integer   
    values, which are the numbers of the matrix types to be used.   

    The remaining lines specify a path name and the specific routines to   
    be timed.  For the nonsymmetric eigenvalue problem, the path name is   
    'CHS'.  A line to request all the routines in this path has the form   
       CHS   T T T T T T T T T T T T   
    where the first 3 characters specify the path name, and up to MAXTYP   
    nonblank characters may appear in columns 4-80.  If the k-th such   
    character is 'T' or 't', the k-th routine will be timed.  If at least   
    one but fewer than 12 nonblank characters are specified, the   
    remaining routines will not be timed.  If columns 4-80 are blank, all   
    the routines will be timed, so the input line   
       CHS   
    is equivalent to the line above.   

   -----------------------------------------------------------------------   

    SEP input file:   

    line 2:  NN, INTEGER   
             Number of values of N.   

    line 3:  NVAL, INTEGER array, dimension (NN)   
             The values for the matrix dimension N.   

    line 4:  NPARM, INTEGER   
             Number of values of the parameters NB and LDA.   

    line 5:  NBVAL, INTEGER array, dimension (NPARM)   
             The values for the blocksize NB.   

    line 6:  LDAVAL, INTEGER array, dimension (NPARM)   
             The values for the leading dimension LDA.   

    line 7:  TIMMIN, REAL   
             The minimum time (in seconds) that a subroutine will be   
             timed.  If TIMMIN is zero, each routine should be timed only   
             once.   

    line 8:  NTYPES, INTEGER   
             The number of matrix types to be used in the timing run.   
             If NTYPES >= MAXTYP, all the types are used.   

    If 0 < NTYPES < MAXTYP, then line 9 specifies NTYPES integer   
    values, which are the numbers of the matrix types to be used.   

    The remaining lines specify a path name and the specific routines to   
    be timed as for the NEP input file.  For the symmetric eigenvalue   
    problem, the path name is 'CST' and up to 8 routines may be timed.   

   -----------------------------------------------------------------------   

    SVD input file:   

    line 2:  NN, INTEGER   
             Number of values of M and N.   

    line 3:  MVAL, INTEGER array, dimension (NN)   
             The values for the matrix dimension M.   

    line 4:  NVAL, INTEGER array, dimension (NN)   
             The values for the matrix dimension N.   

    line 5:  NPARM, INTEGER   
             Number of values of the parameters NB and LDA.   

    line 6:  NBVAL, INTEGER array, dimension (NPARM)   
             The values for the blocksize NB.   

    line 7:  LDAVAL, INTEGER array, dimension (NPARM)   
             The values for the leading dimension LDA.   

    line 8:  TIMMIN, REAL   
             The minimum time (in seconds) that a subroutine will be   
             timed.  If TIMMIN is zero, each routine should be timed only   
             once.   

    line 9:  NTYPES, INTEGER   
             The number of matrix types to be used in the timing run.   
             If NTYPES >= MAXTYP, all the types are used.   

    If 0 < NTYPES < MAXTYP, then line 10 specifies NTYPES integer   
    values, which are the numbers of the matrix types to be used.   

    The remaining lines specify a path name and the specific routines to   
    be timed as for the NEP input file.  For the singular value   
    decomposition the path name is 'CBD' and up to 16 routines may be   
    timed.   

   -----------------------------------------------------------------------   

    GEP input file:   

    line 2:  NN, INTEGER   
             Number of values of N.   

    line 3:  NVAL, INTEGER array, dimension (NN)   
             The values for the matrix dimension N.   

    line 4:  NPARM, INTEGER   
             Number of values of the parameters NB, NS, MAXB, and LDA.   

    line 5:  NBVAL, INTEGER array, dimension (NPARM)   
             The values for the blocksize NB.   

    line 6:  NSVAL, INTEGER array, dimension (NPARM)   
             The values for the number of shifts.   

    line 7:  NEIVAL, INTEGER array, dimension (NPARM)   
             The values for NEISP, used in determining whether multishift   
             will be used.   

    line 8:  NBMVAL, INTEGER array, dimension (NPARM)   
             The values for MINNB, used in determining minimum blocksize.   

    line 9:  NBKVAL, INTEGER array, dimension (NPARM)   
             The values for MINBLK, also used in determining minimum   
             blocksize.   

    line 10: LDAVAL, INTEGER array, dimension (NPARM)   
             The values for the leading dimension LDA.   

    line 11: TIMMIN, REAL   
             The minimum time (in seconds) that a subroutine will be   
             timed.  If TIMMIN is zero, each routine should be timed only   
             once.   

    line 12: NTYPES, INTEGER   
             The number of matrix types to be used in the timing run.   
             If NTYPES >= MAXTYP, all the types are used.   

    If 0 < NTYPES < MAXTYP, then line 13 specifies NTYPES integer   
    values, which are the numbers of the matrix types to be used.   

    The remaining lines specify a path name and the specific routines to   
    be timed.  For the nonsymmetric eigenvalue problem, the path name is   
    'CHG'.  A line to request all the routines in this path has the form   
       CHG   T T T T T T T T T T T T T T T T T T   
    where the first 3 characters specify the path name, and up to MAXTYP   
    nonblank characters may appear in columns 4-80.  If the k-th such   
    character is 'T' or 't', the k-th routine will be timed.  If at least   
    one but fewer than 18 nonblank characters are specified, the   
    remaining routines will not be timed.  If columns 4-80 are blank, all   
    the routines will be timed, so the input line   
       CHG   
    is equivalent to the line above.   

   =======================================================================   

    The workspace requirements in terms of square matrices for the   
    different test paths are as follows:   

    NEP:   3 N**2 + N*(3*NB+2)   
    SEP:   2 N**2 + N*(2*N) + N   
    SVD:   4 N**2 + MAX( 6*N, MAXIN*MAXPRM*MAXT )   
    GEP:   6 N**2 + 3*N   

    MAXN is currently set to 400,   
    LG2MXN = ceiling of log-base-2 of MAXN = 9, and LDAMAX = 420.   
    The real work space needed is LWORK = MAX( MAXN*(4*MAXN+2),   
         2*LDAMAX+1+3*MAXN+2*MAXN*LG2MXN+3*MAXN**2 ),  and the integer   
    workspace needed is  LIWRK2 = 6 + 6*MAXN + 5*MAXN*LG2MXN.   
    For SVD, we assume NRHS may be as big   
    as N.  The parameter NEED is set to 6 to allow for 4 NxN matrices   
    for GEP.   

    The EISPACK routines tested use two real arrays to represent complex   
    data, whereas the LAPACK routines use complex arrays.  The LAPACK   
    arrays are called A, D, and WORK and the corresponding EISPACK arrays   
    are called AR, DR, and WORKR.  To conserve space, we have   
    EQUIVALENCEd the real arrays to their complex analogs.   
                          !!!*** Note ***!!!   
    This EQUIVALENCE is a violation of the FORTRAN-77 standard because   
    the equivalenced arrays are both passed to a subroutine and both   
    modified there.  Most compilers will permit this, but if not, users   
    are advised to comment out these EQUIVALENCE statements in the code   
    below.   

    The work arrays RWORK and RWORK1 are also equivalenced to get the   
    effect of one array with length = max( MAXN, MAXIN*MAXT*MAXPRM ).   
    Generally, RWORK1 will be the larger, and even if MAXN is so large as   
    to make RWORK larger, most machines will not complain.  If this   
    becomes a problem, though, pass RWORK instead of RWORK1 to CTIM21. */



    s1 = second_();
    fatal = FALSE_;
    nep = FALSE_;
    sep = FALSE_;
    svd = FALSE_;
    gep = FALSE_;

/*     Read the 3-character test path */

    i__1 = s_rsfe(&io___17);
    if (i__1 != 0) {
	goto L160;
    }
    i__1 = do_fio(&c__1, path, (ftnlen)3);
    if (i__1 != 0) {
	goto L160;
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L160;
    }
    nep = lsamen_(&c__3, path, "NEP") || lsamen_(&c__3, 
	    path, "CHS");
    sep = lsamen_(&c__3, path, "SEP") || lsamen_(&c__3, 
	    path, "CST");
    svd = lsamen_(&c__3, path, "SVD") || lsamen_(&c__3, 
	    path, "CBD");
    gep = lsamen_(&c__3, path, "GEP") || lsamen_(&c__3, 
	    path, "CHG");

/*     Report values of parameters as they are read. */

    if (nep) {
	s_wsfe(&io___19);
	e_wsfe();
    } else if (sep) {
	s_wsfe(&io___20);
	e_wsfe();
    } else if (svd) {
	s_wsfe(&io___21);
	e_wsfe();
    } else if (gep) {
	s_wsfe(&io___22);
	e_wsfe();
    } else {
	s_wsfe(&io___23);
	do_fio(&c__1, path, (ftnlen)3);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    s_wsfe(&io___24);
    e_wsfe();
    s_wsfe(&io___25);
    e_wsfe();

/*     Read the number of values of M and N. */

    s_rsle(&io___26);
    do_lio(&c__3, &c__1, (char *)&nn, (ftnlen)sizeof(integer));
    e_rsle();
    if (nn < 1) {
	s_wsfe(&io___28);
	do_fio(&c__1, "NN  ", (ftnlen)4);
	do_fio(&c__1, (char *)&nn, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&c__1, (ftnlen)sizeof(integer));
	e_wsfe();
	nn = 0;
	fatal = TRUE_;
    } else if (nn > 12) {
	s_wsfe(&io___29);
	do_fio(&c__1, "NN  ", (ftnlen)4);
	do_fio(&c__1, (char *)&nn, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&c__12, (ftnlen)sizeof(integer));
	e_wsfe();
	nn = 0;
	fatal = TRUE_;
    }

/*     Read the values of M */

    s_rsle(&io___30);
    i__1 = nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_lio(&c__3, &c__1, (char *)&mval[i__ - 1], (ftnlen)sizeof(integer));
    }
    e_rsle();
    if (svd) {
	s_copy(vname, "  M", (ftnlen)6, (ftnlen)3);
    } else {
	s_copy(vname, "  N", (ftnlen)6, (ftnlen)3);
    }
    i__1 = nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (mval[i__ - 1] < 0) {
	    s_wsfe(&io___34);
	    do_fio(&c__1, vname, (ftnlen)6);
	    do_fio(&c__1, (char *)&mval[i__ - 1], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
	    e_wsfe();
	    fatal = TRUE_;
	} else if (mval[i__ - 1] > 400) {
	    s_wsfe(&io___35);
	    do_fio(&c__1, vname, (ftnlen)6);
	    do_fio(&c__1, (char *)&mval[i__ - 1], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&c__400, (ftnlen)sizeof(integer));
	    e_wsfe();
	    fatal = TRUE_;
	}
/* L10: */
    }

/*     Read the values of N */

    if (svd) {
	s_wsfe(&io___36);
	do_fio(&c__1, "M   ", (ftnlen)4);
	i__1 = nn;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_fio(&c__1, (char *)&mval[i__ - 1], (ftnlen)sizeof(integer));
	}
	e_wsfe();
	s_rsle(&io___37);
	i__1 = nn;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_lio(&c__3, &c__1, (char *)&nval[i__ - 1], (ftnlen)sizeof(
		    integer));
	}
	e_rsle();
	i__1 = nn;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (nval[i__ - 1] < 0) {
		s_wsfe(&io___39);
		do_fio(&c__1, "N   ", (ftnlen)4);
		do_fio(&c__1, (char *)&nval[i__ - 1], (ftnlen)sizeof(integer))
			;
		do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
		e_wsfe();
		fatal = TRUE_;
	    } else if (nval[i__ - 1] > 400) {
		s_wsfe(&io___40);
		do_fio(&c__1, "N   ", (ftnlen)4);
		do_fio(&c__1, (char *)&nval[i__ - 1], (ftnlen)sizeof(integer))
			;
		do_fio(&c__1, (char *)&c__400, (ftnlen)sizeof(integer));
		e_wsfe();
		fatal = TRUE_;
	    }
/* L20: */
	}
    } else {
	i__1 = nn;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    nval[i__ - 1] = mval[i__ - 1];
/* L30: */
	}
    }
    s_wsfe(&io___41);
    do_fio(&c__1, "N   ", (ftnlen)4);
    i__1 = nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&nval[i__ - 1], (ftnlen)sizeof(integer));
    }
    e_wsfe();

/*     Read the number of parameter values. */

    s_rsle(&io___42);
    do_lio(&c__3, &c__1, (char *)&nparms, (ftnlen)sizeof(integer));
    e_rsle();
    if (nparms < 1) {
	s_wsfe(&io___44);
	do_fio(&c__1, "NPARMS", (ftnlen)6);
	do_fio(&c__1, (char *)&nparms, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&c__1, (ftnlen)sizeof(integer));
	e_wsfe();
	nparms = 0;
	fatal = TRUE_;
    } else if (nparms > 12) {
	s_wsfe(&io___45);
	do_fio(&c__1, "NPARMS", (ftnlen)6);
	do_fio(&c__1, (char *)&nparms, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&c__12, (ftnlen)sizeof(integer));
	e_wsfe();
	nparms = 0;
	fatal = TRUE_;
    }

/*     Read the values of NB */

    s_rsle(&io___46);
    i__1 = nparms;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_lio(&c__3, &c__1, (char *)&nbval[i__ - 1], (ftnlen)sizeof(integer))
		;
    }
    e_rsle();
    i__1 = nparms;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (nbval[i__ - 1] < 0) {
	    s_wsfe(&io___48);
	    do_fio(&c__1, "NB  ", (ftnlen)4);
	    do_fio(&c__1, (char *)&nbval[i__ - 1], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
	    e_wsfe();
	    fatal = TRUE_;
	}
/* L40: */
    }
    s_wsfe(&io___49);
    do_fio(&c__1, "NB  ", (ftnlen)4);
    i__1 = nparms;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&nbval[i__ - 1], (ftnlen)sizeof(integer));
    }
    e_wsfe();

    if (nep || gep) {

/*        Read the values of NSHIFT */

	s_rsle(&io___50);
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_lio(&c__3, &c__1, (char *)&nsval[i__ - 1], (ftnlen)sizeof(
		    integer));
	}
	e_rsle();
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (nsval[i__ - 1] < 0) {
		s_wsfe(&io___52);
		do_fio(&c__1, "NS  ", (ftnlen)4);
		do_fio(&c__1, (char *)&nsval[i__ - 1], (ftnlen)sizeof(integer)
			);
		do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
		e_wsfe();
		fatal = TRUE_;
	    }
/* L50: */
	}
	s_wsfe(&io___53);
	do_fio(&c__1, "NS  ", (ftnlen)4);
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_fio(&c__1, (char *)&nsval[i__ - 1], (ftnlen)sizeof(integer));
	}
	e_wsfe();

/*        Read the values of MAXB */

	s_rsle(&io___54);
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_lio(&c__3, &c__1, (char *)&mxbval[i__ - 1], (ftnlen)sizeof(
		    integer));
	}
	e_rsle();
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (mxbval[i__ - 1] < 0) {
		s_wsfe(&io___56);
		do_fio(&c__1, "MAXB", (ftnlen)4);
		do_fio(&c__1, (char *)&mxbval[i__ - 1], (ftnlen)sizeof(
			integer));
		do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
		e_wsfe();
		fatal = TRUE_;
	    }
/* L60: */
	}
	s_wsfe(&io___57);
	do_fio(&c__1, "MAXB", (ftnlen)4);
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_fio(&c__1, (char *)&mxbval[i__ - 1], (ftnlen)sizeof(integer));
	}
	e_wsfe();
    } else {
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    nsval[i__ - 1] = 1;
	    mxbval[i__ - 1] = 1;
/* L70: */
	}
    }

    if (gep) {

/*        Read the values of NBMIN */

	s_rsle(&io___58);
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_lio(&c__3, &c__1, (char *)&nbmval[i__ - 1], (ftnlen)sizeof(
		    integer));
	}
	e_rsle();
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (nbmval[i__ - 1] < 0) {
		s_wsfe(&io___60);
		do_fio(&c__1, "NBMIN", (ftnlen)5);
		do_fio(&c__1, (char *)&nbmval[i__ - 1], (ftnlen)sizeof(
			integer));
		do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
		e_wsfe();
		fatal = TRUE_;
	    }
/* L80: */
	}
	s_wsfe(&io___61);
	do_fio(&c__1, "NBMIN", (ftnlen)5);
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_fio(&c__1, (char *)&nbmval[i__ - 1], (ftnlen)sizeof(integer));
	}
	e_wsfe();

/*        Read the values of MINBLK */

	s_rsle(&io___62);
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_lio(&c__3, &c__1, (char *)&nbkval[i__ - 1], (ftnlen)sizeof(
		    integer));
	}
	e_rsle();
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (nbkval[i__ - 1] < 0) {
		s_wsfe(&io___64);
		do_fio(&c__1, "MINBLK", (ftnlen)6);
		do_fio(&c__1, (char *)&nbkval[i__ - 1], (ftnlen)sizeof(
			integer));
		do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
		e_wsfe();
		fatal = TRUE_;
	    }
/* L90: */
	}
	s_wsfe(&io___65);
	do_fio(&c__1, "MINBLK", (ftnlen)6);
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_fio(&c__1, (char *)&nbkval[i__ - 1], (ftnlen)sizeof(integer));
	}
	e_wsfe();
    } else {
	i__1 = nparms;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    nbmval[i__ - 1] = 401;
	    nbkval[i__ - 1] = 401;
/* L100: */
	}
    }

/*     Read the values of LDA */

    s_rsle(&io___66);
    i__1 = nparms;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_lio(&c__3, &c__1, (char *)&ldaval[i__ - 1], (ftnlen)sizeof(integer)
		);
    }
    e_rsle();
    i__1 = nparms;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (ldaval[i__ - 1] < 0) {
	    s_wsfe(&io___68);
	    do_fio(&c__1, "LDA ", (ftnlen)4);
	    do_fio(&c__1, (char *)&ldaval[i__ - 1], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
	    e_wsfe();
	    fatal = TRUE_;
	} else if (ldaval[i__ - 1] > 420) {
	    s_wsfe(&io___69);
	    do_fio(&c__1, "LDA ", (ftnlen)4);
	    do_fio(&c__1, (char *)&ldaval[i__ - 1], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&c__420, (ftnlen)sizeof(integer));
	    e_wsfe();
	    fatal = TRUE_;
	}
/* L110: */
    }
    s_wsfe(&io___70);
    do_fio(&c__1, "LDA ", (ftnlen)4);
    i__1 = nparms;
    for (i__ = 1; i__ <= i__1; ++i__) {
	do_fio(&c__1, (char *)&ldaval[i__ - 1], (ftnlen)sizeof(integer));
    }
    e_wsfe();

/*     Read the minimum time a subroutine will be timed. */

    s_rsle(&io___71);
    do_lio(&c__4, &c__1, (char *)&timmin, (ftnlen)sizeof(real));
    e_rsle();
    s_wsfe(&io___73);
    do_fio(&c__1, (char *)&timmin, (ftnlen)sizeof(real));
    e_wsfe();

/*     Read the number of matrix types to use in timing. */

    s_rsle(&io___74);
    do_lio(&c__3, &c__1, (char *)&ntypes, (ftnlen)sizeof(integer));
    e_rsle();
    if (ntypes < 0) {
	s_wsfe(&io___76);
	do_fio(&c__1, "NTYPES", (ftnlen)6);
	do_fio(&c__1, (char *)&ntypes, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
	e_wsfe();
	fatal = TRUE_;
	ntypes = 0;
    }

/*     Read the matrix types. */

    if (nep) {
	maxtyp = mxtype[0];
    } else if (sep) {
	maxtyp = mxtype[1];
    } else if (svd) {
	maxtyp = mxtype[2];
    } else {
	maxtyp = mxtype[3];
    }
    if (ntypes < maxtyp) {
	s_rsle(&io___78);
	i__1 = ntypes;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    do_lio(&c__3, &c__1, (char *)&iwork[i__ - 1], (ftnlen)sizeof(
		    integer));
	}
	e_rsle();
	i__1 = maxtyp;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dotype[i__ - 1] = FALSE_;
/* L120: */
	}
	i__1 = ntypes;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (iwork[i__ - 1] < 0) {
		s_wsfe(&io___81);
		do_fio(&c__1, "TYPE", (ftnlen)4);
		do_fio(&c__1, (char *)&iwork[i__ - 1], (ftnlen)sizeof(integer)
			);
		do_fio(&c__1, (char *)&c__0, (ftnlen)sizeof(integer));
		e_wsfe();
		fatal = TRUE_;
	    } else if (iwork[i__ - 1] > maxtyp) {
		s_wsfe(&io___82);
		do_fio(&c__1, "TYPE", (ftnlen)4);
		do_fio(&c__1, (char *)&iwork[i__ - 1], (ftnlen)sizeof(integer)
			);
		do_fio(&c__1, (char *)&maxtyp, (ftnlen)sizeof(integer));
		e_wsfe();
		fatal = TRUE_;
	    } else {
		dotype[iwork[i__ - 1] - 1] = TRUE_;
	    }
/* L130: */
	}
    } else {
	ntypes = maxtyp;
	for (i__ = 1; i__ <= 10; ++i__) {
	    dotype[i__ - 1] = TRUE_;
/* L140: */
	}
    }

    if (fatal) {
	s_wsfe(&io___83);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }

/*     Read the input lines indicating the test path and the routines   
       to be timed.  The first three characters indicate the test path. */

L150:
    i__1 = s_rsfe(&io___84);
    if (i__1 != 0) {
	goto L160;
    }
    i__1 = do_fio(&c__1, line, (ftnlen)80);
    if (i__1 != 0) {
	goto L160;
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L160;
    }
    s_copy(c3, line, (ftnlen)3, (ftnlen)3);

/*     -------------------------------------   
       NEP:  Nonsymmetric Eigenvalue Problem   
       ------------------------------------- */

    if (lsamen_(&c__3, c3, "CHS") || lsamen_(&c__3, c3, 
	    "NEP")) {
	ctim21_(line, &nn, nval, &maxtyp, dotype, &nparms, nbval, nsval, 
		mxbval, ldaval, &timmin, &c__6, iseed, &a_ref(1, 1), &ar_ref(
		1, 1), &ar_ref(1, 2), &a_ref(1, 2), &ar_ref(1, 3), &ar_ref(1, 
		4), &a_ref(1, 3), &ar_ref(1, 5), &ar_ref(1, 6), &d___ref(1, 1)
		, &dr_ref(1, 1), &dr_ref(1, 3), work, &workr_ref(1, 1), &
		workr_ref(1, 2), &c_b226, rwork1, logwrk, iwork2, result, &
		c__10, &c__10, &c__12, opcnts, &c__10, &c__10, &c__12, &info, 
		(ftnlen)80);
	if (info != 0) {
	    s_wsfe(&io___92);
	    do_fio(&c__1, "CTIM21", (ftnlen)6);
	    do_fio(&c__1, (char *)&info, (ftnlen)sizeof(integer));
	    e_wsfe();
	}

/*     ----------------------------------   
       SEP:  Symmetric Eigenvalue Problem   
       ---------------------------------- */

    } else if (lsamen_(&c__3, c3, "CST") || lsamen_(&
	    c__3, c3, "SEP")) {
	ctim22_(line, &nn, nval, &maxtyp, dotype, &nparms, nbval, ldaval, &
		timmin, &c__6, iseed, &a_ref(1, 1), &dr_ref(1, 3), &dr_ref(1, 
		4), e2, &a_ref(1, 2), &ar_ref(1, 3), &ar_ref(1, 4), &d___ref(
		1, 1), &dr_ref(1, 1), &a_ref(1, 3), &ar_ref(1, 5), &ar_ref(1, 
		6), work, &c_b226, rwork1, logwrk, iwork2, result, &c__10, &
		c__10, &c__12, opcnts, &c__10, &c__10, &c__12, &info, (ftnlen)
		80);
	if (info != 0) {
	    s_wsfe(&io___94);
	    do_fio(&c__1, "CTIM22", (ftnlen)6);
	    do_fio(&c__1, (char *)&info, (ftnlen)sizeof(integer));
	    e_wsfe();
	}

/*     ----------------------------------   
       SVD:  Singular Value Decomposition   
       ---------------------------------- */

    } else if (lsamen_(&c__3, c3, "CBD") || lsamen_(&
	    c__3, c3, "SVD")) {
	ctim26_(line, &nn, nval, mval, &maxtyp, dotype, &nparms, nbval, 
		ldaval, &timmin, &c__6, iseed, &a_ref(1, 1), &a_ref(1, 2), &
		a_ref(1, 3), &a_ref(1, 4), &dr_ref(1, 1), &d___ref(1, 1), &
		dr_ref(1, 3), &d___ref(1, 2), &d___ref(1, 3), &d___ref(1, 4), 
		work, &c_b226, workr, iwork, logwrk, result, &c__10, &c__10, &
		c__12, opcnts, &c__10, &c__10, &c__12, &info, (ftnlen)80);
	if (info != 0) {
	    s_wsfe(&io___95);
	    do_fio(&c__1, "CTIM26", (ftnlen)6);
	    do_fio(&c__1, (char *)&info, (ftnlen)sizeof(integer));
	    e_wsfe();
	}

/*     -------------------------------------   
       GEP:  Nonsymmetric Eigenvalue Problem   
       ------------------------------------- */

    } else if (lsamen_(&c__3, c3, "CHG") || lsamen_(&
	    c__3, c3, "GEP")) {
	ctim51_(line, &nn, nval, &maxtyp, dotype, &nparms, nbval, nsval, 
		mxbval, nbmval, nbkval, ldaval, &timmin, &c__6, iseed, &a_ref(
		1, 1), &ar_ref(1, 1), &ar_ref(1, 2), &a_ref(1, 2), &ar_ref(1, 
		3), &ar_ref(1, 4), &a_ref(1, 3), &ar_ref(1, 5), &ar_ref(1, 6),
		 &a_ref(1, 4), &ar_ref(1, 7), &ar_ref(1, 8), &a_ref(1, 5), &
		ar_ref(1, 9), &ar_ref(1, 10), &a_ref(1, 6), &ar_ref(1, 11), &
		ar_ref(1, 12), d__, dr, work, &c_b226, rwork1, logwrk, result,
		 &c__10, &c__10, &c__12, opcnts, &c__10, &c__10, &c__12, &
		info, (ftnlen)80);
	if (info != 0) {
	    s_wsfe(&io___96);
	    do_fio(&c__1, "CTIM51", (ftnlen)6);
	    do_fio(&c__1, (char *)&info, (ftnlen)sizeof(integer));
	    e_wsfe();
	}
    } else {
	s_wsle(&io___97);
	e_wsle();
	s_wsle(&io___98);
	e_wsle();
	s_wsfe(&io___99);
	do_fio(&c__1, c3, (ftnlen)3);
	e_wsfe();
    }
    goto L150;
L160:
    s_wsfe(&io___100);
    e_wsfe();
    s2 = second_();
    s_wsfe(&io___102);
    r__1 = s2 - s1;
    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
    e_wsfe();


/*     End of CTIMEE */

    return 0;
} /* MAIN__ */

#undef dr_ref
#undef ar_ref
#undef workr_ref
#undef d___ref
#undef d___subscr
#undef a_ref
#undef a_subscr
#undef dr
#undef rwork1
#undef ar
#undef workr
#undef rwork
#undef d__
#undef a
#undef work


/* Main program alias */ int ctimee_ () { MAIN__ (); return 0; }
