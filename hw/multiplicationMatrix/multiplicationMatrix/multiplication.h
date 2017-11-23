#pragma once
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include <omp.h>

#define N 3

class Multiplication
{
private:
	void generateMatrix2DArray(int *mat[N]);
	void generateMatrixVector(std::vector < std::vector < int > > &mat);
	void generateMatrix1DArray(int *mat);

	void clearMatrix(int *mat[N]);
	void clearMatrix(std::vector < std::vector < int > > &mat);
	void clearMatrix(int *mat);


	void printMat(int mat[N][N]);
	void printMat(int *mat);
	void printMat(std::vector < std::vector < int > > &mat);

	void calcSolo2DArrayRCV(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcSolo2DArrayRVC(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcSolo2DArrayCRV(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcSolo2DArrayCVR(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcSolo2DArrayVCR(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcSolo2DArrayVRC(int * mat1[N], int * mat2[N], int * mat3[N]);

	void calcOmpOut2DArrayRCV(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpOut2DArrayRVC(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpOut2DArrayCRV(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpOut2DArrayCVR(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpOut2DArrayVCR(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpOut2DArrayVRC(int * mat1[N], int * mat2[N], int * mat3[N]);

	void calcOmpMid2DArrayRCV(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpMid2DArrayRVC(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpMid2DArrayCRV(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpMid2DArrayCVR(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpMid2DArrayVCR(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpMid2DArrayVRC(int * mat1[N], int * mat2[N], int * mat3[N]);

	void calcOmpIn2DArrayRCV(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpIn2DArrayRVC(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpIn2DArrayCRV(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpIn2DArrayCVR(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpIn2DArrayVCR(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpIn2DArrayVRC(int * mat1[N], int * mat2[N], int * mat3[N]);

	void calcSolo1DArrayRCV(int * mat1, int * mat2, int * mat3);
	void calcSolo1DArrayRVC(int * mat1, int * mat2, int * mat3);
	void calcSolo1DArrayCRV(int * mat1, int * mat2, int * mat3);
	void calcSolo1DArrayCVR(int * mat1, int * mat2, int * mat3);
	void calcSolo1DArrayVCR(int * mat1, int * mat2, int * mat3);
	void calcSolo1DArrayVRC(int * mat1, int * mat2, int * mat3);

	void calcOmpOut1DArrayRCV(int * mat1, int * mat2, int * mat3);
	void calcOmpOut1DArrayRVC(int * mat1, int * mat2, int * mat3);
	void calcOmpOut1DArrayCRV(int * mat1, int * mat2, int * mat3);
	void calcOmpOut1DArrayCVR(int * mat1, int * mat2, int * mat3);
	void calcOmpOut1DArrayVCR(int * mat1, int * mat2, int * mat3);
	void calcOmpOut1DArrayVRC(int * mat1, int * mat2, int * mat3);

	void calcOmpMid1DArrayRCV(int * mat1, int * mat2, int * mat3);
	void calcOmpMid1DArrayRVC(int * mat1, int * mat2, int * mat3);
	void calcOmpMid1DArrayCRV(int * mat1, int * mat2, int * mat3);
	void calcOmpMid1DArrayCVR(int * mat1, int * mat2, int * mat3);
	void calcOmpMid1DArrayVCR(int * mat1, int * mat2, int * mat3);
	void calcOmpMid1DArrayVRC(int * mat1, int * mat2, int * mat3);

	void calcOmpIn1DArrayRCV(int * mat1, int * mat2, int * mat3);
	void calcOmpIn1DArrayRVC(int * mat1, int * mat2, int * mat3);
	void calcOmpIn1DArrayCRV(int * mat1, int * mat2, int * mat3);
	void calcOmpIn1DArrayCVR(int * mat1, int * mat2, int * mat3);
	void calcOmpIn1DArrayVCR(int * mat1, int * mat2, int * mat3);
	void calcOmpIn1DArrayVRC(int * mat1, int * mat2, int * mat3);

	void calcSoloVectorRCV(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcSoloVectorRVC(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcSoloVectorCRV(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcSoloVectorCVR(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcSoloVectorVCR(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcSoloVectorVRC(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);

	void calcOmpOutVectorRCV(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpOutVectorRVC(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpOutVectorCRV(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpOutVectorCVR(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpOutVectorVCR(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpOutVectorVRC(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);

	void calcOmpMidVectorRCV(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpMidVectorRVC(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpMidVectorCRV(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpMidVectorCVR(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpMidVectorVCR(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpMidVectorVRC(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);

	void calcOmpInVectorRCV(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpInVectorRVC(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpInVectorCRV(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpInVectorCVR(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpInVectorVCR(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpInVectorVRC(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	
	clock_t timer;

public:
	Multiplication();
	void calculateVectors();
	void calculate1DArray();
	void calculate2DArray();
	int getN();
};

