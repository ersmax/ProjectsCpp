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
		//   Postcondition: return the parent class function
		const std::string& getSpecies() const override;
	private:
		std::string name;
	};


} // myNamespaceRPG

#endif // HUMAN_14_09_H
