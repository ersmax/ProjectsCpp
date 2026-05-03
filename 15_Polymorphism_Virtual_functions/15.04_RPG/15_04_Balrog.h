#ifndef BALRGOG_15_04_H
#define BALRGOG_15_04_H

#include "15_04_Demon.h"

namespace myRPG
{
	class Balrog : public Demon
	{
	public:
		Balrog();
		Balrog(int theStrength, int theHitpoints);
		virtual int getDamage() override final;
		//   Postcondition: returns the damage inflicted by a Balrog, 
		// which is the sum of the damage inflicted by a Demon 
		// and an additional attack that inflicts the same amount of damage as the first attack.
		virtual const std::string& getSpecies() const override final;
	private:
		std::string species = "Balrog";
	};
} // myRPG

#endif // BALRGOG_15_04_H
