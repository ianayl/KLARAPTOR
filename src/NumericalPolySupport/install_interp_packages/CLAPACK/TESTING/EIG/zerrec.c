#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer infot, nout;
    logical ok, lerr;
} infoc_;

#define infoc_1 infoc_

struct {
    char srnamt[6];
} srnamc_;

#define srnamc_1 srnamc_

/* Table of constant values */

static integer c__1 = 1;
static integer c__0 = 0;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__3 = 3;

/* Subroutine */ int zerrec_(char *path, integer *nunit)
{
    /* Format strings */
    static char fmt_9999[] = "(1x,a3,\002 routines passed the tests of the e"
	    "rror exits (\002,i3,\002 tests done)\002)";
    static char fmt_9998[] = "(\002 *** \002,a3,\002 routines failed the tes"
	    "ts of the error \002,\002exits ***\002)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions   
       Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer info, ifst, ilst;
    static doublecomplex work[24], a[16]	/* was [4][4] */, b[16]	/* 
	    was [4][4] */, c__[16]	/* was [4][4] */;
    static integer i__, j, m;
    static doublereal s[4], scale;
    static doublecomplex x[4];
    static integer nt;
    static doublereal rw[24];
    extern /* Subroutine */ int chkxer_(char *, integer *, integer *, logical 
	    *, logical *), ztrexc_(char *, integer *, doublecomplex *,
	     integer *, doublecomplex *, integer *, integer *, integer *, 
	    integer *), ztrsna_(char *, char *, logical *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublereal *, doublereal *, integer *,
	     integer *, doublecomplex *, integer *, doublereal *, integer *), ztrsen_(char *, char *, logical *, integer *, 
	    doublecomplex *, integer *, doublecomplex *, integer *, 
	    doublecomplex *, integer *, doublereal *, doublereal *, 
	    doublecomplex *, integer *, integer *), ztrsyl_(
	    char *, char *, integer *, integer *, integer *, doublecomplex *, 
	    integer *, doublecomplex *, integer *, doublecomplex *, integer *,
	     doublereal *, integer *);
    static logical sel[4];
    static doublereal sep[4];

    /* Fortran I/O blocks */
    static cilist io___18 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___19 = { 0, 0, 0, fmt_9998, 0 };



#define a_subscr(a_1,a_2) (a_2)*4 + a_1 - 5
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define b_subscr(a_1,a_2) (a_2)*4 + a_1 - 5
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       June 30, 1999   


    Purpose   
    =======   

    ZERREC tests the error exits for the routines for eigen- condition   
    estimation for DOUBLE PRECISION matrices:   
       ZTRSYL, CTREXC, CTRSNA and CTRSEN.   

    Arguments   
    =========   

    PATH    (input) CHARACTER*3   
            The LAPACK path name for the routines to be tested.   

    NUNIT   (input) INTEGER   
            The unit number for output.   

    ===================================================================== */


    infoc_1.nout = *nunit;
    infoc_1.ok = TRUE_;
    nt = 0;

/*     Initialize A, B and SEL */

    for (j = 1; j <= 4; ++j) {
	for (i__ = 1; i__ <= 4; ++i__) {
	    i__1 = a_subscr(i__, j);
	    a[i__1].r = 0., a[i__1].i = 0.;
	    i__1 = b_subscr(i__, j);
	    b[i__1].r = 0., b[i__1].i = 0.;
/* L10: */
	}
/* L20: */
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	i__1 = a_subscr(i__, i__);
	a[i__1].r = 1., a[i__1].i = 0.;
	sel[i__ - 1] = TRUE_;
/* L30: */
    }

/*     Test ZTRSYL */

    s_copy(srnamc_1.srnamt, "ZTRSYL", (ftnlen)6, (ftnlen)6);
    infoc_1.infot = 1;
    ztrsyl_("X", "N", &c__1, &c__0, &c__0, a, &c__1, b, &c__1, c__, &c__1, &
	    scale, &info);
    chkxer_("ZTRSYL", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 2;
    ztrsyl_("N", "X", &c__1, &c__0, &c__0, a, &c__1, b, &c__1, c__, &c__1, &
	    scale, &info);
    chkxer_("ZTRSYL", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 3;
    ztrsyl_("N", "N", &c__0, &c__0, &c__0, a, &c__1, b, &c__1, c__, &c__1, &
	    scale, &info);
    chkxer_("ZTRSYL", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 4;
    ztrsyl_("N", "N", &c__1, &c_n1, &c__0, a, &c__1, b, &c__1, c__, &c__1, &
	    scale, &info);
    chkxer_("ZTRSYL", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 5;
    ztrsyl_("N", "N", &c__1, &c__0, &c_n1, a, &c__1, b, &c__1, c__, &c__1, &
	    scale, &info);
    chkxer_("ZTRSYL", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 7;
    ztrsyl_("N", "N", &c__1, &c__2, &c__0, a, &c__1, b, &c__1, c__, &c__2, &
	    scale, &info);
    chkxer_("ZTRSYL", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 9;
    ztrsyl_("N", "N", &c__1, &c__0, &c__2, a, &c__1, b, &c__1, c__, &c__1, &
	    scale, &info);
    chkxer_("ZTRSYL", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 11;
    ztrsyl_("N", "N", &c__1, &c__2, &c__0, a, &c__2, b, &c__1, c__, &c__1, &
	    scale, &info);
    chkxer_("ZTRSYL", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    nt += 8;

/*     Test ZTREXC */

    s_copy(srnamc_1.srnamt, "ZTREXC", (ftnlen)6, (ftnlen)6);
    ifst = 1;
    ilst = 1;
    infoc_1.infot = 1;
    ztrexc_("X", &c__1, a, &c__1, b, &c__1, &ifst, &ilst, &info);
    chkxer_("ZTREXC", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 7;
    ztrexc_("N", &c__0, a, &c__1, b, &c__1, &ifst, &ilst, &info);
    chkxer_("ZTREXC", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 4;
    ilst = 2;
    ztrexc_("N", &c__2, a, &c__1, b, &c__1, &ifst, &ilst, &info);
    chkxer_("ZTREXC", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 6;
    ztrexc_("V", &c__2, a, &c__2, b, &c__1, &ifst, &ilst, &info);
    chkxer_("ZTREXC", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 7;
    ifst = 0;
    ilst = 1;
    ztrexc_("V", &c__1, a, &c__1, b, &c__1, &ifst, &ilst, &info);
    chkxer_("ZTREXC", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 7;
    ifst = 2;
    ztrexc_("V", &c__1, a, &c__1, b, &c__1, &ifst, &ilst, &info);
    chkxer_("ZTREXC", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 8;
    ifst = 1;
    ilst = 0;
    ztrexc_("V", &c__1, a, &c__1, b, &c__1, &ifst, &ilst, &info);
    chkxer_("ZTREXC", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 8;
    ilst = 2;
    ztrexc_("V", &c__1, a, &c__1, b, &c__1, &ifst, &ilst, &info);
    chkxer_("ZTREXC", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    nt += 8;

/*     Test ZTRSNA */

    s_copy(srnamc_1.srnamt, "ZTRSNA", (ftnlen)6, (ftnlen)6);
    infoc_1.infot = 1;
    ztrsna_("X", "A", sel, &c__0, a, &c__1, b, &c__1, c__, &c__1, s, sep, &
	    c__1, &m, work, &c__1, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 2;
    ztrsna_("B", "X", sel, &c__0, a, &c__1, b, &c__1, c__, &c__1, s, sep, &
	    c__1, &m, work, &c__1, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 4;
    ztrsna_("B", "A", sel, &c_n1, a, &c__1, b, &c__1, c__, &c__1, s, sep, &
	    c__1, &m, work, &c__1, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 6;
    ztrsna_("V", "A", sel, &c__2, a, &c__1, b, &c__1, c__, &c__1, s, sep, &
	    c__2, &m, work, &c__2, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 8;
    ztrsna_("B", "A", sel, &c__2, a, &c__2, b, &c__1, c__, &c__2, s, sep, &
	    c__2, &m, work, &c__2, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 10;
    ztrsna_("B", "A", sel, &c__2, a, &c__2, b, &c__2, c__, &c__1, s, sep, &
	    c__2, &m, work, &c__2, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 13;
    ztrsna_("B", "A", sel, &c__1, a, &c__1, b, &c__1, c__, &c__1, s, sep, &
	    c__0, &m, work, &c__1, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 13;
    ztrsna_("B", "S", sel, &c__2, a, &c__2, b, &c__2, c__, &c__2, s, sep, &
	    c__1, &m, work, &c__1, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 16;
    ztrsna_("B", "A", sel, &c__2, a, &c__2, b, &c__2, c__, &c__2, s, sep, &
	    c__2, &m, work, &c__1, rw, &info);
    chkxer_("ZTRSNA", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    nt += 9;

/*     Test ZTRSEN */

    sel[0] = FALSE_;
    s_copy(srnamc_1.srnamt, "ZTRSEN", (ftnlen)6, (ftnlen)6);
    infoc_1.infot = 1;
    ztrsen_("X", "N", sel, &c__0, a, &c__1, b, &c__1, x, &m, s, sep, work, &
	    c__1, &info);
    chkxer_("ZTRSEN", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 2;
    ztrsen_("N", "X", sel, &c__0, a, &c__1, b, &c__1, x, &m, s, sep, work, &
	    c__1, &info);
    chkxer_("ZTRSEN", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 4;
    ztrsen_("N", "N", sel, &c_n1, a, &c__1, b, &c__1, x, &m, s, sep, work, &
	    c__1, &info);
    chkxer_("ZTRSEN", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 6;
    ztrsen_("N", "N", sel, &c__2, a, &c__1, b, &c__1, x, &m, s, sep, work, &
	    c__2, &info);
    chkxer_("ZTRSEN", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 8;
    ztrsen_("N", "V", sel, &c__2, a, &c__2, b, &c__1, x, &m, s, sep, work, &
	    c__1, &info);
    chkxer_("ZTRSEN", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 14;
    ztrsen_("N", "V", sel, &c__2, a, &c__2, b, &c__2, x, &m, s, sep, work, &
	    c__0, &info);
    chkxer_("ZTRSEN", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 14;
    ztrsen_("E", "V", sel, &c__3, a, &c__3, b, &c__3, x, &m, s, sep, work, &
	    c__1, &info);
    chkxer_("ZTRSEN", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    infoc_1.infot = 14;
    ztrsen_("V", "V", sel, &c__3, a, &c__3, b, &c__3, x, &m, s, sep, work, &
	    c__3, &info);
    chkxer_("ZTRSEN", &infoc_1.infot, &infoc_1.nout, &infoc_1.lerr, &
	    infoc_1.ok);
    nt += 8;

/*     Print a summary line. */

    if (infoc_1.ok) {
	io___18.ciunit = infoc_1.nout;
	s_wsfe(&io___18);
	do_fio(&c__1, path, (ftnlen)3);
	do_fio(&c__1, (char *)&nt, (ftnlen)sizeof(integer));
	e_wsfe();
    } else {
	io___19.ciunit = infoc_1.nout;
	s_wsfe(&io___19);
	do_fio(&c__1, path, (ftnlen)3);
	e_wsfe();
    }

    return 0;

/*     End of ZERREC */

} /* zerrec_ */

#undef b_ref
#undef b_subscr
#undef a_ref
#undef a_subscr


