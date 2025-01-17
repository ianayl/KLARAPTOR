#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static complex c_b1 = {1.f,0.f};
static integer c__1 = 1;

/* Subroutine */ int clavsy_(char *uplo, char *trans, char *diag, integer *n, 
	integer *nrhs, complex *a, integer *lda, integer *ipiv, complex *b, 
	integer *ldb, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2;
    complex q__1, q__2, q__3;

    /* Local variables */
    static integer j, k;
    extern /* Subroutine */ int cscal_(integer *, complex *, complex *, 
	    integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int cgemv_(char *, integer *, integer *, complex *
	    , complex *, integer *, complex *, integer *, complex *, complex *
	    , integer *), cgeru_(integer *, integer *, complex *, 
	    complex *, integer *, complex *, integer *, complex *, integer *),
	     cswap_(integer *, complex *, integer *, complex *, integer *);
    static complex t1, t2, d11, d12, d21, d22;
    static integer kp;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static logical nounit;


#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define b_subscr(a_1,a_2) (a_2)*b_dim1 + a_1
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]


/*  -- LAPACK auxiliary routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

       CLAVSY  performs one of the matrix-vector operations   
          x := A*x  or  x := A'*x,   
       where x is an N element vector and  A is one of the factors   
       from the symmetric factorization computed by CSYTRF.   
       CSYTRF produces a factorization of the form   
            U * D * U'      or     L * D * L' ,   
       where U (or L) is a product of permutation and unit upper (lower)   
       triangular matrices, U' (or L') is the transpose of   
       U (or L), and D is symmetric and block diagonal with 1 x 1 and   
       2 x 2 diagonal blocks.  The multipliers for the transformations   
       and the upper or lower triangular parts of the diagonal blocks   
       are stored in the leading upper or lower triangle of the 2-D   
       array A.   

       If TRANS = 'N' or 'n', CLAVSY multiplies either by U or U * D   
       (or L or L * D).   
       If TRANS = 'T' or 't', CLAVSY multiplies either by U' or D * U'   
       (or L' or D * L' ).   

    Arguments   
    ==========   

    UPLO   - CHARACTER*1   
             On entry, UPLO specifies whether the triangular matrix   
             stored in A is upper or lower triangular.   
                UPLO = 'U' or 'u'   The matrix is upper triangular.   
                UPLO = 'L' or 'l'   The matrix is lower triangular.   
             Unchanged on exit.   

    TRANS  - CHARACTER*1   
             On entry, TRANS specifies the operation to be performed as   
             follows:   
                TRANS = 'N' or 'n'   x := A*x.   
                TRANS = 'T' or 't'   x := A'*x.   
             Unchanged on exit.   

    DIAG   - CHARACTER*1   
             On entry, DIAG specifies whether the diagonal blocks are   
             assumed to be unit matrices:   
                DIAG = 'U' or 'u'   Diagonal blocks are unit matrices.   
                DIAG = 'N' or 'n'   Diagonal blocks are non-unit.   
             Unchanged on exit.   

    N      - INTEGER   
             On entry, N specifies the order of the matrix A.   
             N must be at least zero.   
             Unchanged on exit.   

    NRHS   - INTEGER   
             On entry, NRHS specifies the number of right hand sides,   
             i.e., the number of vectors x to be multiplied by A.   
             NRHS must be at least zero.   
             Unchanged on exit.   

    A      - COMPLEX array, dimension( LDA, N )   
             On entry, A contains a block diagonal matrix and the   
             multipliers of the transformations used to obtain it,   
             stored as a 2-D triangular matrix.   
             Unchanged on exit.   

    LDA    - INTEGER   
             On entry, LDA specifies the first dimension of A as declared   
             in the calling ( sub ) program. LDA must be at least   
             max( 1, N ).   
             Unchanged on exit.   

    IPIV   - INTEGER array, dimension( N )   
             On entry, IPIV contains the vector of pivot indices as   
             determined by CSYTRF or CHETRF.   
             If IPIV( K ) = K, no interchange was done.   
             If IPIV( K ) <> K but IPIV( K ) > 0, then row K was inter-   
             changed with row IPIV( K ) and a 1 x 1 pivot block was used.   
             If IPIV( K ) < 0 and UPLO = 'U', then row K-1 was exchanged   
             with row | IPIV( K ) | and a 2 x 2 pivot block was used.   
             If IPIV( K ) < 0 and UPLO = 'L', then row K+1 was exchanged   
             with row | IPIV( K ) | and a 2 x 2 pivot block was used.   

    B      - COMPLEX array, dimension( LDB, NRHS )   
             On entry, B contains NRHS vectors of length N.   
             On exit, B is overwritten with the product A * B.   

    LDB    - INTEGER   
             On entry, LDB contains the leading dimension of B as   
             declared in the calling program.  LDB must be at least   
             max( 1, N ).   
             Unchanged on exit.   

    INFO   - INTEGER   
             INFO is the error flag.   
             On exit, a value of 0 indicates a successful exit.   
             A negative value, say -K, indicates that the K-th argument   
             has an illegal value.   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    if (! lsame_(uplo, "U") && ! lsame_(uplo, "L")) {
	*info = -1;
    } else if (! lsame_(trans, "N") && ! lsame_(trans, 
	    "T")) {
	*info = -2;
    } else if (! lsame_(diag, "U") && ! lsame_(diag, 
	    "N")) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*lda < max(1,*n)) {
	*info = -6;
    } else if (*ldb < max(1,*n)) {
	*info = -9;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CLAVSY ", &i__1);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0) {
	return 0;
    }

    nounit = lsame_(diag, "N");
/* ------------------------------------------   

       Compute  B := A * B  (No transpose)   

   ------------------------------------------ */
    if (lsame_(trans, "N")) {

/*        Compute  B := U*B   
          where U = P(m)*inv(U(m))* ... *P(1)*inv(U(1)) */

	if (lsame_(uplo, "U")) {

/*        Loop forward applying the transformations. */

	    k = 1;
L10:
	    if (k > *n) {
		goto L30;
	    }
	    if (ipiv[k] > 0) {

/*              1 x 1 pivot block   

                Multiply by the diagonal element if forming U * D. */

		if (nounit) {
		    cscal_(nrhs, &a_ref(k, k), &b_ref(k, 1), ldb);
		}

/*              Multiply by  P(K) * inv(U(K))  if K > 1. */

		if (k > 1) {

/*                 Apply the transformation. */

		    i__1 = k - 1;
		    cgeru_(&i__1, nrhs, &c_b1, &a_ref(1, k), &c__1, &b_ref(k, 
			    1), ldb, &b_ref(1, 1), ldb);

/*                 Interchange if P(K) != I. */

		    kp = ipiv[k];
		    if (kp != k) {
			cswap_(nrhs, &b_ref(k, 1), ldb, &b_ref(kp, 1), ldb);
		    }
		}
		++k;
	    } else {

/*              2 x 2 pivot block   

                Multiply by the diagonal block if forming U * D. */

		if (nounit) {
		    i__1 = a_subscr(k, k);
		    d11.r = a[i__1].r, d11.i = a[i__1].i;
		    i__1 = a_subscr(k + 1, k + 1);
		    d22.r = a[i__1].r, d22.i = a[i__1].i;
		    i__1 = a_subscr(k, k + 1);
		    d12.r = a[i__1].r, d12.i = a[i__1].i;
		    d21.r = d12.r, d21.i = d12.i;
		    i__1 = *nrhs;
		    for (j = 1; j <= i__1; ++j) {
			i__2 = b_subscr(k, j);
			t1.r = b[i__2].r, t1.i = b[i__2].i;
			i__2 = b_subscr(k + 1, j);
			t2.r = b[i__2].r, t2.i = b[i__2].i;
			i__2 = b_subscr(k, j);
			q__2.r = d11.r * t1.r - d11.i * t1.i, q__2.i = d11.r *
				 t1.i + d11.i * t1.r;
			q__3.r = d12.r * t2.r - d12.i * t2.i, q__3.i = d12.r *
				 t2.i + d12.i * t2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
			i__2 = b_subscr(k + 1, j);
			q__2.r = d21.r * t1.r - d21.i * t1.i, q__2.i = d21.r *
				 t1.i + d21.i * t1.r;
			q__3.r = d22.r * t2.r - d22.i * t2.i, q__3.i = d22.r *
				 t2.i + d22.i * t2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L20: */
		    }
		}

/*              Multiply by  P(K) * inv(U(K))  if K > 1. */

		if (k > 1) {

/*                 Apply the transformations. */

		    i__1 = k - 1;
		    cgeru_(&i__1, nrhs, &c_b1, &a_ref(1, k), &c__1, &b_ref(k, 
			    1), ldb, &b_ref(1, 1), ldb);
		    i__1 = k - 1;
		    cgeru_(&i__1, nrhs, &c_b1, &a_ref(1, k + 1), &c__1, &
			    b_ref(k + 1, 1), ldb, &b_ref(1, 1), ldb);

/*                 Interchange if P(K) != I. */

		    kp = (i__1 = ipiv[k], abs(i__1));
		    if (kp != k) {
			cswap_(nrhs, &b_ref(k, 1), ldb, &b_ref(kp, 1), ldb);
		    }
		}
		k += 2;
	    }
	    goto L10;
L30:

/*        Compute  B := L*B   
          where L = P(1)*inv(L(1))* ... *P(m)*inv(L(m)) . */

	    ;
	} else {

/*           Loop backward applying the transformations to B. */

	    k = *n;
L40:
	    if (k < 1) {
		goto L60;
	    }

/*           Test the pivot index.  If greater than zero, a 1 x 1   
             pivot was used, otherwise a 2 x 2 pivot was used. */

	    if (ipiv[k] > 0) {

/*              1 x 1 pivot block:   

                Multiply by the diagonal element if forming L * D. */

		if (nounit) {
		    cscal_(nrhs, &a_ref(k, k), &b_ref(k, 1), ldb);
		}

/*              Multiply by  P(K) * inv(L(K))  if K < N. */

		if (k != *n) {
		    kp = ipiv[k];

/*                 Apply the transformation. */

		    i__1 = *n - k;
		    cgeru_(&i__1, nrhs, &c_b1, &a_ref(k + 1, k), &c__1, &
			    b_ref(k, 1), ldb, &b_ref(k + 1, 1), ldb);

/*                 Interchange if a permutation was applied at the   
                   K-th step of the factorization. */

		    if (kp != k) {
			cswap_(nrhs, &b_ref(k, 1), ldb, &b_ref(kp, 1), ldb);
		    }
		}
		--k;

	    } else {

/*              2 x 2 pivot block:   

                Multiply by the diagonal block if forming L * D. */

		if (nounit) {
		    i__1 = a_subscr(k - 1, k - 1);
		    d11.r = a[i__1].r, d11.i = a[i__1].i;
		    i__1 = a_subscr(k, k);
		    d22.r = a[i__1].r, d22.i = a[i__1].i;
		    i__1 = a_subscr(k, k - 1);
		    d21.r = a[i__1].r, d21.i = a[i__1].i;
		    d12.r = d21.r, d12.i = d21.i;
		    i__1 = *nrhs;
		    for (j = 1; j <= i__1; ++j) {
			i__2 = b_subscr(k - 1, j);
			t1.r = b[i__2].r, t1.i = b[i__2].i;
			i__2 = b_subscr(k, j);
			t2.r = b[i__2].r, t2.i = b[i__2].i;
			i__2 = b_subscr(k - 1, j);
			q__2.r = d11.r * t1.r - d11.i * t1.i, q__2.i = d11.r *
				 t1.i + d11.i * t1.r;
			q__3.r = d12.r * t2.r - d12.i * t2.i, q__3.i = d12.r *
				 t2.i + d12.i * t2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
			i__2 = b_subscr(k, j);
			q__2.r = d21.r * t1.r - d21.i * t1.i, q__2.i = d21.r *
				 t1.i + d21.i * t1.r;
			q__3.r = d22.r * t2.r - d22.i * t2.i, q__3.i = d22.r *
				 t2.i + d22.i * t2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L50: */
		    }
		}

/*              Multiply by  P(K) * inv(L(K))  if K < N. */

		if (k != *n) {

/*                 Apply the transformation. */

		    i__1 = *n - k;
		    cgeru_(&i__1, nrhs, &c_b1, &a_ref(k + 1, k), &c__1, &
			    b_ref(k, 1), ldb, &b_ref(k + 1, 1), ldb);
		    i__1 = *n - k;
		    cgeru_(&i__1, nrhs, &c_b1, &a_ref(k + 1, k - 1), &c__1, &
			    b_ref(k - 1, 1), ldb, &b_ref(k + 1, 1), ldb);

/*                 Interchange if a permutation was applied at the   
                   K-th step of the factorization. */

		    kp = (i__1 = ipiv[k], abs(i__1));
		    if (kp != k) {
			cswap_(nrhs, &b_ref(k, 1), ldb, &b_ref(kp, 1), ldb);
		    }
		}
		k += -2;
	    }
	    goto L40;
L60:
	    ;
	}
/* ----------------------------------------   

       Compute  B := A' * B  (transpose)   

   ---------------------------------------- */
    } else if (lsame_(trans, "T")) {

/*        Form  B := U'*B   
          where U  = P(m)*inv(U(m))* ... *P(1)*inv(U(1))   
          and   U' = inv(U'(1))*P(1)* ... *inv(U'(m))*P(m) */

	if (lsame_(uplo, "U")) {

/*           Loop backward applying the transformations. */

	    k = *n;
L70:
	    if (k < 1) {
		goto L90;
	    }

/*           1 x 1 pivot block. */

	    if (ipiv[k] > 0) {
		if (k > 1) {

/*                 Interchange if P(K) != I. */

		    kp = ipiv[k];
		    if (kp != k) {
			cswap_(nrhs, &b_ref(k, 1), ldb, &b_ref(kp, 1), ldb);
		    }

/*                 Apply the transformation */

		    i__1 = k - 1;
		    cgemv_("Transpose", &i__1, nrhs, &c_b1, &b[b_offset], ldb,
			     &a_ref(1, k), &c__1, &c_b1, &b_ref(k, 1), ldb);
		}
		if (nounit) {
		    cscal_(nrhs, &a_ref(k, k), &b_ref(k, 1), ldb);
		}
		--k;

/*           2 x 2 pivot block. */

	    } else {
		if (k > 2) {

/*                 Interchange if P(K) != I. */

		    kp = (i__1 = ipiv[k], abs(i__1));
		    if (kp != k - 1) {
			cswap_(nrhs, &b_ref(k - 1, 1), ldb, &b_ref(kp, 1), 
				ldb);
		    }

/*                 Apply the transformations */

		    i__1 = k - 2;
		    cgemv_("Transpose", &i__1, nrhs, &c_b1, &b[b_offset], ldb,
			     &a_ref(1, k), &c__1, &c_b1, &b_ref(k, 1), ldb);
		    i__1 = k - 2;
		    cgemv_("Transpose", &i__1, nrhs, &c_b1, &b[b_offset], ldb,
			     &a_ref(1, k - 1), &c__1, &c_b1, &b_ref(k - 1, 1),
			     ldb);
		}

/*              Multiply by the diagonal block if non-unit. */

		if (nounit) {
		    i__1 = a_subscr(k - 1, k - 1);
		    d11.r = a[i__1].r, d11.i = a[i__1].i;
		    i__1 = a_subscr(k, k);
		    d22.r = a[i__1].r, d22.i = a[i__1].i;
		    i__1 = a_subscr(k - 1, k);
		    d12.r = a[i__1].r, d12.i = a[i__1].i;
		    d21.r = d12.r, d21.i = d12.i;
		    i__1 = *nrhs;
		    for (j = 1; j <= i__1; ++j) {
			i__2 = b_subscr(k - 1, j);
			t1.r = b[i__2].r, t1.i = b[i__2].i;
			i__2 = b_subscr(k, j);
			t2.r = b[i__2].r, t2.i = b[i__2].i;
			i__2 = b_subscr(k - 1, j);
			q__2.r = d11.r * t1.r - d11.i * t1.i, q__2.i = d11.r *
				 t1.i + d11.i * t1.r;
			q__3.r = d12.r * t2.r - d12.i * t2.i, q__3.i = d12.r *
				 t2.i + d12.i * t2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
			i__2 = b_subscr(k, j);
			q__2.r = d21.r * t1.r - d21.i * t1.i, q__2.i = d21.r *
				 t1.i + d21.i * t1.r;
			q__3.r = d22.r * t2.r - d22.i * t2.i, q__3.i = d22.r *
				 t2.i + d22.i * t2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L80: */
		    }
		}
		k += -2;
	    }
	    goto L70;
L90:

/*        Form  B := L'*B   
          where L  = P(1)*inv(L(1))* ... *P(m)*inv(L(m))   
          and   L' = inv(L'(m))*P(m)* ... *inv(L'(1))*P(1) */

	    ;
	} else {

/*           Loop forward applying the L-transformations. */

	    k = 1;
L100:
	    if (k > *n) {
		goto L120;
	    }

/*           1 x 1 pivot block */

	    if (ipiv[k] > 0) {
		if (k < *n) {

/*                 Interchange if P(K) != I. */

		    kp = ipiv[k];
		    if (kp != k) {
			cswap_(nrhs, &b_ref(k, 1), ldb, &b_ref(kp, 1), ldb);
		    }

/*                 Apply the transformation */

		    i__1 = *n - k;
		    cgemv_("Transpose", &i__1, nrhs, &c_b1, &b_ref(k + 1, 1), 
			    ldb, &a_ref(k + 1, k), &c__1, &c_b1, &b_ref(k, 1),
			     ldb);
		}
		if (nounit) {
		    cscal_(nrhs, &a_ref(k, k), &b_ref(k, 1), ldb);
		}
		++k;

/*           2 x 2 pivot block. */

	    } else {
		if (k < *n - 1) {

/*              Interchange if P(K) != I. */

		    kp = (i__1 = ipiv[k], abs(i__1));
		    if (kp != k + 1) {
			cswap_(nrhs, &b_ref(k + 1, 1), ldb, &b_ref(kp, 1), 
				ldb);
		    }

/*                 Apply the transformation */

		    i__1 = *n - k - 1;
		    cgemv_("Transpose", &i__1, nrhs, &c_b1, &b_ref(k + 2, 1), 
			    ldb, &a_ref(k + 2, k + 1), &c__1, &c_b1, &b_ref(k 
			    + 1, 1), ldb);
		    i__1 = *n - k - 1;
		    cgemv_("Transpose", &i__1, nrhs, &c_b1, &b_ref(k + 2, 1), 
			    ldb, &a_ref(k + 2, k), &c__1, &c_b1, &b_ref(k, 1),
			     ldb);
		}

/*              Multiply by the diagonal block if non-unit. */

		if (nounit) {
		    i__1 = a_subscr(k, k);
		    d11.r = a[i__1].r, d11.i = a[i__1].i;
		    i__1 = a_subscr(k + 1, k + 1);
		    d22.r = a[i__1].r, d22.i = a[i__1].i;
		    i__1 = a_subscr(k + 1, k);
		    d21.r = a[i__1].r, d21.i = a[i__1].i;
		    d12.r = d21.r, d12.i = d21.i;
		    i__1 = *nrhs;
		    for (j = 1; j <= i__1; ++j) {
			i__2 = b_subscr(k, j);
			t1.r = b[i__2].r, t1.i = b[i__2].i;
			i__2 = b_subscr(k + 1, j);
			t2.r = b[i__2].r, t2.i = b[i__2].i;
			i__2 = b_subscr(k, j);
			q__2.r = d11.r * t1.r - d11.i * t1.i, q__2.i = d11.r *
				 t1.i + d11.i * t1.r;
			q__3.r = d12.r * t2.r - d12.i * t2.i, q__3.i = d12.r *
				 t2.i + d12.i * t2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
			i__2 = b_subscr(k + 1, j);
			q__2.r = d21.r * t1.r - d21.i * t1.i, q__2.i = d21.r *
				 t1.i + d21.i * t1.r;
			q__3.r = d22.r * t2.r - d22.i * t2.i, q__3.i = d22.r *
				 t2.i + d22.i * t2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			b[i__2].r = q__1.r, b[i__2].i = q__1.i;
/* L110: */
		    }
		}
		k += 2;
	    }
	    goto L100;
L120:
	    ;
	}
    }
    return 0;

/*     End of CLAVSY */

} /* clavsy_ */

#undef b_ref
#undef b_subscr
#undef a_ref
#undef a_subscr


