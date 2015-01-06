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
typedef struct Matrix_Vector Vec2, Vec3, Vec4, Mat2, Mat3, Mat4;



	//these will be given an aribitraty matrix
mkMat // This one will guess which size it should be and set the enum type correctly
mkVec

det() // determinate 
scale(Mat, int) // scales by vector or matrix by _ amount
inverse(Mat)
pow() // raises matrix to _ power much like scale ... same formatting

project(Vec, Vec)
angle(Vec, Vec) // the angle between two vectors
dist(Vec, Vec) // distance between two vectors


normalize() // this is for matrix or vectors
multi(Mat, Mat) // multiplies the two matricies together or does matrix vector multiplication must be able to multiply
add( ) // adds the two matrix or vectors together must be able to add them
crossProd() // cross product of two .. must be able to do the cross or returns null
dotProd() // dot product of two .. must be able to do the dot product or returns null

	//returns an identiy matrix you could also just use mkMat( [1, 0, 0, 0, 1, 0, 0, 0, 1])
mkMat2_Identiy()
mkMat3_Identiy()
mkMat4_Identiy()





#endif