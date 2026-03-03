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
#include <cmath>

typedef double *DoublePtr;

constexpr double EPSILON = 1e-9;

class Polynomial
{
public:
	Polynomial() : coefficients(new double[1]{ 0.0 }), degree(0) {};
	Polynomial(double polynomial[], int degree);
	Polynomial(const Polynomial& myPolynomial);
	Polynomial& operator =(const Polynomial& myPolynomial);
	~Polynomial() { delete[] coefficients; }
	friend std::istream& operator >>(std::istream& inputStream, Polynomial& myPolynomial); 
	friend std::ostream& operator <<(std::ostream& outputStream, const Polynomial& myPolynomial);
private:
	DoublePtr coefficients;
	int degree;
};

int inputValidation();

int main( )
{
	Polynomial aPolynomial;
	std::cout << "Enter a polynomial:\n";
	std::cin >> aPolynomial;
	std::cout << aPolynomial << '\n';
	std::cout << '\n';
	return 0;
}

Polynomial& Polynomial::operator =(const Polynomial& myPolynomial)
{
	if (degree != myPolynomial.degree)
	{
		delete [] coefficients;
		coefficients = new double[myPolynomial.degree + 1];
		degree = myPolynomial.degree;
	}
	// coefficients = myPolynomial.coefficients; // wrong shallow copy
	// correct below: deep copy
	for (int idx = 0; idx <= degree; idx++)
		coefficients[idx] = myPolynomial.coefficients[idx];
	return *this;
}

Polynomial::Polynomial(const Polynomial& myPolynomial) : degree(myPolynomial.degree)
{
	coefficients = new double[degree + 1];
	for (int idx = 0; idx <= degree; idx++)
		coefficients[idx] = myPolynomial.coefficients[idx];
}

Polynomial::Polynomial(double polynomial[], const int degree)
{
	coefficients = new double[degree + 1];
	for (int idx = 0; idx <= degree; idx++)
		coefficients[idx] = polynomial[idx];
}

std::ostream& operator <<(std::ostream& outputStream, const Polynomial& myPolynomial)
{
	for (int idx = myPolynomial.degree; idx >= 0; idx--)
	{
		// if coefficient is 0, skip
		if (std::abs(myPolynomial.coefficients[idx]) < EPSILON)
			continue;
		if (idx != myPolynomial.degree && myPolynomial.coefficients[idx] > 0)
			outputStream << '+';
		outputStream << myPolynomial.coefficients[idx];

		if (idx != 0)
			outputStream << "x";
		if (idx != 0 && idx != 1)
			outputStream << '^' << idx;
	}
	return outputStream;
}

std::istream& operator >>(std::istream& inputStream, Polynomial& myPolynomial)
{
	// e.g. Enter degree: 3
	//		Enter coefficients(from x^3 to x^0) : 3 0 0 -1
	int degree;
	std::cout << "Enter degree:\n";
	inputStream >> degree; 
	
	// Allocate dynamic array for coefficients
	const DoublePtr temp = new double[degree + 1];
	std::cout << "Enter coefficients (from x^" << degree << " to x^0):\n";
	
	int idx = degree;
	while (idx >= 0)
	{
		inputStream >> temp[idx];
		// if highest degree coeff. == 0, reset
		if (idx == degree && temp[idx] < EPSILON)
		{
			std::cerr << "Coefficient of highest degree must be different than 0\n";
			inputStream.clear();
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			idx = degree;
		}
		else
			--idx;
	}
	
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
