#ifndef PASSWORD_11_05_H
#define PASSWORD_11_05_H

#include <string>

namespace Authenticate
{
	void inputPassword();
	//   Postcondition: The user is prompted to enter a password 
	// that is at least 8 characters long and contains at least one non-letter character. 
	// The password is stored in a variable in the unnamed namespace.

	std::string getPassword();
	//   Postcondition: The password entered by the user is returned.
}

#endif