//
// Created by kex on 3.12.17.
//

#include "multiplicationOneArray.h"
std::random_device rd1;
std::mt19937 gen1(rd1());
std::uniform_int_distribution<> dis1(nFrom, nTo);
int a1[N*N],b1[N*N],c1[N*N];

void MultiplicationOneArray::generate1dMatrix() {
    for (int row = 0; row < N * N; row++)
    {
        a1[row] = dis1(gen1);
        b1[row] = dis1(gen1);
    }
}

void MultiplicationOneArray::clear1dMatrix() {
    for (int row = 0; row < N * N; row++)
    {
        c1[row] = 0;
    }
}
void MultiplicationOneArray::calc1dArray(int task, std::string textCycle) {

    int numtasks,taskid,numworkers,source,dest,offset,row,col,val;
    MPI_Status status;

    clock_t t;
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    numworkers = numtasks;

    if (taskid == 0) {
        if(task == 0)
            std::cout << "MATRIX MULTIPLICATION 1D ARRAYS:\n";

        generate1dMatrix();
        t = clock();

        offset = 0;
        typeCycle = task;
        for (dest=1; dest<numworkers; dest++)
        {
            MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&numworkers, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&a1[offset], numworkers*N, MPI_DOUBLE,dest,1, MPI_COMM_WORLD);
            MPI_Send(&b1, N*N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
            offset = offset + numworkers;
        }

        for (row=1; row<numworkers; row++)
        {
            source = row;
            MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&numworkers, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&c1[offset], numworkers*N, MPI_DOUBLE, source, 2, MPI_COMM_WORLD, &status);
        }

        t = clock() - t;
        clear1dMatrix();
        std::cout << textCycle << " time " << static_cast<float>(t)/ CLOCKS_PER_SEC << std::endl;
        fs << static_cast<float>(t)/ CLOCKS_PER_SEC << " & ";


    }

    if (taskid > 0) {
        source = 0;
        MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&numworkers, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&a1, numworkers*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&b1, N*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);

        switch(typeCycle){
            case rpc:
                rpc1d();
                break;
            case rcp:
                rcp1d();
                break;
            case crp:
                crp1d();
                break;
            case cpr:
                cpr1d();
                break;
            case prc:
                prc1d();
                break;
            case pcr:
                pcr1d();
                break;
        }

        MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&numworkers, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&c1, numworkers*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }


}

void MultiplicationOneArray::print1dMatrix() {
    printf("Here is the a matrix:\n");
    for (long row = 0; row < N; row++)
    {
        std::cout << "| ";
        for (long col = N * row; col < N * row + N; col++)
        {
            std::cout << a1[col] << " ";
        }
        std::cout << " |" << std::endl;
    }
    printf("Here is the b matrix:\n");
    for (long row = 0; row < N; row++)
    {
        std::cout << "| ";
        for (long col = N * row; col < N * row + N; col++)
        {
            std::cout << b1[col] << " ";
        }
        std::cout << " |" << std::endl;
    }
    printf("Here is the result matrix:\n");
    for (long row = 0; row < N; row++)
    {
        std::cout << "| ";
        for (long col = N * row; col < N * row + N; col++)
        {
            std::cout << c1[col] << " ";
        }
        std::cout << " |" << std::endl;
    }
}

void MultiplicationOneArray::rcp1d() {
    for (long row = 0; row < N; row++) {
        for (long col = 0; col < N; col++) {
            for (long val = 0; val < N; val++) {
                c1[row * N + col] += a1[row * N + val] * b1[val * N + col];
            }
        }
    }
}

void MultiplicationOneArray::rpc1d() {
    for (long row = 0; row < N; row++) {
        for (long val = 0; val < N; val++) {
            for (long col = 0; col < N; col++) {
                c1[row * N + col] += a1[row * N + val] * b1[val * N + col];
            }
        }
    }
}

void MultiplicationOneArray::crp1d() {
    for (long col = 0; col < N; col++) {
        for (long row = 0; row < N; row++) {
            for (long val = 0; val < N; val++) {
                c1[row * N + col] += a1[row * N + val] * b1[val * N + col];
            }
        }
    }
}

void MultiplicationOneArray::cpr1d() {
    for (long col = 0; col < N; col++) {
        for (long val = 0; val < N; val++) {
            for (long row = 0; row < N; row++) {
                c1[row * N + col] += a1[row * N + val] * b1[val * N + col];
            }
        }
    }
}

void MultiplicationOneArray::prc1d() {
    for (long val = 0; val < N; val++) {
        for (long row = 0; row < N; row++) {
            for (long col = 0; col < N; col++) {
                c1[row * N + col] += a1[row * N + val] * b1[val * N + col];
            }
        }
    }
}

void MultiplicationOneArray::pcr1d() {
    for (long val = 0; val < N; val++) {
        for (long col = 0; col < N; col++) {
            for (long row = 0; row < N; row++) {
                c1[row * N + col] += a1[row * N + val] * b1[val * N + col];
            }
        }
    }
}

void MultiplicationOneArray::initializeM() {
    fs.open("results1DArray.txt");
    fs << " & row\_col\_pos" << " & row\_pos\_col" << " & col\_row\_pos" << " & col\_pos\_row " << " & pos\_row\_col" << " & pos\_col\_row"  << std::endl;


}

void MultiplicationOneArray::finalizeM() {
    fs.close();
}

