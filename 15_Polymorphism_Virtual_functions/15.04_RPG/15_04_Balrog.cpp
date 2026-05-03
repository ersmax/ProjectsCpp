#include <random>
#include <iostream>
#include "15_04_Balrog.h"

namespace myRPG
{
	Balrog::Balrog() : Demon()
	{ /* Body intentionally left empty */ }

	Balrog::Balrog(const int theStrength, const int theHitpoints) : Demon(theStrength, theHitpoints)
	{ /* Body intentionally left empty */ }

	const std::string& Balrog::getSpecies() const { return species; }

	int Balrog::getDamage()
	{
		const int baseDamage = Demon::getDamage();

		// Balrog are so fast that they get to attack twice
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> randomNumber(1, Creature::getStrength());
		const int secondAttack = randomNumber(rng);
		const int totalDamage = baseDamage + secondAttack;
		std::cout << species << " attack twice for: " << secondAttack << " damage points\n"
				  << "Total damage: " << totalDamage << '\n';
		return totalDamage;
	}
} // myRPG