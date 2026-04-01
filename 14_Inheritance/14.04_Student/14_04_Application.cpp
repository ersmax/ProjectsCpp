/*
Create a base class called Student that has their university's name (type string),
their registration number (type int), and their proctor (type UniversityStaff
given in the code that follows). Then create a class called ScienceStudent that
is derived from Student and has additional properties science discipline (type
string), undergraduate or postgraduate course (type string). Be sure your classes
have a reasonable complement of constructors and accessor methods, an overloaded
assignment operator, and a copy constructor. Write a driver program that
tests all your methods.
The definition of the class UniversityStaff follows. The implementation of the
class is part of this programming project.

class UniversityStaff
{
public:
	UniversityStaff( );
	UniversityStaff(string theName);
	UniversityStaff(const UniversityStaff& theObject);
	string getName( ) const;
	UniversityStaff& operator=(const UniversityStaff& rtSide);
	friend istream& operator >>(istream& inStream,
	UniversityStaff& staffObject);
	friend ostream& operator <<(ostream& outStream,
	const UniversityStaff& staffObject);
private:
	string name;
};
*/

#include <iostream>
#include "14_04_Science_Student.h"

int main( )
{
	using myNamespaceUniversity::ScienceStudent;
	ScienceStudent aStudent;

	std::cout << "Enter the credentials of the Science Student below\n\n";
	std::cin >> aStudent;

	std::cout << "The details of the student are:\n";
	std::cout << aStudent;

	std::cout << '\n';
	return 0;
}