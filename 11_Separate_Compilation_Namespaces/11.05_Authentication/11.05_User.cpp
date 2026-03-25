#include <iostream>
#include "11.05_User.h"

namespace
{
	std::string username;

	bool isValid()
	{
		if (username.length() != 8)	return false;

		for (const unsigned char c : username)
			if (!std::isalpha(c))
				return false;
		
		return true;
	};
} // unnamed namespace

namespace Authenticate
{
	void inputUserName()
	{
		do
		{
			std::cout << "Enter your username (8 letters only)\n";
			std::cin >> username;
		} while (!isValid());
	}
	
	std::string getUserName()
	{
		return username;
	}
} // namespace Authenticate
