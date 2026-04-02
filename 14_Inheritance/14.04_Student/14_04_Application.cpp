#include <iostream>
#include "14_04_Science_Student.h"

int main( )
{
	using myNamespaceUniversity::ScienceStudent;
	ScienceStudent aStudent;

	std::cout << "Enter the credentials of the Science Student below\n\n";
	std::cin >> aStudent;

	std::cout << "The details of another student are:\n";
	const ScienceStudent aStudent2(aStudent);
	std::cout << aStudent2;

	ScienceStudent aStudent3;
	aStudent3 = aStudent2;
	std::cout << "The details of a third student are:\n";
	std::cout << aStudent3;

	std::cout << '\n';
	return 0;
}