#include <iostream>
#include <cmath>
#include <limits>

class PrimeNumber
{
public:
	PrimeNumber() : prime(1) {};
	PrimeNumber(const int number) { setPrime(number); }
	int getPrime() const { return prime; }
	PrimeNumber& operator --();					 
	//   Precondition: Prefix notation, return by reference to allow chaining --(--a) 
	// and allow L-value operations
	//   Postcondition: the current object is modified to hold the previous prime number, 
	// and a reference to the current object is returned.

	const PrimeNumber operator --(int);			
	//   Precondition: Postfix notation, return by constant value to avoid chaining (a--)-- 
	// and allow R-value operations
	//   Postcondition: the current object is modified to hold the previous prime number,
	// and a constant PrimeNumber object is returned with the value of the current object before changes.

	PrimeNumber& operator ++();					
	//   Precondition: Prefix notation, return by reference to allow chaining ++(++a)
	// and allow L-value operations
	//   Postcondition: the current object is modified to hold the next prime number,
	// and a reference to the current object is returned.

	const PrimeNumber operator ++(int);			
	//   Precondition: Postfix notation, return by constant value to avoid chaining (a++)++
	// and allow R-value operations
	//   Postcondition: the current object is modified to hold the next prime number,
	// and a constant PrimeNumber object is returned with the value of the current object before changes.

	friend std::istream& operator >>(std::istream& inputStream, PrimeNumber& number);
	//   Precondition: input stream and a PrimeNumber object passed by reference 
	// to allow modification of the object
	//   Postcondition: the input stream is read for an integer, if it's a prime number, 
	// the PrimeNumber object is updated with that value. 
	// If it's not a prime number, the input stream is marked as failed.

	friend std::ostream& operator <<(std::ostream& outputStream, const PrimeNumber& number);
	//   Precondition: output stream and a constant PrimeNumber object passed by reference
	//   Postcondition: the prime number stored in the PrimeNumber object is output to the stream

private:
	int prime;
	void setPrime(int number);
	//   Postcondition: the prime member variable is set to the given number if it's prime,
	// otherwise, it is set to the closest prime number to the given number.
	// Use the helper function findCloserPrime to determine the closest prime number.
};

bool isPrime(int number);
//   Postcondition: returns true if the number is prime, false otherwise

bool isPrimeRecursive(int number, int divisor = 3);
//   Postcondition: returns true if the number is prime, false otherwise. 
// This function uses recursion to check for primality, starting with the smallest odd divisor (3) 
// and checking up to the square root of the number.

int findPreviousPrime(int number);
//   Postcondition: returns the largest prime number that is less than the given number.

int findNextPrime(int number);
//   Postcondition: returns the smallest prime number that is greater than the given number.

int findCloserPrime(int number);
//   Postcondition: returns the prime number that is closest to the given number.
// Use the helper functions findPreviousPrime and findNextPrime to determine the closest prime number.

const PrimeNumber numberValidation();
//   Postcondition: prompts the user to enter a number, validates the input, 
// and returns a PrimeNumber object initialized with the valid input.

int main( )
{
	std::cout << "Enter a number:\n";
	PrimeNumber aPrime = numberValidation();
	PrimeNumber aPrimeCopy = aPrime;
	PrimeNumber aPrimeCopy2 = aPrime;
	PrimeNumber aPrimeCopy3 = aPrime;
	std::cout << "The prime number is: " << aPrime << '\n';
	std::cout << "--" << aPrime << ": " << --aPrime << '\n';
	std::cout << aPrimeCopy << "--" << ": " << aPrimeCopy-- << '\n';


	std::cout << "++" << aPrimeCopy2 << ": " << ++aPrimeCopy2 << '\n';
	std::cout << aPrimeCopy3 << "++" << ": " << aPrimeCopy3++ << '\n';

	std::cout << '\n';
	return 0;
}

PrimeNumber& PrimeNumber::operator --()
{
	prime = findPreviousPrime(prime);
	return *this;
}

const PrimeNumber PrimeNumber::operator --(int postfixNotation)
{
	const int temp = prime;
	prime = findPreviousPrime(prime);
	return PrimeNumber(temp);
}

PrimeNumber& PrimeNumber::operator ++()
{
	prime = findNextPrime(prime);
	return *this;
}

const PrimeNumber PrimeNumber::operator ++(int postFixNotation)
{
	const int temp = prime;
	prime = findNextPrime(prime);
	return PrimeNumber(temp);
}

void PrimeNumber::setPrime(const int number)
{
	if (isPrimeRecursive(number))
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

bool isPrimeRecursive(const int number, const int divisor)
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
		return isPrimeRecursive(number, divisor + 2);
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