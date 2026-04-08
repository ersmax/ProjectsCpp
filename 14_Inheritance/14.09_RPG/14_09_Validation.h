#ifndef VALIDATION_14_09_H
#define VALIDATION_14_09_H

#include <iostream>

namespace myNamespaceValidation
{
	void readNumber(std::istream& inputStream, int& number);
	//   Postcondition: Read a number from the input stream and store it in number.
	void readLetter(std::istream& inputStream, char& letter);
	//   Postcondition: Read a letter from the input stream and store it in letter.

} // myNamespaceValidation

#endif // VALIDATION_14_09_H