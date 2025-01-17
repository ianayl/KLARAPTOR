#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublereal c_b7 = 10.;
static integer c_n1 = -1;
static integer c__5 = 5;
static integer c__13 = 13;
static integer c__1 = 1;

/* Subroutine */ int dchkeq_(doublereal *thresh, integer *nout)
{
    /* Format strings */
    static char fmt_9999[] = "(1x,\002All tests for \002,a3,\002 routines pa"
	    "ssed the threshold\002)";
    static char fmt_9998[] = "(\002 DGEEQU failed test with value \002,d10"
	    ".3,\002 exceeding\002,\002 threshold \002,d10.3)";
    static char fmt_9997[] = "(\002 DGBEQU failed test with value \002,d10"
	    ".3,\002 exceeding\002,\002 threshold \002,d10.3)";
    static char fmt_9996[] = "(\002 DPOEQU failed test with value \002,d10"
	    ".3,\002 exceeding\002,\002 threshold \002,d10.3)";
    static char fmt_9995[] = "(\002 DPPEQU failed test with value \002,d10"
	    ".3,\002 exceeding\002,\002 threshold \002,d10.3)";
    static char fmt_9994[] = "(\002 DPBEQU failed test with value \002,d10"
	    ".3,\002 exceeding\002,\002 threshold \002,d10.3)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5, i__6, i__7, i__8;
    doublereal d__1, d__2, d__3;

    /* Builtin functions   
       Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    double pow_di(doublereal *, integer *);
    integer pow_ii(integer *, integer *), s_wsle(cilist *), e_wsle(void), 
	    s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer info;
    static char path[3];
    static doublereal norm, rpow[11], a[25]	/* was [5][5] */, c__[5];
    static integer i__, j, m, n;
    static doublereal r__[5], ccond, rcond, rcmin, rcmax, ratio, ab[65]	/* 
	    was [13][5] */, ap[15];
    static integer kl;
    extern doublereal dlamch_(char *);
    static logical ok;
    static integer ku;
    extern /* Subroutine */ int dgbequ_(integer *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *), dgeequ_(
	    integer *, integer *, doublereal *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    , dpbequ_(char *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *), 
	    dpoequ_(integer *, doublereal *, integer *, doublereal *, 
	    doublereal *, doublereal *, integer *), dppequ_(char *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    );
    static doublereal reslts[5], eps, pow[11];

    /* Fortran I/O blocks */
    static cilist io___25 = { 0, 0, 0, 0, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_9999, 0 };
    static cilist io___27 = { 0, 0, 0, fmt_9998, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_9997, 0 };
    static cilist io___29 = { 0, 0, 0, fmt_9996, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_9995, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_9994, 0 };



#define a_ref(a_1,a_2) a[(a_2)*5 + a_1 - 6]
#define ab_ref(a_1,a_2) ab[(a_2)*13 + a_1 - 14]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DCHKEQ tests DGEEQU, DGBEQU, DPOEQU, DPPEQU and DPBEQU   

    Arguments   
    =========   

    THRESH  (input) DOUBLE PRECISION   
            Threshold for testing routines. Should be between 2 and 10.   

    NOUT    (input) INTEGER   
            The unit number for output.   

    ===================================================================== */


    s_copy(path, "Double precision", (ftnlen)1, (ftnlen)16);
    s_copy(path + 1, "EQ", (ftnlen)2, (ftnlen)2);

    eps = dlamch_("P");
    for (i__ = 1; i__ <= 5; ++i__) {
	reslts[i__ - 1] = 0.;
/* L10: */
    }
    for (i__ = 1; i__ <= 11; ++i__) {
	i__1 = i__ - 1;
	pow[i__ - 1] = pow_di(&c_b7, &i__1);
	rpow[i__ - 1] = 1. / pow[i__ - 1];
/* L20: */
    }

/*     Test DGEEQU */

    for (n = 0; n <= 5; ++n) {
	for (m = 0; m <= 5; ++m) {

	    for (j = 1; j <= 5; ++j) {
		for (i__ = 1; i__ <= 5; ++i__) {
		    if (i__ <= m && j <= n) {
			i__1 = i__ + j;
			a_ref(i__, j) = pow[i__ + j] * pow_ii(&c_n1, &i__1);
		    } else {
			a_ref(i__, j) = 0.;
		    }
/* L30: */
		}
/* L40: */
	    }

	    dgeequ_(&m, &n, a, &c__5, r__, c__, &rcond, &ccond, &norm, &info);

	    if (info != 0) {
		reslts[0] = 1.;
	    } else {
		if (n != 0 && m != 0) {
/* Computing MAX */
		    d__2 = reslts[0], d__3 = (d__1 = (rcond - rpow[m - 1]) / 
			    rpow[m - 1], abs(d__1));
		    reslts[0] = max(d__2,d__3);
/* Computing MAX */
		    d__2 = reslts[0], d__3 = (d__1 = (ccond - rpow[n - 1]) / 
			    rpow[n - 1], abs(d__1));
		    reslts[0] = max(d__2,d__3);
/* Computing MAX */
		    d__2 = reslts[0], d__3 = (d__1 = (norm - pow[n + m]) / 
			    pow[n + m], abs(d__1));
		    reslts[0] = max(d__2,d__3);
		    i__1 = m;
		    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
			d__2 = reslts[0], d__3 = (d__1 = (r__[i__ - 1] - rpow[
				i__ + n]) / rpow[i__ + n], abs(d__1));
			reslts[0] = max(d__2,d__3);
/* L50: */
		    }
		    i__1 = n;
		    for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
			d__2 = reslts[0], d__3 = (d__1 = (c__[j - 1] - pow[n 
				- j]) / pow[n - j], abs(d__1));
			reslts[0] = max(d__2,d__3);
/* L60: */
		    }
		}
	    }

/* L70: */
	}
/* L80: */
    }

/*     Test with zero rows and columns */

    for (j = 1; j <= 5; ++j) {
	a_ref(4, j) = 0.;
/* L90: */
    }
    dgeequ_(&c__5, &c__5, a, &c__5, r__, c__, &rcond, &ccond, &norm, &info);
    if (info != 4) {
	reslts[0] = 1.;
    }

    for (j = 1; j <= 5; ++j) {
	a_ref(4, j) = 1.;
/* L100: */
    }
    for (i__ = 1; i__ <= 5; ++i__) {
	a_ref(i__, 4) = 0.;
/* L110: */
    }
    dgeequ_(&c__5, &c__5, a, &c__5, r__, c__, &rcond, &ccond, &norm, &info);
    if (info != 9) {
	reslts[0] = 1.;
    }
    reslts[0] /= eps;

/*     Test DGBEQU */

    for (n = 0; n <= 5; ++n) {
	for (m = 0; m <= 5; ++m) {
/* Computing MAX */
	    i__2 = m - 1;
	    i__1 = max(i__2,0);
	    for (kl = 0; kl <= i__1; ++kl) {
/* Computing MAX */
		i__3 = n - 1;
		i__2 = max(i__3,0);
		for (ku = 0; ku <= i__2; ++ku) {

		    for (j = 1; j <= 5; ++j) {
			for (i__ = 1; i__ <= 13; ++i__) {
			    ab_ref(i__, j) = 0.;
/* L120: */
			}
/* L130: */
		    }
		    i__3 = n;
		    for (j = 1; j <= i__3; ++j) {
			i__4 = m;
			for (i__ = 1; i__ <= i__4; ++i__) {
/* Computing MIN */
			    i__5 = m, i__6 = j + kl;
/* Computing MAX */
			    i__7 = 1, i__8 = j - ku;
			    if (i__ <= min(i__5,i__6) && i__ >= max(i__7,i__8)
				     && j <= n) {
				i__5 = i__ + j;
				ab_ref(ku + 1 + i__ - j, j) = pow[i__ + j] * 
					pow_ii(&c_n1, &i__5);
			    }
/* L140: */
			}
/* L150: */
		    }

		    dgbequ_(&m, &n, &kl, &ku, ab, &c__13, r__, c__, &rcond, &
			    ccond, &norm, &info);

		    if (info != 0) {
			if (! (n + kl < m && info == n + kl + 1 || m + ku < n 
				&& info == (m << 1) + ku + 1)) {
			    reslts[1] = 1.;
			}
		    } else {
			if (n != 0 && m != 0) {

			    rcmin = r__[0];
			    rcmax = r__[0];
			    i__3 = m;
			    for (i__ = 1; i__ <= i__3; ++i__) {
/* Computing MIN */
				d__1 = rcmin, d__2 = r__[i__ - 1];
				rcmin = min(d__1,d__2);
/* Computing MAX */
				d__1 = rcmax, d__2 = r__[i__ - 1];
				rcmax = max(d__1,d__2);
/* L160: */
			    }
			    ratio = rcmin / rcmax;
/* Computing MAX */
			    d__2 = reslts[1], d__3 = (d__1 = (rcond - ratio) /
				     ratio, abs(d__1));
			    reslts[1] = max(d__2,d__3);

			    rcmin = c__[0];
			    rcmax = c__[0];
			    i__3 = n;
			    for (j = 1; j <= i__3; ++j) {
/* Computing MIN */
				d__1 = rcmin, d__2 = c__[j - 1];
				rcmin = min(d__1,d__2);
/* Computing MAX */
				d__1 = rcmax, d__2 = c__[j - 1];
				rcmax = max(d__1,d__2);
/* L170: */
			    }
			    ratio = rcmin / rcmax;
/* Computing MAX */
			    d__2 = reslts[1], d__3 = (d__1 = (ccond - ratio) /
				     ratio, abs(d__1));
			    reslts[1] = max(d__2,d__3);

/* Computing MAX */
			    d__2 = reslts[1], d__3 = (d__1 = (norm - pow[n + 
				    m]) / pow[n + m], abs(d__1));
			    reslts[1] = max(d__2,d__3);
			    i__3 = m;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				rcmax = 0.;
				i__4 = n;
				for (j = 1; j <= i__4; ++j) {
				    if (i__ <= j + kl && i__ >= j - ku) {
					ratio = (d__1 = r__[i__ - 1] * pow[
						i__ + j] * c__[j - 1], abs(
						d__1));
					rcmax = max(rcmax,ratio);
				    }
/* L180: */
				}
/* Computing MAX */
				d__2 = reslts[1], d__3 = (d__1 = 1. - rcmax, 
					abs(d__1));
				reslts[1] = max(d__2,d__3);
/* L190: */
			    }

			    i__3 = n;
			    for (j = 1; j <= i__3; ++j) {
				rcmax = 0.;
				i__4 = m;
				for (i__ = 1; i__ <= i__4; ++i__) {
				    if (i__ <= j + kl && i__ >= j - ku) {
					ratio = (d__1 = r__[i__ - 1] * pow[
						i__ + j] * c__[j - 1], abs(
						d__1));
					rcmax = max(rcmax,ratio);
				    }
/* L200: */
				}
/* Computing MAX */
				d__2 = reslts[1], d__3 = (d__1 = 1. - rcmax, 
					abs(d__1));
				reslts[1] = max(d__2,d__3);
/* L210: */
			    }
			}
		    }

/* L220: */
		}
/* L230: */
	    }
/* L240: */
	}
/* L250: */
    }
    reslts[1] /= eps;

/*     Test DPOEQU */

    for (n = 0; n <= 5; ++n) {

	for (i__ = 1; i__ <= 5; ++i__) {
	    for (j = 1; j <= 5; ++j) {
		if (i__ <= n && j == i__) {
		    i__1 = i__ + j;
		    a_ref(i__, j) = pow[i__ + j] * pow_ii(&c_n1, &i__1);
		} else {
		    a_ref(i__, j) = 0.;
		}
/* L260: */
	    }
/* L270: */
	}

	dpoequ_(&n, a, &c__5, r__, &rcond, &norm, &info);

	if (info != 0) {
	    reslts[2] = 1.;
	} else {
	    if (n != 0) {
/* Computing MAX */
		d__2 = reslts[2], d__3 = (d__1 = (rcond - rpow[n - 1]) / rpow[
			n - 1], abs(d__1));
		reslts[2] = max(d__2,d__3);
/* Computing MAX */
		d__2 = reslts[2], d__3 = (d__1 = (norm - pow[n * 2]) / pow[n *
			 2], abs(d__1));
		reslts[2] = max(d__2,d__3);
		i__1 = n;
		for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
		    d__2 = reslts[2], d__3 = (d__1 = (r__[i__ - 1] - rpow[i__]
			    ) / rpow[i__], abs(d__1));
		    reslts[2] = max(d__2,d__3);
/* L280: */
		}
	    }
	}
/* L290: */
    }
    a_ref(4, 4) = -1.;
    dpoequ_(&c__5, a, &c__5, r__, &rcond, &norm, &info);
    if (info != 4) {
	reslts[2] = 1.;
    }
    reslts[2] /= eps;

/*     Test DPPEQU */

    for (n = 0; n <= 5; ++n) {

/*        Upper triangular packed storage */

	i__1 = n * (n + 1) / 2;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ap[i__ - 1] = 0.;
/* L300: */
	}
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ap[i__ * (i__ + 1) / 2 - 1] = pow[i__ * 2];
/* L310: */
	}

	dppequ_("U", &n, ap, r__, &rcond, &norm, &info);

	if (info != 0) {
	    reslts[3] = 1.;
	} else {
	    if (n != 0) {
/* Computing MAX */
		d__2 = reslts[3], d__3 = (d__1 = (rcond - rpow[n - 1]) / rpow[
			n - 1], abs(d__1));
		reslts[3] = max(d__2,d__3);
/* Computing MAX */
		d__2 = reslts[3], d__3 = (d__1 = (norm - pow[n * 2]) / pow[n *
			 2], abs(d__1));
		reslts[3] = max(d__2,d__3);
		i__1 = n;
		for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
		    d__2 = reslts[3], d__3 = (d__1 = (r__[i__ - 1] - rpow[i__]
			    ) / rpow[i__], abs(d__1));
		    reslts[3] = max(d__2,d__3);
/* L320: */
		}
	    }
	}

/*        Lower triangular packed storage */

	i__1 = n * (n + 1) / 2;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ap[i__ - 1] = 0.;
/* L330: */
	}
	j = 1;
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ap[j - 1] = pow[i__ * 2];
	    j += n - i__ + 1;
/* L340: */
	}

	dppequ_("L", &n, ap, r__, &rcond, &norm, &info);

	if (info != 0) {
	    reslts[3] = 1.;
	} else {
	    if (n != 0) {
/* Computing MAX */
		d__2 = reslts[3], d__3 = (d__1 = (rcond - rpow[n - 1]) / rpow[
			n - 1], abs(d__1));
		reslts[3] = max(d__2,d__3);
/* Computing MAX */
		d__2 = reslts[3], d__3 = (d__1 = (norm - pow[n * 2]) / pow[n *
			 2], abs(d__1));
		reslts[3] = max(d__2,d__3);
		i__1 = n;
		for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
		    d__2 = reslts[3], d__3 = (d__1 = (r__[i__ - 1] - rpow[i__]
			    ) / rpow[i__], abs(d__1));
		    reslts[3] = max(d__2,d__3);
/* L350: */
		}
	    }
	}

/* L360: */
    }
    i__ = 13;
    ap[i__ - 1] = -1.;
    dppequ_("L", &c__5, ap, r__, &rcond, &norm, &info);
    if (info != 4) {
	reslts[3] = 1.;
    }
    reslts[3] /= eps;

/*     Test DPBEQU */

    for (n = 0; n <= 5; ++n) {
/* Computing MAX */
	i__2 = n - 1;
	i__1 = max(i__2,0);
	for (kl = 0; kl <= i__1; ++kl) {

/*           Test upper triangular storage */

	    for (j = 1; j <= 5; ++j) {
		for (i__ = 1; i__ <= 13; ++i__) {
		    ab_ref(i__, j) = 0.;
/* L370: */
		}
/* L380: */
	    }
	    i__2 = n;
	    for (j = 1; j <= i__2; ++j) {
		ab_ref(kl + 1, j) = pow[j * 2];
/* L390: */
	    }

	    dpbequ_("U", &n, &kl, ab, &c__13, r__, &rcond, &norm, &info);

	    if (info != 0) {
		reslts[4] = 1.;
	    } else {
		if (n != 0) {
/* Computing MAX */
		    d__2 = reslts[4], d__3 = (d__1 = (rcond - rpow[n - 1]) / 
			    rpow[n - 1], abs(d__1));
		    reslts[4] = max(d__2,d__3);
/* Computing MAX */
		    d__2 = reslts[4], d__3 = (d__1 = (norm - pow[n * 2]) / 
			    pow[n * 2], abs(d__1));
		    reslts[4] = max(d__2,d__3);
		    i__2 = n;
		    for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
			d__2 = reslts[4], d__3 = (d__1 = (r__[i__ - 1] - rpow[
				i__]) / rpow[i__], abs(d__1));
			reslts[4] = max(d__2,d__3);
/* L400: */
		    }
		}
	    }
	    if (n != 0) {
/* Computing MAX */
		i__2 = n - 1;
		ab_ref(kl + 1, max(i__2,1)) = -1.;
		dpbequ_("U", &n, &kl, ab, &c__13, r__, &rcond, &norm, &info);
/* Computing MAX */
		i__2 = n - 1;
		if (info != max(i__2,1)) {
		    reslts[4] = 1.;
		}
	    }

/*           Test lower triangular storage */

	    for (j = 1; j <= 5; ++j) {
		for (i__ = 1; i__ <= 13; ++i__) {
		    ab_ref(i__, j) = 0.;
/* L410: */
		}
/* L420: */
	    }
	    i__2 = n;
	    for (j = 1; j <= i__2; ++j) {
		ab_ref(1, j) = pow[j * 2];
/* L430: */
	    }

	    dpbequ_("L", &n, &kl, ab, &c__13, r__, &rcond, &norm, &info);

	    if (info != 0) {
		reslts[4] = 1.;
	    } else {
		if (n != 0) {
/* Computing MAX */
		    d__2 = reslts[4], d__3 = (d__1 = (rcond - rpow[n - 1]) / 
			    rpow[n - 1], abs(d__1));
		    reslts[4] = max(d__2,d__3);
/* Computing MAX */
		    d__2 = reslts[4], d__3 = (d__1 = (norm - pow[n * 2]) / 
			    pow[n * 2], abs(d__1));
		    reslts[4] = max(d__2,d__3);
		    i__2 = n;
		    for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
			d__2 = reslts[4], d__3 = (d__1 = (r__[i__ - 1] - rpow[
				i__]) / rpow[i__], abs(d__1));
			reslts[4] = max(d__2,d__3);
/* L440: */
		    }
		}
	    }
	    if (n != 0) {
/* Computing MAX */
		i__2 = n - 1;
		ab_ref(1, max(i__2,1)) = -1.;
		dpbequ_("L", &n, &kl, ab, &c__13, r__, &rcond, &norm, &info);
/* Computing MAX */
		i__2 = n - 1;
		if (info != max(i__2,1)) {
		    reslts[4] = 1.;
		}
	    }
/* L450: */
	}
/* L460: */
    }
    reslts[4] /= eps;
    ok = reslts[0] <= *thresh && reslts[1] <= *thresh && reslts[2] <= *thresh 
	    && reslts[3] <= *thresh && reslts[4] <= *thresh;
    io___25.ciunit = *nout;
    s_wsle(&io___25);
    e_wsle();
    if (ok) {
	io___26.ciunit = *nout;
	s_wsfe(&io___26);
	do_fio(&c__1, path, (ftnlen)3);
	e_wsfe();
    } else {
	if (reslts[0] > *thresh) {
	    io___27.ciunit = *nout;
	    s_wsfe(&io___27);
	    do_fio(&c__1, (char *)&reslts[0], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*thresh), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	if (reslts[1] > *thresh) {
	    io___28.ciunit = *nout;
	    s_wsfe(&io___28);
	    do_fio(&c__1, (char *)&reslts[1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*thresh), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	if (reslts[2] > *thresh) {
	    io___29.ciunit = *nout;
	    s_wsfe(&io___29);
	    do_fio(&c__1, (char *)&reslts[2], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*thresh), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	if (reslts[3] > *thresh) {
	    io___30.ciunit = *nout;
	    s_wsfe(&io___30);
	    do_fio(&c__1, (char *)&reslts[3], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*thresh), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	if (reslts[4] > *thresh) {
	    io___31.ciunit = *nout;
	    s_wsfe(&io___31);
	    do_fio(&c__1, (char *)&reslts[4], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*thresh), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
    return 0;

/*     End of DCHKEQ */

} /* dchkeq_ */

#undef ab_ref
#undef a_ref


