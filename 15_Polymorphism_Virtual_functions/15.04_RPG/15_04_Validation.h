#ifndef VALIDATION_15_04_H
#define VALIDATION_15_04_H
#include <iosfwd>

namespace myValidation
{
	void readNumber(std::istream& inputStream, int& theNumber);
	//  Postcondition: Reads an integer from the input stream and stores it in theNumber.

} // myValidation

#endif // VALIDATION_15_04_H
