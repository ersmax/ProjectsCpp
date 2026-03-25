#ifndef USER_11_05_H
#define USER_11_05_H

#include <string>

namespace Authenticate
{
	void inputUserName();
	//   Postcondition: The user is prompted to enter a username 
	// that is exactly 8 letters long.

	std::string getUserName();
	//   Postcondition: The username entered by the user is returned.
}

#endif

