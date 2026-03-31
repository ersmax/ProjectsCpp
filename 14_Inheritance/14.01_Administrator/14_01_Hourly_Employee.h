//   This is the header file 14_01_Hourly_Employee.
// This is the interface for the class HourlyEmployee.

#ifndef HOURLY_EMPLOYEE_14_0_01_H
#define HOURLY_EMPLOYEE_14_0_01_H

#include "14_01_Employee.h"

namespace myNamespaceEmployees
{
	class HourlyEmployee : public Employee
	{
	public:
		HourlyEmployee( );
		HourlyEmployee(	const std::string& theName, const std::string& theSsn,
						double theWageRate, double theHours);
		void setRate(double newWageRate);
		void setHours(double hoursWorked);
		double getRate() const;
		double getHours() const;
		void printCheck();
		// Override base class function behavior of printCheck()
	private:
		double wageRate;
		double hours;
	};
	
} // myNamespaceEmployees

#endif // HOURLY_EMPLOYEE_14_01_H