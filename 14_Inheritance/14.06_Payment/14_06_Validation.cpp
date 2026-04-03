#include <limits>
#include "14_06_Validation.h"

namespace myNamespaceValidation
{
	void readNumber(std::istream& inputStream, float& number)
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

} // myNamespaceValidation
