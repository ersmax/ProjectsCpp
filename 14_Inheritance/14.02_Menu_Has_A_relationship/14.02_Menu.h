#ifndef MENU_14_02_H
#define MENU_14_02_H

#include <memory>
#include <vector>
#include "../14.01_Administrator/14_01_Hourly_Employee.h"
#include "../14.01_Administrator/14_01_Administrator.h"
using myNamespaceEmployees::Employee;

namespace myNamespaceMenu
{

	class Menu
	{
	public:
		Menu();
		void addEmployee();
		//   Precondition: we want to avoid object slicing, 
		// that is derived class that is treated as base class
		// (avoid losing derived class extra member definition and overriden printCheck() ).
		//   Postcondition: the employee is added to the vector of unique pointers to Employee objects.
		void showEmployee();
		//   Postcondition: the employee information is displayed by calling the printCheck() 
		// function of each Employee object in the vector of unique pointers to Employee objects.
		void getNumberEmployees() const;
		//   Postcondition: the number of employees in each category (hourly, salaried, administrator) 
		// is displayed.
	private:
		std::vector<std::unique_ptr<Employee>> employees;
		//   Precondition: the vector of unique pointers to Employee objects is initialized 
		// and ready to store Employee objects.
		static int hourlyEmployees;
		static int salariedEmployees;
		static int administratorEmployees;
	}; 
	
	char choiceValidation();
	//   Postcondition: Reads a character of input from the user and returns it.
	// This allows the user to choose between adding an employee or showing employee information,
	// in a menu-fashion style. 
	// The reason is not defined in an unnamed namespace is that 
	// it is used in both Menu member functions and the test function in 14.02_Application.cpp.

} // myNamespaceMenu

#endif // MENU_14_02_H



