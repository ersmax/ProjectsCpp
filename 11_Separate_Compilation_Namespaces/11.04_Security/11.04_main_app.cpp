#include <iostream>
#include "11.04_Security.h"
#include "11.04_Administrator.h"
#include "11.04_User.h"

int main( )
{
	std::vector<Security> rooster;
	Security aUser;
	std::cin >> aUser;
	rooster.push_back(aUser);
	std::cin >> aUser;
	rooster.push_back(aUser);

	char answer;
	do {
		std::cout << "Check user (\"u\") or admin (\"a\")?\n";
		std::cin >> answer;
		switch (answer)
		{
		case 'a':
			if (Administrator::Login(rooster))
				std::cout << "This is an admin\n";
			break;
		case 'u':
			if (User::Login(rooster))
				std::cout << "This is a user\n";
			break;
		default:
			std::cout << "Not a valid choice\n";
			break;

		}

		std::cout << "Continue? (y/n)";
		std::cin >> answer;

	} while (std::tolower(answer) == 'y');

	std::cout << '\n';
	return 0;
}