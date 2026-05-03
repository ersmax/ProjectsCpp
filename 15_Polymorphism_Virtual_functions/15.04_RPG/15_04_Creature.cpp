#include <stdexcept>
#include <random>
#include <iostream>
#include "15_04_Creature.h"
#include "15_04_Validation.h"

namespace myRPG
{
	Creature::Creature() : strength(1), hitpoints(1)
	{ /* Body intentionally left empty */ }

	Creature::Creature(const int theStrength, const int theHitpoints) 
	{ 
		setStrength(theStrength);
		setHitpoints(theHitpoints);
	}

	void Creature::setStrength(const int theStrength)
	{
		if (theStrength <= 0 || theStrength > MAX_STRENGTH)
			throw std::invalid_argument("Not a valid value\n");
		strength = theStrength;
	}

	void Creature::setHitpoints(const int theHitpoints)
	{
		if (theHitpoints <= 0 || theHitpoints > MAX_HITPOINTS)
			throw std::invalid_argument("Not a valid value\n");
		hitpoints = theHitpoints;
	}

	int Creature::getStrength() const { return strength; }

	int Creature::getHitpoints() const { return hitpoints; }

	int Creature::getDamage()
	{
		std::mt19937 rng(std::random_device{}());

		std::uniform_int_distribution<int> randomNumber(1, strength);
		const int damage = randomNumber(rng);
		std::cout << getSpecies() << " attacks for " << damage << " points!\n";
		return damage;
	}

	std::istream& operator >>(std::istream& inputStream, Creature& theCreature)
	{
		using myValidation::readNumber;
		while (true)
		{
			std::cout << "Enter " << theCreature.getSpecies() << " strength (1-" << MAX_STRENGTH << "):\n";
			readNumber(inputStream, theCreature.strength);
			std::cout << "Enter " << theCreature.getSpecies() << " hitpoints (1-" << MAX_HITPOINTS << "):\n";
			readNumber(inputStream, theCreature.hitpoints);
			if (theCreature.strength > 0 && theCreature.strength <= MAX_STRENGTH &&
				theCreature.hitpoints > 0 && theCreature.hitpoints <= MAX_HITPOINTS)
			{
				break;
			}
			std::cout << "Wrong stats. Retry\n";
		}
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Creature& theCreature)
	{
		outputStream << theCreature.getSpecies() << " strength: " << theCreature.strength << '\n';
		outputStream << theCreature.getSpecies() << " hitpoints: " << theCreature.hitpoints << '\n';
		return outputStream;
	}

} // myRPG
