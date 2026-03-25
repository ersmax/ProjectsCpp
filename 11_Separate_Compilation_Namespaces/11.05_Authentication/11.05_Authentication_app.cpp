#include <iostream>
#include "11.05_User.h"
#include "11.05_Password.h"

int main( )
{
	Authenticate::inputUserName();
	Authenticate::inputPassword();

	std::cout << "Your username is " << Authenticate::getUserName() << '\n';
	std::cout << "Your password is " << Authenticate::getPassword() << '\n';

	std::cout << '\n';
	return 0;
}