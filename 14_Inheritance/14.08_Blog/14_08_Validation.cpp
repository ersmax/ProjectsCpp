#include "14_08_Validation.h"

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


namespace myNamespaceValidation
{
	void readText(std::istream& inputStream, std::string& theText)
	{
		while (true)
		{
			if (!std::getline(inputStream, theText))
			{
				std::cout << "Not a valid text.\n";
				inputStream.clear();
				continue;
			}
			return;
		}
	}

	void readNumber(std::istream& inputStream, int& theNumber)
	{
		readNumberImpl(inputStream, theNumber);
	}

} // myNamespaceValidation
