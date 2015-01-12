// Eric Knapik
// Implementation of Matrix Lib for Matrix fuctions
// written in C




// External Library Includes
#include <stdio.h>



// Internal Library Includes
#include "Matrix_Lib.h"



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
	free( matrix.data );
	matrix = NULL;
	return;
}


double det( Mat matrix )
{

}


Mat inverse( Mat matrix )
{

}


Mat pow( Mat matrix, int power )
{

}


Mat4 rotate( Mat4 matrix, char axis, double degrees )
{

}


Mat transpose( Mat matrix )
{

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
		perror( "Unable to print the matrix to standard out" );
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