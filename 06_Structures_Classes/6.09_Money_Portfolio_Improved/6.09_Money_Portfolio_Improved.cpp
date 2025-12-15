#include <iostream>
#include <limits>

class Money
{
public:
	void setDollars();
	void setCents();
	double convertMoney() const;
	//  Postcondition: The monetary amount is returned as a double with cents.
private:
	double amount = 0.0;
	int getDollars() const;
	int getCents() const;
	int inputValidation();
	//  Postcondition: returns a validated non-negative integer input.
};

int main()
{
	Money aTransaction[2];
	for (int idx = 0; idx < 2; idx++)
	{
		std::cout << "Transaction " << idx + 1 << ":\n"
				  << "Enter dollars:\n";
		aTransaction[idx].setDollars();
		std::cout << "Enter cents:\n";
		aTransaction[idx].setCents();
		std::cout << "This is equivalent to: $"
			      << aTransaction[idx].convertMoney() << "\n";
	}
	std::cout << "\n";
	return 0;
}

void Money::setDollars()
{
	const int input = inputValidation();
	const double remainingCents = amount - static_cast<int>(amount);
	amount = input + remainingCents;
}

void Money::setCents()
{
	const int cents = inputValidation();
	const int dollars = std::floor(amount) + cents / 100;
	const int remainingCents = cents % 100;
	amount = dollars + (static_cast<double>(remainingCents) / 100.0);
}

int Money::getDollars() const
{
	return (std::floor(amount));
}

int Money::getCents() const
{
	const double cents = (amount - std::floor(amount)) * 100.0;
	return (static_cast<int>(cents)) ;
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

double Money::convertMoney() const
{
	return (getDollars() + static_cast<double>(getCents()) / 100.0);
}
