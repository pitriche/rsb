#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::string	tmp;

	tmp = "AB>";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "aBcD|&=";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB|CD|!=";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "A!!!!!!!";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "ABC&D|^";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "ABC>!=";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";

	tmp = "AB|";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB&";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB=";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB^";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB>";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";

	tmp = "AB&!";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB|!";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB|C&!";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";

	tmp = "AB|!C!&";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "AB&C&D&";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";
	tmp = "ABCD&|&";
	std::cout << tmp << std::endl << conjunctive_normal_form(tmp) << "\n\n";

	/* HIIIGHWAAAAY TOO THE */
	/* Testing zone */
	// std::cout << std::endl << (str = "AB|C&!") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "AB&!") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "AB|!") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "AB|!C!&") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "AB&C&D&") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "ABCD&|&") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));

	// std::cout << std::endl << (str = "AB>") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "aBcD|&=") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "AB|CD|!=") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "ABC&D|^") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	// std::cout << std::endl << (str = "ABC>!=") << std::endl;
	// print_truth_table(str);
	// print_truth_table(conjunctive_normal_form(str));
	return (0);
}