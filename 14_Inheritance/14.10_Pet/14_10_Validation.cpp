#include <string>
#include "14_10_Validation.h"

namespace
{
	template <typename T>
	void readNumberImpl(std::istream& inputStream, T& number)
	{
		while (true)
		{
			if (!(inputStream >> number))
			{
				std::cout << "Not a valid input\n";
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

	void readName(std::istream& inputStream, std::string& name)
	{
		while (true)
		{
			if (!std::getline(inputStream, name))
			{
				std::cout << "Not a valid input\n";
				inputStream.clear();
				continue;
			}
			return;
		}
	}
} // myNamespaceValidation
