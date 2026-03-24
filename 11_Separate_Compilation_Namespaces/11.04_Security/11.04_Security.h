#ifndef SECURITY_11_04_H
#define SECURITY_11_04_H

#include <string>
#include <vector>

const std::vector<int> PRIVILEGES = {1, 2};
// 1 = user | 2 == admin

class Security
{
public:
	Security();
	Security(const std::string& user, const std::string& pwd, int userType);
	int validate(const std::string& user, const std::string& pwd) const;
	//   Postcondition:
	// This subroutine returns 0 if the credentials are invalid, 1 if valid user, and 2 if valid administrator.

	const std::string& getName() const;
	const std::string& getPassword() const;
	friend std::istream& operator >>(std::istream& inputStream, Security& myLogin);

private:
	std::string username;
	std::string password;
	int privilege;
};

#endif
