#include <iostream>
#include <limits>

class Money
{
public:
	void setDollars();
	void setCents();
	double convertMoney();
	//  Postcondition: The monetary amount is returned as a double with cents.
private:
	int dollars = 0;
	int cents = 0;
	int getDollars();
	int getCents();
	int inputValidation();
	//  Postcondition: returns a validated non-negative integer input.
};

int main( )
{
	Money aTransaction;
	std::cout << "Enter dollars:\n";
	aTransaction.setDollars();
	std::cout << "Enter cents:\n";
	aTransaction.setCents();
	std::cout << "This is equivalent to: $" 
		      << aTransaction.convertMoney();
	std::cout << "\n";
	return 0;
}

void Money::setDollars()
{
	dollars = inputValidation();
}

void Money::setCents()
{
	cents = inputValidation();
}

int Money::getDollars()
{
	return dollars;
}

int Money::getCents()
{
	return cents;
}

int Money::inputValidation()
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

double Money::convertMoney()
{
	double total = getDollars() + getCents() / 100;
	const int remainderCents = getCents() % 100;
	total += static_cast<double>(remainderCents) / 100.0;
	return total;
}
