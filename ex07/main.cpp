#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::cout << "sat ab& -> " << sat("ab&") << std::endl;
	std::cout << "sat AB| -> " << sat("AB|") << std::endl;
	std::cout << "sat AB|CD|= -> " << sat("AB|CD|=") << std::endl;
	std::cout << "sat aBcD|&= -> " << sat("aBcD|&=") << std::endl;
	std::cout << "sat ABC>!^ -> " << sat("ABC>!^") << std::endl;
	std::cout << "sat ABB&| -> " << sat("ABB&|") << std::endl;
	std::cout << "sat AA&BB|^ -> " << sat("AA&BB|^") << std::endl;
	std::cout << "sat AAAA&|> -> " << sat("AAAA&|>") << std::endl;
	std::cout << "sat AB&C| -> " << sat("AB&C|") << std::endl << std::endl;

	std::cout << "sat AA!& -> " << sat("AA!&") << std::endl;
	std::cout << "sat AA^ -> " << sat("AA^") << std::endl;
	std::cout << "sat AA| -> " << sat("AA|") << std::endl;
	return (0);
}