#include <iostream>

#include "15_04_Balrog.h"
#include "15_04_Creature.h"
#include "15_04_Cyberdemon.h"
#include "15_04_Elf.h"
#include "15_04_Human.h"

using myRPG::Creature;
using myRPG::Balrog;
using myRPG::Cyberdemon;
using myRPG::Human;
using myRPG::Elf;

void battleArena(Creature& creature1, Creature& creature2);
//   Postconditon: The function simulates a battle between creature1 and creature2, 
// where each creature attacks the other until one or both creatures have zero or less hit points. 
// The function outputs the result of each attack and the final outcome of the battle (win, lose, tie).

int main( )
{
	Elf anElf;
	Human aHuman;
	Balrog aBalrog;
	Cyberdemon aCyberdemon;

	std::cout << "Enter stats for Elf:\n";
	std::cin >> anElf;
	std::cout << "Enter stats for Human:\n";
	std::cin >> aHuman;
	std::cout << "Enter stats for Balrog:\n";
	std::cin >> aBalrog;
	std::cout << "Enter stats for Cyberdemon:\n";
	std::cin >> aCyberdemon;

	// Create copies of creatures before each battle
	{
		Elf elf = anElf; Balrog balrog = aBalrog;
		std::cout << "\n--- Elf vs Balrog ---\n";
		battleArena(elf, balrog);
	}
	{
		Human human = aHuman; Cyberdemon cyberdemon = aCyberdemon;
		std::cout << "\n--- Human vs Cyberdemon ---\n";
		battleArena(human, cyberdemon);
	}
	{
		Balrog balrog = aBalrog; Cyberdemon cyberdemon = aCyberdemon;
		std::cout << "\n--- Balrog vs Cyberdemon ---\n";
		battleArena(balrog, cyberdemon);
	}
	{
		Elf elf = anElf; Human human = aHuman;
		std::cout << "\n--- Elf vs Human ---\n";
		battleArena(elf, human);
	}

	std::cout << '\n';
	return 0;
}

void battleArena(Creature& creature1, Creature& creature2)
{
	while (	creature1.getHitpoints() > 0 &&
			creature2.getHitpoints() > 0)
	{
		const int dmgCreature1 = creature1.getDamage();
		const int dmgCreature2 = creature2.getDamage();

		const int lifeCreature1 = creature1.getHitpoints();
		const int lifeCreature2 = creature2.getHitpoints();
		creature1.setHitpoints(lifeCreature1 - dmgCreature2);
		creature2.setHitpoints(lifeCreature2 - dmgCreature1);

		const int normalizedLifeCreature1 = (creature1.getHitpoints() < 0) ? 0 : creature1.getHitpoints();
		int normalizedLifeCreature2 = (creature2.getHitpoints() < 0) ? 0 : creature2.getHitpoints();
		std::cout << "Recap turn:\n";
		std::cout << creature1.getSpecies() << " attacks for " << dmgCreature1 << ". "
				  << "Remaining life: " << normalizedLifeCreature1 << '\n';
		std::cout << creature2.getSpecies() << " attacks for " << dmgCreature2 << ". "
				  << "Remaining life: " << normalizedLifeCreature2 << '\n';
	}
	const int lifeCreature1 = creature1.getHitpoints();
	const int lifeCreature2 = creature2.getHitpoints();

	if (lifeCreature1 <= 0 && lifeCreature2 <= 0)
		std::cout << "Tie. Both creatures died.\n";
	else if (lifeCreature1 > 0)
		std::cout << creature1.getSpecies() << " wins (remaining life: " << lifeCreature1 << ")\n";
	else if (lifeCreature2 > 0)
		std::cout << creature2.getSpecies() << " wins (remaining life: " << lifeCreature2 << ")\n";
		
	std::cout << '\n';
}
