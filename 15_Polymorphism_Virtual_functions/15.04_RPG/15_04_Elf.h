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
		virtual const std::string& getSpecies() const override final;
	private:
		std::string species = "Elf";
	};
	
} // myRPG

#endif // ELF_15_04_H
