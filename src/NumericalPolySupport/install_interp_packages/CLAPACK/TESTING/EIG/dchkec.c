#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;

/* Subroutine */ int dchkec_(doublereal *thresh, logical *tsterr, integer *
	nin, integer *nout)
{
    /* Format strings */
    static char fmt_9989[] = "(\002 Tests of the Nonsymmetric eigenproblem c"
	    "ondition estim\002,\002ation routines\002,/\002 DLALN2, DLASY2, "
	    "DLANV2, DLAEXC, DTRS\002,\002YL, DTREXC, DTRSNA, DTRSEN, DLAQT"
	    "R\002,/)";
    static char fmt_9988[] = "(\002 Relative machine precision (EPS) = \002,"
	    "d16.6,/\002 Safe \002,\002minimum (SFMIN)             = \002,d16"
	    ".6,/)";
    static char fmt_9987[] = "(\002 Routines pass computational tests if tes"
	    "t ratio is les\002,\002s than\002,f8.2,//)";
    static char fmt_9999[] = "(\002 Error in DLALN2: RMAX =\002,d12.3,/\002 "
	    "LMAX = \002,i8,\002 N\002,\002INFO=\002,2i8,\002 KNT=\002,i8)";
    static char fmt_9998[] = "(\002 Error in DLASY2: RMAX =\002,d12.3,/\002 "
	    "LMAX = \002,i8,\002 N\002,\002INFO=\002,i8,\002 KNT=\002,i8)";
    static char fmt_9997[] = "(\002 Error in DLANV2: RMAX =\002,d12.3,/\002 "
	    "LMAX = \002,i8,\002 N\002,\002INFO=\002,i8,\002 KNT=\002,i8)";
    static char fmt_9996[] = "(\002 Error in DLAEXC: RMAX =\002,d12.3,/\002 "
	    "LMAX = \002,i8,\002 N\002,\002INFO=\002,2i8,\002 KNT=\002,i8)";
    static char fmt_9995[] = "(\002 Error in DTRSYL: RMAX =\002,d12.3,/\002 "
	    "LMAX = \002,i8,\002 N\002,\002INFO=\002,i8,\002 KNT=\002,i8)";
    static char fmt_9994[] = "(\002 Error in DTREXC: RMAX =\002,d12.3,/\002 "
	    "LMAX = \002,i8,\002 N\002,\002INFO=\002,3i8,\002 KNT=\002,i8)";
    static char fmt_9993[] = "(\002 Error in DTRSNA: RMAX =\002,3d12.3,/\002"
	    " LMAX = \002,3i8,\002 NINFO=\002,3i8,\002 KNT=\002,i8)";
    static char fmt_9992[] = "(\002 Error in DTRSEN: RMAX =\002,3d12.3,/\002"
	    " LMAX = \002,3i8,\002 NINFO=\002,3i8,\002 KNT=\002,i8)";
    static char fmt_9991[] = "(\002 Error in DLAQTR: RMAX =\002,d12.3,/\002 "
	    "LMAX = \002,i8,\002 N\002,\002INFO=\002,i8,\002 KNT=\002,i8)";
    static char fmt_9990[] = "(/1x,\002All tests for \002,a3,\002 routines p"
	    "assed the thresh\002,\002old (\002,i6,\002 tests run)\002)";

    /* Builtin functions   
       Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static char path[3];
    extern /* Subroutine */ int dget31_(doublereal *, integer *, integer *, 
	    integer *), dget32_(doublereal *, integer *, integer *, integer *)
	    , dget33_(doublereal *, integer *, integer *, integer *), dget34_(
	    doublereal *, integer *, integer *, integer *), dget35_(
	    doublereal *, integer *, integer *, integer *), dget36_(
	    doublereal *, integer *, integer *, integer *, integer *), 
	    dget37_(doublereal *, integer *, integer *, integer *, integer *),
	     dget38_(doublereal *, integer *, integer *, integer *, integer *)
	    , dget39_(doublereal *, integer *, integer *, integer *);
    static doublereal sfmin;
    static integer klaln2, llaln2, nlaln2[2];
    static doublereal rlaln2;
    static integer klanv2, llanv2, nlanv2;
    static doublereal rlanv2;
    static integer klasy2, llasy2, nlasy2;
    static doublereal rlasy2;
    extern doublereal dlamch_(char *);
    static logical ok;
    extern /* Subroutine */ int derrec_(char *, integer *);
    static integer klaexc, llaexc, nlaexc[2];
    static doublereal rlaexc;
    static integer klaqtr, llaqtr, ktrexc, ltrexc, ktrsna, nlaqtr, ltrsna[3];
    static doublereal rlaqtr;
    static integer ktrsen;
    static doublereal rtrexc;
    static integer ltrsen[3], ntrexc[3], ntrsen[3], ntrsna[3];
    static doublereal rtrsna[3], rtrsen[3];
    static integer ntests, ktrsyl, ltrsyl, ntrsyl;
    static doublereal rtrsyl, eps;

    /* Fortran I/O blocks */
    static cilist io___4 = { 0, 0, 0, fmt_9989, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_9988, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_9987, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___17 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___27 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___32 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___37 = { 0, 0, 0, fmt_9994, 0 };
    static cilist io___42 = { 0, 0, 0, fmt_9993, 0 };
    static cilist io___47 = { 0, 0, 0, fmt_9992, 0 };
    static cilist io___52 = { 0, 0, 0, fmt_9991, 0 };
    static cilist io___54 = { 0, 0, 0, fmt_9990, 0 };



/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DCHKEC tests eigen- condition estimation routines   
           DLALN2, DLASY2, DLANV2, DLAQTR, DLAEXC,   
           DTRSYL, DTREXC, DTRSNA, DTRSEN   

    In all cases, the routine runs through a fixed set of numerical   
    examples, subjects them to various tests, and compares the test   
    results to a threshold THRESH. In addition, DTREXC, DTRSNA and DTRSEN   
    are tested by reading in precomputed examples from a file (on input   
    unit NIN).  Output is written to output unit NOUT.   

    Arguments   
    =========   

    THRESH  (input) DOUBLE PRECISION   
            Threshold for residual tests.  A computed test ratio passes   
            the threshold if it is less than THRESH.   

    TSTERR  (input) LOGICAL   
            Flag that indicates whether error exits are to be tested.   

    NIN     (input) INTEGER   
            The logical unit number for input.   

    NOUT    (input) INTEGER   
            The logical unit number for output.   

    ===================================================================== */


    s_copy(path, "Double precision", (ftnlen)1, (ftnlen)16);
    s_copy(path + 1, "EC", (ftnlen)2, (ftnlen)2);
    eps = dlamch_("P");
    sfmin = dlamch_("S");

/*     Print header information */

    io___4.ciunit = *nout;
    s_wsfe(&io___4);
    e_wsfe();
    io___5.ciunit = *nout;
    s_wsfe(&io___5);
    do_fio(&c__1, (char *)&eps, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&sfmin, (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___6.ciunit = *nout;
    s_wsfe(&io___6);
    do_fio(&c__1, (char *)&(*thresh), (ftnlen)sizeof(doublereal));
    e_wsfe();

/*     Test error exits if TSTERR is .TRUE. */

    if (*tsterr) {
	derrec_(path, nout);
    }

    ok = TRUE_;
    dget31_(&rlaln2, &llaln2, nlaln2, &klaln2);
    if (rlaln2 > *thresh || nlaln2[0] != 0) {
	ok = FALSE_;
	io___12.ciunit = *nout;
	s_wsfe(&io___12);
	do_fio(&c__1, (char *)&rlaln2, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&llaln2, (ftnlen)sizeof(integer));
	do_fio(&c__2, (char *)&nlaln2[0], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&klaln2, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    dget32_(&rlasy2, &llasy2, &nlasy2, &klasy2);
    if (rlasy2 > *thresh) {
	ok = FALSE_;
	io___17.ciunit = *nout;
	s_wsfe(&io___17);
	do_fio(&c__1, (char *)&rlasy2, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&llasy2, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nlasy2, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&klasy2, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    dget33_(&rlanv2, &llanv2, &nlanv2, &klanv2);
    if (rlanv2 > *thresh || nlanv2 != 0) {
	ok = FALSE_;
	io___22.ciunit = *nout;
	s_wsfe(&io___22);
	do_fio(&c__1, (char *)&rlanv2, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&llanv2, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nlanv2, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&klanv2, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    dget34_(&rlaexc, &llaexc, nlaexc, &klaexc);
    if (rlaexc > *thresh || nlaexc[1] != 0) {
	ok = FALSE_;
	io___27.ciunit = *nout;
	s_wsfe(&io___27);
	do_fio(&c__1, (char *)&rlaexc, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&llaexc, (ftnlen)sizeof(integer));
	do_fio(&c__2, (char *)&nlaexc[0], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&klaexc, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    dget35_(&rtrsyl, &ltrsyl, &ntrsyl, &ktrsyl);
    if (rtrsyl > *thresh) {
	ok = FALSE_;
	io___32.ciunit = *nout;
	s_wsfe(&io___32);
	do_fio(&c__1, (char *)&rtrsyl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ltrsyl, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&ntrsyl, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&ktrsyl, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    dget36_(&rtrexc, &ltrexc, ntrexc, &ktrexc, nin);
    if (rtrexc > *thresh || ntrexc[2] > 0) {
	ok = FALSE_;
	io___37.ciunit = *nout;
	s_wsfe(&io___37);
	do_fio(&c__1, (char *)&rtrexc, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ltrexc, (ftnlen)sizeof(integer));
	do_fio(&c__3, (char *)&ntrexc[0], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&ktrexc, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    dget37_(rtrsna, ltrsna, ntrsna, &ktrsna, nin);
    if (rtrsna[0] > *thresh || rtrsna[1] > *thresh || ntrsna[0] != 0 || 
	    ntrsna[1] != 0 || ntrsna[2] != 0) {
	ok = FALSE_;
	io___42.ciunit = *nout;
	s_wsfe(&io___42);
	do_fio(&c__3, (char *)&rtrsna[0], (ftnlen)sizeof(doublereal));
	do_fio(&c__3, (char *)&ltrsna[0], (ftnlen)sizeof(integer));
	do_fio(&c__3, (char *)&ntrsna[0], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&ktrsna, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    dget38_(rtrsen, ltrsen, ntrsen, &ktrsen, nin);
    if (rtrsen[0] > *thresh || rtrsen[1] > *thresh || ntrsen[0] != 0 || 
	    ntrsen[1] != 0 || ntrsen[2] != 0) {
	ok = FALSE_;
	io___47.ciunit = *nout;
	s_wsfe(&io___47);
	do_fio(&c__3, (char *)&rtrsen[0], (ftnlen)sizeof(doublereal));
	do_fio(&c__3, (char *)&ltrsen[0], (ftnlen)sizeof(integer));
	do_fio(&c__3, (char *)&ntrsen[0], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&ktrsen, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    dget39_(&rlaqtr, &llaqtr, &nlaqtr, &klaqtr);
    if (rlaqtr > *thresh) {
	ok = FALSE_;
	io___52.ciunit = *nout;
	s_wsfe(&io___52);
	do_fio(&c__1, (char *)&rlaqtr, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&llaqtr, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nlaqtr, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&klaqtr, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    ntests = klaln2 + klasy2 + klanv2 + klaexc + ktrsyl + ktrexc + ktrsna + 
	    ktrsen + klaqtr;
    if (ok) {
	io___54.ciunit = *nout;
	s_wsfe(&io___54);
	do_fio(&c__1, path, (ftnlen)3);
	do_fio(&c__1, (char *)&ntests, (ftnlen)sizeof(integer));
	e_wsfe();
    }

    return 0;

/*     End of DCHKEC */

} /* dchkec_ */

