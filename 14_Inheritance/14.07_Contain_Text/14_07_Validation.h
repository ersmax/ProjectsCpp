#ifndef VALIDATION_14_07_H
#define VALIDATION_14_07_H

#include <iostream>

namespace myNamespaceValidation
{
	void readText(std::istream& inputStream, std::string& myText);
	//   Precondition: inputStream is open, myText is a valid string variable.
	//   Postcondition: inputStream has been modified to read a string into myText.
}

#endif
