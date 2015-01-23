// Eric Knapik
// Implementation of Matrix Lib for Matrix fuctions
// written in C




// External Library Includes
#include <stdio.h>



// Internal Library Includes
#include "Matrix_Lib.h"


// Many functions will use this one, to make thier own matrix to return it.
Mat mkMat( double data[] )
{
	int numElements = sizeof( data ) / sizeof( double );
	Mat matrix;

	if( numElements == 4 )
	{
		matrix.type = MAT2;
		matrix->data = malloc( sizeof( double ) * 4 );
		for( int i = 0; i < 4; i++ )
		{
			matrix->data[i] = data[i];
		}
	}
	else if( numElements == 9 )
	{
		matrix.type = MAT3;
		matrix->data = malloc( sizeof( double ) * 9 );
		for( int i = 0; i < 9; i++ )
		{
			matrix->data[i] = data[i];
		}
	}
	else if( numElements == 16 )
	{
		matrix.type = MAT4;
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


void destroyMat( Mat matrix )
{
	if( matrix != NULL )
	{
		free( matrix.data );
	}
	matrix = NULL;
	return;
}


double det( Mat matrix )
{
	double determinate;
	if( matrix.type == MAT2 )
	{
		double val1, val2;

		val1 = matrix->data[0] * matrix->data[3];
		val2 = matrix->data[1] * matrix->data[2];

		determinate = val1 - val2;
	}
	else if( matrix.type == MAT3 )
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
	else if( matrix.type == Mat4 )
	{
		Mat matrix1, matrix2, matrix3, matrix4;

		matrix1 = mkMat( [ matrix->data[5], matrix->data[6], matrix->data[7],
							matrix->data[9], matrix->data[10], matrix->data[11],
							matrix->data[13], matrix->data[14], matrix->data[15] ] );

		matrix2 = mkMat( [ matrix->data[4], matrix->data[6], matrix->data[7],
							matrix->data[8], matrix->data[10], matrix->data[11],
							matrix->data[12], matrix->data[14], matrix->data[15] ] );

		matrix3 = mkMat( [ matrix->data[4], matrix->data[5], matrix->data[7],
							matrix->data[8], matrix->data[9], matrix->data[11],
							matrix->data[12], matrix->data[13], matrix->data[15] ] );

		matrix4 = mkMat( [ matrix->data[4], matrix->data[5], matrix->data[6],
							matrix->data[8], matrix->data[9], matrix->data[10],
							matrix->data[12], matrix->data[13], matrix->data[14] ] );

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
		determinate = NULL;
		perror( "Could not find the determinate of the matrix\n" );
	}

	return determinate;
}

// This will rely on the determinate function
Mat inverse( Mat matrix )
{

}

// This relies on the matrix multiplication function
// I have a fear that there is a massive memory leak here because I loose a matrix
// Every time I iteratate through the for loop.
Mat pow( Mat matrix, int power )
{
	Mat returnMat = matrix;
	for( int i = 1; i < power; i++ )
	{
		returnMat = multi( returnMat, matrix );
	}

	retun returnMat;
}


Mat4 rotate( Mat4 matrix, char axis, double degrees )
{

}


Mat transpose( Mat matrix )
{
	Mat matrixTrans;

	if( matrix.type == MAT2 )
	{
		matrixTrans = mkMat( [ matrix->data[0], matrix->data[2], 
								matrix->data[1], matrix->data[3] ] );
	}
	else if( matrix.type == MAT3 )
	{
		matrixTrans = mkMat( [ matrix->data[0], matrix->data[3], matrix->data[6],
								matrix->data[1], matrix->data[4], matrix->data[7],
								matrix->data[2], matrix->data[5], matrix->data[8] ] );
	}
	else if( matrix.type == MAT4 )
	{
		matrixTrans = mkMat( [ matrix->data[0], matrix->data[4], matrix->data[8], matrix->data[12],
								matrix->data[1], matrix->data[5], matrix->data[9], matrix->data[13],
								matrix->data[2], matrix->data[6], matrix->data[10], matrix->data[14],
								matrix->data[3], matrix->data[7], matrix->data[11], matrix->data[15] ] );
	}
	else
	{
		perror( "Could not creat the transpose of the matrix passed in\n" );
		matrixTrans = NULL;
	}

	return matrixTrans;
}



void print( Mat_Vec mat_vec )
{
	if( mat_vec.type == Vec2 )
	{
		printf( "%f\n", mat_vec.x );
		printf( "%f\n", mat_vec.y );

	}
	else if( mat_vec.type == Vec3 )
	{
		printf( "%f\n", mat_vec.x );
		printf( "%f\n", mat_vec.y );
		printf( "%f\n", mat_vec.z );

	}
	else if( mat_vec.type == Vec4 )
	{
		printf( "%f\n", mat_vec.x );
		printf( "%f\n", mat_vec.y );
		printf( "%f\n", mat_vec.z );
		printf( "%f\n", mat_vec.w );

	}
	else if( mat_vec.type == Mat2 )
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
	else if( mat_vec.type == Mat3 )
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
	else if( mat_vec.type == Mat4 )
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



Mat2 mkMat2I( void )
{
	Mat matrix;
	matrix->data = malloc( sizeof( double ) * 4 );
	matrix->data[0] = 1;
	matrix->data[1] = 0;

	matrix->data[2] = 0;
	matrix->data[3] = 1;

	return matrix;
}

Mat3 mkMat3I( void )
{
	Mat matrix;
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

Mat4 mkMat4I( void )
{
	Mat matrix;
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