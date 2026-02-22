/*
Define a class named PrimeNumber that stores a prime number. 
The default constructor should set the prime number to 1. Add another constructor that allows
the caller to set the prime number. Also, add a function to get the prime number.
Finally, overload the prefix and postfix ++ and −− operators so they return a PrimeNumber object that is the next largest prime number (for ++) and the next smallest
prime number (for −−). For example, if the object’s prime number is set to 13, then
invoking ++ should return a PrimeNumber object whose prime number is set to 17.
Create an appropriate test program for the class.
*/

#include <iostream>
#include <vector>
#include <cmath>

class PrimeNumber
{
public:
	PrimeNumber() : prime(1) {};
	PrimeNumber(const int number) { setPrime(number); }
	const PrimeNumber operator --();	// prefix notation
	const PrimeNumber operator --(int);	// postfix notation
	const PrimeNumber operator ++();	// prefix notation
	const PrimeNumber operator ++(int);	// postfix notation
	friend std::istream& operator >>(std::istream& inputStream, PrimeNumber& number);
	friend std::ostream& operator <<(std::ostream& outputStream, const PrimeNumber& number);
private:
	int prime;
	void setPrime(int number);
};

bool isPrime(int number);
bool isPrimeRecursive(int number, int divisor);
int findPreviousPrime(int number);
int findNextPrime(int number);
int findCloserPrime(int number);
const PrimeNumber numberValidation();

int main( )
{
	std::cout << "Enter a number:\n";
	const PrimeNumber aPrime = numberValidation();
	std::cout << "The prime number is: " << aPrime << '\n';


	std::cout << '\n';
	return 0;
}

void PrimeNumber::setPrime(const int number)
{
	if (isPrime(number))
		prime = number;
	else
		prime = findCloserPrime(number);
}

std::istream& operator >>(std::istream& inputStream, PrimeNumber& number)
{
	int inputNumber;
	inputStream >> inputNumber;
	if (!(isPrime(inputNumber)))
	{
		// mark the stream as failed
		inputStream.setstate(std::ios::failbit);
		return inputStream;
	}
	number.setPrime(inputNumber);
	return inputStream;
}

std::ostream& operator <<(std::ostream& outputStream, const PrimeNumber& number)
{
	outputStream << number.prime;
	return outputStream;
}

int findCloserPrime(const int number)
{
	const int previous = findPreviousPrime(number);
	const int next = findNextPrime(number);

	const int previousDifference = std::abs(previous - number);
	const int nextDifference = std::abs(next - number);
	const int closest = (previousDifference <= nextDifference) ? previous : next;

	std::cout << "Previous prime to " << number << ": " << previous << '\n';
	std::cout << "Next prime to " << number << ": " << next << '\n';
	std::cout << "Closest prime to " << number << ": " << closest << '\n';

	return closest;	
}

int findPreviousPrime(const int number)
{
	if (number <= 3)	return 2;

	int previous = (number % 2 == 0) ? (number - 1) : (number - 2);
	while (previous > 3)
	{
		if (isPrime(previous)) 
			break;
		previous -= 2;			// skip even numbers
	}
	return previous;
}

int findNextPrime(const int number)
{
	if (number < 2)		return 2;
	if (number == 2)	return 3;

	bool found = false;
	int next = (number % 2 == 0) ? (number + 1) : (number + 2);
	while (!found)
	{
		if (isPrime(next))
			found = true;
		else
			next += 2;
	}
	return next;
}

bool isPrime(const int number)
{
	if (number <= 2)
		return (number == 2);
	if (number % 2 == 0)	return false;
	
	// Check divisibility by all odd numbers up to sqrt(number)
	const int limit = static_cast<int>(std::sqrt(number));
	for (int next = 3; next <= limit; next += 2)
		if (number % next == 0)		
			return false;

	return true;
}

bool isPrime(const int number, const int divisor = 3)
{
	if (number <= 3)		
		return (number == 2 || number == 3);
	if (number % 2 == 0)		// even number
		return false;
	if (number % divisor == 0)	// multiple
		return false;
	
	// Check divisibility by all odd numbers up to sqrt(number)
	if (divisor * divisor > number)
		return true;
	else
		return isPrime(number, divisor + 2);
}

const PrimeNumber numberValidation()
{
	int number;
	while (true)
	{
		if (!(std::cin >> number))
		{
			std::cout << "Error in the input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return number;
	}
}