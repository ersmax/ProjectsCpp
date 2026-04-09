#include <string>
#include "14_11_Validation.h"

namespace myNamespaceValidation
{
	void readName(std::istream& inputStream, std::string& aName)
	{
		while (true)
		{
			if (!std::getline(inputStream, aName))
			{
				std::cout << "Wrong input\n";
				inputStream.clear();
				continue;
			}
			return;
		}
	}

	void readName(std::istream& inputStream, char& aName)
	{
		while (true)
		{
			if (!(inputStream >> aName))
			{
				std::cout << "Wrong input\n";
				inputStream.clear();
				inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}
	}

} // myNamespaceValidation
