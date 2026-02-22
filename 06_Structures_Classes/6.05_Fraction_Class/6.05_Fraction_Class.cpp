#include <iostream>
#include <limits>

class Fraction
{
public:
	void setNumerator();
	void setDenominator();
	int getNumerator() const;
	int getDenominator() const;
	void reduce() const;
	//  Postcondition: output the fraction in reduced terms
	double divide() const;
	//  Postcondition: return the division of numerator by denominator
private:
	int numerator;
	int denominator;
	int findGcd() const;
	//  Postcondition: return the greatest common divisor 
	// by means of the binary GCD algorithm
};

int numberValidation();
//  Postcondition: return a valid integer input from user

bool isEven(int number);
//  Precondition: number is an integer
//  Postcondition: return true if number is even, false otherwise

int main( )
{
	Fraction aNumber;
	
	std::cout << "Enter numerator: ";
	aNumber.setNumerator();
	std::cout << "Enter denominator: ";
	aNumber.setDenominator();
	aNumber.reduce();
	std::cout << "The division is: " << aNumber.divide();

	std::cout << "\n";
	return 0;
}

void Fraction::setNumerator()
{
	numerator = numberValidation();
}

void Fraction::setDenominator()
{
	denominator = numberValidation();
}

int Fraction::getNumerator() const
{
	return numerator;
}

int Fraction::getDenominator() const
{
	return denominator;
}

void Fraction::reduce() const
{
	const int gcd = (denominator == 0) ? numerator : findGcd();
	std::cout << "The reduce terms of "
		<< numerator << "/" << denominator
		<< " is "
		<< numerator / gcd;
	if ((denominator / gcd) != 1)
		std::cout << "/" << denominator / gcd;
	std::cout << "\n";
}

int Fraction::findGcd() const
{
	int number1 = numerator;
	int number2 = denominator;
	int idx = 0;
	while (isEven(number1) && isEven(number2))
	{
		number1 /= 2;	
		number2 /= 2;	
		idx++;
	}

	while (number1 != 0)
	{
		while (isEven(number1))
			number1 /= 2;
		while (isEven(number2))
			number2 /= 2;
		if (number1 >= number2)
			number1 -= number2;
		else
			number2 -= number1;
	}
	return ((1 << idx) * number2);
}

double Fraction::divide() const
{
	return (static_cast<double>(numerator) / static_cast<double>(denominator));
}

bool isEven(const int number)
{
	return (number % 2 == 0);
}

int numberValidation()
{
	int number;
	while (true)
	{
		while (!(std::cin >> number))
		{
			std::cout << "Not a valid number;\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}
	return number;
}
