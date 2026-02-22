/*
Define a class named Money that stores a monetary amount. The class should have
two private integer variables, one to store the number of dollars and another to
store the number of cents. Add accessor and mutator functions to read and set both
member variables. Add another function that returns the monetary amount as a
double. Write a program that tests all of your functions with at least two different
Money objects.
*/
/*
Do Programming Project 6.8, the definition of a Money class, 
except create a default constructor that sets the monetary amount to 0 dollars and 0 cents, and create
a second constructor with input parameters for the amount of the dollars and cents
variables. Modify your test code to invoke the constructors.
*/

#include <iostream>
#include <limits>

class Money
{
public:
	Money(): dollars(0), cents(0) {};
	Money(const int dollars) : cents(0) { setDollars(dollars); }
	Money(const int dollars, const int cents) { setDollars(dollars); setCents(cents); }
	void setDollars(int money);

	void setCents(int money);
	double convertMoney() const;
	//  Postcondition: The monetary amount is returned as a double with cents.
	int getDollars() const { return dollars; }
	int getCents() const { return cents; }
private:
	int dollars = 0;
	int cents = 0;
};

int numberValidation();

int main()
{
	std::cout << "Enter dollars:\n";
	const int dollars = numberValidation();
	std::cout << "Enter cents:\n";
	const int cents = numberValidation();
	try
	{
		const Money aTransaction(dollars,cents);
		std::cout << "This is equivalent to: $"
				  << aTransaction.convertMoney();
	} catch (const std::invalid_argument& e) {
		std::cout << "Error creating the object " << e.what() << '\n';
	}
	std::cout << "\n";
	return 0;
}

void Money::setDollars(const int money)
{
	if (money >= 0)
		dollars = money;
	else
		throw std::invalid_argument("Invalid amount of dollars\n");
}

void Money::setCents(const int money)
{
	if (money >= 0)
		cents = money;
	else
		throw std::invalid_argument("Invalid amount of cents\n");
}

int numberValidation()
{
	int input;
	while (true)
	{
		if (!(std::cin >> input))
		{
			std::cout << "Wrong value\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (input >= 0) break;
		std::cout << "Wrong value\n";
	}
	return input;
}

double Money::convertMoney() const
{
	double total = getDollars() + getCents() / 100;
	const int remainderCents = getCents() % 100;
	total += static_cast<double>(remainderCents) / 100.0;
	return total;
}

