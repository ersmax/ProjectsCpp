#ifndef DEMON_14_09_F
#define DEMON_14_09_F

#include "14_09_Creature.h"

namespace myNamespaceRPG
{
	constexpr int DEMONIC_ATTACK = 50;

	class Demon : public Creature
	{
	public:
		Demon();
		Demon(int newStrength, int newHit);
		int getDamage() const override;
		//   Precondition: Demons can inflict damage of 50 with a 5% chance
		//   Postcondition: Compute the additional damage from the demonic attack 
		// and add it to the base damage computed by Creature::getDamage()
	private:
	};


} // myNamespaceRPG

#endif // DEMON_14_09_F
