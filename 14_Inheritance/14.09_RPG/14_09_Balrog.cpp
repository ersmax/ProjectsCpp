#include <iostream>
#include <random>
#include "14_09_Balrog.h"

namespace myNamespaceRPG
{
	Balrog::Balrog() : Demon(), name("Balrog")
	{ /* Body intentionally left empty */ }

	Balrog::Balrog(int newStrength, int newHit) : Demon(newStrength, newHit), name("Balrog")
	{ /* Body intentionally left empty */ }

	const std::string& Balrog::getSpecies() const { return name; }

	int Balrog::getDamage() const 
	{
		// Base damage (including Demon 5% +50 points)
		int damage = Demon::getDamage();

		// Double attack from Balrog class (Base attack)
		// (old implementation)
		// damage += myNamespaceRPG::Creature::getDamage();

		// Balrog gets a second, fast attack: random in [1, strength]
		static thread_local std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(1, getStrength());
		const int damage2 = dist(rng);

		std::cout << "Balrog speed attack inflicts "
				  << damage2 << " additional damage points!\n";

		damage += damage2;

		return damage;
	}

} // myNamespaceRPG
