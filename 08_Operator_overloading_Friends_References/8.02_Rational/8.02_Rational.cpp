#include <iostream>
#include <limits>
#include <cmath>

class Rational
{
public:
	Rational() : numerator(0), denominator(1) {};
	Rational(const int wholeNumber) : numerator(wholeNumber), denominator(1) { };
	Rational(const int number1, const int number2) : numerator(number1) { setDenominator(number2); normalize(); }
	const Rational operator +(const Rational& secondOperand) const;
	const Rational operator -(const Rational& secondOperand) const;
	const Rational operator *(const Rational& secondOperand) const;
	const Rational operator /(const Rational& secondOperand) const;
	bool operator ==(const Rational& secondOperand) const;
	bool operator !=(const Rational& secondOperand) const;
	bool operator <(const Rational& secondOperand) const;
	//   Precondition: the calling object denominator and secondOperand object denominator are both positive
	//   Postcondition: returns true if the calling object is less than secondOperand; otherwise, returns false

	bool operator <=(const Rational& secondOperand) const;
	//   Precondition: the calling object denominator and secondOperand object denominator are both positive
	//   Postcondition: returns true if the calling object is less than or equal to secondOperand; otherwise, returns false

	bool operator >(const Rational& secondOperand) const;
	//   Precondition: the calling object denominator and secondOperand object denominator are both positive
	//   Postcondition: returns true if the calling object is greater than secondOperand; otherwise, returns false

	bool operator >=(const Rational& secondOperand) const;
	//   Precondition: the calling object denominator and secondOperand object denominator are both positive
	//   Postcondition: returns true if the calling object is greater than or equal to secondOperand; otherwise, returns false

	int getNumerator() const { return numerator; }
	int getDenominator() const { return denominator; }
	friend std::ostream& operator <<(std::ostream& outputStream, const Rational& rational);
	//   Precondition: outputStream is cout, rational is a valid Rational object
	//   Postcondition: rational is sent to the output stream in the form numerator/denominator (e.g. 3/4).

	friend std::istream& operator >>(std::istream& inputStream, Rational& rational);
	//   Precondition: inputStream is cin, rational is a valid Rational object
	//   Postcondition: rational is set to the value read from the input stream.
private:
	int numerator;
	int denominator;
	void setDenominator(int number);
	//   Postcondition: sets denominator to number if number is not zero; 
	// otherwise, throws an exception.

	void normalize();
	//	 Postcondition: normalizes the rational number so that 
	// the denominator is positive and the numerator and denominator are as small as possible. 
	// For example, after normalization 4/-8 would be represented the same as −1/2.
};

int findGcd(int number1, int number2);
int findLcm(int number1, int number2);
Rational inputRational();

int main( )
{
	try
	{
		std::cout << "Enter a valid rational:\n";
		Rational aRational1 = inputRational();
		std::cout << "The rational is " << aRational1 << '\n';

		Rational aRational2;
		std::cout << "Enter another rational:\n";
		std::cin >> aRational2;
		std::cout << "The rational is " << aRational2 << '\n';

		std::cout << aRational1 << " + " << aRational2 << " = " << aRational1 + aRational2 << '\n';
		std::cout << aRational1 << " - " << aRational2 << " = " << aRational1 - aRational2 << '\n';
		std::cout << aRational1 << " * " << aRational2 << " = " << aRational1 * aRational2 << '\n';
		std::cout << aRational1 << " / " << aRational2 << " = " << aRational1 / aRational2 << '\n';
		if (aRational1 != aRational2)
			std::cout << aRational1 << " is different from " << aRational2 << '\n';

	} catch (const std::invalid_argument& e)
	{
		std::cout << "Error constructing the rational: " << e.what() << '\n';
	}

	std::cout << '\n';
	return 0;
}

std::ostream& operator <<(std::ostream& outputStream, const Rational& rational)
{
	outputStream << rational.numerator << '/' << rational.denominator;
	return outputStream;
}

std::istream& operator >>(std::istream& inputStream, Rational& rational)
{
	int newNumerator, newDenominator;
	char slash;
	inputStream >> newNumerator >> slash >> newDenominator;

	if (slash != '/' || newDenominator == 0)
	{
		// manually mark the stream as failed		
		inputStream.setstate(std::ios::failbit);
		return inputStream;
	}
	
	rational.numerator = newNumerator;
	rational.denominator = newDenominator;
	rational.normalize();

	return inputStream;
}

Rational inputRational()
{
	Rational r;
	while (true)
	{
		std::cout << "Enter a rational number (format: numerator/denominator):\n";
		if (!(std::cin >> r))
		{
			std::cout << "Not a valid rational\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return r;
	}
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

const Rational Rational::operator -(const Rational& secondOperand) const
{	
	const int newDenominator = denominator * secondOperand.denominator;
	const int newNumerator = numerator * secondOperand.denominator -
							 secondOperand.numerator * denominator;
	return Rational(newNumerator, newDenominator);
}

const Rational Rational::operator *(const Rational& secondOperand) const
{
	const int newNumerator = numerator * secondOperand.numerator;
	const int newDenominator = denominator * secondOperand.denominator;
	return Rational(newNumerator, newDenominator);
}

const Rational Rational::operator /(const Rational& secondOperand) const
{
	if (secondOperand.numerator == 0)
		throw std::invalid_argument("Cannot divide by zero\n");

	const int newNumerator = numerator * secondOperand.denominator;
	const int newDenominator = denominator * secondOperand.numerator;
	return Rational(newNumerator, newDenominator);
}

bool Rational::operator ==(const Rational& secondOperand) const
{
	if (denominator == secondOperand.denominator)
		return (numerator == secondOperand.numerator);
	
	return (numerator * secondOperand.denominator == denominator * secondOperand.numerator);
}

bool Rational::operator !=(const Rational& secondOperand) const
{
	return !(*this == secondOperand);
}

bool Rational::operator <(const Rational& secondOperand) const
{
	return (numerator * secondOperand.denominator < denominator * secondOperand.numerator);
}

bool Rational::operator <=(const Rational& secondOperand) const
{
	return (numerator * secondOperand.denominator <= denominator * secondOperand.numerator);
}

bool Rational::operator >(const Rational& secondOperand) const
{
	return secondOperand < *this;
}

bool Rational::operator >=(const Rational& secondOperand) const
{
	return secondOperand <= *this;
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

