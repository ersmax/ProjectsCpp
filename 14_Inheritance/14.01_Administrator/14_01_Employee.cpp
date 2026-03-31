//   This is the file 14_01_Employee.cpp.
// This is the implementation for the class Employee.
// The interface for the class Employee is in the header 
// file 14_01_Employee.h.

#include <iostream>
#include "14_01_Employee.h"

namespace myNamespaceEmployees
{
	Employee::Employee() : name("No name"), ssn("No number"), netPay(0)
	{ /* Body intentionally left empty */ }

	Employee::Employee(const std::string& theName, const std::string& theSsn) : name(theName), ssn(theSsn), netPay(0)
	{ /* Body intentionally left empty */ }

	std::string Employee::getName() const { return name; }

	std::string Employee::getSsn() const { return ssn; }

	double Employee::getNetPay() const { return netPay; }

	void Employee::setName(const std::string& newName) { name = newName; }

	void Employee::setSsn(const std::string& newSsn) { ssn = newSsn; }

	void Employee::setNetPay(const double newNetPay) { netPay = newNetPay; }

	void Employee::printCheck()
	{
		std::cout	<< "\nERROR: printCheck FUNCTION CALLED FOR AN UNDIFFERENTIATED EMPLOYEE.\n"
					<< "Aborting the program.\n"
					<< "Check with the author of the program about this bug.\n";
		std::exit(1);
	}

} // myNamespaceEmployees
