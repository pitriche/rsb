#include "Algorithm.hpp"
#include <iostream>

std::ostream	&operator<<(std::ostream &lhs, const std::vector<std::vector<int>> &rhs)
{
	lhs << "{" << std::endl;
	for (const std::vector<int> &set : rhs)
	{
		lhs << "{";
		for (unsigned i = 0; i < set.size(); ++i)
			lhs << set[i] << (i + 1 < set.size() ? ", " : "");
		lhs << "}" << std::endl;
	}
	lhs << "}" << std::endl;
	return (lhs);
}

int	main()
{
	std::cout << "powerset ({}) " << powerset({}) << std::endl;
	std::cout << "powerset ({1}) " << powerset({1}) << std::endl;
	std::cout << "powerset ({1, 10}) " << powerset({1, 10}) << std::endl;
	std::cout << "powerset ({1, 2, 4, 5}) " << powerset({1, 2, 4, 5}) << std::endl;
	// std::cout << powerset({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) << std::endl;
	return (0);
}