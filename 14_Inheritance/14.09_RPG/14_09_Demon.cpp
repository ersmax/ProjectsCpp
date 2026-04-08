#include <random>
#include <iostream>
#include "14_09_Demon.h"

namespace myNamespaceRPG
{
	Demon::Demon() : Creature()
	{ /* Body intentionally left empty */ }

	Demon::Demon(const int newStrength, const int newHit) : Creature(newStrength, newHit)
	{ /* Body intentionally left empty */ }

	int Demon::getDamage() const
	{
		// Base damage from Creature (random in [1, strength])
		int damage = Creature::getDamage();
		
		// 5% chance: generate number in [0, 99] and check if it's < 5
		static thread_local std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> chanceDamage(0, 99);
		if (chanceDamage(rng) < 5)
		{
			std::cout << "Demonic attack inflicts " << DEMONIC_ATTACK
					  << " additional damage points!\n";
			damage += DEMONIC_ATTACK;
		}
		return damage;
	}

} //myNamespaceRPG
