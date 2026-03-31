/*
Write a program that uses the class SalariedEmployee given in Display 14.4.
Your program is to define a derived class called Administrator, which is to be
derived from the class SalariedEmployee. You are allowed to change private in
the base class to protected. You are to supply the following additional data and
function members:
■ A member variable of type string that contains the administrator’s title, (such
as Director or Vice President).
■ A member variable of type string that contains the company area of responsibility
(such as Production, Accounting, or Personnel).
■ A member variable of type string that contains the name of this administrator’s
immediate supervisor.
■ A protected member variable of type double that holds the administrator’s
annual salary. It is possible for you to use the existing salary member if you
changed private in the base class to protected.
■ A member function called setSupervisor, which changes the supervisor name.
■ A member function for reading in an administrator’s data from the keyboard.
■ A member function called print, which outputs the object’s data to the screen.
■ Finally, an overloading of the member function printCheck( ) with appropriate
notations on the check.
*/


//   This is the header file 14_01_Employee.h
// This is the interface for the class Employee.
//   This is primarily intended to be used as a base class 
// to derive classes for different kinds of employees.

#ifndef EMPLOYEE_14_01_H
#define EMPLOYEE_14_01_H

#include <string>

namespace myNamespaceEmployees
{
	class Employee
	{
	public:
		Employee();
		Employee(const std::string& theName, const std::string& theSsn);
		std::string getName() const;
		std::string getSsn() const;
		double getNetPay() const;
		void setName(const std::string& newName);
		void setSsn(const std::string& newSsn);
		void setNetPay(double newNetPay);
		static void printCheck();
	private:
		std::string name;
		std::string ssn;
		double netPay;
	};
} // myNamespaceEmployees


#endif // EMPLOYEE_14_01_H
