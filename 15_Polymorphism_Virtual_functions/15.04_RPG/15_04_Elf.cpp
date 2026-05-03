#include <random>
#include <iostream>
#include "15_04_Elf.h"

namespace myRPG
{
	Elf::Elf() : Creature()
	{ /* Body intentionally left empty */ }

	Elf::Elf(const int theStrength, const int theHitpoints) : Creature(theStrength, theHitpoints)
	{ /* Body intentionally left empty */ }

	const std::string& Elf::getSpecies() const { return species; }

	int Elf::getDamage()
	{
		const int baseDamage = Creature::getDamage();

		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> randomNumber(0, 99);
		
		// Elves have 10% chance to inflict a magical attack that doubles the damage
		if (randomNumber(rng) < CHANCE_MAGIC)
		{
			const int totalDamage = 2 * baseDamage;
			std::cout << "Double damage for Elf. Total damage: " << totalDamage << '\n';
			return totalDamage;
		}
		return baseDamage;
	}
} // myRPG
