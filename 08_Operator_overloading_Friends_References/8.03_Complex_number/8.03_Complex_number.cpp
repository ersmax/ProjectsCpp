/*
Define a class for complex numbers. A complex number is a number of the form
a + b*i 
where for our purposes, a and b are numbers of type double, and i is a number
that represents the quantity 1-1. Represent a complex number as two values
of type double. Name the member variables real and imaginary. (The variable
for the number that is multiplied by i is the one called imaginary.) Call the class
Complex. Include a constructor with two parameters of type double that can be
used to set the member variables of an object to any values. 
Include a constructor that has only a single parameter of type double; call this parameter realPart
and define the constructor so that the object will be initialized to realPart + 0*i.
Include a default constructor that initializes an object to 0 (that is, to 0 + 0*i).
Overload all the following operators so that they correctly apply to the type
Complex: ==, +, −, *, >>, and <<. You should also write a test program to test your
class. Hints: To add or subtract two complex numbers, add or subtract the two
member variables of type double. The product of two complex numbers is given
by the following formula:
(a + b*i)*(c + d*i) =  = (a*c - b*d ) + (a*d + b*c)*i
In the interface file, you should define a constant i as follows:
const Complex i(0, 1);
*/

#include <iostream> 
#include <limits>
#include <string>

// forward declare the class and declare but don't define yet the constant
class Complex;			
extern const Complex i;


class Complex
{
public:
	Complex() : real(0), imaginary(0) {};
	Complex(const double realPart, const double imaginaryPart) : real(realPart), imaginary(imaginaryPart) {};
	Complex(const double realPart) : real(realPart), imaginary(0) {};
	friend std::ostream& operator <<(std::ostream& outputStream, const Complex& number);
	friend std::istream& operator >>(std::istream& inputStream, Complex& number);
	bool operator ==(const Complex& number);
private:
	double real;
	double imaginary;
};

const Complex i(0, 1);

Complex inputComplex();

int main( )
{
	std::cout << "Enter complex number (format: a+b):\n";
	Complex aComplex = inputComplex();
	std::cout << "Your complex number is: " << aComplex << '\n';

	std::cout << '\n';
	return 0;
}

std::ostream& operator <<(std::ostream& outputStream, const Complex& number)
{
	std::string sign = " + ";
	if (number.imaginary < 0) sign = " - ";
	outputStream << number.real << sign << number.imaginary << "*i";
	return outputStream;
}

std::istream& operator >>(std::istream& inputStream, Complex& number)
{
	char sign;
	double realPart, imaginaryPart;
	inputStream >> realPart >> sign >> imaginaryPart;
	if (sign != '+' && sign != '-')
	{
		// manually mark the stream as failed
		inputStream.setstate(std::ios::failbit);
		return inputStream;
	}
	number.real = realPart;
	number.imaginary = (sign == '-') ? -imaginaryPart : imaginaryPart;
	return inputStream;
}

Complex inputComplex()
{
	Complex complexNumber;
	while (true)
	{
		if (!(std::cin >> complexNumber))
		{
			std::cout << "Not a complex number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return complexNumber;
	}
}
