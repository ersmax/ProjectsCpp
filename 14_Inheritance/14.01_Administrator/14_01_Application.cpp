//   This is the application file to test the derived class SalariedEmployee

#include <iostream>
#include <stdexcept>
#include "14_01_Administrator.h"


int main()
{
	using myNamespaceEmployees::Administrator;

	try
	{
		std::string role = "dIRECTOR";
		std::string area = "accOunting";
		std::string area2 = "prodUCtion";
		Administrator bob("Mr. Big Shot", "987-65-4321", 10500.50, role, area, "John Doe");
		std::cout << "Check for " << bob.getName() << '\n';
		bob.setSupervisor("Gianni");
		bob.printCheck();
		std::cout << "Check for " << bob.getName() << '\n';
		bob.printCheck();

		Administrator joe;
		joe.readData();
		joe.printCheck();
	} catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << '\n';
	}

	std::cout << '\n';
	return 0;
}