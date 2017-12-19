#pragma once
#include <stdio.h>
#include <random>
#include <iostream>
#include <time.h>
#include <fstream>
#include <thread>
#define N 2000
#define nFrom 1
#define nTo 2

class Multiplication
{
private:
	void generate2DMatrix(long* mat[N]);
	void print2DMatrix(long* mat[N]);
	void clear2DMatrix();
	int nThreads;
public:
	void calc2dArray();
	Multiplication(int nThreads) : nThreads(nThreads) {};
};