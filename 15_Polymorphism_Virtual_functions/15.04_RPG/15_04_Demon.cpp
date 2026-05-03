#include <random>
#include <iostream>
#include "15_04_Demon.h"

namespace myRPG
{
	Demon::Demon() : Creature()
	{ /* Body intentionally left empty */ }

	Demon::Demon(const int theStrength, const int theHitpoints) : Creature(theStrength, theHitpoints)
	{ /* Body intentionally left empty */ }

	int Demon::getDamage()
	{
		int baseDamage = Creature::getDamage();

		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> randomNumber(0, 99);

		// Demons have additional 5% chance of inflicting a demonic attack, which is 50 points
		if (randomNumber(rng) < 5)
		{
			const int totalDamage = baseDamage + ADDITIONAL_DMG;
			std::cout << "Demon attack inflicts additional " << ADDITIONAL_DMG << " points damage\n";
			return totalDamage;
		}
		return baseDamage;
	}

} // myRPG

// TODO: implement the Classes Balrogs and Cyberdemons, plus the final battle royal logic in main