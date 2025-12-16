#include <iostream>
#include <limits>
#include <cmath>

constexpr double POUND_OUNCES = 16.0;
constexpr double KILO_POUNDS = 2.21;

class Weight
{
public:
	void setWeightPounds();
	void setWeightKilograms();
	void setWeightOunces();
	double getPounds() const;
	double getKilograms() const;
	double getOunces() const;
private:
	double pounds = 0;
	double convertPounds(int ounces);
	//   Precondition: ounces is a non-negative integer.
	//   Postcondition: The equivalent weight in pounds is returned.
	double convertPounds(double kilograms);
	//   Precondition: kilograms is a non-negative double.
	//   Postcondition: The equivalent weight in pounds is returned.
	double inputValidation();
	//   Postcondition: returns a validated non-negative double input.
};

int main( )
{
	Weight person;
	std::cout << "Enter pounds: ";
	person.setWeightPounds();
	std::cout << "Pounds: " << person.getPounds() << "\n";
	std::cout << "Kilograms: " << person.getKilograms() << "\n";
	std::cout << "Ounces: " << person.getOunces() << "\n\n";
	
	std::cout << "Enter kilos: ";
	person.setWeightKilograms();
	std::cout << "Pounds: " << person.getPounds() << "\n";
	std::cout << "Kilograms: " << person.getKilograms() << "\n";
	std::cout << "Ounces: " << person.getOunces() << "\n\n";
	
	std::cout << "Enter ounces: ";
	person.setWeightOunces();
	std::cout << "Pounds: " << person.getPounds() << "\n";
	std::cout << "Kilograms: " << person.getKilograms() << "\n";
	std::cout << "Ounces: " << person.getOunces() << "\n";

	std::cout << "\n";
	return 0;
}

void Weight::setWeightPounds()
{
	pounds = inputValidation();
}

void Weight::setWeightOunces()
{
	const int ounces = std::floor(inputValidation());
	pounds = convertPounds(ounces);
}

void Weight::setWeightKilograms()
{
	const double kilo = inputValidation();
	pounds = convertPounds(kilo); 
}

double Weight::inputValidation()
{
	double input;
	while (true)
	{
		if (!(std::cin >> input))
		{
			std::cout << "Error\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (input >= 0) break;
		std::cout << "Weight must be greater than 0.\n";
	}
	return input;
}

double Weight::convertPounds(const int ounces)
{
	return (static_cast<double>(ounces) / POUND_OUNCES);
}

double Weight::convertPounds(const double kilograms)
{
	return (kilograms * KILO_POUNDS);
}

double Weight::getPounds() const
{
	return pounds;
}

double Weight::getKilograms() const
{
	return (pounds / KILO_POUNDS);
}

double Weight::getOunces() const
{
	return (pounds * POUND_OUNCES);
}
