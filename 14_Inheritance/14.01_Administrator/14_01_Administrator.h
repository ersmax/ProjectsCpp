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