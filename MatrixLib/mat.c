// Eric Knapik
// Implementation of Matrix Lib for Matrix fuctions
// written in C





// Internal Library Includes
#include "Matrix_Lib.h"


// Many functions will use this one, to make thier own matrix to return it.
// This function could be shrunk down and only use the if conditionals
// to set the type of matrix but I want to see the differences and keep
// it separate
Mat* mkMat( double data[] )
{
	int numElements = sizeof( data ) / sizeof( double );
	Mat *matrix = malloc( sizeof(struct Matrix_Vector) );

	if( numElements == 4 )
	{
		matrix->type = MAT2;
		matrix->data = malloc( sizeof( double ) * 4 );
		for( int i = 0; i < 4; i++ )
		{
			matrix->data[i] = data[i];
		}
	}
	else if( numElements == 9 )
	{
		matrix->type = MAT3;
		matrix->data = malloc( sizeof( double ) * 9 );
		for( int i = 0; i < 9; i++ )
		{
			matrix->data[i] = data[i];
		}
	}
	else if( numElements == 16 )
	{
		matrix->type = MAT4;
		matrix->data = malloc( sizeof( double ) * 16 );
		for( int i = 0; i < 16; i++ )
		{
			matrix->data[i] = data[i];
		}
	}
	else
	{
		matrix = NULL;
	}

	return matrix;
}


void destroyMat( Mat *matrix )
{
	if( matrix != NULL )
	{
		free( matrix->data );
	}
	free( matrix );
	return;
}


double det( Mat *matrix )
{
	double determinate;
	double array[9];

	if( matrix->type == MAT2 )
	{
		double val1, val2;

		val1 = matrix->data[0] * matrix->data[3];
		val2 = matrix->data[1] * matrix->data[2];

		determinate = val1 - val2;
	}
	else if( matrix->type == MAT3 )
	{
		double val1, val2, val3;

		val1 = matrix->data[0] * matrix->data[4] * matrix->data[8];
		val2 = matrix->data[1] * matrix->data[5] * matrix->data[6];
		val3 = matrix->data[2] * matrix->data[3] * matrix->data[7];

		determinate = val1 + val2 + val3;

		val1 = matrix->data[2] * matrix->data[4] * matrix->data[6];
		val2 = matrix->data[0] * matrix->data[5] * matrix->data[7];
		val3 = matrix->data[1] * matrix->data[3] * matrix->data[8];

		determinate = determinate - val1 - val2 - val3;
	}
	else if( matrix->type == MAT4 )
	{
		Mat *matrix1, *matrix2, *matrix3, *matrix4;

		// use the array to make each one of the matricies
		array[0] = matrix->data[5];
		array[1] = matrix->data[6];
		array[2] = matrix->data[7];
		array[3] = matrix->data[9];
		array[4] = matrix->data[10];
		array[5] = matrix->data[11];
		array[6] = matrix->data[13];
		array[7] = matrix->data[14];
		array[8] = matrix->data[15];

		matrix1 = mkMat( array );

		// matrix 2
		array[0] = matrix->data[4];
		array[1] = matrix->data[6];
		array[2] = matrix->data[7];
		array[3] = matrix->data[8];
		array[4] = matrix->data[10];
		array[5] = matrix->data[11];
		array[6] = matrix->data[12];
		array[7] = matrix->data[14];
		array[8] = matrix->data[15];

		matrix2 = mkMat( array );

		// matrix 3
		array[0] = matrix->data[4],
		array[1] = matrix->data[5],
		array[2] = matrix->data[7],
		array[3] = matrix->data[8],
		array[4] = matrix->data[9],
		array[5] = matrix->data[11],
		array[6] = matrix->data[12],
		array[7] = matrix->data[13],
		array[8] = matrix->data[15];

		matrix3 = mkMat( array );


		// matrix 4
		array[0] = matrix->data[4];
		array[1] = matrix->data[5];
		array[2] = matrix->data[6];
		array[3] = matrix->data[8];
		array[4] = matrix->data[9];
		array[5] = matrix->data[10];
	    array[6] = matrix->data[12];
	    array[7] = matrix->data[13];
	    array[8] = matrix->data[14];

		matrix4 = mkMat( array );

		determinate = matrix->data[0] * det(matrix1);
		determinate = determinate - ( matrix->data[1] * det(matrix2) );
		determinate = determinate + ( matrix->data[2] * det(matrix3) );
		determinate = determinate - ( matrix->data[3] * det(matrix4) );

		destroyMat( matrix1 );
		destroyMat( matrix2 );
		destroyMat( matrix3 );
		destroyMat( matrix4 );
	}
	else
	{
		determinate = -99999999;
		perror( "Could not find the determinate of the matrix\n" );
	}

	return determinate;
}


Mat* transpose( Mat *matrix )
{
	Mat *matrixTrans;
	double array2[4];
	double array3[9];
	double array4[16];

	if( matrix->type == MAT2 )
	{
		array2[0] = matrix->data[0];
		array2[1] = matrix->data[2];
		array2[2] = matrix->data[1];
		array2[3] = matrix->data[3];

		matrixTrans = mkMat( array2 );
	}
	else if( matrix->type == MAT3 )
	{
		array3[0] = matrix->data[0];
		array3[1] = matrix->data[3];
		array3[2] = matrix->data[6];
		array3[3] = matrix->data[1];
		array3[4] = matrix->data[4];
		array3[5] = matrix->data[7];
		array3[6] = matrix->data[2];
		array3[7] = matrix->data[5];
		array3[8] = matrix->data[8];

		matrixTrans = mkMat( array3 );
	}
	else if( matrix->type == MAT4 )
	{
		array4[0] = matrix->data[0];
		array4[1] = matrix->data[4];
		array4[2] = matrix->data[8];
		array4[3] = matrix->data[12];
		array4[4] = matrix->data[1];
		array4[5] = matrix->data[5];
		array4[6] = matrix->data[9];
		array4[7] = matrix->data[13];
		array4[8] = matrix->data[2];
		array4[9] = matrix->data[6];
		array4[10] = matrix->data[10];
		array4[11] = matrix->data[14];
		array4[12] = matrix->data[3];
		array4[13] = matrix->data[7];
		array4[14] = matrix->data[11];
		array4[15] = matrix->data[15];

		matrixTrans = mkMat( array4 );
	}
	else
	{
		perror( "Could not creat the transpose of the matrix passed in\n" );
		matrixTrans = NULL;
	}

	return matrixTrans;
}



void print( Mat_Vec *mat_vec )
{
	if( mat_vec->type == VEC2 )
	{
		printf( "%f\n", mat_vec->x );
		printf( "%f\n", mat_vec->y );

	}
	else if( mat_vec->type == VEC3 )
	{
		printf( "%f\n", mat_vec->x );
		printf( "%f\n", mat_vec->y );
		printf( "%f\n", mat_vec->z );

	}
	else if( mat_vec->type == VEC4 )
	{
		printf( "%f\n", mat_vec->x );
		printf( "%f\n", mat_vec->y );
		printf( "%f\n", mat_vec->z );
		printf( "%f\n", mat_vec->w );

	}
	else if( mat_vec->type == MAT2 )
	{
		for( int row = 0; row < 2; row++ )
		{
			for( int col = 0; col < 2; col++ )
			{
				printf( "%f ", mat_vec->data[col + (row * 2)] );
			}
			printf( "\n" );
		}

	}
	else if( mat_vec->type == MAT3 )
	{
		for( int row = 0; row < 3; row++ )
		{
			for( int col = 0; col < 3; col++ )
			{
				printf( "%f ", mat_vec->data[col + (row * 3)] );
			}
			printf( "\n" );
		}
	}
	else if( mat_vec->type == MAT4 )
	{
		for( int row = 0; row < 4; row++ )
		{
			for( int col = 0; col < 4; col++ )
			{
				printf( "%f ", mat_vec->data[col + (row * 4)] );
			}
			printf( "\n" );
		}
	}
	else
	{
		perror( "Unable to print the matrix to standard out\n" );
	}
	
	return;
}



Mat2* mkMat2I( void )
{
	Mat *matrix;
	matrix->data = malloc( sizeof( double ) * 4 );
	matrix->data[0] = 1;
	matrix->data[1] = 0;

	matrix->data[2] = 0;
	matrix->data[3] = 1;

	return matrix;
}

Mat3* mkMat3I( void )
{
	Mat *matrix;
	matrix->data = malloc( sizeof( double ) * 9 );
	matrix->data[0] = 1;
	matrix->data[1] = 0;
	matrix->data[2] = 0;

	matrix->data[3] = 0;
	matrix->data[4] = 1;
	matrix->data[5] = 0;

	matrix->data[6] = 0;
	matrix->data[7] = 0;
	matrix->data[8] = 1;

	return matrix;
}

Mat4* mkMat4I( void )
{
	Mat *matrix;
	matrix->data = malloc( sizeof( double ) * 16 );
	matrix->data[0] = 1;
	matrix->data[1] = 0;
	matrix->data[2] = 0;
	matrix->data[3] = 0;

	matrix->data[4] = 0;
	matrix->data[5] = 1;
	matrix->data[6] = 0;
	matrix->data[7] = 0;

	matrix->data[8] = 0;
	matrix->data[9] = 0;
	matrix->data[10] = 1;
	matrix->data[11] = 0;

	matrix->data[12] = 0;
	matrix->data[13] = 0;
	matrix->data[14] = 0;
	matrix->data[15] = 1;

	return matrix;
}