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
	matrix.data = NULL;
	return;
}


void print( Mat_Vec mat_vec )
{
	
	return;
}