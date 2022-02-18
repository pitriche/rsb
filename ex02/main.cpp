#include "Algorithm.hpp"
#include <iostream>

int	main()
{
	std::cout << "0 gray code -> " << gray_code((short)0) << std::endl;
	std::cout << "1 gray code -> " << gray_code((short)1) << std::endl;
	std::cout << "2 gray code -> " << gray_code((int)2) << std::endl;
	std::cout << "3 gray code -> " << gray_code((int)3) << std::endl;
	std::cout << "4 gray code -> " << gray_code((long)4) << std::endl;
	std::cout << "5 gray code -> " << gray_code((long)5) << std::endl;
	std::cout << "6 gray code -> " << gray_code(6) << std::endl;
	std::cout << "7 gray code -> " << gray_code(7) << std::endl;
	std::cout << "8 gray code -> " << gray_code(8) << std::endl;
	return (0);
}

/*
0001
0011
0010
0110
0111
0101
0100
1100
*/