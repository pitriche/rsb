#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::cout << "10 + 13 = " << adder(10, 13) << std::endl;
	std::cout << "10 + -3 = " << adder(10, -3) << std::endl;
	std::cout << "-10 + -13 = " << adder(-10, -13) << std::endl;
	std::cout << "2147483647 + -1 = " << adder(2147483647, -1) << std::endl;
	std::cout << "2147483647 + 1 = " << adder(2147483647, 1) << std::endl << std::endl;

	std::cout << "-2147483647 = " << negative(2147483647) << std::endl;
	std::cout << "-(-214000000007648) = " << negative(-214000000007648L) << std::endl;
	std::cout << "-(-2147483648) = " << negative((int)-2147483648) << std::endl;
	std::cout << "-0 = " << negative(0) << std::endl;
	std::cout << "-(-10) = " << negative(-10) << std::endl << std::endl;

	std::cout << "10 - 13 = " << subber(10, 13) << std::endl;
	std::cout << "10 - -3 = " << subber(10, -3) << std::endl;
	std::cout << "-10 - -13 = " << subber(-10, -13) << std::endl;
	std::cout << "2147483647 - -1 = " << subber(2147483647, -1) << std::endl;
	std::cout << "2147483647 - 1 = " << subber(2147483647, 1) << std::endl;
	return (0);
}