#include <algorithm>		// std::min
#include <iostream>
#include <string>
#include <limits>			// std::numeric_limits
#include <iomanip>			// std::setprecision
#include <conio.h>			// _kbhit, _getch
#include <thread>			// sleep_for
#include <chrono>			// ms

constexpr double PRICE_LITER = 2.832;
constexpr double STEP_REFILL = 0.1;

class GasPump
{
public:
	double getAmount() const;
	//   Postcondition: return amount of fuel
	double getCharges() const;
	//   Postcondition: return the fuel cost
	void setCharges(double userPrice);
	//   Precondition: userPrice is the amount of 
	// money the user is willing to spend
	//   Postcondition: set the amount of fuel desired
	// by user, up to `userPrice`
private:
	double amount = 0.0;
	double charges = 0.0;
	void setAmount();
};

double showUnitCharge();
//   Postcondition: return the constant price/liter
void setFuel(double& userPrice);
//   Postcondition: set how much the user wanna spend

int main( )
{
	GasPump driver1;
	double userPrice = 0.0;
	setFuel(userPrice);
	driver1.setCharges(userPrice);

	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << "Driver's chosen price: " << driver1.getCharges() << "\n";
	std::cout << "Price per liter: " << showUnitCharge() << "\n";
	std::cout << "Total fuel: " << driver1.getAmount() << " liters\n";


	std::cout << "\n";
	return 0;
}

double GasPump::getAmount() const
{
	return amount;
}

double GasPump::getCharges() const
{
	return charges;
}


void GasPump::setCharges(const double userPrice)
{
	charges = 0.0;
	constexpr double eps = 1e-9;
	std::cout << "Press enter to refill (or 'ESC'):\n";
	while (charges + eps < userPrice)
	{
		if (_kbhit())
		{
			const char input = _getch();
			if (input == 27) break;	// ESCAPE
			if (input == 13)		// Enter
			{
				charges = std::min(charges + STEP_REFILL, userPrice);
				std::cout << "\r" << std::left
					<< std::setw(20)
					<< ("Fuel: " + std::to_string(charges) + " $")
					<< std::flush;

			}
		}
		// Add small delay
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "\n";
	setAmount();
}

void GasPump::setAmount()
{
	amount = charges / PRICE_LITER;
}

double showUnitCharge( )
{
	return PRICE_LITER;
}

void setFuel(double& userPrice)
{
	int input;
	const std::string qty = "$5, $10, $20, $50, $100";
	while (true)
	{
		std::cout << "Enter a valid input as combination of " << qty << ":\n";
		std::cout << "(To exit: -1)\n";
		if (!(std::cin >> input)) // EOF
		{
			std::cout << "Wrong input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		// consume remaining input
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input == -1) break;
		if ((input >= 5) && (input % 5 == 0))
			userPrice += input;
		else
			std::cout << "Wrong input\n";
	}
}
