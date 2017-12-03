//
// Created by kex on 3.12.17.
//

#ifndef MULTIPLICATIONMPI_MULTIPLICATION_H
#define MULTIPLICATIONMPI_MULTIPLICATION_H


#include <stdio.h>
#include <random>
#include <iostream>
#include <time.h>
#include <fstream>
#include <mpi.h>

#define N 200
#define nFrom 0
#define nTo 50
#define rpc 0
#define rcp 1
#define crp 2
#define cpr 3
#define prc 4
#define pcr 5

class Multiplication {
private:
    void generate2DMatrix();
    void print2DMatrix();
    void clear2DMatrix();

    void rpc2d();
    void rcp2d();
    void crp2d();
    void cpr2d();
    void prc2d();
    void pcr2d();

    std::ofstream fs;
    int typeCycle;
    int taskid = 0;



public:
    void initializeM();
    void finalizeM();
    void calc2dArray(int task, std::string textCycle);
};


#endif //MULTIPLICATIONMPI_MULTIPLICATION_H
