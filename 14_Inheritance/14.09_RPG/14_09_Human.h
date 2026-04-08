#ifndef HUMAN_14_09_H
#define HUMAN_14_09_H

#include "14_09_Creature.h"

namespace myNamespaceRPG
{
	class Human : public Creature
	{
	public:
		Human();
		Human(int newStrength, int newHit);
		int getDamage() const override;
		//   Postcondition: return the parent class function.
		// (The human does not have any special attacks, 
		// so it just uses the base damage from Creature)
		const std::string& getSpecies() const override;
		//   Postcondition: Return the string "Human"
	private:
		std::string name;
	};


} // myNamespaceRPG

#endif // HUMAN_14_09_H
