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
	double scaleAmount = dotProd( vector1, vector2 ) / dotProd( vector1, vector1 );
	Vec returnVec;

	if( vector1.type == VEC2 )
	{
		returnVec = mkVec([ vector1.x, vector1.y ]);
	}
	else if( vector1.type == VEC3 )
	{
		returnVec = mkVec([ vector1.x, vector1.y, vector1.z ]);
	}
	else if( vector1.type == VEC4 )
	{
		returnVec = mkVec([ vector1.x, vector1.y, vector1.z, vector1.w ]);
	}
	returnVec = scale( returnVec, scaleAmount );

	return returnVec;
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


Vec normalize( Vec vec )
{
	Vec returnVec;
	double vecLen = length( vec );

	if( vec.type == VEC2 )
	{
		returnVec = mkVec([ (vec.x / vecLen), (vec.y / vecLen) ]);
	}
	else if( vec.type == VEC3 )
	{
		returnVec = mkVec([ (vec.x / vecLen), (vec.y / vecLen), (vec.z / vecLen) ]);
	}
	else if( vec.type == VEC4 )
	{
		returnVec = mkVec([ (vec.x / vecLen), (vec.y / vecLen), (vec.z / vecLen), (vec.w / vecLen) ]);
	}
	else
	{
		perror( "Could not normalize the vector\n" );
		returnVec = NULL;
	}

	return returnVec;
}


Mat_Vec multi( Mat matrix, Mat_Vec mat_vec )
{
	
	if( matrix.type != MAT2 || matrix.type != MAT3 || matrix.type != MAT4 )
	{
		perror( "The first param was not a matrix\n" );
		return NULL;
	}

	Mat returnMat_Vec;
	// 2x2 * 2x1
	if( matrix.type == MAT2 && mat_vec.type == VEC2 )
	{
		returnMat_Vec = mkVec([ ((matrix->data[0] * mat_vec.x) + (matrix->data[1] * mat_vec.y)), 
			((matrix->data[2] * mat_vec.x) + (matrix->data[3] * mat_vec.y)) ]);
	}
	// 2x2 * 2x2
	else if( matrix.type == MAT2 && mat_vec.type == MAT2 )
	{
		returnMat_Vec = mkMat([ ((matrix->data[0] * mat_vec->data[0] ) + (matrix->data[1] * mat_vec->data[2])), 
			((matrix->data[0] * mat_vec->data[1]) + (matrix->data[1] * mat_vec->data[3])),
			((matrix->data[1] * mat_vec->data[0]) + (matrix->data[3] * mat_vec->data[2])),
			((matrix->data[1] * mat_vec->data[1]) + (matrix->data[3] * mat_vec->data[3])) ]);
	}
	// 3x3 * 3x1
	else if( matrix.type == MAT3 && mat_vec.type == VEC3 )
	{
		returnMat_Vec = mkVec([ ((matrix->data[0] * mat_vec.x) + (matrix->data[1] * mat_vec.y) + (matrix->data[2] * mat_vec.z)),
			((matrix->data[3] * mat_vec.x) + (matrix->data[4] * mat_vec.y) + (matrix->data[5] * mat_vec.z)),
			((matrix->data[6] * mat_vec.x) + (matrix->data[7] * mat_vec.y) + (matrix->data[8] * mat_vec.z)) ]);
	}
	// 3x3 * 3x3
	else if( matrix.type == MAT3 && mat_vec.type == MAT3 )
	{
		returnMat_Vec = mkMat([ ((matrix->data[0] * mat_vec->data[0] ) + (matrix->data[1] * mat_vec->data[3]) + (matrix->data[2] * mat_vec->data[6])), 
			((matrix->data[0] * mat_vec->data[1] ) + (matrix->data[1] * mat_vec->data[4]) + (matrix->data[2] * mat_vec->data[7])),
			((matrix->data[0] * mat_vec->data[2] ) + (matrix->data[1] * mat_vec->data[5]) + (matrix->data[2] * mat_vec->data[8])),
			((matrix->data[3] * mat_vec->data[0] ) + (matrix->data[3] * mat_vec->data[3]) + (matrix->data[4] * mat_vec->data[6])),
			((matrix->data[3] * mat_vec->data[1] ) + (matrix->data[3] * mat_vec->data[4]) + (matrix->data[4] * mat_vec->data[7])),
			((matrix->data[3] * mat_vec->data[2] ) + (matrix->data[3] * mat_vec->data[5]) + (matrix->data[4] * mat_vec->data[8])),
			((matrix->data[6] * mat_vec->data[0] ) + (matrix->data[7] * mat_vec->data[3]) + (matrix->data[8] * mat_vec->data[6])),
			((matrix->data[6] * mat_vec->data[1] ) + (matrix->data[7] * mat_vec->data[4]) + (matrix->data[8] * mat_vec->data[7])),
			((matrix->data[6] * mat_vec->data[2] ) + (matrix->data[7] * mat_vec->data[5]) + (matrix->data[8] * mat_vec->data[8])) ]);
	}
	// 4x4 * 4x1
	else if( matrix.type == MAT4 && mat_vec.type == VEC4 )
	{
		returnMat_Vec = mkVec([ ((matrix->data[0] * mat_vec.x) + (matrix->data[1] * mat_vec.y) + (matrix->data[2] * mat_vec.z) + (matrix->data[3] * mat_vec.z)),
			((matrix->data[4] * mat_vec.x) + (matrix->data[5] * mat_vec.y) + (matrix->data[6] * mat_vec.z) + (matrix->data[7] * mat_vec.z)),
			((matrix->data[8] * mat_vec.x) + (matrix->data[9] * mat_vec.y) + (matrix->data[10] * mat_vec.z) + (matrix->data[11] * mat_vec.z)),
			((matrix->data[12] * mat_vec.x) + (matrix->data[13] * mat_vec.y) + (matrix->data[14] * mat_vec.z) + (matrix->data[15] * mat_vec.z)) ]);
	}
	// 4x4 * 4x4
	else if( matrix.type == MAT4 && mat_vec.type == MAT4 )
	{
		returnMat_Vec = mkMat([ ((matrix->data[0] * mat_vec->data[0] ) + (matrix->data[1] * mat_vec->data[4]) + (matrix->data[2] * mat_vec->data[8]) + (matrix->data[3] * mat_vec->data[12])), 
			((matrix->data[0] * mat_vec->data[1] ) + (matrix->data[1] * mat_vec->data[5]) + (matrix->data[2] * mat_vec->data[9]) + (matrix->data[3] * mat_vec->data[13])),
			((matrix->data[0] * mat_vec->data[2] ) + (matrix->data[1] * mat_vec->data[6]) + (matrix->data[2] * mat_vec->data[10]) + (matrix->data[3] * mat_vec->data[14])),
			((matrix->data[0] * mat_vec->data[3] ) + (matrix->data[1] * mat_vec->data[7]) + (matrix->data[2] * mat_vec->data[11]) + (matrix->data[3] * mat_vec->data[15])),
			((matrix->data[4] * mat_vec->data[0] ) + (matrix->data[5] * mat_vec->data[4]) + (matrix->data[6] * mat_vec->data[8]) + (matrix->data[7] * mat_vec->data[12])),
			((matrix->data[4] * mat_vec->data[1] ) + (matrix->data[5] * mat_vec->data[5]) + (matrix->data[6] * mat_vec->data[9]) + (matrix->data[7] * mat_vec->data[13])),
			((matrix->data[4] * mat_vec->data[2] ) + (matrix->data[5] * mat_vec->data[6]) + (matrix->data[6] * mat_vec->data[10]) + (matrix->data[7] * mat_vec->data[14])),
			((matrix->data[4] * mat_vec->data[3] ) + (matrix->data[5] * mat_vec->data[7]) + (matrix->data[6] * mat_vec->data[11]) + (matrix->data[7] * mat_vec->data[15])),
			((matrix->data[8] * mat_vec->data[0] ) + (matrix->data[9] * mat_vec->data[4]) + (matrix->data[10] * mat_vec->data[8]) + (matrix->data[11] * mat_vec->data[12])),
			((matrix->data[8] * mat_vec->data[1] ) + (matrix->data[9] * mat_vec->data[5]) + (matrix->data[10] * mat_vec->data[9]) + (matrix->data[11] * mat_vec->data[13])),
			((matrix->data[8] * mat_vec->data[2] ) + (matrix->data[9] * mat_vec->data[6]) + (matrix->data[10] * mat_vec->data[10]) + (matrix->data[11] * mat_vec->data[14])),
			((matrix->data[8] * mat_vec->data[3] ) + (matrix->data[9] * mat_vec->data[7]) + (matrix->data[10] * mat_vec->data[11]) + (matrix->data[11] * mat_vec->data[15])),
			((matrix->data[12] * mat_vec->data[0] ) + (matrix->data[13] * mat_vec->data[4]) + (matrix->data[14] * mat_vec->data[8]) + (matrix->data[15] * mat_vec->data[12])),
			((matrix->data[12] * mat_vec->data[1] ) + (matrix->data[13] * mat_vec->data[5]) + (matrix->data[14] * mat_vec->data[9]) + (matrix->data[15] * mat_vec->data[13])),
			((matrix->data[12] * mat_vec->data[2] ) + (matrix->data[13] * mat_vec->data[6]) + (matrix->data[14] * mat_vec->data[10]) + (matrix->data[15] * mat_vec->data[14])),
			((matrix->data[12] * mat_vec->data[3] ) + (matrix->data[13] * mat_vec->data[7]) + (matrix->data[14] * mat_vec->data[11]) + (matrix->data[15] * mat_vec->data[15])) ]);
	}
	else
	{
		perror( "Unable to multiply the given params returning NULL\n" );
		returnMat_Vec = NULL;
	}
	
	return returnMat_Vec;
}


Mat_Vec addMV( Mat_Vec mat_vec1, Mat_Vec mat_vec2 )
{

}


Mat_Vec scale( Mat_Vec mat_vec, double scaleAmount )
{
	if( mat_vec.type == VEC2 )
	{
		mat_vec.x = mat_vec.x * scaleAmount;
		mat_vec.y = mat_vec.y * scaleAmount;
	}
	else if( mat_vec.type == VEC3 )
	{
		mat_vec.x = mat_vec.x * scaleAmount;
		mat_vec.y = mat_vec.y * scaleAmount;
		mat_vec.z = mat_vec.z * scaleAmount;
	}
	else if( mat_vec.type == VEC4 )
	{
		mat_vec.x = mat_vec.x * scaleAmount;
		mat_vec.y = mat_vec.y * scaleAmount;
		mat_vec.z = mat_vec.z * scaleAmount;
		mat_vec.w = mat_vec.w * scaleAmount;
	}
	else if( mat_vec.type == MAT2 )
	{
		mat_vec->data[0] = mat_vec->data[0] * scaleAmount;
		mat_vec->data[1] = mat_vec->data[1] * scaleAmount;
		mat_vec->data[2] = mat_vec->data[2] * scaleAmount;
		mat_vec->data[3] = mat_vec->data[3] * scaleAmount;
	}
	else if( mat_vec.type == MAT3 )
	{
		mat_vec->data[0] = mat_vec->data[0] * scaleAmount;
		mat_vec->data[1] = mat_vec->data[1] * scaleAmount;
		mat_vec->data[2] = mat_vec->data[2] * scaleAmount;
		mat_vec->data[3] = mat_vec->data[3] * scaleAmount;
		mat_vec->data[4] = mat_vec->data[4] * scaleAmount;
		mat_vec->data[5] = mat_vec->data[5] * scaleAmount;
		mat_vec->data[6] = mat_vec->data[6] * scaleAmount;
		mat_vec->data[7] = mat_vec->data[7] * scaleAmount;
		mat_vec->data[8] = mat_vec->data[8] * scaleAmount;
	}
	else if( mat_vec.type == MAT4 )
	{
		mat_vec->data[0] = mat_vec->data[0] * scaleAmount;
		mat_vec->data[1] = mat_vec->data[1] * scaleAmount;
		mat_vec->data[2] = mat_vec->data[2] * scaleAmount;
		mat_vec->data[3] = mat_vec->data[3] * scaleAmount;
		mat_vec->data[4] = mat_vec->data[4] * scaleAmount;
		mat_vec->data[5] = mat_vec->data[5] * scaleAmount;
		mat_vec->data[6] = mat_vec->data[6] * scaleAmount;
		mat_vec->data[7] = mat_vec->data[7] * scaleAmount;
		mat_vec->data[8] = mat_vec->data[8] * scaleAmount;
		mat_vec->data[9] = mat_vec->data[9] * scaleAmount;
		mat_vec->data[10] = mat_vec->data[10] * scaleAmount;
		mat_vec->data[11] = mat_vec->data[11] * scaleAmount;
		mat_vec->data[12] = mat_vec->data[12] * scaleAmount;
		mat_vec->data[13] = mat_vec->data[13] * scaleAmount;
		mat_vec->data[14] = mat_vec->data[14] * scaleAmount;
		mat_vec->data[15] = mat_vec->data[15] * scaleAmount;
	}
	else
	{
		perror( "Unable to scale the matrix or vector passed in\n" );
	}

	return mat_vec;
}