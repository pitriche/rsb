#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::cout << "ab&" << std::endl;
	print_truth_table("ab&");

	std::cout << std::endl << "AB|" << std::endl;
	print_truth_table("AB|");

	std::cout << std::endl << "ABCD||=" << std::endl;
	print_truth_table("ABCD||=");

	std::cout << std::endl << "aBcD|&=" << std::endl;
	print_truth_table("aBcD|&=");

	std::cout << std::endl << "ABC>!^" << std::endl;
	print_truth_table("ABC>!^");

	std::cout << std::endl << "ABB&|" << std::endl;
	print_truth_table("ABB&|");

	std::cout << std::endl << "AA&BB|^" << std::endl;
	print_truth_table("AA&BB|^");

	std::cout << std::endl << "AAAA&|>" << std::endl;
	print_truth_table("AAAA&|>");

	std::cout << std::endl << "AB&C|" << std::endl;
	print_truth_table("AB&C|");
	return (0);
}