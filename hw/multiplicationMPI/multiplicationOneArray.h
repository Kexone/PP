//
// Created by kex on 3.12.17.
//

#ifndef MULTIPLICATIONMPI_MULTIPLICATIONONEARRAY_H
#define MULTIPLICATIONMPI_MULTIPLICATIONONEARRAY_H

#include <stdio.h>
#include <random>
#include <iostream>
#include <time.h>
#include <mpi.h>
#include <fstream>

#define N 200
#define nFrom 0
#define nTo 50
#define rpc 0
#define rcp 1
#define crp 2
#define cpr 3
#define prc 4
#define pcr 5
class MultiplicationOneArray {


    private:
        void generate1dMatrix();
        void print1dMatrix();
        void clear1dMatrix();

        void rpc1d();
        void rcp1d();
        void crp1d();
        void cpr1d();
        void prc1d();
        void pcr1d();

        std::ofstream fs;
        int typeCycle;




    public:
        void initializeM();
        void finalizeM();
        void calc1dArray(int task, std::string textCycle);

};


#endif //MULTIPLICATIONMPI_MULTIPLICATIONONEARRAY_H
