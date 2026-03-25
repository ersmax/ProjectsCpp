#ifndef SECURITY_11_04_H
#define SECURITY_11_04_H

#include <string>
#include <vector>

extern const std::vector<int> PRIVILEGES;
// 1 = user | 2 == admin

class Security
{
public:
	Security();
	Security(std::string user, std::string pwd, int userType);
	int validate(const std::string& user, const std::string& pwd) const;
	//   Postcondition:
	// This subroutine returns 0 if the credentials are invalid, 1 if valid user, and 2 if valid administrator.

	friend std::istream& operator >>(std::istream& inputStream, Security& myLogin);
	//   Precondition: inputStream is a valid input stream and myLogin is a Security object.
	//   Postcondition: This function prompts the user to enter a valid username, password, 
	// and privileges (1 for user, 2 for admin). It validates the input and updates 
	// the myLogin object with the provided credentials.

private:
	std::string username;
	std::string password;
	int privilege;
};

#endif
