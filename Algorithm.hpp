#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include <iostream>	/* logic_error */
# include <stack>		/* stack */
# include <array>		/* array */
# include <vector>		/* vector */

/* ########################################################################## */
/* #####################		Math utility			##################### */
/* ########################################################################## */

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
/* #####################			Binary				##################### */
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
/* #####################			Expressions			##################### */
/* ########################################################################## */

/* what the stack function pop SHOULD be */
template <typename T>
T	pop(std::stack<T> &stk)
{
	T	tmp;

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

bool	eval_formula(const std::string &str)
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

/* initial parsing phase */
unsigned	vars_in_eval(std::string &str)
{
	unsigned			tmp;
	unsigned			variables;

	variables = 0;
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
	return (variables);
}

void	print_truth_table(std::string str)
{
	std::stack<bool>	stk;
	unsigned			variables;

	variables = vars_in_eval(str);

	/* header print */
	std::cout << "| ";
	for (char c = 'A'; c < (char)variables + 'A'; ++c)
		std::cout << c << " | ";
	std::cout << "= |" << std::endl << "|";
	for (unsigned c = 0; c < variables + 1; ++c)
		std::cout << "---|";
	std::cout << std::endl;

	for (unsigned bits = 0; bits < power(2U, variables); ++bits)
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

bool	sat(std::string str)
{
	std::stack<bool>	stk;
	unsigned			variables;

	variables = vars_in_eval(str);

	for (unsigned bits = 0; bits < power(2U, variables); ++bits)
	{
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
		if (pop(stk))
			return (true);
		while (stk.size() > 0)
			stk.pop();
	}
	return (false);
}

/* ########################################################################## */
/* #####################		Set Expression			##################### */
/* ########################################################################## */

inline bool			set_contains(const std::vector<int> &set, int i)
{
	for (int nb : set)
		if (nb == i)
			return (true);
	return (false);
}

/* remove duplicates */
std::vector<int>	&set_clean(std::vector<int> &set)
{
	std::vector<int>	unique;

	for (unsigned i = 0; i < set.size(); ++i)
		if (!set_contains(unique, set[i]))
			unique.push_back(set[i]);
	set = unique;
	return (set);
}

/* ########################################################################## */

/* set union */
std::vector<int>	set_or(std::vector<int> set1,
	const std::vector<int> &set2)
{
	set1.insert(set1.end(), set2.begin(), set2.end());
	return (set_clean(set1));
}

/* set intersection */
std::vector<int>	set_and(const std::vector<int> &set1,
	const std::vector<int> &set2)
{
	std::vector<int>	res;

	for (int nb : set1)
		if (set_contains(set2, nb))
			res.push_back(nb);
	return (set_clean(res));
}

/* symetric difference, exclusive disjunction */
std::vector<int>	set_xor(const std::vector<int> &set1,
	const std::vector<int> &set2)
{
	std::vector<int>	res;

	for (int nb : set1)
		if (!set_contains(set2, nb))
			res.push_back(nb);
	for (int nb : set2)
		if (!set_contains(set1, nb))
			res.push_back(nb);
	return (set_clean(res));
}

/* NOR = XOR with superset */
std::vector<int>	set_not(const std::vector<int> &set,
	const std::vector<int> &superset)
{ return (set_xor(set, superset)); }

/* logical equivalence */
std::vector<int>	set_eq(const std::vector<int> &set1,
	const std::vector<int> &set2, const std::vector<int> &superset)
{
	std::vector<int>	not12;

	not12 = set_and(set_not(set1, superset), set_not(set2, superset));
	return (set_or(set_and(set1, set2), not12));
}

/* material condition */
std::vector<int>	set_imply(const std::vector<int> &set1,
	const std::vector<int> &set2, const std::vector<int> &superset)
{ return (set_or(set_not(set1, superset), set2)); }

/* ########################################################################## */

std::vector<int>	eval_set(std::string str,
	std::vector<std::vector<int>> sets)
{
	std::stack<std::vector<int>>	stk;
	std::vector<int>				superset;
	unsigned						set_nb;

	/* check for str/sets match and get superset */
	set_nb = vars_in_eval(str);
	if (set_nb > sets.size())
		throw std::logic_error("Mismatched set and expression");
	for (unsigned int i = 0; i < set_nb; ++i)
		superset = set_or(superset, sets[i]);
	for (char c : str)
		switch (c)
		{
			case 'A' ... 'Z' : stk.push(sets[c - 'A']);	break;
			case '!' : stk.push(set_not(pop(stk), superset)); break;
			case '&' : stk.push(set_and(pop(stk), pop(stk))); break;
			case '|' : stk.push(set_or(pop(stk), pop(stk))); break;
			case '=' : stk.push(set_eq(pop(stk), pop(stk), superset)); break;
			case '^' : stk.push(set_xor(pop(stk), pop(stk))); break;
			case '>' : stk.push(set_imply(pop(stk), pop(stk), superset)); break;
		}
	return (stk.top());
}

/* ########################################################################## */
/* #####################			Misc				##################### */
/* ########################################################################## */

std::vector<std::vector<int>>	powerset(const std::vector<int> &set)
{
	std::vector<std::vector<int>>	res;

	res.resize(power(2, set.size()));
	for (unsigned bits = 0; bits < res.size(); ++bits)
		for (unsigned i = 0; i < set.size(); ++i)
			if (bit(bits, i))
				res[bits].push_back(set[i]);
	return (res);
}

double							map(unsigned short x, unsigned short y)
{
	unsigned long	res;

	res = (unsigned)x | ((unsigned)y << 16);
	return (*(double *)(&res));
}

std::array<unsigned short, 2>	reverse_map(double n)
{
	std::array<unsigned short, 2>	res;
	unsigned long					decode;

	decode = *(unsigned long *)(&n);
	res[0] = decode & 0xffffU;
	res[1] = (decode >> 16) & 0xffffU;
	return (res);
}

#endif
