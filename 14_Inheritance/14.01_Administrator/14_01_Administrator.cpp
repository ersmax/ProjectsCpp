//   This is the implementation file 14_01_Administrator.cpp.
// It represents the implementation of the class Administrator 
// defined in the header file 14_01_Administrator.h.

#include <iomanip>
#include <iostream>
#include <cctype>
#include <vector>
#include "14_01_Administrator.h"

constexpr int WEEKS = 52;
const std::vector<std::string> TITLES = {"Director", "Vice president"};
const std::vector<std::string> RESPONSIBILITIES = {"Production", "Accounting", "Personnel"};

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
				std::cout << "Not a valid input\n";
				std::cin.clear();
				continue;
			}
			if (!line.empty())	return line;
			
			std::cout << "Input cannot be empty\n";
		}
	}

	void capitalize(std::string& myString)
	//   Postcondition: Modifies the input string so that the first character is uppercase
	// and the rest are lowercase.
	{
		bool firstChar = true;
		for (char& c : myString)
		{
			const unsigned char uc = static_cast<unsigned char>(c);
			if (firstChar)
			{
				c = static_cast<char>(std::toupper(uc));
				firstChar = false;
			}
			else
				c = static_cast<char>(std::tolower(uc));
		}
	}

	std::string readChoice(const std::string& prompt, const std::vector<std::string>& options)
	//    Postcondition: Helper to read and validate a choice against a fixed list.
	{
		while (true)
		{
			std::cout << prompt;
			for (const std::string& option : options)
				std::cout << option << " ";
			std::cout << '\n';

			std::string input = inputValidation();
			capitalize(input);

			for (const std::string& option : options)
				if (input == option)
					return input;

			std::cout << "Not a valid choice. Retry\n";
		}
	}
}

namespace myNamespaceEmployees
{
	Administrator::Administrator() : SalariedEmployee(), 
										title("No title"), areaResponsibility("No area"),
										nameSupervisor("No name"), annualSalary(0)
	{ /* body intentionally left empty */ }

	Administrator::Administrator(const std::string& theName, const std::string& theSsn,
								const double theWeeklySalary, const std::string& theTitle, 
								const std::string& theArea, const std::string& theSupervisor) 
								: SalariedEmployee(theName, theSsn, theWeeklySalary), nameSupervisor(theSupervisor)
	{
		bool foundTitle = false, foundArea = false;
		std::string normTitle = theTitle;
		std::string normArea = theArea;
		capitalize(normTitle);
		capitalize(normArea);
		for (const std::string& option : TITLES)
			if (normTitle == option)
			{
				title = normTitle;
				foundTitle = true;
				break;
			}
		if (!foundTitle)	throw std::invalid_argument("Not a valid title\n");

		for (const std::string& option : RESPONSIBILITIES)
			if (normArea == option)
			{
				areaResponsibility = normArea;
				foundArea = true;
				break;
			}
		if (!foundArea)	throw std::invalid_argument("Not a valid area of responsibility\n");

		annualSalary = WEEKS * getSalary();
	}

	void Administrator::readData()
	{
		std::cout << "Enter administrator's name:\n";
		setName(inputValidation());
		std::cout << "Enter ssn:\n";
		setSsn(inputValidation());
		std::cout << "Enter weekly salary:\n";
		int salary;
		std::cin >> salary;
		setSalary(salary);
		
		title = readChoice("Choose a valid title among these: ", TITLES);
		areaResponsibility = readChoice("Choose a valid area of responsibilities among these: ", RESPONSIBILITIES);
		std::cout << "Enter supervisor name: ";
		nameSupervisor = inputValidation();
		annualSalary = WEEKS * getSalary();
	}

	void Administrator::setSupervisor(const std::string& theSupervisor)
	{
		nameSupervisor = theSupervisor;
	}

	void Administrator::print() const
	{
		std::cout << std::setw(15) << "Name: " << getName() << '\n';
		std::cout << std::setw(15) << "Title: " << title << '\n';
		std::cout << std::setw(15) << "Area: " << areaResponsibility << '\n';
		std::cout << std::setw(15) << "Annual salary: " << annualSalary << '\n';
		std::cout << std::setw(15) << "Supervisor: " << nameSupervisor << '\n';
	}

	void Administrator::printCheck()
	{
		setNetPay(annualSalary);
		std::cout << '\n' << std::string(25, '_') << '\n';
		std::cout << "Pay to the order of " << getName() << '\n';
		std::cout << "The sum of " << getNetPay() << " Dollars (annual)\n";
		std::cout << std::string(25, '_') << '\n';
		std::cout << "Check Stub: NOT NEGOTIABLE\n";
		std::cout << "Employee Number: " << getSsn() << '\n';
		std::cout << "Administrator Annual Pay: " << getSalary() * 52 << '\n';
		std::cout << std::string(25, '_') << '\n';
	}
}
