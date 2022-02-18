#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::cout << "map(0, 0) => " << map(0, 0) << std::endl;
	std::cout << "map(0, 10) => " << map(0, 10) << std::endl;
	std::cout << "map(10, 0) => " << map(10, 0) << std::endl;
	std::cout << "map(10, 100) => " << map(10, 100) << std::endl;
	std::cout << "map(65535U, 65535U) => " << map(65535U, 65535U) << std::endl;
	std::cout << "map(1, 0) == map(0, 1) -> " << (map(1, 0) == map(0, 1)) << std::endl;

	return (0);
}