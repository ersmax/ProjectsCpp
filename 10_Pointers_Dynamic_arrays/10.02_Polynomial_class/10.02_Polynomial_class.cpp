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
//#include <cmath>

typedef double *DoublePtr;

constexpr double EPSILON = 1e-9;

class Polynomial
{
public:
	Polynomial() : coefficients(new double[1]{ 0.0 }), degree(0) {};
	Polynomial(double polynomial[], int newDegree);
	Polynomial(const Polynomial& myPolynomial);
	Polynomial& operator =(const Polynomial& myPolynomial);
	~Polynomial() { delete[] coefficients; }
	int getDegree() const { return degree; }
	double evaluate(double unknownVar) const;
	const Polynomial operator +(const Polynomial& rhs) const;
	const Polynomial operator -(const Polynomial& rhs) const;
	const Polynomial operator *(const Polynomial& rhs) const;
	double& operator [](int index);
	double operator [](int index) const;
	friend const Polynomial operator +(const Polynomial& myPolynomial, double constant);
	friend const Polynomial operator +(double constant, const Polynomial& myPolynomial);
	friend const Polynomial operator -(const Polynomial& myPolynomial, double constant);
	friend const Polynomial operator -(double constant, const Polynomial& myPolynomial);
	friend const Polynomial operator *(const Polynomial& myPolynomial, double constant);
	friend const Polynomial operator *(double constant, const Polynomial& myPolynomial);
	friend std::istream& operator >>(std::istream& inputStream, Polynomial& myPolynomial); 
	friend std::ostream& operator <<(std::ostream& outputStream, const Polynomial& myPolynomial);
private:
	DoublePtr coefficients;
	int degree;
};

int main( )
{
	Polynomial aPolynomial, aPolynomial2;
	std::cout << "Enter a polynomial:\n";
	std::cin >> aPolynomial;
	std::cout << "Enter another polynomial:\n";
	std::cin >> aPolynomial2;
	std::cout << "First Polynomial: " << aPolynomial << '\n';
	std::cout << "Second Polynomial: " << aPolynomial2 << '\n';
	std::cout << aPolynomial << " + " << aPolynomial2 << " = " << aPolynomial + aPolynomial2 << '\n';
	std::cout << aPolynomial << " + " << 5 << " = " << aPolynomial + 5 << '\n';
	std::cout << 6 << " + " << aPolynomial << " = " << 6 + aPolynomial << '\n';
	std::cout << aPolynomial << " - " << aPolynomial2 << " = " << aPolynomial - aPolynomial2 << '\n';
	std::cout << aPolynomial << " - " << 5 << " = " << aPolynomial - 5 << '\n';
	std::cout << 6 << " - " << aPolynomial << " = " << 6 - aPolynomial << '\n';
	std::cout << aPolynomial << " * " << aPolynomial2 << " = " << aPolynomial * aPolynomial2 << '\n';
	std::cout << aPolynomial << " * " << 5 << " = " << aPolynomial * 5 << '\n';
	std::cout << 6 << " * " << aPolynomial << " = " << 6 * aPolynomial << '\n';

	std::cout << "\nTesting the same operand: " << aPolynomial << "\n";
	std::cout << aPolynomial << " + " << aPolynomial << " = " << aPolynomial + aPolynomial << '\n';
	std::cout << aPolynomial << " - " << aPolynomial << " = " << aPolynomial - aPolynomial << '\n';
	std::cout << aPolynomial << " * " << aPolynomial << " = " << aPolynomial * aPolynomial << '\n';

	std::cout << "\nTesting extractor function: " << aPolynomial << "\n";
	std::cout << "aPolynomial[degree] = " << aPolynomial[aPolynomial.getDegree()] << "\n";
	std::cout << "\nTesting assignment function: " << aPolynomial << "\n";
	std::cout << "aPolynomial[degree] = 10\n"; 
	aPolynomial[aPolynomial.getDegree()] = 10;
	std::cout << "\nTesting extractor function: " << aPolynomial << "\n";
	std::cout << "aPolynomial[degree] = " << aPolynomial[aPolynomial.getDegree()] << "\n";

	std::cout << "\nTesting evaluation function: " << aPolynomial << "\n";
	std::cout << aPolynomial.evaluate(2) << '\n';

	std::cout << '\n';
	return 0;
}

double Polynomial::evaluate(const double unknownVar) const
// Horner's Method
{
	double result = 0.0;
	for (int idx = degree; idx >= 0; --idx)
		result = result * unknownVar + coefficients[idx];
	return result;
	
	//double sum = coefficients[0];
	//for (int idx = 1; idx <= degree; idx++)
	//	sum += coefficients[idx] * std::pow(unknownVar, idx);
	//return sum;
}

double& Polynomial::operator [](const int index)
{
	if (index < 0 || index > degree)
		throw std::out_of_range("Polynomial index out of range\n");
	return coefficients[index];
}


double Polynomial::operator [](const int index) const
{
	if (index < 0 || index > degree)
		throw std::out_of_range("Polynomial index out of range\n");
	return coefficients[index];
}

const Polynomial operator +(const double constant, const Polynomial& myPolynomial)
{
	Polynomial temp = Polynomial(myPolynomial.coefficients, myPolynomial.degree);
	temp.coefficients[0] += constant;
	return temp;
}

const Polynomial operator -(const double constant, const Polynomial& myPolynomial)
{
	Polynomial temp = Polynomial(myPolynomial.coefficients, myPolynomial.degree);
	temp.coefficients[0] -= constant;
	return temp;
}

const Polynomial operator *(const double constant, const Polynomial& myPolynomial)
{
	Polynomial temp = Polynomial(myPolynomial.coefficients, myPolynomial.degree);
	for (int idx = 0; idx <= myPolynomial.degree; idx++)
		temp.coefficients[idx] *= constant;
	return temp;
}

const Polynomial operator +(const Polynomial& myPolynomial, const double constant)
{
	const DoublePtr newCoefficients = new double[myPolynomial.degree + 1];
	for (int idx = 0; idx <= myPolynomial.degree; idx++)
		newCoefficients[idx] = myPolynomial.coefficients[idx];
	newCoefficients[0] += constant;
	Polynomial newPolynomial = Polynomial(newCoefficients, myPolynomial.degree);
	delete [] newCoefficients;
	return newPolynomial;
}

const Polynomial operator -(const Polynomial& myPolynomial, const double constant)
{
	const DoublePtr newCoefficients = new double[myPolynomial.degree + 1];
	for (int idx = 0; idx <= myPolynomial.degree; idx++)
		newCoefficients[idx] = myPolynomial.coefficients[idx];
	newCoefficients[0] -= constant;
	Polynomial newPolynomial = Polynomial(newCoefficients, myPolynomial.degree);
	delete [] newCoefficients;
	return newPolynomial;
}

const Polynomial operator *(const Polynomial& myPolynomial, const double constant)
{
	const DoublePtr newCoefficients = new double[myPolynomial.degree + 1];
	for (int idx = 0; idx <= myPolynomial.degree; idx++)
		newCoefficients[idx] = myPolynomial.coefficients[idx] * constant;
	Polynomial newPolynomial = Polynomial(newCoefficients, myPolynomial.degree);
	delete [] newCoefficients;
	return newPolynomial;
}

Polynomial::Polynomial(const Polynomial& myPolynomial) : degree(myPolynomial.degree)
{
	coefficients = new double[degree + 1];
	for (int idx = 0; idx <= degree; idx++)
		coefficients[idx] = myPolynomial.coefficients[idx];
}

Polynomial::Polynomial(double polynomial[], const int newDegree) : degree(newDegree)
{
	coefficients = new double[newDegree + 1];
	for (int idx = 0; idx <= newDegree; idx++)
		coefficients[idx] = polynomial[idx];
}

Polynomial& Polynomial::operator =(const Polynomial& myPolynomial)
{
	if (degree != myPolynomial.degree)
	{
		delete[] coefficients;
		coefficients = new double[myPolynomial.degree + 1];
		degree = myPolynomial.degree;
	}
	// coefficients = myPolynomial.coefficients; // wrong shallow copy
	// correct below: deep copy
	for (int idx = 0; idx <= degree; idx++)
		coefficients[idx] = myPolynomial.coefficients[idx];
	return *this;
}

const Polynomial Polynomial::operator +(const Polynomial& rhs) const
{
	const int maxDegree = std::max(this->degree, rhs.degree);
	const DoublePtr sumCoefficients = new double[maxDegree + 1];
	
	// Initialization of coefficients
	for (int idx = 0; idx <= maxDegree; ++idx)
		sumCoefficients[idx] = 0.0;
	// Add coefficients from both sides
	for (int idx = 0; idx <= degree; ++idx)
		sumCoefficients[idx] += coefficients[idx];
	for (int idx = 0; idx <= rhs.degree; ++idx)
		sumCoefficients[idx] += rhs.coefficients[idx];

	// Create new dynamic array with parameterized constructor, then deallocate temp array
	Polynomial result(sumCoefficients, maxDegree);
	delete [] sumCoefficients;
	return result;
}

const Polynomial Polynomial::operator -(const Polynomial& rhs) const
{
	const int maxDegree = std::max(this->degree, rhs.degree);
	const DoublePtr differenceCoefficients = new double[maxDegree + 1];

	// Initialization of coefficients
	for (int idx = 0; idx <= maxDegree; ++idx)
		differenceCoefficients[idx] = 0.0;
	// Deduct coefficients from both sides
	for (int idx = 0; idx <= degree; ++idx)
		differenceCoefficients[idx] += coefficients[idx];
	for (int idx = 0; idx <= rhs.degree; ++idx)
		differenceCoefficients[idx] -= rhs.coefficients[idx];

	// Create new dynamic array with parameterized constructor, then deallocate temp array
	Polynomial result(differenceCoefficients, maxDegree);
	delete[] differenceCoefficients;
	return result;
}

const Polynomial Polynomial::operator *(const Polynomial& rhs) const
{
	const int maxDegree = degree + rhs.degree;
	const DoublePtr newCoefficients = new double[maxDegree + 1];

	// Initialization of coefficients
	for (int idx = 0; idx <= maxDegree; ++idx)
		newCoefficients[idx] = 0.0;
	// Multiply coefficients from both sides
	for (int idx = 0; idx <= degree; ++idx)
		for (int jdx = 0; jdx <= rhs.degree; ++jdx)
			newCoefficients[idx + jdx] += coefficients[idx] * rhs.coefficients[jdx];

	// Create new dynamic array with parameterized constructor, then deallocate temp array
	Polynomial result(newCoefficients, maxDegree);
	delete [] newCoefficients;
	return result;
}



std::ostream& operator <<(std::ostream& outputStream, const Polynomial& myPolynomial)
{
	bool printed = false;
	for (int idx = myPolynomial.degree; idx >= 0; idx--)
	{
		// if coefficient is 0, skip
		if (std::abs(myPolynomial.coefficients[idx]) < EPSILON)
			continue;
		if (idx != myPolynomial.degree && myPolynomial.coefficients[idx] > 0)
			outputStream << '+';
		
		if (idx == myPolynomial.degree && 
			(std::abs(myPolynomial.coefficients[idx]) - 1.0) < EPSILON)
			outputStream << "";
		else
			outputStream << myPolynomial.coefficients[idx];
		printed = true;

		if (idx != 0)
			outputStream << "x";
		if (idx != 0 && idx != 1)
			outputStream << '^' << idx;
	}
	if (!printed)	outputStream << '0';
	return outputStream;
}

std::istream& operator >>(std::istream& inputStream, Polynomial& myPolynomial)
{
	// e.g. Enter degree: 3
	//		Enter coefficients(from x^3 to x^0) : 3 0 0 -1
	int newDegree;
	std::cout << "Enter degree:\n";
	inputStream >> newDegree; 
	
	// Allocate dynamic array for coefficients
	const DoublePtr temp = new double[newDegree + 1];
	std::cout << "Enter coefficients (from x^" << newDegree << " to x^0):\n";
	
	int idx = newDegree;
	while (idx >= 0)
	{
		inputStream >> temp[idx];
		// if highest degree coeff. == 0, reset
		if (idx == newDegree && (std::abs(temp[idx]) < EPSILON))
		{
			std::cerr << "Coefficient of highest degree must be different than 0\n";
			inputStream.clear();
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			idx = newDegree;
		}
		else
			--idx;
	}
	inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Deallocate old dynamic array set up with default constructor
	delete [] myPolynomial.coefficients;
	// Shallow copy of the pointer temp (point to the same address) 
	myPolynomial.coefficients = temp;
	myPolynomial.degree = newDegree;

	return inputStream;
}
