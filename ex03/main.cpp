#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::cout << "01& " << eval_formula("01&") << std::endl;
	std::cout << "01| " << eval_formula("01|") << std::endl;
	std::cout << "01> " << eval_formula("01>") << std::endl;
	std::cout << "10> " << eval_formula("10>") << std::endl;
	std::cout << "1011||= " << eval_formula("1011||=") << std::endl;
	std::cout << "1011|&= " << eval_formula("1011|&=") << std::endl << std::endl;

	std::cout << "101>!^ " << eval_formula("101>!^") << std::endl;

	return (0);
}