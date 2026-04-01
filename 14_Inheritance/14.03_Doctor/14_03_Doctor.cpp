#include <iostream>
#include <vector>
#include <limits>
#include "14_03_Doctor.h"

const std::vector<std::string> SPECIALITIES = {"Pediatrician", "Obstetrician", "General practitioner"};

namespace
{
	std::string inputValidation()
	//   Postcondition: Reads a line of input from the user and returns it. 
	// If the input is empty or invalid, prompts the user to enter a valid input until a non-empty line is entered.
	{
		std::string line;
		while (true)
		{
			if (!std::getline(std::cin, line))
			{
				std::cout << "Not a valid line\n";
				std::cin.clear();
				continue;
			}
			if (!line.empty())	return line;
			std::cout << "Input cannot be empty\n";
		}
	}

	void capitalize(std::string& myString)
	{
		bool firstChar = true;
		for (char& c : myString)
			if (firstChar)
			{
				const unsigned char uc = static_cast<unsigned char>(c);
				c = static_cast<char>(std::toupper(uc));
				firstChar = false;
			}
			else
			{
				const unsigned char uc = static_cast<unsigned char>(c);
				c = static_cast<char>(std::tolower(uc));
			}
	}

	std::string readChoice(const std::string& prompt, const std::vector<std::string>& options)
	//   Postcondition: Helper to read and validate a choice against a fixed list.
	{
		while (true)
		{
			std::cout << prompt << '\n';
			for (size_t idx = 0; idx < options.size(); idx++)
			{
				std::cout << options[idx];
				if (idx != options.size() - 1)
					std::cout << ", ";
				else
					std::cout << '\n';
			}
			std::cout << "Specialty:\n";
			std::string choice = inputValidation();
			capitalize(choice);
			for (const std::string& option : options)
				if (choice == option)
					return choice;
			std::cout << "Not a valid choice. Retry\n";
		}
	}

	double numberValidation()
	{
		double amount;
		while (true)
		{
			if (!(std::cin >> amount))
			{
				std::cout << "Not a valid amount\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (amount > 0.0)	return amount;
			std::cout << "Amount should be greater than or equal to 0\n";
		}
	}
}

namespace myNamespaceEmployees
{


	Doctor::Doctor() : SalariedEmployee(), specialty("No specialty"), fee(0)
	{ /* body intentionally left empty */ }

	Doctor::Doctor(	const std::string& theName, const std::string& theSsn, const double theWeeklySalary, 
					const std::string& theSpecialty, const double theFee)
					: SalariedEmployee(theName, theSsn, theWeeklySalary), fee(theFee)
	{
		bool validSpecialty = false;
		std::string capitalizedSpecialty = theSpecialty;
		capitalize(capitalizedSpecialty);
		
		for (const std::string& s : SPECIALITIES)
			if (capitalizedSpecialty == s)
			{
				specialty = capitalizedSpecialty;
				validSpecialty = true;
				break;
			}
		if (!validSpecialty)	throw std::invalid_argument("Not a valid specialty\n");
	}

	void Doctor::readData()
	{
		std::cout << "Enter a valid doctor's name:\n";
		setName(inputValidation());
		std::cout << "Enter a valid SSN:\n";
		setSsn(inputValidation());
		std::cout << "Enter weekly salary:\n";
		setSalary(numberValidation());
		setNetPay(getSalary());

		specialty = readChoice("Choose a specialty among these", SPECIALITIES);
		std::cout << "Enter office visit fee:\n";
		fee = numberValidation();
	}

	const std::string& Doctor::getSpecialty() const { return specialty; }

	double Doctor::getFee() const { return fee; }

	void Doctor::printCheck()
	{
		std::cout << '\n' << std::string(25, '_') << '\n';
		std::cout << "Pay to the order of " << getName() << '\n';
		std::cout << "$ weekly: " << getNetPay() << '\n';
		std::cout << std::string(25, '_') << '\n';
		std::cout << "Check Stub: NOT NEGOTIABLE\n";
		std::cout << "Employee Number: " << getSsn() << '\n';
		std::cout << "Doctor specialty: " << specialty << '\n';
		std::cout << "Office visit fee: " << fee << '\n';
		std::cout << std::string(25, '_') << '\n';
	}

} // myNamespaceEmployees
