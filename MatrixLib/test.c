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
    double array16[] = {1, 2, 2, 1, 1, 2, 4, 2, 2, 7, 5, 2, -1, 4, -6, 3};


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

    /////// DETERMINATE FUNCTION //////////
    printf( "DETERMINATE TEST\n" );
    double determinate;
    matrix = mkMat( 16, array16 );
    print( matrix );
    determinate = det( matrix );
    printf( "The determinate is: %.2f \n", determinate );

    printf("\n");
    ////////// END DETERMINATE TEST/////////

    ////////// TRANSPOSE TEST ////////
    printf( "Transpose test\n");
    Mat *matrixTrans;
    matrixTrans = transpose( matrix );
    print( matrix );
    printf( "\n" );
    print( matrixTrans );
    printf( "\n" );
    
    destroyMat( matrixTrans );
    destroyMat( matrix );

    /////// END TRANSPOSE TEST //////////
    
    ///// MULTIPLICATION TEST ///////////
    printf( "MULTIPLICATION TEST \n" );
    Mat *matrix2;
    Mat *answerMat;
    matrix = mkMat( 9, array9 );
    matrix2 = mkMat3I();
    answerMat = multi( matrix, matrix2 );

    print( answerMat );
    printf( "\n" );
    
    destroyMat( answerMat );
    destroyMat( matrix2 );
    destroyMat( matrix );

    ///////// END MULTIPLICATION TEST ///////////

    
    return 0;

}
