#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static real c_b7 = 1.f;
static integer c__1 = 1;

/* Subroutine */ int sort03_(char *rc, integer *mu, integer *mv, integer *n, 
	integer *k, real *u, integer *ldu, real *v, integer *ldv, real *work, 
	integer *lwork, real *result, integer *info)
{
    /* System generated locals */
    integer u_dim1, u_offset, v_dim1, v_offset, i__1, i__2;
    real r__1, r__2, r__3;

    /* Builtin functions */
    double r_sign(real *, real *);

    /* Local variables */
    static integer i__, j;
    static real s;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int sort01_(char *, integer *, integer *, real *, 
	    integer *, real *, integer *, real *);
    extern doublereal slamch_(char *);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer isamax_(integer *, real *, integer *);
    static integer irc, lmx;
    static real ulp, res1, res2;


#define u_ref(a_1,a_2) u[(a_2)*u_dim1 + a_1]
#define v_ref(a_1,a_2) v[(a_2)*v_dim1 + a_1]


/*  -- LAPACK test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    SORT03 compares two orthogonal matrices U and V to see if their   
    corresponding rows or columns span the same spaces.  The rows are   
    checked if RC = 'R', and the columns are checked if RC = 'C'.   

    RESULT is the maximum of   

       | V*V' - I | / ( MV ulp ), if RC = 'R', or   

       | V'*V - I | / ( MV ulp ), if RC = 'C',   

    and the maximum over rows (or columns) 1 to K of   

       | U(i) - S*V(i) |/ ( N ulp )   

    where S is +-1 (chosen to minimize the expression), U(i) is the i-th   
    row (column) of U, and V(i) is the i-th row (column) of V.   

    Arguments   
    ==========   

    RC      (input) CHARACTER*1   
            If RC = 'R' the rows of U and V are to be compared.   
            If RC = 'C' the columns of U and V are to be compared.   

    MU      (input) INTEGER   
            The number of rows of U if RC = 'R', and the number of   
            columns if RC = 'C'.  If MU = 0 SORT03 does nothing.   
            MU must be at least zero.   

    MV      (input) INTEGER   
            The number of rows of V if RC = 'R', and the number of   
            columns if RC = 'C'.  If MV = 0 SORT03 does nothing.   
            MV must be at least zero.   

    N       (input) INTEGER   
            If RC = 'R', the number of columns in the matrices U and V,   
            and if RC = 'C', the number of rows in U and V.  If N = 0   
            SORT03 does nothing.  N must be at least zero.   

    K       (input) INTEGER   
            The number of rows or columns of U and V to compare.   
            0 <= K <= max(MU,MV).   

    U       (input) REAL array, dimension (LDU,N)   
            The first matrix to compare.  If RC = 'R', U is MU by N, and   
            if RC = 'C', U is N by MU.   

    LDU     (input) INTEGER   
            The leading dimension of U.  If RC = 'R', LDU >= max(1,MU),   
            and if RC = 'C', LDU >= max(1,N).   

    V       (input) REAL array, dimension (LDV,N)   
            The second matrix to compare.  If RC = 'R', V is MV by N, and   
            if RC = 'C', V is N by MV.   

    LDV     (input) INTEGER   
            The leading dimension of V.  If RC = 'R', LDV >= max(1,MV),   
            and if RC = 'C', LDV >= max(1,N).   

    WORK    (workspace) REAL array, dimension (LWORK)   

    LWORK   (input) INTEGER   
            The length of the array WORK.  For best performance, LWORK   
            should be at least N*N if RC = 'C' or M*M if RC = 'R', but   
            the tests will be done even if LWORK is 0.   

    RESULT  (output) REAL   
            The value computed by the test described above.  RESULT is   
            limited to 1/ulp to avoid overflow.   

    INFO    (output) INTEGER   
            0  indicates a successful exit   
            -k indicates the k-th parameter had an illegal value   

    =====================================================================   


       Check inputs   

       Parameter adjustments */
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1 * 1;
    u -= u_offset;
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1 * 1;
    v -= v_offset;
    --work;

    /* Function Body */
    *info = 0;
    if (lsame_(rc, "R")) {
	irc = 0;
    } else if (lsame_(rc, "C")) {
	irc = 1;
    } else {
	irc = -1;
    }
    if (irc == -1) {
	*info = -1;
    } else if (*mu < 0) {
	*info = -2;
    } else if (*mv < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > max(*mu,*mv)) {
	*info = -5;
    } else if (irc == 0 && *ldu < max(1,*mu) || irc == 1 && *ldu < max(1,*n)) 
	    {
	*info = -7;
    } else if (irc == 0 && *ldv < max(1,*mv) || irc == 1 && *ldv < max(1,*n)) 
	    {
	*info = -9;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("SORT03", &i__1);
	return 0;
    }

/*     Initialize result */

    *result = 0.f;
    if (*mu == 0 || *mv == 0 || *n == 0) {
	return 0;
    }

/*     Machine constants */

    ulp = slamch_("Precision");

    if (irc == 0) {

/*        Compare rows */

	res1 = 0.f;
	i__1 = *k;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    lmx = isamax_(n, &u_ref(i__, 1), ldu);
	    s = r_sign(&c_b7, &u_ref(i__, lmx)) * r_sign(&c_b7, &v_ref(i__, 
		    lmx));
	    i__2 = *n;
	    for (j = 1; j <= i__2; ++j) {
/* Computing MAX */
		r__2 = res1, r__3 = (r__1 = u_ref(i__, j) - s * v_ref(i__, j),
			 dabs(r__1));
		res1 = dmax(r__2,r__3);
/* L10: */
	    }
/* L20: */
	}
	res1 /= (real) (*n) * ulp;

/*        Compute orthogonality of rows of V. */

	sort01_("Rows", mv, n, &v[v_offset], ldv, &work[1], lwork, &res2);

    } else {

/*        Compare columns */

	res1 = 0.f;
	i__1 = *k;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    lmx = isamax_(n, &u_ref(1, i__), &c__1);
	    s = r_sign(&c_b7, &u_ref(lmx, i__)) * r_sign(&c_b7, &v_ref(lmx, 
		    i__));
	    i__2 = *n;
	    for (j = 1; j <= i__2; ++j) {
/* Computing MAX */
		r__2 = res1, r__3 = (r__1 = u_ref(j, i__) - s * v_ref(j, i__),
			 dabs(r__1));
		res1 = dmax(r__2,r__3);
/* L30: */
	    }
/* L40: */
	}
	res1 /= (real) (*n) * ulp;

/*        Compute orthogonality of columns of V. */

	sort01_("Columns", n, mv, &v[v_offset], ldv, &work[1], lwork, &res2);
    }

/* Computing MIN */
    r__1 = dmax(res1,res2), r__2 = 1.f / ulp;
    *result = dmin(r__1,r__2);
    return 0;

/*     End of SORT03 */

} /* sort03_ */

#undef v_ref
#undef u_ref


