#include "14_09_Validation.h"

namespace
{
	template <typename T>
	void readNumberImpl(std::istream& inputStream, T& number)
	{
		while (true)
		{
			if (!(inputStream >> number))
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

namespace myNamespaceValidation
{
	void readNumber(std::istream& inputStream, int& number)
	{
		readNumberImpl(inputStream, number);
	}
} // myNamespaceValidation