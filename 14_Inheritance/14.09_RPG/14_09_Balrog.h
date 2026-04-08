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
		const std::string& getSpecies() const override;
	private:
		std::string name;
	};

} // myNamespaceRPG

#endif // BALROG_14_09_H
