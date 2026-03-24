#include <iostream>
#include "11.04_Administrator.h"

namespace
{
	std::string nameValidation()
	{
		std::string name;
		while (true)
		{
			if (!(std::cin >> name))
			{
				std::cout << "Not a valid input\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return name;
		}
	}
}

bool Administrator::Login(const std::vector<Security>& users)
{
	std::cout << "Enter a username:\n";
	const std::string name = nameValidation();
	std::cout << "Enter a password:\n";
	const std::string pwd = nameValidation();
	
	for (const Security& user : users)
	{
		// check name == user.username && pwd == user.password
		const int userPrivilege = user.validate(name, pwd);
		if (userPrivilege == PRIVILEGES[1])		// PRIVILEGES[1] : admin
			return true;
	}
	return false;
}
