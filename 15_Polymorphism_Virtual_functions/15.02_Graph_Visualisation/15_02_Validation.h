#ifndef VALIDATION_15_02_H
#define VALIDATION_15_02_H

#include <iostream>
#include <string>

namespace myValidation
{
	void readNumber(std::istream& inputStream, double& theNumber);
	//   Postcondition: inputs a number from inputStream and stores it in number. 
	void readNumber(std::istream& inputStream, int& theNumber);
	//   Postcondition: inputs a number from inputStream and stores it in number. 
	void readName(std::istream& inputStream, std::string& theName);
	//   Postcondition: inputs a name from inputStream and stores it in name.

} // myValidation


#endif // VALIDATION_15_02_H
