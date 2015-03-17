// Eric Knapik
// Implementation of Matrix Lib for vector fuctions
// written in C




// Internal Library Includes
#include "Matrix_Lib.h"

// Personal Defines
#define PI 3.14159265


Vec* mkVec( int numElements, double data[] )
{
	Vec *vector = malloc( sizeof( struct Matrix_Vector ) );

	if( numElements >= 2 )
	{
		vector->type = VEC2;
		vector->x = data[0];
		vector->y = data[1];
	}
	if( numElements >= 3 )
	{
		vector->type = VEC3;
		vector->z = data[2];
	}
	if( numElements == 4 )
	{
		vector->type = VEC4;
		vector->w = data[3];
	}

	if( numElements < 2 || numElements > 4 )
	{
		vector = NULL;
	}

	return vector;
}

void destroyVec( Vec *vector )
{
	free( vector );
}

// project Vector 1 onto vector 2
Vec* project( Vec *vector1, Vec *vector2 )
{
	double scaleAmount = dotProd( vector1, vector2 ) / dotProd( vector2, vector2 );
	Vec *returnVec;
	double array2[2];
	double array3[3];
	double array4[4];

	if( vector2->type == VEC2 )
	{
		array2[0] = vector2->x;
		array2[1] = vector2->y;

		returnVec = mkVec( 2, array2 );
	}
	else if( vector2->type == VEC3 )
	{
		array3[0] = vector2->x;
		array3[1] = vector2->y;
		array3[2] = vector2->z;

		returnVec = mkVec( 3, array3 );
	}
	else if( vector2->type == VEC4 )
	{
		array4[0] = vector2->x;
		array4[1] = vector2->y;
		array4[2] = vector2->z;
		array4[3] = vector2->w;

		returnVec = mkVec( 4, array4 );
	}
	returnVec = scale( returnVec, scaleAmount );

	return returnVec;
}


double dotProd( Vec *vec1, Vec *vec2 )
{
	double answer = 0;
	if( vec1->type == vec2->type == VEC2 )
	{
		answer = vec1->x * vec2->x;
		answer = answer + ( vec1->y * vec2->y );
	}
	else if( vec1->type == vec2->type == VEC3 )
	{
		answer = vec1->x * vec2->x;
		answer = answer + ( vec1->y * vec2->y );
		answer = answer + ( vec1->z * vec2->z );
	}
	else if( vec1->type == vec2->type == VEC4 )
	{
		answer = vec1->x * vec2->x;
		answer = answer + ( vec1->y * vec2->y );
		answer = answer + ( vec1->z * vec2->z );
		answer = answer + ( vec1->w * vec2->w );
	}
	else
	{
		perror( "Could not find the dot product between the vectors\n" );
		answer = -99999999;
	}

	return answer;
}

Vec3* crossProd( Vec3 *vec1, Vec3 *vec2 )
{
	Vec3 *returnVec = NULL;
	double array3[3];

	if( vec1->type == vec2->type == VEC3 )
	{
		array3[0] = ((vec1->y*vec2->z) - (vec1->z*vec2->y));
		array3[1] = -((vec1->x*vec2->z)-(vec1->z*vec2->x));
		array3[2] = ((vec1->x*vec2->y)-(vec1->y*vec2->x));

		returnVec = mkVec( 3, array3 );
	}
	else
	{
		perror( "Vectors passed in are not of type VEC3 returning NULL\n" );
	}

	return returnVec;
}


Vec4* vec3ToVec4( Vec3 *vector )
{
	if( vector->type == VEC3 )
	{
		vector->type = VEC4;
		vector->w = 0;
	}
	else
	{
		perror( "Vector is not of type VEC3\n" );
		return NULL;
	}
}

double length( Vec *vector )
{
	double length = 0;

	length = dotProd( vector, vector );
	length = sqrt( length );

	return length;
}


// uv = ||u|| ||v|| cos(theta);
// 
double angle( Vec *vec1, Vec *vec2 )
{
	double answer, val;

	val = 180.0 / PI;

	answer = dotProd( vec1, vec2 ) / length( vec1 ) / length( vec2 );
	answer = acos( answer ) * val;

	return answer;
}


Vec* normalize( Vec *vec )
{
	Vec *returnVec;
	double vecLen = length( vec );
	double array2[2];
	double array3[3];
	double array4[4];

	if( vec->type == VEC2 )
	{
		array2[0] = (vec->x / vecLen);
		array2[1] = (vec->y / vecLen);

		returnVec = mkVec( 2, array2 );
	}
	else if( vec->type == VEC3 )
	{
		array3[0] = (vec->x / vecLen);
		array3[1] = (vec->y / vecLen);
		array3[2] = (vec->z / vecLen);

		returnVec = mkVec( 3, array3 );
	}
	else if( vec->type == VEC4 )
	{
		array4[0] = (vec->x / vecLen);
		array4[1] = (vec->y / vecLen);
		array4[2] = (vec->z / vecLen);
		array4[3] = (vec->w / vecLen);

		returnVec = mkVec( 4, array4 );
	}
	else
	{
		perror( "Could not normalize the vector\n" );
		returnVec = NULL;
	}

	return returnVec;
}


Mat_Vec* multi( Mat *matrix, Mat_Vec *mat_vec )
{
	if( !(matrix->type == MAT2 || matrix->type == MAT3 || matrix->type == MAT4) )
	{
		perror( "The first param was not a matrix\n" );
		return NULL;
	}

	Mat *returnMat_Vec;
	double array2[2];
	double array3[3];
	double array4[4];
	double array9[9];
	double array16[16];
	
	// 2x2 * 2x1
	if( matrix->type == MAT2 && mat_vec->type == VEC2 )
	{
		array2[0] = ((matrix->data[0] * mat_vec->x) + (matrix->data[1] * mat_vec->y));
		array2[1] = ((matrix->data[2] * mat_vec->x) + (matrix->data[3] * mat_vec->y));

		returnMat_Vec = mkVec( 2, array2 );
	}
	// 2x2 * 2x2
	else if( matrix->type == MAT2 && mat_vec->type == MAT2 )
	{
		array4[0] = ((matrix->data[0] * mat_vec->data[0] ) + (matrix->data[1] * mat_vec->data[2]));
		array4[1] = ((matrix->data[0] * mat_vec->data[1]) + (matrix->data[1] * mat_vec->data[3]));
		array4[2] = ((matrix->data[1] * mat_vec->data[0]) + (matrix->data[3] * mat_vec->data[2]));
		array4[3] = ((matrix->data[1] * mat_vec->data[1]) + (matrix->data[3] * mat_vec->data[3]));

		returnMat_Vec = mkMat( 4, array4 );
	}
	// 3x3 * 3x1
	else if( matrix->type == MAT3 && mat_vec->type == VEC3 )
	{
		array3[0] = ((matrix->data[0] * mat_vec->x) + (matrix->data[1] * mat_vec->y) + (matrix->data[2] * mat_vec->z));
		array3[1] = ((matrix->data[3] * mat_vec->x) + (matrix->data[4] * mat_vec->y) + (matrix->data[5] * mat_vec->z));
		array3[2] = ((matrix->data[6] * mat_vec->x) + (matrix->data[7] * mat_vec->y) + (matrix->data[8] * mat_vec->z));

		returnMat_Vec = mkVec( 3, array3 );
	}
	// 3x3 * 3x3
	else if( matrix->type == MAT3 && mat_vec->type == MAT3 )
	{
		array9[0] = ((matrix->data[0] * mat_vec->data[0] ) + (matrix->data[1] * mat_vec->data[3]) + (matrix->data[2] * mat_vec->data[6]));
		array9[1] = ((matrix->data[0] * mat_vec->data[1] ) + (matrix->data[1] * mat_vec->data[4]) + (matrix->data[2] * mat_vec->data[7]));
		array9[2] = ((matrix->data[0] * mat_vec->data[2] ) + (matrix->data[1] * mat_vec->data[5]) + (matrix->data[2] * mat_vec->data[8]));
		array9[3] = ((matrix->data[3] * mat_vec->data[0] ) + (matrix->data[3] * mat_vec->data[3]) + (matrix->data[4] * mat_vec->data[6]));
		array9[4] = ((matrix->data[3] * mat_vec->data[1] ) + (matrix->data[3] * mat_vec->data[4]) + (matrix->data[4] * mat_vec->data[7]));
		array9[5] = ((matrix->data[3] * mat_vec->data[2] ) + (matrix->data[3] * mat_vec->data[5]) + (matrix->data[4] * mat_vec->data[8]));
		array9[6] = ((matrix->data[6] * mat_vec->data[0] ) + (matrix->data[7] * mat_vec->data[3]) + (matrix->data[8] * mat_vec->data[6]));
		array9[7] = ((matrix->data[6] * mat_vec->data[1] ) + (matrix->data[7] * mat_vec->data[4]) + (matrix->data[8] * mat_vec->data[7]));
		array9[8] = ((matrix->data[6] * mat_vec->data[2] ) + (matrix->data[7] * mat_vec->data[5]) + (matrix->data[8] * mat_vec->data[8]));

		returnMat_Vec = mkMat( 9, array9 );
	}
	// 4x4 * 4x1
	else if( matrix->type == MAT4 && mat_vec->type == VEC4 )
	{
		array4[0] = ((matrix->data[0] * mat_vec->x) + (matrix->data[1] * mat_vec->y) + (matrix->data[2] * mat_vec->z) + (matrix->data[3] * mat_vec->z));
		array4[1] = ((matrix->data[4] * mat_vec->x) + (matrix->data[5] * mat_vec->y) + (matrix->data[6] * mat_vec->z) + (matrix->data[7] * mat_vec->z));
		array4[2] = ((matrix->data[8] * mat_vec->x) + (matrix->data[9] * mat_vec->y) + (matrix->data[10] * mat_vec->z) + (matrix->data[11] * mat_vec->z));
		array4[3] = ((matrix->data[12] * mat_vec->x) + (matrix->data[13] * mat_vec->y) + (matrix->data[14] * mat_vec->z) + (matrix->data[15] * mat_vec->z));

		returnMat_Vec = mkVec( 4, array4 );
	}
	// 4x4 * 4x4
	else if( matrix->type == MAT4 && mat_vec->type == MAT4 )
	{
		array16[0] = ((matrix->data[0] * mat_vec->data[0] ) + (matrix->data[1] * mat_vec->data[4]) + (matrix->data[2] * mat_vec->data[8]) + (matrix->data[3] * mat_vec->data[12]));
		array16[1] = ((matrix->data[0] * mat_vec->data[1] ) + (matrix->data[1] * mat_vec->data[5]) + (matrix->data[2] * mat_vec->data[9]) + (matrix->data[3] * mat_vec->data[13]));
		array16[2] = ((matrix->data[0] * mat_vec->data[2] ) + (matrix->data[1] * mat_vec->data[6]) + (matrix->data[2] * mat_vec->data[10]) + (matrix->data[3] * mat_vec->data[14]));
		array16[3] = ((matrix->data[0] * mat_vec->data[3] ) + (matrix->data[1] * mat_vec->data[7]) + (matrix->data[2] * mat_vec->data[11]) + (matrix->data[3] * mat_vec->data[15]));
		array16[4] = ((matrix->data[4] * mat_vec->data[0] ) + (matrix->data[5] * mat_vec->data[4]) + (matrix->data[6] * mat_vec->data[8]) + (matrix->data[7] * mat_vec->data[12]));
		array16[5] = ((matrix->data[4] * mat_vec->data[1] ) + (matrix->data[5] * mat_vec->data[5]) + (matrix->data[6] * mat_vec->data[9]) + (matrix->data[7] * mat_vec->data[13]));
		array16[6] = ((matrix->data[4] * mat_vec->data[2] ) + (matrix->data[5] * mat_vec->data[6]) + (matrix->data[6] * mat_vec->data[10]) + (matrix->data[7] * mat_vec->data[14]));
		array16[7] = ((matrix->data[4] * mat_vec->data[3] ) + (matrix->data[5] * mat_vec->data[7]) + (matrix->data[6] * mat_vec->data[11]) + (matrix->data[7] * mat_vec->data[15]));
		array16[8] = ((matrix->data[8] * mat_vec->data[0] ) + (matrix->data[9] * mat_vec->data[4]) + (matrix->data[10] * mat_vec->data[8]) + (matrix->data[11] * mat_vec->data[12]));
		array16[9] = ((matrix->data[8] * mat_vec->data[1] ) + (matrix->data[9] * mat_vec->data[5]) + (matrix->data[10] * mat_vec->data[9]) + (matrix->data[11] * mat_vec->data[13]));
		array16[10] = ((matrix->data[8] * mat_vec->data[2] ) + (matrix->data[9] * mat_vec->data[6]) + (matrix->data[10] * mat_vec->data[10]) + (matrix->data[11] * mat_vec->data[14]));
		array16[11] = ((matrix->data[8] * mat_vec->data[3] ) + (matrix->data[9] * mat_vec->data[7]) + (matrix->data[10] * mat_vec->data[11]) + (matrix->data[11] * mat_vec->data[15]));
		array16[12] = ((matrix->data[12] * mat_vec->data[0] ) + (matrix->data[13] * mat_vec->data[4]) + (matrix->data[14] * mat_vec->data[8]) + (matrix->data[15] * mat_vec->data[12]));
		array16[13] = ((matrix->data[12] * mat_vec->data[1] ) + (matrix->data[13] * mat_vec->data[5]) + (matrix->data[14] * mat_vec->data[9]) + (matrix->data[15] * mat_vec->data[13]));
		array16[14] = ((matrix->data[12] * mat_vec->data[2] ) + (matrix->data[13] * mat_vec->data[6]) + (matrix->data[14] * mat_vec->data[10]) + (matrix->data[15] * mat_vec->data[14]));
		array16[15] = ((matrix->data[12] * mat_vec->data[3] ) + (matrix->data[13] * mat_vec->data[7]) + (matrix->data[14] * mat_vec->data[11]) + (matrix->data[15] * mat_vec->data[15]));

		returnMat_Vec = mkMat( 16, array16 );
	}
	else
	{
		perror( "Unable to multiply the given params returning NULL\n" );
		returnMat_Vec = NULL;
	}
	
	return returnMat_Vec;
}


Mat_Vec* addMV( Mat_Vec *mat_vec1, Mat_Vec *mat_vec2 )
{
	Mat *returnMat_Vec;
	double array2[2];
	double array3[3];
	double array4[4];
	double array9[9];
	double array16[16];

	if( mat_vec1->type == VEC2 && mat_vec2->type == VEC2 )
	{
		array2[0] = (mat_vec1->x + mat_vec2->x);
		array2[1] = (mat_vec1->y + mat_vec2->y);

		returnMat_Vec = mkVec( 2, array2 );
	}
	else if( mat_vec1->type == VEC3 && mat_vec2->type == VEC3 )
	{
		array3[0] = (mat_vec1->x + mat_vec2->x);
		array3[1] = (mat_vec1->y + mat_vec2->y);
		array3[2] = (mat_vec1->z + mat_vec2->z);

		returnMat_Vec = mkVec( 3, array3 );
	}
	else if( mat_vec1->type == VEC4 && mat_vec2->type == VEC4 )
	{
		array4[0] = (mat_vec1->x + mat_vec2->x);
		array4[1] = (mat_vec1->y + mat_vec2->y);
		array4[2] = (mat_vec1->z + mat_vec2->z);
		array4[3] = (mat_vec1->w + mat_vec2->w);

		returnMat_Vec = mkVec( 4, array4 );
	}
	else if( mat_vec1->type == MAT2 && mat_vec2->type == MAT2 )
	{
		array4[0] = (mat_vec1->data[0] + mat_vec2->data[0]);
		array4[1] = (mat_vec1->data[1] + mat_vec2->data[1]);
		array4[2] = (mat_vec1->data[2] + mat_vec2->data[2]);
		array4[3] = (mat_vec1->data[3] + mat_vec2->data[3]);

		returnMat_Vec = mkMat( 4, array4 );
	}
	else if( mat_vec1->type == MAT2 && mat_vec2->type == MAT2 )
	{
		array9[0] = (mat_vec1->data[0] + mat_vec2->data[0]);
		array9[1] = (mat_vec1->data[1] + mat_vec2->data[1]);
		array9[2] = (mat_vec1->data[2] + mat_vec2->data[2]);
		array9[3] = (mat_vec1->data[3] + mat_vec2->data[3]);
		array9[4] = (mat_vec1->data[4] + mat_vec2->data[4]);
		array9[5] = (mat_vec1->data[5] + mat_vec2->data[5]);
		array9[6] = (mat_vec1->data[6] + mat_vec2->data[6]);
		array9[7] = (mat_vec1->data[7] + mat_vec2->data[7]);
		array9[8] = (mat_vec1->data[8] + mat_vec2->data[8]);

		returnMat_Vec = mkMat( 9, array9 );
	}
	else if( mat_vec1->type == MAT2 && mat_vec2->type == MAT2 )
	{
		array16[0] = (mat_vec1->data[0] + mat_vec2->data[0]);
		array16[1] = (mat_vec1->data[1] + mat_vec2->data[1]);
		array16[2] = (mat_vec1->data[2] + mat_vec2->data[2]);
		array16[3] = (mat_vec1->data[3] + mat_vec2->data[3]);
		array16[4] = (mat_vec1->data[4] + mat_vec2->data[4]);
		array16[5] = (mat_vec1->data[5] + mat_vec2->data[5]);
		array16[6] = (mat_vec1->data[6] + mat_vec2->data[6]);
		array16[7] = (mat_vec1->data[7] + mat_vec2->data[7]);
		array16[8] = (mat_vec1->data[8] + mat_vec2->data[8]);
		array16[9] = (mat_vec1->data[9] + mat_vec2->data[9]);
		array16[10] = (mat_vec1->data[10] + mat_vec2->data[10]);
		array16[11] = (mat_vec1->data[11] + mat_vec2->data[11]);
		array16[12] = (mat_vec1->data[12] + mat_vec2->data[12]);
		array16[13] = (mat_vec1->data[13] + mat_vec2->data[13]);
		array16[14] = (mat_vec1->data[14] + mat_vec2->data[14]);
		array16[15] = (mat_vec1->data[15] + mat_vec2->data[15]);

		returnMat_Vec = mkMat( 16, array16 );
	}
	else
	{
		perror( "Could not add the matricies or vectors together return NULL\n" );
		returnMat_Vec = NULL;
	}

	return returnMat_Vec;
}


Mat_Vec* scale( Mat_Vec *mat_vec, double scaleAmount )
{
	if( mat_vec->type == VEC2 )
	{
		mat_vec->x = mat_vec->x * scaleAmount;
		mat_vec->y = mat_vec->y * scaleAmount;
	}
	else if( mat_vec->type == VEC3 )
	{
		mat_vec->x = mat_vec->x * scaleAmount;
		mat_vec->y = mat_vec->y * scaleAmount;
		mat_vec->z = mat_vec->z * scaleAmount;
	}
	else if( mat_vec->type == VEC4 )
	{
		mat_vec->x = mat_vec->x * scaleAmount;
		mat_vec->y = mat_vec->y * scaleAmount;
		mat_vec->z = mat_vec->z * scaleAmount;
		mat_vec->w = mat_vec->w * scaleAmount;
	}
	else if( mat_vec->type == MAT2 )
	{
		mat_vec->data[0] = mat_vec->data[0] * scaleAmount;
		mat_vec->data[1] = mat_vec->data[1] * scaleAmount;
		mat_vec->data[2] = mat_vec->data[2] * scaleAmount;
		mat_vec->data[3] = mat_vec->data[3] * scaleAmount;
	}
	else if( mat_vec->type == MAT3 )
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
	else if( mat_vec->type == MAT4 )
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
