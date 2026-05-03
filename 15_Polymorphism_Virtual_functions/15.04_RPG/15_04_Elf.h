#ifndef ELF_15_04_H
#define ELF_15_04_H
#include "15_04_Creature.h"

namespace myRPG
{
	constexpr int CHANCE_MAGIC = 10;

	class Elf : public Creature
	{
	public:
		Elf();
		Elf(int theStrength, int theHitpoints);
		virtual int getDamage() override final;
		//   Postcondition: returns the damage inflicted by an Elf,
		// which is the sum of the damage inflicted by a Creature and, with a 10% chance, 
		// magical damage that is double the amount of damage inflicted by the Creature.
		virtual const std::string& getSpecies() const override final;
	private:
		std::string species = "Elf";
	};
	
} // myRPG

#endif // ELF_15_04_H
