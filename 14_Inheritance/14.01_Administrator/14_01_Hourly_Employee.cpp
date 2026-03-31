//   This is the file 14_01_Hourly_Employee.cpp.
// This is the implementation for the class HourlyEmployee.
// The interface for the class HourlyEmployee is in the header
// file 14_01_Hourly_Employee.h.

#include <iostream>
#include "14_01_Hourly_Employee.h"

namespace myNamespaceEmployees
{
	HourlyEmployee::HourlyEmployee() : Employee(), wageRate(0), hours(0)
	{ /* Body intentionally left empty */ }

	HourlyEmployee::HourlyEmployee(	const std::string& theName, 
									const std::string& theSsn,
									const double theWageRate, 
									const double theHours)
	
									: Employee(theName, theSsn), wageRate(theWageRate), hours(theHours) 

	{ /* Body intentionally left empty */ }

	void HourlyEmployee::setRate(const double newWageRate) { wageRate = newWageRate; }

	void HourlyEmployee::setHours(const double hoursWorked) { hours = hoursWorked; }

	double HourlyEmployee::getHours() const { return hours; }

	double HourlyEmployee::getRate() const { return wageRate; }

	void HourlyEmployee::printCheck()
	{
		setNetPay(hours * wageRate);
		std::cout << '\n' << std::string(25, '_') << '\n';
		std::cout << "Pay to the order of " << getName() << '\n';
		std::cout << "The sum of " << getNetPay() << " Dollars\n";
		std::cout << std::string(25, '_') << '\n';
		std::cout << "Check Stub: NOT NEGOTIABLE\n";
		std::cout << "Employee Number: " << getSsn() << '\n';
		std::cout << "Hourly Employee. \nHours Worked: " << hours;
		std::cout << " Rate: " << wageRate << " Pay: " << getNetPay() << '\n';
		std::cout << std::string(25, '_') << '\n';
	}

} // myNamespaceEmployees
