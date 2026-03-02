/*
Using dynamic arrays, implement a polynomial class with polynomial addition,
subtraction, and multiplication.
Discussion: A variable in a polynomial does nothing but act as a placeholder for
the coefficients. Hence, the only interesting thing about polynomials is the array
of coefficients and the corresponding exponent. Think about the polynomial
x*x*x + x + 1
Where is the term in x*x? One simple way to implement the polynomial class is to
use an array of type double to store the coefficients. The index of the array is the
exponent of the corresponding term. If a term is missing, then it simply has a zero
coefficient.
There are techniques for representing polynomials of high degree with many missing terms. 
These use so-called sparse matrix techniques. Unless you already know
these techniques, or learn very quickly, do not use these techniques.
Provide a default constructor, a copy constructor, and a parameterized constructor
that enables an arbitrary polynomial to be constructed.
Supply an overloaded operator = and a destructor.
Provide these operations:
polynomial + polynomial, constant + polynomial, polynomial + constant,
polynomial - polynomial, constant - polynomial, polynomial - constant.
polynomial * polynomial, constant * polynomial, polynomial * constant,
Supply functions to assign and extract coefficients, indexed by exponent.
Supply a function to evaluate the polynomial at a value of type double.
You should decide whether to implement these functions as members, friends, or
standalone functions.
*/

#include <iostream>
#include <string>

typedef double *DoublePtr;

class Polynomial
{
public:
	Polynomial() : coefficients(new double[1]{ 0.0 }), degree(0) {};
	Polynomial(int polynomial, int degree);
	friend std::istream& operator >>(std::istream& inputStream, Polynomial& myPolynomial); 
private:
	DoublePtr coefficients;
	int degree;
};

int main( )
{
	std::cout << '\n';
	return 0;
}

int inputValidation();

Polynomial::Polynomial(int polynomial, const int degree)
{
	coefficients = new double[degree];
	for (int idx = 0; idx <= degree; idx++)
		coefficients[idx] = polynomial[idx];
}

std::istream& operator >>(std::istream& inputStream, Polynomial& myPolynomial)
{
	// e.g. Enter degree: 3
	//		Enter coefficients(from x^3 to x^0) : 3 0 0 -1
	int degree;
	std::cout << "Enter degree:\n";
	inputStream >> degree; 
	
	// Allocate dynamic array for coefficients
	DoublePtr temp = new double[degree + 1];
	std::cout << "Enter coefficients (from x^" << degree << " to x^0):\n";
	for (int idx = degree; idx >= 0; --idx)
		inputStream >> temp[idx];
	
	// Deallocate old dynamic array set up with default constructo
	delete [] myPolynomial.coefficients;
	// Shallow copy of the pointer temp (point to the same address) 
	myPolynomial.coefficients = temp;
	myPolynomial.degree = degree;

	return inputStream;
}

int inputValidation()
{
	int number;
	while (true)
	{
		if (!(std::cin >> number))
		{
			std::cout << "Wrong input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return number;
	}
}
