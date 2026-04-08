#include <iostream>
#include <random>
#include "14_09_Elf.h"

namespace myNamespaceRPG
{
	Elf::Elf() : Creature(), name("Elf")
	{ /* Body intentionally left empty */ }

	Elf::Elf(const int newStrength, const int newHit) : Creature(newStrength, newHit), name("Elf") 
	{ /* Body intentionally left empty */ }

	const std::string& Elf::getSpecies() const { return name; }

	int Elf::getDamage() const
	{
		// Base attack from Creature (random in [1, strength])
		int damage = Creature::getDamage();

		// 10% chance for magical double damage
		static thread_local std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> chanceMagic(0, 9);

		if (chanceMagic(rng) == 0)
		{
			std::cout << "Magical attack inflicts " << damage << " additional damage points\n";
			damage *= 2;
		}
		return damage;
	}

} // myNamespaceRPG
