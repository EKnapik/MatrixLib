// Author: Eric M. Knapik
// This is a test of the matrixLib
// This should test all functions to ensure
// that the code is working as intened


#include "Matrix_Lib.h"

int main( int argc, char *argv[] )
{

    Mat *matrix;
    double array2[] =  {3, 6};
    double array3[] =  {1, 4, 5};
    double array4[] =  {4, 6, 1, 8};
    double array9[] =  {3, 2, 4, 7, 1, 2, 6, 7, 78};
    double array16[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};


    // TEST ALL THE IDENTITIES ////////////////////////////

    printf("IDENTITY TEST\n");
    matrix = mkMat2I();
    print( matrix );
    printf("\n");
    destroyMat( matrix );

    matrix = mkMat3I();
    print( matrix );
    printf("\n");
    destroyMat( matrix );

    matrix = mkMat4I();
    print( matrix );
    printf("\n");
    destroyMat( matrix );

    // IDENTITY TEST COMPLETE /////////////////////////////

    //////////// TEST THE CREATION USING mkMat of variable sizes

    printf("VARIABLE MATRIX CREATION TEST\n");
    matrix = mkMat( 4, array4 );
    print( matrix );
    printf( "\n" );
    destroyMat( matrix );

    //////////// TEST THE CREATION OF VARIABLE SIZES COMPLETE
    printf("SCALE TEST\n");
    matrix = mkMat( 9, array9 );
    print( matrix );
    printf( "\n scaled:\n" );
    matrix = scale( matrix, 2 );
    print( matrix );
    printf( "\n" );
    destroyMat( matrix );

    return 0;

}
