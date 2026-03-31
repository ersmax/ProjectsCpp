//   This is the header file 14_01_Salaried_Employee.h.
// This is the interface for the class SalariedEmployee.
#ifndef SALARIED_EMPLOYEE_14_01_H
#define SALARIED_EMPLOYEE_14_01_H

#include "14_01_Employee.h"

namespace myNamespaceEmployees
{
	class SalariedEmployee : public Employee
	{
	public:
		SalariedEmployee();
		SalariedEmployee(const std::string& theName, const std::string& theSsn, double theWeeklySalary);
		double getSalary() const;
		void setSalary(double newSalary);
		void printCheck();
		// Override base class function behavior of printCheck()
	private:
		double salary;	// weekly
	};
} // myNamespaceEmployees

#endif // SALARIED_EMPLOYEE_14_01_H