build:
mpic++ main.cpp multiplication.cpp multiplicationOneArray.cpp  -std=c++11

run with 4 threads:
mpirun -np 4 ./a.out
