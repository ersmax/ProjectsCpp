#ifndef VALIDATION_14_11_h
#define VALIDATION_14_11_h

#include <iostream>

namespace myNamespaceValidation
{
	void readName(std::istream& inputStream, std::string& aName); 
	//   Postcondition: Read the name input from the user. 
	void readName(std::istream& inputStream, char& aName);
	//   Postcondition: Read the character input from the user.

} // myNamespaceValidation


#endif // VALIDATION_14_11_h
