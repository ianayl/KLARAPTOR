#include "blaswrap.h"
/*  -- translated by f2c (version 19990503).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

doublereal slatm3_(integer *m, integer *n, integer *i__, integer *j, integer *
	isub, integer *jsub, integer *kl, integer *ku, integer *idist, 
	integer *iseed, real *d__, integer *igrade, real *dl, real *dr, 
	integer *ipvtng, integer *iwork, real *sparse)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real temp;
    extern doublereal slaran_(integer *), slarnd_(integer *, integer *);


/*  -- LAPACK auxiliary test routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   





    Purpose   
    =======   

       SLATM3 returns the (ISUB,JSUB) entry of a random matrix of   
       dimension (M, N) described by the other paramters. (ISUB,JSUB)   
       is the final position of the (I,J) entry after pivoting   
       according to IPVTNG and IWORK. SLATM3 is called by the   
       SLATMR routine in order to build random test matrices. No error   
       checking on parameters is done, because this routine is called in   
       a tight loop by SLATMR which has already checked the parameters.   

       Use of SLATM3 differs from SLATM2 in the order in which the random   
       number generator is called to fill in random matrix entries.   
       With SLATM2, the generator is called to fill in the pivoted matrix   
       columnwise. With SLATM3, the generator is called to fill in the   
       matrix columnwise, after which it is pivoted. Thus, SLATM3 can   
       be used to construct random matrices which differ only in their   
       order of rows and/or columns. SLATM2 is used to construct band   
       matrices while avoiding calling the random number generator for   
       entries outside the band (and therefore generating random numbers   
       in different orders for different pivot orders).   

       The matrix whose (ISUB,JSUB) entry is returned is constructed as   
       follows (this routine only computes one entry):   

         If ISUB is outside (1..M) or JSUB is outside (1..N), return zero   
            (this is convenient for generating matrices in band format).   

         Generate a matrix A with random entries of distribution IDIST.   

         Set the diagonal to D.   

         Grade the matrix, if desired, from the left (by DL) and/or   
            from the right (by DR or DL) as specified by IGRADE.   

         Permute, if desired, the rows and/or columns as specified by   
            IPVTNG and IWORK.   

         Band the matrix to have lower bandwidth KL and upper   
            bandwidth KU.   

         Set random entries to zero as specified by SPARSE.   

    Arguments   
    =========   

    M      - INTEGER   
             Number of rows of matrix. Not modified.   

    N      - INTEGER   
             Number of columns of matrix. Not modified.   

    I      - INTEGER   
             Row of unpivoted entry to be returned. Not modified.   

    J      - INTEGER   
             Column of unpivoted entry to be returned. Not modified.   

    ISUB   - INTEGER   
             Row of pivoted entry to be returned. Changed on exit.   

    JSUB   - INTEGER   
             Column of pivoted entry to be returned. Changed on exit.   

    KL     - INTEGER   
             Lower bandwidth. Not modified.   

    KU     - INTEGER   
             Upper bandwidth. Not modified.   

    IDIST  - INTEGER   
             On entry, IDIST specifies the type of distribution to be   
             used to generate a random matrix .   
             1 => UNIFORM( 0, 1 )   
             2 => UNIFORM( -1, 1 )   
             3 => NORMAL( 0, 1 )   
             Not modified.   

    ISEED  - INTEGER array of dimension ( 4 )   
             Seed for random number generator.   
             Changed on exit.   

    D      - REAL array of dimension ( MIN( I , J ) )   
             Diagonal entries of matrix. Not modified.   

    IGRADE - INTEGER   
             Specifies grading of matrix as follows:   
             0  => no grading   
             1  => matrix premultiplied by diag( DL )   
             2  => matrix postmultiplied by diag( DR )   
             3  => matrix premultiplied by diag( DL ) and   
                           postmultiplied by diag( DR )   
             4  => matrix premultiplied by diag( DL ) and   
                           postmultiplied by inv( diag( DL ) )   
             5  => matrix premultiplied by diag( DL ) and   
                           postmultiplied by diag( DL )   
             Not modified.   

    DL     - REAL array ( I or J, as appropriate )   
             Left scale factors for grading matrix.  Not modified.   

    DR     - REAL array ( I or J, as appropriate )   
             Right scale factors for grading matrix.  Not modified.   

    IPVTNG - INTEGER   
             On entry specifies pivoting permutations as follows:   
             0 => none.   
             1 => row pivoting.   
             2 => column pivoting.   
             3 => full pivoting, i.e., on both sides.   
             Not modified.   

    IWORK  - INTEGER array ( I or J, as appropriate )   
             This array specifies the permutation used. The   
             row (or column) originally in position K is in   
             position IWORK( K ) after pivoting.   
             This differs from IWORK for SLATM2. Not modified.   

    SPARSE - REAL between 0. and 1.   
             On entry specifies the sparsity of the matrix   
             if sparse matix is to be generated.   
             SPARSE should lie between 0 and 1.   
             A uniform ( 0, 1 ) random number x is generated and   
             compared to SPARSE; if x is larger the matrix entry   
             is unchanged and if x is smaller the entry is set   
             to zero. Thus on the average a fraction SPARSE of the   
             entries will be set to zero.   
             Not modified.   

    =====================================================================   







   -----------------------------------------------------------------------   



       Check for I and J in range   

       Parameter adjustments */
    --iwork;
    --dr;
    --dl;
    --d__;
    --iseed;

    /* Function Body */
    if (*i__ < 1 || *i__ > *m || *j < 1 || *j > *n) {
	*isub = *i__;
	*jsub = *j;
	ret_val = 0.f;
	return ret_val;
    }

/*     Compute subscripts depending on IPVTNG */

    if (*ipvtng == 0) {
	*isub = *i__;
	*jsub = *j;
    } else if (*ipvtng == 1) {
	*isub = iwork[*i__];
	*jsub = *j;
    } else if (*ipvtng == 2) {
	*isub = *i__;
	*jsub = iwork[*j];
    } else if (*ipvtng == 3) {
	*isub = iwork[*i__];
	*jsub = iwork[*j];
    }

/*     Check for banding */

    if (*jsub > *isub + *ku || *jsub < *isub - *kl) {
	ret_val = 0.f;
	return ret_val;
    }

/*     Check for sparsity */

    if (*sparse > 0.f) {
	if (slaran_(&iseed[1]) < *sparse) {
	    ret_val = 0.f;
	    return ret_val;
	}
    }

/*     Compute entry and grade it according to IGRADE */

    if (*i__ == *j) {
	temp = d__[*i__];
    } else {
	temp = slarnd_(idist, &iseed[1]);
    }
    if (*igrade == 1) {
	temp *= dl[*i__];
    } else if (*igrade == 2) {
	temp *= dr[*j];
    } else if (*igrade == 3) {
	temp = temp * dl[*i__] * dr[*j];
    } else if (*igrade == 4 && *i__ != *j) {
	temp = temp * dl[*i__] / dl[*j];
    } else if (*igrade == 5) {
	temp = temp * dl[*i__] * dl[*j];
    }
    ret_val = temp;
    return ret_val;

/*     End of SLATM3 */

} /* slatm3_ */

