#include <iostream>
#include "14_03_Doctor.h"
using myNamespaceEmployees::Doctor;


int main( )
{
	Doctor joe;
	joe.readData();

	Doctor joe2 = joe;
	joe2.printCheck();

	Doctor joe3(joe2);
	joe3.printCheck();

	std::cout << '\n';
	return 0;
}