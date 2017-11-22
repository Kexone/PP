#pragma once
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include <omp.h>

#define N 1000

class Multiplication
{
private:
	void generateMatrix2DArray(int *mat[N]);
	void generateMatrixVector(std::vector < std::vector < int > > &mat);
	void generateMatrix1DArray(int *mat);

	void printMat2DArray(int mat[N][N]);
	void printMat1DArray(int *mat);
	void printMat1DArrayT(int *mat);
	void printMatVector(std::vector < std::vector < int > > &mat);

	void fillVectors(std::vector < std::vector < int > > &matrix);

	void calcSolo2DArray(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpOut2DArray(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpMid2DArray(int * mat1[N], int * mat2[N], int * mat3[N]);
	void calcOmpIn2DArray(int * mat1[N], int * mat2[N], int * mat3[N]);

	void calcSolo1DArray(int * mat1, int * mat2, int * mat3);
	void calcOmpOut1DArray(int * mat1, int * mat2, int * mat3);
	void calcOmpMid1DArray(int * mat1, int * mat2, int * mat3);
	void calcOmpIn1DArray(int * mat1, int * mat2, int * mat3);

	void calcSoloVector(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpMidVector(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpOutVector(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);
	void calcOmpInVector(std::vector < std::vector < int > > &mat1, std::vector < std::vector < int > > &mat2, std::vector < std::vector < int > > &mat3);

	clock_t timer;

public:
	Multiplication();
	void calculateVectors();
	void calculate1DArray();
	void calculate2DArray();
	int getN();
};

