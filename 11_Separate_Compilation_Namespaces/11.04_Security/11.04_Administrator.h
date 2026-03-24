#ifndef ADMINISTRATOR_11_04_H
#define ADMINISTRATOR_11_04_H

#include "11.04_Security.h"

class Administrator
{
public:
	static bool Login(const std::vector<Security>& users);
	//   Postcondition: this function returns true if a given username and password
	// have administrator clearance.
};

#endif