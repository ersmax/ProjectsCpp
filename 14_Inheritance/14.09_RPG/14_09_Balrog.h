#ifndef BALROG_14_09_H
#define BALROG_14_09_H

#include "14_09_Demon.h"

namespace myNamespaceRPG
{
	class Balrog : public Demon
	{
	public:
		Balrog();
		Balrog(int newStrength, int newHit);
		int getDamage() const override;
		//   Precondition: Balrogs are so fast thet get to attack twice
		//   Postcondition: Compute the additional damage from the Balrog's second attack 
		// and add it to the base damage computed by Demon::getDamage()
		const std::string& getSpecies() const override;
		//   Postcondition: Return the string "Balrog"
	private:
		std::string name;
	};

} // myNamespaceRPG

#endif // BALROG_14_09_H
