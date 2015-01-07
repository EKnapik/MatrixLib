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
	VEC4
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
typedef struct Matrix_Vector Vec, Vec2, Vec3, Vec4, Mat, Mat2, Mat3, Mat4, Mat_Vec;


Vec mkVec( double data[] );

Mat mkMat( double data[] );
//these will be given an aribitraty matrix
// This one will guess which size it should be and set the enum type correctly


double det( Mat matrix );
Mat_Vec scale( Mat_Vec matrix, double scaleAmount );
Mat inverse( Mat matrix );
Mat pow( Mat matrix, int power );

Vec project( Vec vector1, Vec vector2 );
double angle( Vec vector1, Vec vector2 );
double dist( Vec vector1, Vec vector2 );


Mat_Vec normalize( Mat_Vec mat_vec );
Mat_Vec multi( Mat matrix, Mat_Vec mat_vec );
Mat_Vec add( Mat_Vec mat_vec1, Mat_Vec mat_vec2 );
double dotProd( Vec vec1, Vec vec2 );

Mat2 mkMat2_Identiy( void );
Mat3 mkMat3_Identiy( void );
Mat4 mkMat4_Identiy( void );

	//returns an identiy matrix you could also just use mkMat( [1, 0, 0, 0, 1, 0, 0, 0, 1])





#endif