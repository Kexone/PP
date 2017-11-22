#include "multiplication.h"


#define nFrom 1
#define nTo 2

std::random_device rd;
std::mt19937 gen(rd()); 
std::uniform_int_distribution<> dis(nFrom, nTo);

int Multiplication::getN()
{
	return N;
}

Multiplication::Multiplication() { }

void Multiplication::generateMatrix2DArray(int *mat[N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			mat[i][j] = dis(gen);
		}
	}
}

void Multiplication::generateMatrixVector(std::vector<std::vector<int>>& mat)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			mat[i][j] = dis(gen);
		}
	}
}

void Multiplication::generateMatrix1DArray(int* mat)
{
	for (int i = 0; i < N*N; i++)
	{
		mat[i] = dis(gen);
	}
}

void Multiplication::calculateVectors()
{
	std::vector < std::vector < int > > matrix1;
	std::vector < std::vector < int > > matrix2;
	std::vector < std::vector < int > > matrix3;
	fillVectors(matrix1);
	fillVectors(matrix2);
	fillVectors(matrix3);

	generateMatrixVector(matrix1);
	generateMatrixVector(matrix2);


	timer = clock();
	calcSoloVector(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on solo cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;
	
	timer = clock();
	calcOmpMidVector(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP middle for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	timer = clock();
	calcOmpOutVector(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP outline for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	timer = clock();
	calcOmpInVector(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP inline for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	matrix1.clear();
	matrix2.clear();
	matrix3.clear();
}

void Multiplication::calculate1DArray()
{
	int* matrix1 = new int[N*N];
	int* matrix2 = new int[N*N];
	int* matrix3 = new int[N*N];

	for (int i = 0; i < N*N; i++)
		matrix3[i] = 0;

	generateMatrix1DArray(matrix1);
	generateMatrix1DArray(matrix2);

	//printMat1DArray(matrix1);
	//std::cout << std::endl;
	//printMat1DArray(matrix2);
	timer = clock();
	calcSolo1DArray(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on solo cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	timer = clock();
	calcOmpMid1DArray(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP middle for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	timer = clock();
	calcOmpOut1DArray(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP outline for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	timer = clock();
	calcOmpIn1DArray(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP inline for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	delete[] matrix1;
	delete[] matrix2;
	delete[] matrix3;
}


void Multiplication::calculate2DArray()
{
	int** matrix1 = new int*[N];
	int** matrix2 = new int*[N];
	int** matrix3 = new int*[N];
	for(int i = 0; i < N; i++)
	{
		matrix1[i] = new int[N];
		matrix2[i] = new int[N];
		matrix3[i] = new int[N];
	}


	generateMatrix2DArray(matrix1);
	generateMatrix2DArray(matrix2);

	timer = clock();
	calcSolo2DArray(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on solo cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	timer = clock();
	calcOmpMid2DArray(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP middle for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	timer = clock();
	calcOmpOut2DArray(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP outline for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	timer = clock();
	calcOmpIn2DArray(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Multiplication on OMP inline for cpu took: " << static_cast<float> (timer / CLOCKS_PER_SEC) << " second." << std::endl;

	for(size_t i = N; i > 0;)
	{
		delete[] matrix1[--i];
		delete[] matrix2[i];
		delete[] matrix3[i];
	}
	delete[] matrix1;
	delete[] matrix2;
	delete[] matrix3;
}

void Multiplication::printMat2DArray(int mat[N][N])
{
	for (int i = 0; i < N; i++)	{
		std::cout << "| ";
		for (int j = 0; j < N; j++)	{
			std::cout << mat[i][j] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

void Multiplication::printMat1DArray(int* mat)
{
	for (int i = 0; i < N; i++) {
		std::cout << "| ";
		for (int j = N*i; j < N*i+N; j++) {
			std::cout << mat[j] << " ";
		}
		std::cout << " |" << std::endl;
	}
}

void Multiplication::printMat1DArrayT(int* mat)
{
	for (int i = 0; i < N; i++) {
		std::cout << "| ";
		for (int j = i; j < N*N;) {
			std::cout << mat[j] << " ";
			j += N;
		}
		std::cout << " |" << std::endl;
	}
}

void Multiplication::printMatVector(std::vector<std::vector<int>>& mat)
{
	for (int i = 0; i < N; i++) {
		std::cout << "| ";
		for (int j = 0; j < N; j++) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

void Multiplication::fillVectors(std::vector < std::vector < int > > &matrix)
{
	std::vector<int> tmp(N);
	std::fill(tmp.begin(), tmp.end(), 0);
	for (int i = 0; i < N; i++) {
		matrix.push_back(tmp);
	}
	tmp.clear();
}

void Multiplication::calcSoloVector(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void Multiplication::calcOmpOutVector(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void Multiplication::calcOmpMidVector(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int i = 0; i < N; i++) {
#pragma omp parallel for
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}


void Multiplication::calcOmpInVector(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
#pragma omp parallel for
			for (int k = 0; k < N; k++) {
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void Multiplication::calcSolo2DArray(int * mat1[N], int * mat2[N], int * mat3[N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void Multiplication::calcOmpOut2DArray(int * mat1[N], int * mat2[N], int * mat3[N])
{
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void Multiplication::calcOmpMid2DArray(int * mat1[N], int * mat2[N], int * mat3[N])
{
	for (int i = 0; i < N; i++) {
#pragma omp parallel for
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}


void Multiplication::calcOmpIn2DArray(int * mat1[N], int * mat2[N], int * mat3[N])
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
#pragma omp parallel for
			for (int k = 0; k < N; k++) {
				mat3[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
}

void Multiplication::calcSolo1DArray(int * mat1, int * mat2, int * mat3)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i * N + j] += mat1[i * N + k] * mat2[k * N + j];
			}
		}
	}
}

void Multiplication::calcOmpOut1DArray(int * mat1, int * mat2, int * mat3)
{
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i * N + j] += mat1[i * N + k] * mat2[k * N + j];
			}
		}
	}
}

void Multiplication::calcOmpMid1DArray(int * mat1, int * mat2, int * mat3)
{
	for (int i = 0; i < N; i++) {
#pragma omp parallel for
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				mat3[i * N + j] += mat1[i * N + k] * mat2[k * N + j];
			}
		}
	}
}


void Multiplication::calcOmpIn1DArray(int * mat1, int * mat2, int * mat3)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
#pragma omp parallel for
			for (int k = 0; k < N; k++) {
				mat3[i * N + j] += mat1[i * N + k] * mat2[k * N + j];
			}
		}
	}
}