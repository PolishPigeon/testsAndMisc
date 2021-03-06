// bernoulli_distribution
#include <iostream>
#include <random>

int main()
{
	const int nrolls=10000;
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution distribution(0.5);
	
	int count=0;  // count number of trues
	
	for (int i=0; i<nrolls; ++i) if (distribution(gen)) ++count;
	
	std::cout << "bernoulli_distribution (0.5) x 10000:" << std::endl;
	std::cout << "true:  " << count << std::endl;
	std::cout << "false: " << nrolls-count << std::endl;
	
	return 0;
}
