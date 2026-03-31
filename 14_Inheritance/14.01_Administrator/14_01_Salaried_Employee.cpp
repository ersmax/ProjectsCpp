//   This is the file 14_01_Salaried_Employee.cpp.
// This is the implementation file for the class SalariedEmployee.
// The interface for the class SalariedEmployee is in the header 
// file 14_01_Salaried_Employee.h.

#include <iostream>
#include "14_01_Salaried_Employee.h"

namespace myNamespaceEmployees
{
	SalariedEmployee::SalariedEmployee() : Employee(), salary(0)
	{ /* Body intentionally left empty */ }

	SalariedEmployee::SalariedEmployee(	const std::string& theName, 
										const std::string& theSsn,
										const double theWeeklySalary)
										: Employee(theName, theSsn), salary(theWeeklySalary)  
	{ /* Body intentionally left empty */ }

	void SalariedEmployee::setSalary(const double newSalary) { salary = newSalary; }

	double SalariedEmployee::getSalary() const { return salary; }

	void SalariedEmployee::printCheck()
	{
		setNetPay(salary);
		std::cout << '\n' << std::string(25, '_') << '\n';
		std::cout << "Pay to the order of " << getName() << '\n';
		std::cout << "The sum of " << getNetPay() << " Dollars\n";
		std::cout << std::string(25, '_') << '\n';
		std::cout << "Check Stub: NOT NEGOTIABLE\n";
		std::cout << "Employee Number: " << getSsn() << '\n';
		std::cout << "Salaried Employee. Regular Pay: " << salary << '\n';
		std::cout << std::string(25, '_') << '\n';
	}
} // myNamespaceEmployees
