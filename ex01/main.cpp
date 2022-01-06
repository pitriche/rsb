#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::cout << "0 * 0 = " << multiplier(0, 0) << std::endl;
	std::cout << "1 * 1 = " << multiplier(1, 1) << std::endl;
	std::cout << "10 * 13 = " << multiplier(10, 13) << std::endl;
	std::cout << "10 * -3 = " << multiplier(10, -3) << std::endl;
	std::cout << "-10 * 3 = " << multiplier(-10, 3) << std::endl;
	std::cout << "-10 * -13 = " << multiplier(-10, -13) << std::endl;
	std::cout << "2147483647 * -1 = " << multiplier(2147483647, -1) << std::endl;
	std::cout << "2147483647 * 1 = " << multiplier(2147483647, 1) << std::endl;
	std::cout << "2147483647 * 2147483647 = " << multiplier(2147483647, 2147483647) << std::endl;
	std::cout << "2147483647 * -2147483648 = " << multiplier(2147483647, (int)-2147483648) << std::endl;
	std::cout << "-2147483648 * -2147483648 = " << multiplier((int)-2147483648, (int)-2147483648) << std::endl;

	// std::cout << std::endl << "Regular arythmetics:" << std::endl;
	// std::cout << "2147483647 * 2147483647 = " << (2147483647 * 2147483647) << std::endl;
	// std::cout << "2147483647 * -2147483648 = " << (2147483647 * (int)-2147483648) << std::endl;
	// std::cout << "-2147483648 * -2147483648 = " << ((int)-2147483648 * (int)-2147483648) << std::endl;
	return (0);
}