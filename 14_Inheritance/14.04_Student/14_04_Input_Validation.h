#ifndef INPUT_VALIDATION_14_04_H
#define INPUT_VALIDATION_14_04_H

#include <string>
#include <iostream>
#include <istream>
#include <limits>

namespace myNamespaceValidation
{
	void readName(std::istream& inputStream, std::string& myString);
	void readNumber(std::istream& inputStream, int& aNumber);

	template <typename T>
	void readObject(std::istream& inputStream, T& object)
	//    Postcondition: Generic reader that uses operator >> on the object and retries on failure.
	// Defined in the header so it can be used with any type in other translation units.
	{
		while (true)
		{
			if (inputStream >> object) return;
			std::cout << "Wrong input\n";
			inputStream.clear();
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

} // myNamespaceValidation

#endif // INPUT_VALIDATION_14_04_H
