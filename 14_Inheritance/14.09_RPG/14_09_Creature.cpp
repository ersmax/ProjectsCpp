#include <stdexcept>
#include <iostream>
#include <random>
#include "14_09_Creature.h"
#include "14_09_Validation.h"

namespace myNamespaceRPG
{
	Creature::Creature() : strength(10), hitpoints(10)
	{ /* Body intentionally left empty */ }

	Creature::Creature(const int newStrength, const int newHit)
	{
		if (newStrength < 0 || newStrength > MAX_STRENGTH ||
			newHit < 0 || newHit > MAX_HITPOINTS)
			throw std::invalid_argument("Not valid stats");
		strength = newStrength;
		hitpoints = newHit;
	}

	int Creature::getDamage() const
	{
		static thread_local std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> dist(1, strength);
		const int damage = dist(rng);
		std::cout << getSpecies() << " attack for " << damage << " points\n";
		return damage;
	}

	int Creature::getStrength() const { return strength; }

	int Creature::getHitpoints() const { return hitpoints; }

	std::istream& operator >>(std::istream& inputStream, Creature& aCreature)
	{
		using myNamespaceValidation::readNumber;
		while (true)
		{
			std::cout << "Enter strength (0-" << MAX_STRENGTH << "):\n";
			readNumber(inputStream, aCreature.strength);
			std::cout << "Enter hitpoints (0-" << MAX_HITPOINTS << "):\n";
			readNumber(inputStream, aCreature.hitpoints);
			if (aCreature.strength >= 0 && aCreature.strength <= MAX_STRENGTH &&
				aCreature.hitpoints >= 0 && aCreature.strength <= MAX_HITPOINTS)
				break;
			
			std::cout << "Wrong stats. Retry\n";
		} 
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Creature& aCreature)
	{
		std::cout << "Strength: " << aCreature.strength << '\n';
		std::cout << "Hitpoints: " << aCreature.hitpoints << '\n';
		return outputStream;
	}

} // myNamespaceRPG