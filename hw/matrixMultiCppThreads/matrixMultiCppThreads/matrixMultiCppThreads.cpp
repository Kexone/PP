#include "multiplication.h"
#include <ctime>
int main()
{

	clock_t interval;
	for (int i = 1; i < 5; i++) {
		std::cout << "Calc with "<<i << " thread ";
		Multiplication mp = Multiplication(i);
		interval = clock();
		mp.calc2dArray();
		interval = clock() - interval;
		std::cout << " took " << static_cast<float>(interval) / CLOCKS_PER_SEC << std::endl;
	}
	std::cin.get();
    return 0;
}

