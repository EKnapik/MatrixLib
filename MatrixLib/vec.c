// Eric Knapik
// Implementation of Matrix Lib for vector fuctions
// written in C




// External Library Includes




// Internal Library Includes
#include "Matrix_Lib.h"



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


Vec project( Vec vector1, Vec vector2 )
{

}


double dotProd( Vec vec1, Vec vec2 )
{

}


