#include <iostream>
#include "15_04_Validation.h"

namespace
{
	
	template <typename T>
	void readNumberImpl(std::istream& inputStream, T& theNumber)
	{
		while (true)
		{
			if (!(inputStream >> theNumber))
			{
				std::cout << "Not a valid number\n";
				inputStream.clear();
				inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
	}

} // unnamed namespace

namespace myValidation
{
	void readNumber(std::istream& inputStream, int& theNumber)
	{
		readNumberImpl(inputStream, theNumber);
	}
} // myValidation