#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <string>

namespace myNamespaceValidation
{
	void readText(std::istream& inputStream, std::string& theText);
	void readNumber(std::istream& inputStream, int& theNumber);

} // myNamespaceValidation

#endif // VALIDATION_H