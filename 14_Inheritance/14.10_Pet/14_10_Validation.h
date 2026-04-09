#ifndef VALIDATION_14_10_H
#define VALIDATION_14_10_H

#include <iostream>

namespace myNamespaceValidation
{
	void readNumber(std::istream& inputStream, int& number);
	//   Postcondition: inputs a number from inputStream and stores it in number. 
	void readName(std::istream& inputStream, std::string& name);
	//   Postcondition: inputs a name from inputStream and stores it in name.

} // myNamespaceValidation

#endif // VALIDATION_14_10_H