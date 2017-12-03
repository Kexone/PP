//
// Created by kex on 3.12.17.
//

#include "multiplication.h"
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(nFrom, nTo);
int a[N][N],b[N][N],c[N][N];

void Multiplication::generate2DMatrix() {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            a[i][j]= dis(gen);
            b[i][j]= dis(gen);
        }
    }
}

void Multiplication::clear2DMatrix() {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            c[i][j]= 0;
        }
    }
}
void Multiplication::calc2dArray(int task, std::string textCycle) {

    int numtasks,taskid,numworkers,source,dest,offset,row,col,val;
    MPI_Status status;

    clock_t t;
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    numworkers = numtasks;

    if (taskid == 0) {
        if(task == 0)
            std::cout << "MATRIX MULTIPLICATION 2D ARRAYS:\n";


        generate2DMatrix();
        t = clock();

        offset = 0;
        typeCycle = task;
        for (dest=1; dest<numworkers; dest++)
        {
            MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&numworkers, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&a[offset][0], numworkers*N, MPI_DOUBLE,dest,1, MPI_COMM_WORLD);
            MPI_Send(&b, N*N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
            offset = offset + numworkers;
        }

        for (row=1; row<numworkers; row++)
        {
            source = row;
            MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&numworkers, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&c[offset][0], numworkers*N, MPI_DOUBLE, source, 2, MPI_COMM_WORLD, &status);
        }

        t = clock() - t;
        clear2DMatrix();
        std::cout << textCycle << " time " << static_cast<float>(t)/ CLOCKS_PER_SEC << std::endl;
        fs << static_cast<float>(t)/ CLOCKS_PER_SEC << " & ";


    }

    if (taskid > 0) {
        source = 0;
        MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&numworkers, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&a, numworkers*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, N*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);

        switch(typeCycle){
            case rpc:
                rpc2d();
                break;
            case rcp:
                rcp2d();
                break;
            case crp:
                crp2d();
                break;
            case cpr:
                cpr2d();
                break;
            case prc:
                prc2d();
                break;
            case pcr:
                pcr2d();
                break;
        }

        MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&numworkers, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&c, numworkers*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }


}

void Multiplication::print2DMatrix() {
    printf("Here is the a matrix:\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%d   ", a[row][col]);
        printf("\n");
    }
    printf("Here is the b matrix:\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%d   ", b[row][col]);
        printf("\n");
    }
    printf("Here is the result matrix:\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%d   ", c[row][col]);
        printf("\n");
    }
}

void Multiplication::rcp2d() {
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            for (int val = 0; val < N; val++)
            {
                c[row][col] +=  a[row][val] * b[val][col];
            }
        }
    }
}

void Multiplication::rpc2d() {
    for (int row = 0; row < N; row++)
    {
        for (int val = 0; val < N; val++)
        {
            for (int col = 0; col < N; col++)
            {
                c[row][col] +=  a[row][val] * b[val][col];
            }
        }
    }
}

void Multiplication::crp2d() {
    for (int col = 0; col < N; col++)
    {
        for (int row = 0; row < N; row++)
        {
            for (int val = 0; val < N; val++)
            {
                c[row][col] +=  a[row][val] * b[val][col];
            }
        }
    }
}

void Multiplication::cpr2d() {
    for (int col = 0; col < N; col++)
    {
        for (int val = 0; val < N; val++)
        {
            for (int row = 0; row < N; row++)
            {
                c[row][col] +=  a[row][val] * b[val][col];
            }
        }
    }
}

void Multiplication::prc2d() {
    for (int val = 0; val < N; val++)
    {
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                c[row][col] +=  a[row][val] * b[val][col];
            }
        }
    }
}

void Multiplication::pcr2d() {
    for (int val = 0; val < N; val++)
    {
        for (int col = 0; col < N; col++)
        {
            for (int row = 0; row < N; row++)
            {
                c[row][col] +=  a[row][val] * b[val][col];
            }
        }
    }
}

void Multiplication::initializeM() {
    fs.open("results2DArray.txt");
    fs << " & row\_col\_pos" << " & row\_pos\_col" << " & col\_row\_pos" << " & col\_pos\_row " << " & pos\_row\_col" << " & pos\_col\_row"  << std::endl;


}

void Multiplication::finalizeM() {
    fs.close();
}


