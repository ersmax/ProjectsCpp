/*
Define a class for rational numbers. A rational number is a number that can be
represented as the quotient of two integers. For example, 1/2, 3/4, 64/2, and so
forth are all rational numbers. (By 1/2 and so on we mean the everyday fraction,
not the integer division this expression would produce in a C++ program.)
Represent rational numbers as two values of type int, one for the numerator and
one for the denominator. Call the class Rational. Include a constructor with
two arguments that can be used to set the member variables of an object to any
legitimate values. Also include a constructor that has only a single parameter of
type int; call this single parameter wholeNumber and define the constructor so
that the object will be initialized to the rational number wholeNumber/1. Include
a default constructor that initializes an object to 0 (that is, to 0/1). Overload
the input and output operators >> and <<. Numbers are to be input and output
in the form 1/2, 15/32, 300/401, and so forth. Note that the numerator, the
denominator, or both may contain a minus sign, so −1/2, 15/−32, and −300/−401
are also possible inputs. Overload all the following operators so that they correctly
apply to the type Rational: ==, <, <=, >, >=, +, −, *, and /. Write a test program
to test your class. Hints: Two rational numbers a/b and c/d are equal if a*d equals
c*b. If b and d are positive rational numbers, a/b is less than c/d provided a*d
is less than c*b. You should include a function to normalize the values stored
so that, after normalization, the denominator is positive and the numerator and
denominator are as small as possible. For example, after normalization 4/-8 would
be represented the same as −1/2.
*/

#include <iostream>

class Rational
{
public:
	Rational() : numerator(0), denominator(1) {};
	Rational(const int wholeNumber) : numerator(wholeNumber), denominator(1) { };
	Rational(const int number1, const int number2) : numerator(number1) { setDenominator(number2); normalize(); }
	const Rational operator +(const Rational& secondOperand) const;
	int getNumerator() const { return numerator; }
	int getDenominator() const { return denominator; }
private:
	int numerator;
	int denominator;
	void setDenominator(int number);
	void normalize();
};

int findGcd(int number1, int number2);

int main( )
{
	try
	{
		Rational aRational(1, 6);
		Rational aRational2(1, -2);
		Rational aRational3 = aRational + aRational2;
		std::cout << aRational3.getNumerator() << '/' << aRational3.getDenominator() << '\n';
	} catch (const std::invalid_argument& e)
	{
		std::cout << "Error constructing the rational: " << e.what() << '\n';
	}

	std::cout << '\n';
	return 0;
}

int findGcd(const int number1, const int number2)
{
	if (number2 == 0)	return (std::abs(number1));
	int dividend = std::abs(number1);
	int divisor = std::abs(number2);

	while (dividend % divisor != 0)
	{
		const int temp = dividend % divisor;
		dividend = divisor;
		divisor = temp;
	}
	return divisor;
}

int findLcm(const int number1, const int number2)
{
	if (number1 == 0 || number2 == 0)	return 0;
	return ((std::abs(number1) * std::abs(number2)) / findGcd(number1, number2));
}

const Rational Rational::operator +(const Rational& secondOperand) const
{
	const int lcm = findLcm(denominator, secondOperand.denominator);
	const int newNumerator = (lcm / denominator) * numerator +
							 (lcm / secondOperand.denominator) * secondOperand.numerator;

	return Rational(newNumerator, lcm);
}

void Rational::setDenominator(const int number)
{
	if (number == 0)
		throw std::invalid_argument("Denominator cannot be 0.\n");
		
	denominator = number;
}

void Rational::normalize()
{
	if (denominator < 0)
	{
		denominator = -denominator;
		numerator = -numerator;
	}
	int gcd = findGcd(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
}

