#include <iostream>
#include <cctype>
#include "11.04_Security.h"
#include "11.04_Administrator.h"
#include "11.04_User.h"

void test(const std::vector<Security>& roosterUsers);
//   Precondition: roosterUsers is a vector of Security objects 
// that have been initialized with user credentials.
//   Postcondition: This function prompts the user to check if a user or admin is logging in,
// and then calls the appropriate Login function to verify the credentials. 
// The function continues to prompt the user until they choose to stop.

int main( )
{
	std::vector<Security> rooster;
	Security aUser;
	std::cin >> aUser;
	rooster.push_back(aUser);
	std::cin >> aUser;
	rooster.push_back(aUser);

	test(rooster);
	

	std::cout << '\n';
	return 0;
}

void test(const std::vector<Security>& roosterUsers)
{
	Security aUser;
	char answer;
	do {
		std::cout << "Check user (\"u\") or admin (\"a\")?\n";
		std::cin >> answer;
		switch (answer)
		{
		case 'a':
			if (Administrator::Login(roosterUsers))
				std::cout << "This is an admin\n";
			break;
		case 'u':
			if (User::Login(roosterUsers))
				std::cout << "This is a user\n";
			break;
		default:
			std::cout << "Not a valid choice\n";
			break;

		}
		std::cout << "Continue? (y/n)";
		std::cin >> answer;

	} while (std::tolower(static_cast<unsigned char>(answer)) == 'y');
}
