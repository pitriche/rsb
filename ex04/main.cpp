#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::string str;

	std::cout << (str = "ab&") << std::endl;
	print_truth_table(str);
	std::cout << std::endl << (str = "AB|") << std::endl;
	print_truth_table(str);
	std::cout << std::endl << (str = "AB>") << std::endl;
	print_truth_table(str);
	std::cout << std::endl << (str = "A!B|") << std::endl;
	print_truth_table(str);

	std::cout << std::endl << (str = "AB|CD|=") << std::endl;
	print_truth_table(str);
	std::cout << std::endl << (str = "aBcD|&=") << std::endl;
	print_truth_table(str);
	std::cout << std::endl << (str = "ABC>!^") << std::endl;
	print_truth_table(str);
	std::cout << std::endl << (str = "ABB&|") << std::endl;
	print_truth_table(str);

	std::cout << std::endl << (str = "AA&BB|^") << std::endl;
	print_truth_table(str);
	std::cout << std::endl << (str = "AAAA&|>") << std::endl;
	print_truth_table(str);
	std::cout << std::endl << (str = "AB&C|") << std::endl;
	print_truth_table(str);
	return (0);
}