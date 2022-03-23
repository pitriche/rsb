#include "Algorithm.hpp"
#include <iostream>

std::ostream	&operator<<(std::ostream &lhs, const std::vector<int> &rhs)
{
	lhs << "{";
	for (unsigned i = 0; i < rhs.size(); ++i)
		lhs << rhs[i] << (i + 1 < rhs.size() ? ", " : "");
	lhs << "}";
	return (lhs);
}

int	main()
{
	std::vector<int>	set1({1, 1, 1, 2, 3, 2, 1, 2, 1});
	std::vector<int>	set2({-1, 1, -1, 2, 3, 2, 1, 2, 1});
	std::vector<int>	set3({2, 4, 5});
	std::vector<int>	superset;

	std::cout << "set1 " << set_clean(set1) << std::endl;
	std::cout << "set2 " << set_clean(set2) << std::endl;
	std::cout << "set3 " << set3 << std::endl;
	superset = set_or(set_or(set1, set2), set3);
	std::cout << "superset " << superset << std::endl << std::endl;
	std::cout << "set2 or set3 " << set_or(set2, set3) << std::endl;
	std::cout << "set2 and set3 " << set_and(set2, set3) << std::endl;
	std::cout << "set2 xor set3 " << set_xor(set2, set3) << std::endl;
	std::cout << "Not set1 " << set_not(set1, superset) << std::endl << std::endl;
	std::cout << "set1 imply set3 " << set_imply(set3, set1, superset) << std::endl;
	std::cout << "set1 equal set3 " << set_eq(set1, set3, superset) << std::endl << std::endl << std::endl;

	std::cout << "ABC&& " << eval_set("ABC&&", {set1, set2, set3}) << std::endl;
	std::cout << "AA&BB|>C!C&| " << eval_set("AA&BB|>C!C&|", {set1, set2, set3}) << std::endl;
	std::cout << "A!A& " << eval_set("A!A&", {set1, set2, set3}) << std::endl;
	std::cout << "A! " << eval_set("A!", {set1, set2, set3}) << std::endl;

	return (0);
}