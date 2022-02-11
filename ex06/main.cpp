#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::string	tmp;


	tmp = "aBcD|&=";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB|CD|=";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "A!!!!!!!";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "ABC&D|^";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "ABC>!=";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";

	// tmp = "AB|";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "AB&";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "AB=";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "AB^";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "AB>";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";

	// tmp = "AB&!";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "AB|!";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "AB|C&!";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";

	// tmp = "AB|!C!&";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "AB&C&D&";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	// tmp = "ABCD&|&";
	// std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	return (0);
}