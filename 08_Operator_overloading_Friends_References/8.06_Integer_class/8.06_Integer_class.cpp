/*
Define a class named MyInteger that stores an integer and has functions to get and
set the integer’s value. Then, overload the [] operator so that the index returns the
digit in position i, where i = 0 is the least-significant digit. If no such digit exists
then −1 should be returned.
For example, if x is of type MyInteger and is set to 418, then x[0] should return
8, x[1] should return 1, x[2] should return 4, and x[3] should return −1.
*/

#include <iostream>
#include <limits>

int inputValidation();
//   Postcondition: Asks the user for a valid integer and returns it.

class MyInteger
{
public:
	MyInteger() : number(0) {};
	MyInteger(const int num) : number(num) {};
	void setNumber() { number = inputValidation(); }
	int getNumber() const{ return number; }
	int operator [](int position) const;
	//   Precondition: position is a non-negative integer.
	//   Postcondition: Returns the digit in position i, where i = 0 is the least-significant digit.

	friend std::istream& operator >>(std::istream& inputStream, MyInteger& number);
	//   Precondition: inputStream contains an integer.
	//   Postcondition: number is set to the value read from inputStream.

	friend std::ostream& operator <<(std::ostream& outputStream, const MyInteger& number);
	//   Precondition: number is a MyInteger object.
	//   Postcondition: number is sent to the output stream.

private:
	int number;
};


int main( )
{
	MyInteger anInteger;
	std::cout << "Enter an integer:\n";
	std::cin >> anInteger;
	std::cout << "Entered number: " << anInteger << '\n';
	std::cout << "Query a digit (0: least-significant digit):\n";
	int digit;
	do
	{
		const int position = inputValidation();
		digit = anInteger[position];
		if (digit == -1)
			std::cout << "Not a valid position. Retry\n";
		else
			std::cout << "Digit at position " << position << ": " <<  digit << '\n';

	} while (digit == -1);
	
	std::cout << '\n';
	return 0;
}

std::istream& operator >>(std::istream& inputStream, MyInteger& number)
{
	int inputNumber;
	inputStream >> inputNumber;
	number.number = inputNumber;
	return inputStream;
}

std::ostream& operator <<(std::ostream& outputStream, const MyInteger& number)
{
	outputStream << number.number;
	return outputStream;
}

int inputValidation()
{
	int number;
	while (true)
	{
		std::cout << "Enter a valid number:\n";
		if (!(std::cin >> number))
		{
			std::cout << "Error\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return number;
	}
}

int MyInteger::operator [](const int position) const
{
	if (position < 0)	return -1;
	
	int temp = std::abs(number);
	for (int idx = 0; idx < position; idx++)
	{
		temp = temp / 10;
		if (temp == 0)	return -1;
	}
	const int remainder = temp % 10;
	return remainder;
}