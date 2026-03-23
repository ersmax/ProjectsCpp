/*
Obtain the source code for the PFArrayD class and the demonstration program
from Displays 11.10, 10.11, and 10.12. Modify this program to use namespaces
and separate compilation. Put the class definition and other function declarations
in one file. Place the implementations in a separate file. Distribute the namespace
definition across the two files. Place the demonstration program in a third file. To
provide access to names in namespaces, you may use local using declarations such as
using std::cout;
or use local using directives such as
using namespace std;
inside a block, or qualify names using the names of namespaces, such as std::cout.
You may not use global namespace directives such as the following which are not
in a block and apply to the entire file:
using namespace std;
*/


//   This is the application file for a partially filled array of doubles
#include <iostream>
#include <cctype>
#include "11.02_PFArrayD.h"

void testPFArrayD();
//   Postcondition: Conduct one test of the class PFArrayD

int main( )
{
	std::cout << "This program tests the class PFArrayD\n";
	char answer;
	do
	{
		testPFArrayD();
		std::cout << "Test again? (y/n)\n";
		std::cin >> answer;

	} while (std::tolower(answer) == 'y');

	return 0;
}

void testPFArrayD()
{
	int capacity;
	std::cout << "Enter capacity of the array:\n";
	std::cin >> capacity;

	using myNamespace::PFArrayD;
	PFArrayD temp(capacity);

	std::cout << "Enter up to " << capacity << " non negative numbers\n";
	std::cout << "Place a negative number at the end\n";
	std::cin >> temp;
	
	std::cout << "You entered the following " << temp.getNumberUSed() << " numbers:\n";
	std::cout << temp;
}
