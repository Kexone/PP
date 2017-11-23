#pragma once
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include <omp.h>
#define N 500

class Multiplication
{
private:
	void generateMatrix2DArray(long *mat[N]);
	void generateMatrixVector(std::vector < std::vector < long > > &mat);
	void generateMatrix1DArray(long *mat);

	void clearMatrix(long *mat[N]);
	void clearMatrix(std::vector < std::vector < long > > &mat);
	void clearMatrix(long *mat);


	void printMat(long mat[N][N]);
	void printMat(long *mat);
	void printMat(std::vector < std::vector < long > > &mat);

	void calcSolo2DArrayRCV(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcSolo2DArrayRVC(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcSolo2DArrayCRV(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcSolo2DArrayCVR(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcSolo2DArrayVCR(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcSolo2DArrayVRC(long * mat1[N], long * mat2[N], long * mat3[N]);

	void calcOmpOut2DArrayRCV(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpOut2DArrayRVC(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpOut2DArrayCRV(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpOut2DArrayCVR(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpOut2DArrayVCR(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpOut2DArrayVRC(long * mat1[N], long * mat2[N], long * mat3[N]);

	void calcOmpMid2DArrayRCV(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpMid2DArrayRVC(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpMid2DArrayCRV(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpMid2DArrayCVR(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpMid2DArrayVCR(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpMid2DArrayVRC(long * mat1[N], long * mat2[N], long * mat3[N]);

	void calcOmpIn2DArrayRCV(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpIn2DArrayRVC(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpIn2DArrayCRV(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpIn2DArrayCVR(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpIn2DArrayVCR(long * mat1[N], long * mat2[N], long * mat3[N]);
	void calcOmpIn2DArrayVRC(long * mat1[N], long * mat2[N], long * mat3[N]);

	void calcSolo1DArrayRCV(long * mat1, long * mat2, long * mat3);
	void calcSolo1DArrayRVC(long * mat1, long * mat2, long * mat3);
	void calcSolo1DArrayCRV(long * mat1, long * mat2, long * mat3);
	void calcSolo1DArrayCVR(long * mat1, long * mat2, long * mat3);
	void calcSolo1DArrayVCR(long * mat1, long * mat2, long * mat3);
	void calcSolo1DArrayVRC(long * mat1, long * mat2, long * mat3);

	void calcOmpOut1DArrayRCV(long * mat1, long * mat2, long * mat3);
	void calcOmpOut1DArrayRVC(long * mat1, long * mat2, long * mat3);
	void calcOmpOut1DArrayCRV(long * mat1, long * mat2, long * mat3);
	void calcOmpOut1DArrayCVR(long * mat1, long * mat2, long * mat3);
	void calcOmpOut1DArrayVCR(long * mat1, long * mat2, long * mat3);
	void calcOmpOut1DArrayVRC(long * mat1, long * mat2, long * mat3);

	void calcOmpMid1DArrayRCV(long * mat1, long * mat2, long * mat3);
	void calcOmpMid1DArrayRVC(long * mat1, long * mat2, long * mat3);
	void calcOmpMid1DArrayCRV(long * mat1, long * mat2, long * mat3);
	void calcOmpMid1DArrayCVR(long * mat1, long * mat2, long * mat3);
	void calcOmpMid1DArrayVCR(long * mat1, long * mat2, long * mat3);
	void calcOmpMid1DArrayVRC(long * mat1, long * mat2, long * mat3);

	void calcOmpIn1DArrayRCV(long * mat1, long * mat2, long * mat3);
	void calcOmpIn1DArrayRVC(long * mat1, long * mat2, long * mat3);
	void calcOmpIn1DArrayCRV(long * mat1, long * mat2, long * mat3);
	void calcOmpIn1DArrayCVR(long * mat1, long * mat2, long * mat3);
	void calcOmpIn1DArrayVCR(long * mat1, long * mat2, long * mat3);
	void calcOmpIn1DArrayVRC(long * mat1, long * mat2, long * mat3);

	void calcSoloVectorRCV(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcSoloVectorRVC(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcSoloVectorCRV(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcSoloVectorCVR(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcSoloVectorVCR(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcSoloVectorVRC(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);

	void calcOmpOutVectorRCV(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpOutVectorRVC(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpOutVectorCRV(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpOutVectorCVR(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpOutVectorVCR(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpOutVectorVRC(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);

	void calcOmpMidVectorRCV(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpMidVectorRVC(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpMidVectorCRV(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpMidVectorCVR(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpMidVectorVCR(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpMidVectorVRC(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);

	void calcOmpInVectorRCV(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpInVectorRVC(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpInVectorCRV(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpInVectorCVR(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpInVectorVCR(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	void calcOmpInVectorVRC(std::vector < std::vector < long > > &mat1, std::vector < std::vector < long > > &mat2, std::vector < std::vector < long > > &mat3);
	
	clock_t timer;

public:


	Multiplication();
	void calculateVectors();
	void calculate1DArray();
	void calculate2DArray();
	long getN();
};

