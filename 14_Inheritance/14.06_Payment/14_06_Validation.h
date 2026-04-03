#ifndef VALIDATION_14_06_H
#define VALIDATION_14_06_H

#include <iostream>

namespace myNamespaceValidation
{
	void readNumber(std::istream& inputStream, float& number);
	//   Precondition: inputStream is open, number is a valid float variable.
	//   Postcondition: inputStream has been modified to read a number into number.
	void readNumber(std::istream& inputStream, int& number);
	void readInput(std::istream& inputStream, std::string& input);
	//   Precondition: inputStream is open, input is a valid string variable.
	//   Postcondition: inputStream has been modified to read a string into input.

} // myNamespaceValidation

#endif // VALIDATION_14_06_H
