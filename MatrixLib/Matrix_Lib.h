// Author: Eric Knapik
// Matrix_Lib.h for vec.c and mat.c

#ifndef MATRIX_LIB
#define MATRIX_LIB


//The overall structure for the vectors or matrixs, they will be the same
typedef enum
{
	MAT2,
	MAT3,
	MAT4,
	VEC2,
	VEC3,
	VEC4,
	Mat_Vec
} Mat_Vec_Type;

struct Matrix_Vector
{
	double x;
	double y;
	double z;
	double w;
	double *data;
	Mat_Vec_Type type;
}

// Typedef all the ways you can write the enums into the struct Matrix_Vector
// These are all refrences to the same struct, this will just be for convenience when
// programming using the library this is also the same enum type
typedef struct Matrix_Vector Vec, Vec2, Vec3, Vec4, Mat, Mat2, Mat3, Mat4, Mat_Vec;

/**
* this takes in an array of doubles and given that array will determine
* what kind of vector to make given the size of the array, this will place
* the values into the x, y, z, w and sets the enum type returns a
* Matrix_Vector struct
*
* @param an array of doubles
* @return a Matrix_Vector Struct configured for a vector
**/
Vec mkVec( double data[] );

/**
* This will take an array of doubles and given the size of the array
* will determine what kind of matrix array to make and what to set the enum as
* This will not set variables for the x,y,z,w doubles they are never set. This
* only uses the *data
*
* @param an array of doubles
* @return a Matrix_Vector Struct configured for a Matrix
**/
Mat mkMat( double data[] );

/**
* destroys a matrix, frees the dynamically allocated data region
* of the struct. This should probably be done, yea that would be nice
* kinda
* returns void
**/
void destroyMat( Mat matrix );

/**
* given a matrix in the Matrix_Vector Struct will return the determinate
* of any matrix that is of size 2, 3, or 4.
* returns a double
**/
double det( Mat matrix );

/**
* will scale a matrix or a vector in the Matrix_Vector Struct format and
* multiply each part by the double scaleAmount
* returns that Matrix_Vector Struct
**/
Mat_Vec scale( Mat_Vec mat_vec, double scaleAmount );

/**
* given a matrix in the Matrix_Vector Struct format will return the inverse
* of that matrix, if the inverse does not exist will return NULL.
* returns the inverse of that Matrix_Vector Struct
**/
Mat inverse( Mat matrix );

/**
* will multiply that matrix in the Matrix_Vector Struct format by itself
* the power number of times then returns that Matrix_Vector Struct.
**/
Mat pow( Mat matrix, int power );


/**
* This will rotate a matrix by so many degrees according to the char passed in
* takes char x, y, or z and degrees 0 -  360. Then rotates the matrix accordingly
* Matrix must be a Mat4
* returns Mat4 a new Mat
**/
Mat4 rotate( Mat4 matrix, char axis, double degrees );

/**
* given a matrix that is a 2x2 or 3x3 or 4x4 will return the transpose of that matrix
* This makes a new matrix and returns the transpose of the matrix passed in.
* returns a Mat
**/
Mat transpose( Mat matrix );

/**
* This returns a new vector that is the projection of vector2 onto vector1.
* this will make a new Matrix_Vector Struct and return the projection
* return Matrix_Vector Struct
* project v onto u where v is vector2 and u is vector1
**/
Vec project( Vec vector1, Vec vector2 );

/**
* returns the angle between two vectors
* retuns a double that is the amount of degrees between two vectors
**/
double angle( Vec vector1, Vec vector2 );


/**
* returns the length of a vector
* returns a double
**/
double length( Vec vector );


/**
* given a matrix or a vector as notated by the Mat_Vec notation. and returns
* that vector or matrix normalized.
* retuns a Matrix_Vector Struct
**/
Mat_Vec normalize( Mat_Vec mat_vec );

/**
* if valid will do the matrix multiplication of two matrixes and can do the
* the matrix vector multiplication.
* returns a new Matrix_Vector Struct
**/
Mat_Vec multi( Mat matrix, Mat_Vec mat_vec );

/**
* will add two matricies or two vectors together and returns
* a new Matrix_Vector Struct
* returns a Matrix_Vector Struct
**/
Mat_Vec addMV( Mat_Vec mat_vec1, Mat_Vec mat_vec2 );

/**
* prints to standard out the matrix or vector passed in. returns void;
**/
void print( Mat_Vec mat_vec );

/**
* this will take the dot product of two vectors and return
* the double that is the dot product of those two vectors
* returns a double
**/
double dotProd( Vec vec1, Vec vec2 );

/**
* returns an identity matrix that is the appropriate size
* returns an identiy matrix you could also just use mkMat( [1, 0, 0, 0, 1, 0, 0, 0, 1])
**/
Mat2 mkMat2I( void );
Mat3 mkMat3I( void );
Mat4 mkMat4I( void );

#endif