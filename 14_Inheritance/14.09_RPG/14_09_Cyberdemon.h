#ifndef CYBERDEMON_14_09_H
#define CYBERDEMON_14_09_H

#include "14_09_Demon.h"

namespace myNamespaceRPG
{
	class Cyberdemon : public Demon
	{
	public:
		Cyberdemon();
		Cyberdemon(int newStrength, int newHit);
		const std::string& getSpecies() const override;
		//   Postcondition: Return the string "Cyberdemon"
	private:
		std::string name;
	};

} // myNamespaceRPG

#endif // CYBERDEMON_14_09_H
