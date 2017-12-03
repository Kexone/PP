#include <stdio.h>
#include <iostream>
#include "multiplication.h"
#include "multiplicationOneArray.h"
#include <mpi.h>



int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);

    Multiplication mp;

    mp.initializeM();
    mp.calc2dArray(0, "rpc");
    mp.calc2dArray(1, "rcp");
    mp.calc2dArray(2, "crp");
    mp.calc2dArray(3, "cpr");
    mp.calc2dArray(4, "prc");
    mp.calc2dArray(5, "pcr");
    mp.finalizeM();

    MultiplicationOneArray mp1;

    mp1.initializeM();
    mp1.calc1dArray(0, "rpc");
    mp1.calc1dArray(1, "rcp");
    mp1.calc1dArray(2, "crp");
    mp1.calc1dArray(3, "cpr");
    mp1.calc1dArray(4, "prc");
    mp1.calc1dArray(5, "pcr");
    MPI_Finalize();

}
