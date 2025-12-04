/*
Write the definition for a class named GasPump to be used to model a pump at an
automobile service station. Before you go further with this programming exercise,
write down the behavior you expect from a gas pump from the point of view of the
purchaser.
The following are listed things a gas pump might be expected to do. If your list
differs, and you think your list is as good or better than these, then consult your
instructor. You and your instructor should jointly decide what behavior you are to
implement. Then implement and test the agreed upon design for a gas pump class.
a. A display of the amount dispensed
b. A display of the amount charged for the amount dispensed
c. A display of the cost per gallon, liter, or other unit of volume that is used where
you reside
d. Before use, the gas pump must reset the amount dispensed and amount charged
to zero.
e. Once started, a gas pump continues to dispense fuel, keep track of the amount
dispensed, and compute the charge for the amount dispensed until stopped.
f. A stop dispensing control of some kind is needed.
Implement the behavior of the gas pump as declarations of member functions of
the gas pump class, then write implementations of these member functions. You
will have to decide if there is data the gas pump has to keep track of that the user
of the pump should not have access to. If so, make these private member variables.
*/


#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <conio.h> // _kbhit, _getch
#include <thread>  // sleep_for
#include <chrono>  // ms



constexpr double PRICE_GALLON = 2.832;
constexpr double STEP_REFILL = 0.1;

class GasPump
{
public:
	double getAmount() const;
	double getCharges() const;
	void setAmount(double userPrice);
private:
	double amount = 0.0;
	double charges = 0.0;
	void setCharges();
};

double showUnitCharge();
void setFuel(double& userPrice);

int main( )
{
	GasPump driver1;
	double userPrice = 0.0;
	setFuel(userPrice);
	driver1.setAmount(userPrice);
	std::cout << "Driver's chosen amount: " << driver1.getAmount() << "\n";

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


void GasPump::setAmount(const double userPrice)
{
	amount = 0.0;
	std::cout << "Press enter to refill (or 'ESC'):\n";
	while (amount < userPrice)
	{
		if (_kbhit())
		{
			const char input = _getch();
			if (input == 27) break;	// ESCAPE
			if (input == 13)		// Enter
			{
				amount += STEP_REFILL;
				std::cout << "\r" << std::left
					<< std::setw(40)
					<< ("Fuel: " + std::to_string(amount));

			}
		}
		// Add small delay
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "\n";
}

void GasPump::setCharges()
{
	// TODO
}

double showUnitCharge( )
{
	return PRICE_GALLON;
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
		if ((input >= 5) && (input <= 100) && (input % 5 == 0))
			userPrice += input;
		else
			std::cout << "Wrong input\n";
	}
}

