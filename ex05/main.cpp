#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::cout << "ab&" << std::endl;
	negation_normal_form("ab&");

	std::cout << std::endl << "AB|" << std::endl;
	negation_normal_form("AB|");

	std::cout << std::endl << "ABC&D|^" << std::endl;
	negation_normal_form("ABC&D|^");

	std::cout << std::endl << "AB&C|D^" << std::endl;
	negation_normal_form("AB&C|D^");

	std::cout << std::endl << "A!!!!" << std::endl;
	negation_normal_form("A!!!!");
	std::cout << std::endl << "A!!!!!!!" << std::endl;
	negation_normal_form("A!!!!!!!");

	// std::cout << std::endl << "AB|CD|=" << std::endl;
	// negation_normal_form("AB|CD|=");

	// std::cout << std::endl << "aBcD|&=" << std::endl;
	// negation_normal_form("aBcD|&=");

	// std::cout << std::endl << "ABC>!^" << std::endl;
	// negation_normal_form("ABC>!^");

	// std::cout << std::endl << "ABB&|" << std::endl;
	// negation_normal_form("ABB&|");

	// std::cout << std::endl << "AA&BB|^" << std::endl;
	// negation_normal_form("AA&BB|^");

	// std::cout << std::endl << "AAAA&|>" << std::endl;
	// negation_normal_form("AAAA&|>");

	// std::cout << std::endl << "AB&C|" << std::endl;
	// negation_normal_form("AB&C|");
	return (0);
}