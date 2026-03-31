/*
Add temporary, administrative, permanent, and other classifications of employees
to the hierarchy from Displays 14.1, 14.3, and 14.4. Implement and test this
hierarchy.
Test all member functions. A user interface with a menu would be a nice
touch for your test program.
*/

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
			void showEmployee();
			void getNumberEmployees() const;
		private:
			std::vector<std::unique_ptr<Employee>> employees;
			static int hourlyEmployees;
			static int salariedEmployees;
			static int administratorEmployees;
		}; 

} // myNamespaceMenu

#endif // MENU_14_02_H



