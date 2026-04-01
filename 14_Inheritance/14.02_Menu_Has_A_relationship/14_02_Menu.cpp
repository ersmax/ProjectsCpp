#include <iomanip>
#include <iostream>
#include <limits>
#include "14_02_Menu.h"


using myNamespaceEmployees::Administrator;
using myNamespaceEmployees::SalariedEmployee;
using myNamespaceEmployees::HourlyEmployee;

typedef SalariedEmployee *SalariedPtr;
typedef Administrator *AdministratorPtr;
typedef HourlyEmployee *HourlyPtr;
typedef Employee *EmployeePtr;

namespace 
{
	std::string nameValidation()
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

	const Administrator addAdministrator()
	//   Postcondition: Add administrator to the vector of employees
	{
		Administrator anAdmin;
		anAdmin.readData();
		return anAdmin;
	}

	const SalariedEmployee addSalaried()
	//   Postcondition: Add salaried employee to the vector of employees
	{
		SalariedEmployee aSalaried;
		std::cout << "Enter salaried employee name:\n";
		aSalaried.setName(nameValidation());
		std::cout << "Enter salaried employee SSN:\n";
		aSalaried.setSsn(nameValidation());
		std::cout << "Enter weekly salary:\n";
		aSalaried.setSalary(numberValidation());
		aSalaried.setNetPay(aSalaried.getSalary());
		return aSalaried;
	}

	const HourlyEmployee addHourly()
	//   Postcondition: Add hourly employee to the vector of employees
	{
		HourlyEmployee anHourly;
		std::cout << "Enter hourly employee name:\n";
		anHourly.setName(nameValidation());
		std::cout << "Enter hourly employee SSN:\n";
		anHourly.setSsn(nameValidation());
		std::cout << "Enter hourly wage rate:\n";
		anHourly.setRate(numberValidation());
		std::cout << "Enter hours worked:\n";
		anHourly.setHours(numberValidation());
		anHourly.setNetPay(anHourly.getRate() * anHourly.getHours());
		return anHourly;
	}

	void showSalaried(const std::vector<std::unique_ptr<Employee>>& employees)
	//   Postcondition: show only Salaried class
	{
		for (const auto& e : employees)
			if (const SalariedPtr salaried = dynamic_cast<SalariedPtr>(e.get()))
			// if the real object is a SalariedEmployee (or a class derived from it, 
			// like Administrator), the cast succeeds and returns a non‑null pointer.
				salaried->printCheck();
	}

	void showAdministrators(const std::vector<std::unique_ptr<Employee>>& employees)
	//   Postcondition: show only Administrator class
	{
		for (const auto& e : employees)
			if (const AdministratorPtr admin = dynamic_cast<AdministratorPtr>(e.get()))
				admin->printCheck();
	}

	void showHourly(const std::vector<std::unique_ptr<Employee>>& employees)
	//   Postcondition: show only Hourly
	{
		for (const auto& e : employees)
			if (const HourlyPtr hourly = dynamic_cast<HourlyPtr>(e.get()))
				hourly->printCheck();
	}

	void showAll(const std::vector<std::unique_ptr<Employee>>& employees)
	//   Postcondition: show every employee using dynamic dispatch
	{
		for (const auto& e : employees)
			e->printCheck();
	}

} // unnamed namespace

namespace myNamespaceMenu
{
	int Menu::hourlyEmployees = 0;
	int Menu::salariedEmployees = 0;
	int Menu::administratorEmployees = 0;

	char choiceValidation()
	{
		char choice;
		while (true)
		{
			if (!(std::cin >> choice))
			{
				std::cout << "Not a valid choice\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return choice;
		}
	}

	Menu::Menu()
	{ /* body intentionally left empty */ }

	void Menu::addEmployee()
	{
		std::cout << "Add Hourly employee ('h'), Salaried employee ('s') or Administrator ('a')?\n";
		char type = choiceValidation();
		switch (type)
		{
       case 'a':
		{
			std::unique_ptr<Administrator> admin = std::make_unique<Administrator>(addAdministrator());
			// allocate an Administrator on the heap and wrap it in a unique_ptr.
			employees.push_back(std::move(admin));
			// transfer ownership of the unique_ptr from admin to the vector.
			salariedEmployees++;
			administratorEmployees++;
			break;
		}
		case 's':
		{
			std::unique_ptr<SalariedEmployee> salaried = std::make_unique<SalariedEmployee>(addSalaried());
			employees.push_back(std::move(salaried));
			salariedEmployees++;
			break;
		}
		case 'h':
		{
			std::unique_ptr<HourlyEmployee> hourly = std::make_unique<HourlyEmployee>(addHourly());
			employees.push_back(std::move(hourly));
			hourlyEmployees++;
			break;
		}
		default:
			std::cout << "Not a valid employee\n";
			break;
		}
	}

	void Menu::showEmployee()
	{
		std::cout << "Show Hourly employee ('h'), Salaried employee ('s'), Administrator ('a'), or Everybody ('e')?\n";
		char type = choiceValidation();
		switch (type)
		{
		case 'a':
			showAdministrators(employees);
			break;
		case 's':
			showSalaried(employees);
			break;
		case 'h':
			showHourly(employees);
			break;
		case 'e':
			showAll(employees);
			break;
		default:
			std::cout << "Not a valid choice\n";
			break;
		}
	}

    void Menu::getNumberEmployees() const
	{
		std::cout << std::setw(30)	<< "Number of employees: " << employees.size() << '\n';
		std::cout << std::setw(30)	<< "Number of hourly employees: " << hourlyEmployees << '\n';
		std::cout << std::setw(30)	<< "Number of salaried employees: " << salariedEmployees 
									<< "(of whom are administrators) : " << administratorEmployees << '\n';
   }
}
