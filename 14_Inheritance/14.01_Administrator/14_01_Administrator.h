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

//   This is the header file 14_01_Administrator.h.
// It represents the interface for the class Administrator.

#ifndef ADMINISTRATOR_14_01_H
#define ADMINISTRATOR_14_01_H

#include "14_01_Salaried_Employee.h"

namespace myNamespaceEmployees
{
	class Administrator : public SalariedEmployee
	{
	public:
		Administrator();
		//   Postcondition: name, ssn, title, areaResponsibility, nameSupervisor are set to "No name", 
		// "No number", "No title", "No area", and "No name" respectively. annualSalary is set to 0.
		Administrator(	const std::string& theName, const std::string& theSsn, double theWeeklySalary,
						const std::string& theTitle, const std::string& theArea, const std::string& theSupervisor);
		//   Postcondition: The administrator's name, ssn, weekly salary, title, area of responsibility, 
		// and supervisor are set to the values specified by the parameters. annualSalary is set to 52 times the weekly salary.
		void setSupervisor(const std::string& theSupervisor);
		//   Postcondition: The supervisor's name is set to the value specified by the parameter.
		void readData();
		//   Postcondition: The administrator's name, ssn, weekly salary, title, area of responsibility, 
		// and supervisor are set to values read from the keyboard. annualSalary is set to 52 times the weekly salary.
		void print() const;
		//   Postcondition: The administrator's name, ssn, weekly salary, title, area of responsibility,
		// and supervisor have been printed to the screen.
		void printCheck();
		//   Precondition: Override base class function behavior of printCheck()
		//   Postcondition: The administrator's name, ssn, and annual salary have been printed on a check.
	private:
		std::string title;
		//   Precondition: title must be one of the following: "Director", "Vice President"
		std::string areaResponsibility;
		std::string nameSupervisor;
		double annualSalary;
	};
} // myNamespaceEmployees

#endif // ADMINISTRATOR_14_01_H