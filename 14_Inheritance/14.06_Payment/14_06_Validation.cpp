#include <limits>
#include <string>
#include "14_06_Validation.h"

namespace
{
	template<typename T>
	void readNumberImpl(std::istream& inputStream, T& number)
	//   Postcondition: Reading  numeric types from a stream
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
	void readNumber(std::istream& inputStream, float& number)
	{
		readNumberImpl(inputStream, number);
	}

	void readNumber(std::istream& inputStream, int& number)
	{
		readNumberImpl(inputStream, number);
	}

	void readInput(std::istream& inputStream, std::string& input)
	{
		while (true)
		{
			if (!std::getline(inputStream, input))
			{
				std::cout << "Not a valid input\n";
				inputStream.ignore();
				continue;
			}
			return;
		}
	}
} // myNamespaceValidation
