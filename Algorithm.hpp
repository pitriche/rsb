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

/* initial parsing phase, caps all letters */
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
































/* push not operators to the basic operands */





/* ########################################################################## */
/* #####################	Expressions refining		##################### */
/* ########################################################################## */

enum	e_operation
{
	None,	/* to facilitate error detection */
	And,
	Or,
	Xor,
	Equal,
	Imply,
	Letter
};

struct	Oper
{
	e_operation	op;
	bool		neg;	/* not, because it's a keyword... */

	char		letter;
	Oper		*a;
	Oper		*b;

/* -------------------------------------------------------------------------- */

	Oper(std::string &str) : op(None), neg(false), a(0), b(0)
	{
		// std::cout << "New operator on ["<<str<<"]\n";
		while (str.size() && str[0] == '!')
		{
			neg ^= 1;
			str.erase(0, 1);
		}
		if (!str.size())
			throw std::logic_error("Invalid expression");
		switch (str[0])
		{
			case '&' : this->op = And; break;
			case '|' : this->op = Or; break;
			case '^' : this->op = Xor; break;
			case '=' : this->op = Equal; break;
			case '>' : this->op = Imply; break;
			default :
				this->op = Letter;
				this->letter = str[0];
				break;
		}
		str.erase(0, 1);
		if (this->op != Letter)
		{
			a = new Oper(str);
			b = new Oper(str);
		}
	}

	Oper(const Oper &src) : op(src.op), neg(src.neg), letter(src.letter)
	{
		if (src.a)
			this->a = new Oper(*src.a);
		if (src.b)
			this->b = new Oper(*src.b);
	}

	~Oper(void)
	{
		if (a)
			delete this->a;
		if (b)
			delete this->b;
	}

	/* shift all operators to And and OR */
	void	normal_form(void)
	{
		Oper	*tmp_a;
		Oper	*tmp_b;
		std::string	str;

		if (this->op == Letter)
			return ;
		if (this->op == And || this->op == Or)
		{
			this->a->normal_form();
			this->b->normal_form();
			return ;
		}
		if (this->op == Imply) /* AB> <=> A!B^ */
		{
			this->op = Or;
			this->b->neg ^= 1;
			this->a->normal_form();
			this->b->normal_form();
			return ;
		}

		tmp_a = new Oper(*this->a);
		tmp_b = new Oper(*this->b);
		this->a->a = tmp_a;
		this->a->b = tmp_b;
		this->b->a = new Oper(*tmp_a);
		this->b->b = new Oper(*tmp_b);
		this->a->op = And;
		this->b->op = And;
		this->a->neg = false;
		this->b->neg = false;
		if (this->op == Xor) /* AB^ <=> A!B&AB!&| */
		{
			this->a->b->neg ^= 1;
			this->b->a->neg ^= 1;
		}
		else if (this->op == Equal) /* AB= <=> AB&A!B!&| */
		{
			this->a->a->neg ^= 1;
			this->a->b->neg ^= 1;
		}
		this->op = Or;

		this->a->normal_form();
		this->b->normal_form();
	}

	/* shift all operators to And, must be normal form (only And and OR) */
	void	conjunctive_form(void)
	{
		Oper	*tmp_a;
		Oper	*tmp_b;
		std::string	str;

		if (this->op == Letter)
			return ;
		if (this->op == And || this->op == Or)
		{
			this->a->normal_form();
			this->b->normal_form();
			return ;
		}
		if (this->op == Imply) /* AB> <=> A!B^ */
		{
			this->op = Or;
			this->b->neg ^= 1;
			this->a->normal_form();
			this->b->normal_form();
			return ;
		}

		tmp_a = new Oper(*this->a);
		tmp_b = new Oper(*this->b);
		this->a->a = tmp_a;
		this->a->b = tmp_b;
		this->b->a = new Oper(*tmp_a);
		this->b->b = new Oper(*tmp_b);
		this->a->op = And;
		this->b->op = And;
		this->a->neg = false;
		this->b->neg = false;
		if (this->op == Xor) /* AB^ <=> A!B&AB!&| */
		{
			this->a->b->neg ^= 1;
			this->b->a->neg ^= 1;
		}
		else if (this->op == Equal) /* AB= <=> AB&A!B!&| */
		{
			this->a->a->neg ^= 1;
			this->a->b->neg ^= 1;
		}
		this->op = Or;

		this->a->normal_form();
		this->b->normal_form();
	}

	/* push NOT operators to letters */
	void	push_not(void)
	{
		if (this->op == Letter)
			return ;
		if (this->neg)
		{
			this->neg = false;
			this->a->neg ^= 1;
			this->b->neg ^= 1;
			if (this->op == Or)
				this->op = And;
			else
				this->op = Or;
		}
		this->a->push_not();
		this->b->push_not();
	}
};


void	print_Node(const Oper &node, unsigned tab)
{
	for (unsigned i = 0; i < tab; ++i)
		std::cout << ' ';

	if (node.neg)
		std::cout << '!';
	if (node.op == Letter)
		std::cout << node.letter << '\n';
	else
	{
		if (node.op == And) std::cout << '&';
		if (node.op == Or) std::cout << '|';
		if (node.op == Xor) std::cout << '^';
		if (node.op == Equal) std::cout << '=';
		if (node.op == Imply) std::cout << '>';
		std::cout << '\n';
		print_Node(*node.a, tab + 2);
		print_Node(*node.b, tab + 2);
	}
}

void	string_Node(const Oper &node, std::string &str)
{
	if (node.neg)
		str.insert(str.begin(), '!');
	if (node.op == Letter)
		str.insert(str.begin(), node.letter);
	else
	{
		if (node.op == And) str.insert(str.begin(), '&');
		if (node.op == Or) str.insert(str.begin(), '|');
		if (node.op == Xor) str.insert(str.begin(), '^');
		if (node.op == Equal) str.insert(str.begin(), '=');
		if (node.op == Imply) str.insert(str.begin(), '>');
		string_Node(*node.a, str);
		string_Node(*node.b, str);
	}
}

std::string	negation_normal_form(std::string str)
{
	std::string	res;
	Oper		*expr;

	vars_in_eval(str);	/* caps all letters */
	res = str;
	str.clear();
	for (unsigned i = res.size(); i > 0; --i)	/* invert the string */
		str.push_back(res[i - 1]);

	expr = new Oper(str);	/* construct tree */

	expr->normal_form();
	expr->push_not();
	res.clear();
	string_Node(*expr, res);
	return (res);
}

std::string	conjunctive_normal_form(std::string str)
{
	std::string	res;
	Oper		*expr;

	vars_in_eval(str);	/* caps all letters */
	res = str;
	str.clear();
	for (unsigned i = res.size(); i > 0; --i)	/* invert the string */
		str.push_back(res[i - 1]);

	expr = new Oper(str);	/* construct tree */

	expr->normal_form();
	expr->conjunctive_form();
	expr->push_not();
	
	res.clear();
	string_Node(*expr, res);
	return (res);
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
