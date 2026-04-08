#ifndef ELF_14_09_H
#define ELF_14_09_H

#include "14_09_Creature.h"

namespace myNamespaceRPG
{
	class Elf : public Creature
	{
	public:
		Elf();
		Elf(int newStrength, int newHit);
		const std::string& getSpecies() const override;
		int getDamage() const override;
		//   Precondition: Elves inflict double magical damage with a 10% chance
	private:
		std::string name;
	};

} // myNamespaceRPG

#endif // ELF_14_09_H
