#ifndef DEMON_15_04_H
#define DEMON_15_04_H
#include "15_04_Creature.h"

namespace myRPG
{
	constexpr int CHANCE_DEMON = 5;
	constexpr int ADDITIONAL_DMG = 50;

	class Demon : public Creature
	{
	public:
		Demon();
		Demon(int theStrength, int theHitpoints);
		virtual int getDamage() override;
		//   Postcondition: returns the damage inflicted by a Demon, 
		// which is the sum of the damage inflicted by a Creature and an additional 5% of that damage.
	private:
	};

} // myRPG

#endif // DEMON_15_04_H

