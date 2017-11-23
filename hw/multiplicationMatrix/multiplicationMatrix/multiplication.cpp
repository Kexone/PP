#include "multiplication.h"
#include <iostream>
#include <fstream>

#define nFrom 0
#define nTo 50

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(nFrom, nTo);

int Multiplication::getN()
{
	return N;
}

Multiplication::Multiplication()
{
}

#pragma region generators

void Multiplication::generateMatrix2DArray(int* mat[N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			mat[row][col] = dis(gen);
		}
	}
}

void Multiplication::generateMatrixVector(std::vector<std::vector<int>>& mat)
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			mat[row][col] = dis(gen);
		}
	}
}

void Multiplication::generateMatrix1DArray(int* mat)
{
	for (int row = 0; row < N * N; row++)
	{
		mat[row] = dis(gen);
	}
}

void Multiplication::clearMatrix(int* mat[500])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			mat[row][col] = 0;
		}
	}
}

void Multiplication::clearMatrix(std::vector<std::vector<int>>& mat)
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			mat[row][col] = 0;
		}
	}
}

void Multiplication::clearMatrix(int* mat)
{
	for (int row = 0; row < N * N; row++)
	{
		mat[row] = 0;
	}
}
#pragma endregion

#pragma region main calc public parts

void Multiplication::calculateVectors()
{
	std::ofstream fs("resultsVectors.csv");
	fs  << "rcp;" << "rpc;" << "crp;" << "cpr;" << "prc;" << "pcr;" << std::endl;

	std::vector<std::vector<int>> matrix1;
	std::vector<std::vector<int>> matrix2;
	std::vector<std::vector<int>> matrix3;
	std::vector<int> tmp(N);

	std::fill(tmp.begin(), tmp.end(), 0);
	for (int row = 0; row < N; row++)
	{
		matrix1.push_back(tmp);
		matrix2.push_back(tmp);
		matrix3.push_back(tmp);
	}
	tmp.clear();


	generateMatrixVector(matrix1);
	generateMatrixVector(matrix2);

	timer = clock();
	calcSoloVectorRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	printMat(matrix3);
	clearMatrix(matrix3);

	timer = clock();
	calcSoloVectorRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	printMat(matrix3);
	clearMatrix(matrix3);

	timer = clock();
	calcSoloVectorCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	printMat(matrix3);
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSoloVectorCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	printMat(matrix3);
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSoloVectorVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSoloVectorVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOutVectorRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOutVectorRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOutVectorCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOutVectorCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOutVectorVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOutVectorVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMidVectorRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMidVectorRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMidVectorCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMidVectorCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMidVectorVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMidVectorVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpInVectorRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpInVectorRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpInVectorCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpInVectorCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpInVectorVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpInVectorVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	fs.close();
	matrix1.clear();
	matrix2.clear();
	matrix3.clear();
}

void Multiplication::calculate1DArray()
{
	std::ofstream fs("results1DArray.csv");
	fs << "rcp;" << "rpc;" << "crp;" << "cpr;" << "prc;" << "pcr;" << std::endl;

	int* matrix1 = new int[N * N];
	int* matrix2 = new int[N * N];
	int* matrix3 = new int[N * N];

	for (int row = 0; row < N * N; row++)
		matrix3[row] = 0;

	generateMatrix1DArray(matrix1);
	generateMatrix1DArray(matrix2);

	timer = clock();
	calcSolo1DArrayRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo1DArrayRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo1DArrayCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo1DArrayCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo1DArrayVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo1DArrayVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut1DArrayRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut1DArrayRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut1DArrayCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut1DArrayCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut1DArrayVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut1DArrayVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid1DArrayRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid1DArrayRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid1DArrayCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid1DArrayCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid1DArrayVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid1DArrayVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn1DArrayRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn1DArrayRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn1DArrayCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn1DArrayCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn1DArrayVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn1DArrayVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	fs.close();

	delete[] matrix1;
	delete[] matrix2;
	delete[] matrix3;
}

void Multiplication::calculate2DArray()
{
	std::ofstream fs("results2DArray.csv");
	fs << "rcp;" << "rpc;" << "crp;" << "cpr;" << "prc;" << "pcr;" << std::endl;

	int** matrix1 = new int*[N];
	int** matrix2 = new int*[N];
	int** matrix3 = new int*[N];
	for (int row = 0; row < N; row++)
	{
		matrix1[row] = new int[N];
		matrix2[row] = new int[N];
		matrix3[row] = new int[N];
	}


	generateMatrix2DArray(matrix1);
	generateMatrix2DArray(matrix2);

	timer = clock();
	calcSolo2DArrayRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo2DArrayRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo2DArrayCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo2DArrayCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo2DArrayVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcSolo2DArrayVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "Solo cpu PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut2DArrayRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut2DArrayRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut2DArrayCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut2DArrayCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut2DArrayVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpOut2DArrayVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP OUT PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid2DArrayRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid2DArrayRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid2DArrayCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid2DArrayCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid2DArrayVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpMid2DArrayVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP MID PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn2DArrayRCV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN RCP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn2DArrayRVC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN RPC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn2DArrayCRV(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN CRP: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn2DArrayCVR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN CPR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn2DArrayVRC(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN PRC: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";";
	clearMatrix(matrix3);

	timer = clock();
	calcOmpIn2DArrayVCR(matrix1, matrix2, matrix3);
	timer = clock() - timer;
	std::cout << "OMP IN PCR: " << static_cast<float>(timer) / CLOCKS_PER_SEC << " second." << std::endl;
	fs << static_cast<float>(timer) / CLOCKS_PER_SEC << ";" << std::endl;
	clearMatrix(matrix3);

	fs.close();
	for (size_t row = N; row > 0;)
	{
		delete[] matrix1[--row];
		delete[] matrix2[row];
		delete[] matrix3[row];
	}
	delete[] matrix1;
	delete[] matrix2;
	delete[] matrix3;
}

#pragma endregion

#pragma region print section

void Multiplication::printMat(int mat[N][N])
{
	for (int row = 0; row < N; row++)
	{
		std::cout << "| ";
		for (int col = 0; col < N; col++)
		{
			std::cout << mat[row][col] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

void Multiplication::printMat(int* mat)
{
	for (int row = 0; row < N; row++)
	{
		std::cout << "| ";
		for (int col = N * row; col < N * row + N; col++)
		{
			std::cout << mat[col] << " ";
		}
		std::cout << " |" << std::endl;
	}
}

void Multiplication::printMat(std::vector<std::vector<int>>& mat)
{
	for (int row = 0; row < N; row++)
	{
		std::cout << "| ";
		for (int col = 0; col < N; col++)
		{
			std::cout << mat[row][col] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

#pragma endregion 

#pragma region 2D arrays

void Multiplication::calcSolo2DArrayRCV(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSolo2DArrayRVC(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSolo2DArrayCRV(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSolo2DArrayCVR(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSolo2DArrayVCR(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSolo2DArrayVRC(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOut2DArrayRCV(int* mat1[N], int* mat2[N], int* mat3[N])
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOut2DArrayRVC(int* mat1[N], int* mat2[N], int* mat3[N])
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOut2DArrayCRV(int* mat1[N], int* mat2[N], int* mat3[N])
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOut2DArrayCVR(int* mat1[N], int* mat2[N], int* mat3[N])
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOut2DArrayVCR(int* mat1[N], int* mat2[N], int* mat3[N])
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOut2DArrayVRC(int* mat1[N], int* mat2[N], int* mat3[N])
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMid2DArrayRCV(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int row = 0; row < N; row++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMid2DArrayRVC(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int row = 0; row < N; row++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMid2DArrayCRV(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int col = 0; col < N; col++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMid2DArrayCVR(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int col = 0; col < N; col++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMid2DArrayVCR(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int val = 0; val < N; val++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMid2DArrayVRC(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int val = 0; val < N; val++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpIn2DArrayRCV(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpIn2DArrayRVC(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpIn2DArrayCRV(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpIn2DArrayCVR(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpIn2DArrayVCR(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpIn2DArrayVRC(int* mat1[N], int* mat2[N], int* mat3[N])
{
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

#pragma endregion 


#pragma region Vectors

void Multiplication::calcSoloVectorRCV(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSoloVectorRVC(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSoloVectorCRV(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSoloVectorCVR(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSoloVectorVCR(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcSoloVectorVRC(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOutVectorRCV(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOutVectorRVC(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOutVectorCRV(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOutVectorCVR(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOutVectorVCR(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpOutVectorVRC(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMidVectorRCV(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int row = 0; row < N; row++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMidVectorRVC(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int row = 0; row < N; row++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMidVectorCRV(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int col = 0; col < N; col++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMidVectorCVR(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int col = 0; col < N; col++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMidVectorVCR(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int val = 0; val < N; val++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpMidVectorVRC(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int val = 0; val < N; val++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpInVectorRCV(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpInVectorRVC(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpInVectorCRV(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int val = 0; val < N; val++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpInVectorCVR(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpInVectorVCR(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int row = 0; row < N; row++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

void Multiplication::calcOmpInVectorVRC(std::vector<std::vector<int>>& mat1, std::vector<std::vector<int>>& mat2, std::vector<std::vector<int>>& mat3)
{
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int col = 0; col < N; col++)
			{
				mat3[row][col] += mat1[row][val] * mat2[val][col];
			}
		}
	}
}

#pragma endregion 

#pragma region 1D arrays

void Multiplication::calcSolo1DArrayRCV(int* mat1, int* mat2, int* mat3)
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcSolo1DArrayRVC(int* mat1, int* mat2, int* mat3)
{
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcSolo1DArrayCRV(int* mat1, int* mat2, int* mat3)
{
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcSolo1DArrayCVR(int* mat1, int* mat2, int* mat3)
{
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcSolo1DArrayVCR(int* mat1, int* mat2, int* mat3)
{
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcSolo1DArrayVRC(int* mat1, int* mat2, int* mat3)
{
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpOut1DArrayRCV(int* mat1, int* mat2, int* mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpOut1DArrayRVC(int* mat1, int* mat2, int* mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpOut1DArrayCRV(int* mat1, int* mat2, int* mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpOut1DArrayCVR(int* mat1, int* mat2, int* mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpOut1DArrayVCR(int* mat1, int* mat2, int* mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpOut1DArrayVRC(int* mat1, int* mat2, int* mat3)
{
#pragma omp parallel for shared(mat1, mat2, mat3)
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpMid1DArrayRCV(int* mat1, int* mat2, int* mat3)
{
	for (int row = 0; row < N; row++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int col = 0; col < N; col++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpMid1DArrayRVC(int* mat1, int* mat2, int* mat3)
{
	for (int row = 0; row < N; row++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int val = 0; val < N; val++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpMid1DArrayCRV(int* mat1, int* mat2, int* mat3)
{
	for (int col = 0; col < N; col++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int row = 0; row < N; row++)
		{
			for (int val = 0; val < N; val++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpMid1DArrayCVR(int* mat1, int* mat2, int* mat3)
{
	for (int col = 0; col < N; col++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int val = 0; val < N; val++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpMid1DArrayVCR(int* mat1, int* mat2, int* mat3)
{
	for (int val = 0; val < N; val++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int col = 0; col < N; col++)
		{
			for (int row = 0; row < N; row++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpMid1DArrayVRC(int* mat1, int* mat2, int* mat3)
{
	for (int val = 0; val < N; val++)
	{
#pragma omp parallel for shared(mat1, mat2, mat3)
		for (int row = 0; row < N; row++)
		{
			for (int col = 0; col < N; col++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpIn1DArrayRCV(int* mat1, int* mat2, int* mat3)
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int val = 0; val < N; val++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpIn1DArrayRVC(int* mat1, int* mat2, int* mat3)
{
	for (int row = 0; row < N; row++)
	{
		for (int val = 0; val < N; val++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int col = 0; col < N; col++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpIn1DArrayCRV(int* mat1, int* mat2, int* mat3)
{
	for (int col = 0; col < N; col++)
	{
		for (int row = 0; row < N; row++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int val = 0; val < N; val++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpIn1DArrayCVR(int* mat1, int* mat2, int* mat3)
{
	for (int col = 0; col < N; col++)
	{
		for (int val = 0; val < N; val++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int row = 0; row < N; row++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpIn1DArrayVCR(int* mat1, int* mat2, int* mat3)
{
	for (int val = 0; val < N; val++)
	{
		for (int col = 0; col < N; col++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int row = 0; row < N; row++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

void Multiplication::calcOmpIn1DArrayVRC(int* mat1, int* mat2, int* mat3)
{
	for (int val = 0; val < N; val++)
	{
		for (int row = 0; row < N; row++)
		{
#pragma omp parallel for shared(mat1, mat2, mat3)
			for (int col = 0; col < N; col++)
			{
				mat3[row * N + col] += mat1[row * N + val] * mat2[val * N + col];
			}
		}
	}
}

#pragma endregion 
