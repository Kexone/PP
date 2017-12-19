#include "multiplication.h"
#include <mutex>

std::mutex barrier;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(nFrom, nTo);

void Multiplication::generate2DMatrix(long* mat[N])
{
	for (long row = 0; row < N; row++)
	{
		for (long col = 0; col < N; col++)
		{
			mat[row][col] = dis(gen);
		}
	}
}

void Multiplication::print2DMatrix(long* mat[N])
{
	for (long row = 0; row < N; row++)
	{
		std::cout << "| ";
		for (long col = 0; col < N; col++)
		{
			std::cout << mat[row][col] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

void Multiplication::clear2DMatrix()
{
}

void Multiplication::calc2dArray()
{
	long** a = new long*[N];
	long** b = new long*[N];
	long** c = new long*[N];
	for (long row = 0; row < N; row++)
	{
		a[row] = new long[N];
		b[row] = new long[N];
		c[row] = new long[N];
		std::fill(c[row], c[row] + N, 0);
	}
	//generate2DMatrix(a);
	//generate2DMatrix(b);
	//std::cout << "Matrix A: " << std::endl;
	//print2DMatrix(a);
	//std::cout << "\nMatrix B: " << std::endl;
	//print2DMatrix(b);

	std::vector<std::thread> threads(nThreads);
	std::mutex m;
	//barrier.lock();
	unsigned long sum = 0;
	for (size_t t = 0; t < nThreads; ++t) {
		threads[t] = std::thread(std::bind(
			[&](const long start, const long end) {
			// Start each thread for different parts of the array
				unsigned long lSum = 0;
				for (int row = start; row < end; row++)
				{
					for (int col = 0; col < N; col++)
					{
						for (int val = 0; val < N; val++)
						{
							lSum++;
							c[row][col] += a[row][val] * b[val][col];
						}
					}
				}
				std::lock_guard<std::mutex> lock(m);
				sum += lSum;
		}, t * (N / nThreads), (t + 1 == nThreads) ? N : (t + 1) * (N / nThreads))
		);
	}
	//std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
	//barrier.unlock();
	// Wait for all threads to finish (join)
	for (auto &thread : threads) {
		thread.join();
	}
	//std::cout << "\nResult: " << std::endl;
//	print2DMatrix(c);
	std::cout << "\nOperations: " << sum << std::endl;

	for (size_t row = N; row > 0;)
	{
		delete[] a[--row];
		delete[] b[row];
		delete[] c[row];
	}
	delete[] a;
	delete[] b;
	delete[] c;
}