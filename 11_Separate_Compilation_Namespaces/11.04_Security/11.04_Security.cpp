#include <iostream>
#include <stdexcept>
#include <limits>
#include "11.04_Security.h"

const std::vector<int> PRIVILEGES = {1, 2};

namespace
{
	void inputValidation(std::istream& inputStream, std::string& name)
	{
		while (true)
		{
			if (!(inputStream >> name))
			{
				std::cout << "Not a valid input\n";
				inputStream.clear();
				inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}

	void inputValidation(std::istream& inputStream, int& number)
	{
		while (true)
		{
			if (!(inputStream >> number))
			{
				std::cout << "Not a valid input\n";
				inputStream.clear();
				inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (number < 1 || number > 2)	// check privileges
				continue;
			break;
		}
	}


} // unnamed namespace

Security::Security() : privilege(1)
{ /* body intentionally left empty */ }

Security::Security(std::string user, std::string pwd, const int userType) : username(std::move(user)), 
																			password(std::move(pwd))
{
	if (userType < 1 || userType > 2)
		throw std::invalid_argument("Not a valid privilege type\n");

	privilege = userType;
}

int Security::validate(const std::string& user, const std::string& pwd) const
{
	if (user == username && pwd == password)
		return privilege;
	
	return 0;
}

std::istream& operator >>(std::istream& inputStream, Security& myLogin)
{
	std::cout << "Enter valid username:\n";
	inputValidation(inputStream, myLogin.username);
	std::cout << "Enter valid password:\n";
	inputValidation(inputStream, myLogin.password);
	std::cout << "Enter valid privileges (1 = user | 2 = admin)\n";
	inputValidation(inputStream, myLogin.privilege);
	return inputStream;
}
