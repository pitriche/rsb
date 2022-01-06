#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include <iostream>	/* logic_error */
# include <stack>		/* stack */

template <typename T>
T	square(T scalar) { return (scalar * scalar); }

template <typename T>
T	abs(T scalar)
{
	if (scalar >= (T)0)
		return (scalar);
	return (scalar * (T)(-1));
}

template <typename T>
T	power(T scalar, int pow)
{
	T	mult;

	if (pow == 0)
		return ((T)1);
	if (pow < 0)
		return ((T)1 / power(scalar, abs(pow)));
	mult = scalar;
	for (int i = 1; i < pow; ++i)
		scalar = scalar * mult;
	return (scalar);
}

/* Babylonian Method with fermi estimate */
template <typename T>
T	sqrt(T scalar)
{
	const static float	steps =	15;
	T					res;
	int					estimate;

	if (scalar < (T)0)
		throw std::logic_error("Square root on negative number isn't a real "
		"number");
	estimate = 0;
	if (scalar >= 1)
		while (power(1000.0, estimate) < scalar)
			++estimate;
	else
		while (power(1000.0, estimate) > scalar)
			--estimate;
	res = power(1000.0, estimate / 2);
	for (unsigned i = 0; i < steps; ++i)
		res = (res + (scalar / res)) / 2;
	return (res);
}

/* ########################################################################## */

/* T is for integers, undefined behavior on other data types */
template <typename T>
T	adder(T n1, T n2)
{
	bool	carry;
	bool	bit1;
	bool	bit2;
	T		res;

	res = (T)0;
	carry = 0;
	for (unsigned bit = 0; bit < (sizeof(T) << 3); ++bit)
	{
		bit1 = (n1 >> bit) & 0x1;
		bit2 = (n2 >> bit) & 0x1;
		res |= (T)(bit1 ^ bit2 ^ carry) << bit;
		carry = ((bit1 ^ bit2) & carry) | (bit1 & bit2);
	}
	return (res);
}

/* operator NOT, equivalent of ~ */
template <typename T>
T	invert(T n)
{
	T	res;

	res = (T)0;
	for (unsigned bit = 0; bit < (sizeof(T) << 3); ++bit)
		res |= (T)(((n >> bit) & 0x1) ^ 1) << bit;
	return (res);
}

/* transform number into C2 negative number */
template <typename T>
T	negative(T n) { return (adder(invert(n), (T)1)); }

template <typename T>
T	subber(T n1, T n2) { return (adder(n1, negative(n2))); }

template <typename T>
T	multiplier(T n1, T n2)
{
	T		res;

	res = (T)0;
	for (unsigned bit = 0; bit < (sizeof(T) << 3); ++bit)
		if ((n1 >> bit) & 0x1)
			res = adder(res, n2 << bit);
	return (res);
}

template <typename T>
T	gray_code(T n) { return (n ^ (n >> 1)); }

/* ########################################################################## */

/* what the stack function pop SHOULD be */
bool	pop(std::stack<bool> &stk)
{
	bool	tmp;

	if (stk.empty())
		throw std::logic_error("Invalid expression");
	tmp = stk.top();
	stk.pop();
	return (tmp);
}

/* /!\ LSB FIRST /!\ */
/* extract the Nth bit of any sized integer, starting 0, without protection ! */
template <typename T>
bool	bit(T number, unsigned bit)
{ return ((number >> bit) & 0x1); }

bool	eval_formula(std::string str)
{
	std::stack<bool>	stk;

	for (char c : str)
		switch (c)
		{
			case '0' : stk.push(false); break;
			case '1' : stk.push(true); break;

			case '!' : stk.push(!pop(stk)); break;
			case '&' : stk.push(pop(stk) & pop(stk)); break;
			case '|' : stk.push(pop(stk) | pop(stk)); break;
			case '=' : stk.push(pop(stk) == pop(stk)); break;
			case '^' : stk.push(pop(stk) ^ pop(stk)); break;
			case '>' : stk.push(!pop(stk) | pop(stk)); break;

			default : throw std::logic_error("Invalid character");
		}
	return (stk.top());
}

void	print_truth_table(std::string str)
{
	std::stack<bool>	stk;
	unsigned			variables;
	unsigned			tmp;

	variables = 0;
	/* initial parsing phase */
	for (char &c : str)
		if (isalpha(c))
		{
			c = toupper(c);
			tmp = (unsigned)(c - 'A');
			if (tmp > variables)
				throw std::logic_error("Invalid letter order");
			else if (tmp == variables)
				++variables;
		}
		else if (c != '!' && c != '&' && c != '|' && c != '=' && c != '^' &&
			c != '>')
			throw std::logic_error("Invalid character");
	if (variables == 0)
		throw std::logic_error("Invalid expression");

	/* header print */
	std::cout << "| ";
	for (char c = 'A'; c < (char)variables + 'A'; ++c)
		std::cout << c << " | ";
	std::cout << "= |" << std::endl << "|";
	for (unsigned c = 0; c < variables + 1; ++c)
		std::cout << "---|";
	std::cout << std::endl;
	

	for (unsigned bits = 0; bits < power(2, variables); ++bits)
	{
		/* input bits print */
		std::cout << "| ";
		for (unsigned b = 1; b <= variables; ++b)
			std::cout << bit(bits, variables - b) << " | ";
		for (char c : str)
			switch (c)
			{
				case 'A' ... 'Z' :
					/* '@' is before 'A' to make c - '@' start by 1 */
					stk.push(bit(bits, variables - (c - '@')));
					break;

				case '!' : stk.push(!pop(stk)); break;
				case '&' : stk.push(pop(stk) & pop(stk)); break;
				case '|' : stk.push(pop(stk) | pop(stk)); break;
				case '=' : stk.push(pop(stk) == pop(stk)); break;
				case '^' : stk.push(pop(stk) ^ pop(stk)); break;
				case '>' : stk.push(!pop(stk) | pop(stk)); break;
			}
		std::cout << pop(stk) << " |" << std::endl;

		while (stk.size() > 0)
			stk.pop();
	}

}

/* ########################################################################## */



#endif
