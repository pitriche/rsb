#include "Algorithm.hpp"
#include <iostream>

std::ostream	&operator<<(std::ostream &lhs, const std::array<unsigned short, 2> &rhs)
{
	lhs << rhs[0] << ", " << rhs[1];
	return (lhs);
}

int	main()
{
	std::cout << "reverse_map(map(0, 0)) => " << reverse_map(map(0, 0)) << std::endl;
	std::cout << "reverse_map(map(0, 10)) => " << reverse_map(map(0, 10)) << std::endl;
	std::cout << "reverse_map(map(10, 0)) => " << reverse_map(map(10, 0)) << std::endl;
	std::cout << "reverse_map(map(10, 100)) => " << reverse_map(map(10, 100)) << std::endl;
	std::cout << "reverse_map(map(65535U, 65535U)) => " << reverse_map(map(65535U, 65535U)) << std::endl;
	std::cout << "reverse_map(0.4) => " << reverse_map(0.4) << std::endl;
	std::cout << "reverse_map(42.0) => " << reverse_map(42.0) << std::endl;
	return (0);
}