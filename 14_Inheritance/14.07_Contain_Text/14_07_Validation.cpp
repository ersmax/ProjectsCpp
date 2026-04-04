#include "14_07_Validation.h"

#include <string>

namespace myNamespaceValidation
{
	void readText(std::istream& inputStream, std::string& myText)
	{
		while (true)
		{
			if (!std::getline(inputStream, myText))
			{
				std::cout << "Input not valid\n";
				inputStream.clear();
				continue;
			}
			return;
		}
	}

} // myNamespaceValidation
