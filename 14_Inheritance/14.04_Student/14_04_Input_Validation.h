#ifndef INPUT_VALIDATION_14_04_H
#define INPUT_VALIDATION_14_04_H

#include <string>
#include <iostream>
#include <istream>
#include <limits>

namespace myNamespaceValidation
{
	void readName(std::istream& inputStream, std::string& myString);
	//   Precondition: The input stream is open and ready for input. myString is a reference to a string variable.
	//   Postcondition: A string has been read from the input stream and stored in myString. 
	// The string must not be empty and must not contain any digits. 
	// If the input is invalid, the user is prompted to re-enter the string until a valid string is entered.
	void readNumber(std::istream& inputStream, int& aNumber);
	//   Precondition: The input stream is open and ready for input. aNumber is a reference to an int variable.
	//   Postcondition: An integer has been read from the input stream and stored in aNumber.
	template <typename T>
	void readObject(std::istream& inputStream, T& object)
	//   Precondition: The input stream is open and ready for input. 
	// object is a reference to a variable of any type that has an overloaded operator >> defined for it.
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
