#include <iostream>
#include <limits>
#include "14_04_Input_Validation.h"

namespace myNamespaceValidation
{
	void readName(std::istream& inputStream, std::string& myString)
	{
		while (true)
		{
			if (!std::getline(inputStream, myString))
			{
				std::cout << "Wrong input\n";
				inputStream.clear();
				continue;
			}
			if (!myString.empty())	return;
			std::cout << "Input cannot be empty\n";
		}
	}

	void readNumber(std::istream& inputStream, int& aNumber)
	{
		while (true)
		{
			if (!(inputStream >> aNumber))
			{
				std::cout << "Wrong number\n";
				inputStream.clear();
				inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
	}

} // myNamespaceValidation
