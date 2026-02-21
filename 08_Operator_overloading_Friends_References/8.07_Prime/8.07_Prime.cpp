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
private:
	int prime;
	void setPrime(int number);
};

bool isPrime(int number, std::vector<int>& primeNumbers);
void setPrime(int number, std::vector<int>& primeNumbers);

int main( )
{
	std::vector<int> primeNumbers;
	primeNumbers.push_back(2);

	std::cout << 'n';
	return 0;
}

bool isPrime(const int number, std::vector<int>& primeNumbers)
{
	if (number <= 1)		return false;
	if (number == 2)		return true;
	if (number % 2 == 0)	return false;

	// First pass: check if prime is cached
	for (const int prime : primeNumbers)
		if (number == prime)
			return true;
	//   Second pass: check if the remainder up to sqrt(number) is 0
	// For instance, we have only 2 in primeNumbers, and `number` is 3
	for (const int prime : primeNumbers)
	{
		if (prime * prime > number)	break;	// e.g. 3
		if (number % prime == 0)	return false;
	}

	// Check the remaining numbers up to sqrt(number). 
	// Skip even numbers with += 2, unless, the last prime is 2
	const int limit = static_cast<int>(std::sqrt(number));
	const int lastPrime = primeNumbers.back();
	const int nextNumber = (lastPrime == 2) ? 3 : lastPrime + 2;

	for (int next = nextNumber; next <= limit; next += 2)
		if (number % next == 0)		
			return false;
	
	setPrime(number, primeNumbers);
	return true;
}

void setPrime(const int number, std::vector<int>& primeNumbers)
{
	primeNumbers.push_back(number);
}

