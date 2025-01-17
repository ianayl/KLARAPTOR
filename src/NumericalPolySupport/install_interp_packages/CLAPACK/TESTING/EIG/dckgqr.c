#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__8 = 8;
static integer c__1 = 1;
static integer c__0 = 0;

/* Subroutine */ int dckgqr_(integer *nm, integer *mval, integer *np, integer 
	*pval, integer *nn, integer *nval, integer *nmats, integer *iseed, 
	doublereal *thresh, integer *nmax, doublereal *a, doublereal *af, 
	doublereal *aq, doublereal *ar, doublereal *taua, doublereal *b, 
	doublereal *bf, doublereal *bz, doublereal *bt, doublereal *bwk, 
	doublereal *taub, doublereal *work, doublereal *rwork, integer *nin, 
	integer *nout, integer *info)
{
    /* Format strings */
    static char fmt_9999[] = "(\002 DLATMS in DCKGQR:    INFO = \002,i5)";
    static char fmt_9998[] = "(\002 M=\002,i4,\002 P=\002,i4,\002, N=\002,"
	    "i4,\002, type \002,i2,\002, test \002,i2,\002, ratio=\002,g13.6)";
    static char fmt_9997[] = "(\002 N=\002,i4,\002 M=\002,i4,\002, P=\002,"
	    "i4,\002, type \002,i2,\002, test \002,i2,\002, ratio=\002,g13.6)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;

    /* Builtin functions   
       Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static char path[3];
    static integer imat;
    static char type__[1];
    static integer nrun, i__, m, n, p, modea, modeb, nfail;
    static char dista[1], distb[1];
    static integer iinfo;
    static doublereal anorm, bnorm;
    static integer lwork;
    extern /* Subroutine */ int dlatb9_(char *, integer *, integer *, integer 
	    *, integer *, char *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, char *, char *), 
	    alahdg_(integer *, char *);
    static integer im, in, ip;
    static doublereal cndnma, cndnmb;
    static integer nt;
    extern /* Subroutine */ int alareq_(char *, integer *, logical *, integer 
	    *, integer *, integer *), alasum_(char *, integer *, 
	    integer *, integer *, integer *), dlatms_(integer *, 
	    integer *, char *, integer *, char *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, integer *, char *, 
	    doublereal *, integer *, doublereal *, integer *);
    static logical dotype[8];
    extern /* Subroutine */ int dgqrts_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     integer *, doublereal *, doublereal *), dgrqts_(integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, integer *, doublereal *
	    , doublereal *, integer *, doublereal *, doublereal *);
    static logical firstt;
    static doublereal result[7];
    static integer lda, ldb, kla, klb, kua, kub;

    /* Fortran I/O blocks */
    static cilist io___30 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___37 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_9997, 0 };



/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       March 31, 1993   


    Purpose   
    =======   

    DCKGQR tests   
    DGGQRF: GQR factorization for N-by-M matrix A and N-by-P matrix B,   
    DGGRQF: GRQ factorization for M-by-N matrix A and P-by-N matrix B.   

    Arguments   
    =========   

    NM      (input) INTEGER   
            The number of values of M contained in the vector MVAL.   

    MVAL    (input) INTEGER array, dimension (NM)   
            The values of the matrix row(column) dimension M.   

    NP      (input) INTEGER   
            The number of values of P contained in the vector PVAL.   

    PVAL    (input) INTEGER array, dimension (NP)   
            The values of the matrix row(column) dimension P.   

    NN      (input) INTEGER   
            The number of values of N contained in the vector NVAL.   

    NVAL    (input) INTEGER array, dimension (NN)   
            The values of the matrix column(row) dimension N.   

    NMATS   (input) INTEGER   
            The number of matrix types to be tested for each combination   
            of matrix dimensions.  If NMATS >= NTYPES (the maximum   
            number of matrix types), then all the different types are   
            generated for testing.  If NMATS < NTYPES, another input line   
            is read to get the numbers of the matrix types to be used.   

    ISEED   (input/output) INTEGER array, dimension (4)   
            On entry, the seed of the random number generator.  The array   
            elements should be between 0 and 4095, otherwise they will be   
            reduced mod 4096, and ISEED(4) must be odd.   
            On exit, the next seed in the random number sequence after   
            all the test matrices have been generated.   

    THRESH  (input) DOUBLE PRECISION   
            The threshold value for the test ratios.  A result is   
            included in the output file if RESULT >= THRESH.  To have   
            every test ratio printed, use THRESH = 0.   

    NMAX    (input) INTEGER   
            The maximum value permitted for M or N, used in dimensioning   
            the work arrays.   

    A       (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    AF      (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    AQ      (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    AR      (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    TAUA    (workspace) DOUBLE PRECISION array, dimension (NMAX)   

    B       (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    BF      (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    BZ      (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    BT      (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    BWK     (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    TAUB    (workspace) DOUBLE PRECISION array, dimension (NMAX)   

    WORK    (workspace) DOUBLE PRECISION array, dimension (NMAX*NMAX)   

    RWORK   (workspace) DOUBLE PRECISION array, dimension (NMAX)   

    NIN     (input) INTEGER   
            The unit number for input.   

    NOUT    (input) INTEGER   
            The unit number for output.   

    INFO    (output) INTEGER   
            = 0 :  successful exit   
            > 0 :  If DLATMS returns an error code, the absolute value   
                   of it is returned.   

    =====================================================================   


       Initialize constants.   

       Parameter adjustments */
    --rwork;
    --work;
    --taub;
    --bwk;
    --bt;
    --bz;
    --bf;
    --b;
    --taua;
    --ar;
    --aq;
    --af;
    --a;
    --iseed;
    --nval;
    --pval;
    --mval;

    /* Function Body */
    s_copy(path, "GQR", (ftnlen)3, (ftnlen)3);
    *info = 0;
    nrun = 0;
    nfail = 0;
    firstt = TRUE_;
    alareq_(path, nmats, dotype, &c__8, nin, nout);
    lda = *nmax;
    ldb = *nmax;
    lwork = *nmax * *nmax;

/*     Do for each value of M in MVAL. */

    i__1 = *nm;
    for (im = 1; im <= i__1; ++im) {
	m = mval[im];

/*        Do for each value of P in PVAL. */

	i__2 = *np;
	for (ip = 1; ip <= i__2; ++ip) {
	    p = pval[ip];

/*           Do for each value of N in NVAL. */

	    i__3 = *nn;
	    for (in = 1; in <= i__3; ++in) {
		n = nval[in];

		for (imat = 1; imat <= 8; ++imat) {

/*                 Do the tests only if DOTYPE( IMAT ) is true. */

		    if (! dotype[imat - 1]) {
			goto L30;
		    }

/*                 Test DGGRQF   

                   Set up parameters with DLATB9 and generate test   
                   matrices A and B with DLATMS. */

		    dlatb9_("GRQ", &imat, &m, &p, &n, type__, &kla, &kua, &
			    klb, &kub, &anorm, &bnorm, &modea, &modeb, &
			    cndnma, &cndnmb, dista, distb);

/*                 Generate M by N matrix A */

		    dlatms_(&m, &n, dista, &iseed[1], type__, &rwork[1], &
			    modea, &cndnma, &anorm, &kla, &kua, "No packing", 
			    &a[1], &lda, &work[1], &iinfo);
		    if (iinfo != 0) {
			io___30.ciunit = *nout;
			s_wsfe(&io___30);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			e_wsfe();
			*info = abs(iinfo);
			goto L30;
		    }

/*                 Generate P by N matrix B */

		    dlatms_(&p, &n, distb, &iseed[1], type__, &rwork[1], &
			    modeb, &cndnmb, &bnorm, &klb, &kub, "No packing", 
			    &b[1], &ldb, &work[1], &iinfo);
		    if (iinfo != 0) {
			io___31.ciunit = *nout;
			s_wsfe(&io___31);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			e_wsfe();
			*info = abs(iinfo);
			goto L30;
		    }

		    nt = 4;

		    dgrqts_(&m, &p, &n, &a[1], &af[1], &aq[1], &ar[1], &lda, &
			    taua[1], &b[1], &bf[1], &bz[1], &bt[1], &bwk[1], &
			    ldb, &taub[1], &work[1], &lwork, &rwork[1], 
			    result);

/*                 Print information about the tests that did not   
                   pass the threshold. */

		    i__4 = nt;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			if (result[i__ - 1] >= *thresh) {
			    if (nfail == 0 && firstt) {
				firstt = FALSE_;
				alahdg_(nout, "GRQ");
			    }
			    io___35.ciunit = *nout;
			    s_wsfe(&io___35);
			    do_fio(&c__1, (char *)&m, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&result[i__ - 1], (ftnlen)
				    sizeof(doublereal));
			    e_wsfe();
			    ++nfail;
			}
/* L10: */
		    }
		    nrun += nt;

/*                 Test DGGQRF   

                   Set up parameters with DLATB9 and generate test   
                   matrices A and B with DLATMS. */

		    dlatb9_("GQR", &imat, &m, &p, &n, type__, &kla, &kua, &
			    klb, &kub, &anorm, &bnorm, &modea, &modeb, &
			    cndnma, &cndnmb, dista, distb);

/*                 Generate N-by-M matrix  A */

		    dlatms_(&n, &m, dista, &iseed[1], type__, &rwork[1], &
			    modea, &cndnma, &anorm, &kla, &kua, "No packing", 
			    &a[1], &lda, &work[1], &iinfo);
		    if (iinfo != 0) {
			io___36.ciunit = *nout;
			s_wsfe(&io___36);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			e_wsfe();
			*info = abs(iinfo);
			goto L30;
		    }

/*                 Generate N-by-P matrix  B */

		    dlatms_(&n, &p, distb, &iseed[1], type__, &rwork[1], &
			    modea, &cndnma, &bnorm, &klb, &kub, "No packing", 
			    &b[1], &ldb, &work[1], &iinfo);
		    if (iinfo != 0) {
			io___37.ciunit = *nout;
			s_wsfe(&io___37);
			do_fio(&c__1, (char *)&iinfo, (ftnlen)sizeof(integer))
				;
			e_wsfe();
			*info = abs(iinfo);
			goto L30;
		    }

		    nt = 4;

		    dgqrts_(&n, &m, &p, &a[1], &af[1], &aq[1], &ar[1], &lda, &
			    taua[1], &b[1], &bf[1], &bz[1], &bt[1], &bwk[1], &
			    ldb, &taub[1], &work[1], &lwork, &rwork[1], 
			    result);

/*                 Print information about the tests that did not   
                   pass the threshold. */

		    i__4 = nt;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			if (result[i__ - 1] >= *thresh) {
			    if (nfail == 0 && firstt) {
				firstt = FALSE_;
				alahdg_(nout, path);
			    }
			    io___38.ciunit = *nout;
			    s_wsfe(&io___38);
			    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&m, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(integer))
				    ;
			    do_fio(&c__1, (char *)&imat, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(
				    integer));
			    do_fio(&c__1, (char *)&result[i__ - 1], (ftnlen)
				    sizeof(doublereal));
			    e_wsfe();
			    ++nfail;
			}
/* L20: */
		    }
		    nrun += nt;

L30:
		    ;
		}
/* L40: */
	    }
/* L50: */
	}
/* L60: */
    }

/*     Print a summary of the results. */

    alasum_(path, nout, &nfail, &nrun, &c__0);

    return 0;

/*     End of DCKGQR */

} /* dckgqr_ */

