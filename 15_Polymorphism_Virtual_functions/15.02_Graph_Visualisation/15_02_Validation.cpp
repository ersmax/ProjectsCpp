#include "15_02_Validation.h"

namespace
{
	template <typename T>
	void readNumberImpl(std::istream& inputStream, T& theNumber)
	{
		while (true)
		{
			if (!(inputStream >> theNumber))
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

namespace myValidation
{
	void readNumber(std::istream& inputStream, double& theNumber)
	{
		readNumberImpl(inputStream, theNumber);
	}

	void readNumber(std::istream& inputStream, int& theNumber)
	{
		readNumberImpl(inputStream, theNumber);
	}

	void readName(std::istream& inputStream, std::string& theName)
	{
		while (true)
		{
			if (!std::getline(inputStream, theName))
			{
				std::cout << "Not a valid name\n";
				inputStream.clear();
				continue;
			}
			return;
		}
	}

} // myValidation