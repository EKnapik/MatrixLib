// Eric Knapik
// Implementation of Matrix Lib for vector fuctions
// written in C




// External Library Includes
#include <math.h>



// Internal Library Includes
#include "Matrix_Lib.h"

// Personal Defines
#define PI 3.14159265


Vec mkVec( double data[] )
{
	int numElements = sizeof( data ) / sizeof( double );
	Vec vector;

	if( numElements >= 2 )
	{
		vector.type = VEC2;
		vector.x = data[0];
		vector.y = data[1];
	}
	if( numElements >= 3 )
	{
		vector.type = VEC3;
		vector.z = data[2];
	}
	if( numElements == 4 )
	{
		vector.type = VEC4;
		vector.w = data[3];
	}

	if( numElements < 2 || numElements > 4 )
	{
		vector = NULL;
	}

	return vector;
}


// project v onto u where v is vector2 and u is vector1
Vec project( Vec vector1, Vec vector2 )
{

}


double dotProd( Vec vec1, Vec vec2 )
{
	double answer = 0;
	if( vec1.type == vec2.type == VEC2 )
	{
		answer = vec1.x * vec2.x;
		answer = answer + ( vec1.y * vec2.y );
	}
	else if( vec1.type == vec2.type == VEC3 )
	{
		answer = vec1.x * vec2.x;
		answer = answer + ( vec1.y * vec2.y );
		answer = answer + ( vec1.z * vec2.z );
	}
	else if( vec1.type == vec2.type == VEC4 )
	{
		answer = vec1.x * vec2.x;
		answer = answer + ( vec1.y * vec2.y );
		answer = answer + ( vec1.z * vec2.z );
		answer = answer + ( vec1.w * vec2.w );
	}
	else
	{
		perror( "Could not find the dot product between the vectors\n" );
		answer = NULL;
	}

	return answer;
}


double length( Vec vector )
{
	double length = 0;

	length = dotProd( vector, vector );
	length = sqrt( length );

	return length;
}


// uv = ||u|| ||v|| cos(theta);
// 
double angle( Vec vec1, Vec vec2 )
{
	double answer, val;

	val = 180.0 / PI;

	answer = dotProd( vec1, vec2 ) / length( vec1 ) / length( vec2 );
	answer = acos( answer ) * val;

	return answer;
}


Mat_Vec normalize( Mat_Vec mat_vec )
{

}


Mat_Vec multi( Mat matrix, Mat_Vec mat_vec )
{

}


Mat_Vec addMV( Mat_Vec mat_vec1, Mat_Vec mat_vec2 )
{

}


Mat_Vec scale( Mat_Vec mat_vec, double scaleAmount )
{
	if( mat_vec.type == VEC2 )
	{

	}
	else if( mat_vec.type == VEC3 )
	{

	}
	else if( mat_vec.type == VEC4 )
	{

	}
	else if( mat_vec.type == MAT2 )
	{

	}
	else if( mat_vec.type == MAT3 )
	{

	}
	else if( mat_vec.type == MAT4 )
	{

	}
	else
	{
		perror( "Unable to scale the matrix or vector passed in\n" );
	}

	return mat_vec;
}