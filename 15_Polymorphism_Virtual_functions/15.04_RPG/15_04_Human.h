#ifndef HUMAN_15_04_H
#define HUMAN_15_04_H
#include "15_04_Creature.h"

namespace myRPG
{
	class Human : public Creature
	{
	public:
		Human();
		Human(int theStrength, int theHitpoints);
		virtual const std::string& getSpecies() const override final;
	private:
		std::string species = "Human";
	};
		
} // myRPG

#endif // HUMAN_15_04_H
