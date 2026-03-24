#ifndef USER_11_04_H
#define USER_11_04_H

#include "11.04_Security.h"

class User
{
public:
	static bool Login(const std::vector<Security>& users);
	//   Postcondition: this function returns true if a given username and password
	// have either administrator or user clearance.
};


#endif