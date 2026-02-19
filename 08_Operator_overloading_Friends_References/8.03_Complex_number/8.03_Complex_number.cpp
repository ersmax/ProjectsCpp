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
	//   Postcondition: number is sent to the output stream in the form a + b*i (e.g. 3 + 4*i).

	friend std::istream& operator >>(std::istream& inputStream, Complex& number);
	//   Postcondition: number is set to the value read from the input stream.

	bool operator ==(const Complex& anotherNumber) const;
	//   Postcondition: returns true if the calling object is equal to anotherNumber; otherwise, returns false

	const friend Complex operator +(const Complex& firstNumber, const Complex& secondNumber);
	//   Postcondition: returns the sum of firstNumber and secondNumber. 
	// A friend function is used, since it allows automatic type conversion, in case one of the operands 
	// is a double (which would be converted to a Complex object with 0 imaginary part).
	// This allows expressions such as `3.5 + aComplex` or `aComplex + 3.5` to work correctly.

	const friend Complex operator -(const Complex& firstNumber, const Complex& secondNumber);
	//   Postcondition: returns the difference of firstNumber and secondNumber.

	const friend Complex operator *(const Complex& firstNumber, const Complex& secondNumber);
	//   Postcondition: returns the product of firstNumber and secondNumber.
private:
	double real;
	double imaginary;
};

const Complex i(0, 1);

Complex inputComplex();

int main( )
{
	std::cout << "5 * i = " << 5 * i << '\n';

	std::cout << "Enter complex number (format: a+b):\n";
	Complex aComplex = inputComplex();
	std::cout << "Your complex number is: " << aComplex << '\n';

	std::cout << "Enter another complex number (format: a+b):\n";
	Complex anotherComplex;
	std::cin >> anotherComplex;
	std::cout << "Your second complex number is: " << anotherComplex << '\n';

	if (aComplex == anotherComplex)
		std::cout << aComplex << " = " << anotherComplex << '\n';
	else
		std::cout << aComplex << " <> " << anotherComplex << '\n';

	std::cout << aComplex << " + " << anotherComplex << " = " << aComplex + anotherComplex << '\n';
	std::cout << aComplex << " - " << anotherComplex << " = " << aComplex - anotherComplex << '\n';
	std::cout << aComplex << " * " << anotherComplex << " = " << aComplex * anotherComplex << '\n';



	std::cout << '\n';
	return 0;
}

const Complex operator +(const Complex& firstNumber, const Complex& secondNumber)
{
	double realPart = firstNumber.real + secondNumber.real;
	double imaginaryPart = firstNumber.imaginary + secondNumber.imaginary;
	return Complex(realPart, imaginaryPart);
}

const Complex operator -(const Complex& firstNumber, const Complex& secondNumber)
{
	double realPart = firstNumber.real - secondNumber.real;
	double imaginaryPart = firstNumber.imaginary - secondNumber.imaginary;
	return Complex(realPart, imaginaryPart);
}

const Complex operator *(const Complex& firstNumber, const Complex& secondNumber)
{
	double realPart = firstNumber.real * secondNumber.real -
					  firstNumber.imaginary * secondNumber.imaginary;
	double imaginaryPart = firstNumber.real * secondNumber.imaginary +
						   firstNumber.imaginary * secondNumber.real;
	return Complex(realPart, imaginaryPart);
}

bool Complex::operator ==(const Complex& anotherNumber) const
{
	return (real == anotherNumber.real && imaginary == anotherNumber.imaginary);
}

std::ostream& operator <<(std::ostream& outputStream, const Complex& number)
{
	if (number.imaginary >= 0)
		outputStream << number.real << " + " << number.imaginary << "*i";
	else
		outputStream << number.real << " - " << -number.imaginary << "*i";
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
