/*
This Programming Project requires that you first complete Programming Project 14.9
from Chapter 14.
class Creature
{
 private:
 int type; // 0 human, 1 cyberdemon, 2 balrog, 3 elf
 int strength; // How much damage we can inflict
 int hitpoints; // How much damage we can sustain
 string getSpecies(); // Returns type of species
 public:
 Creature( );
 // Initialize to human, 10 strength, 10 hit points
 Creature(int newType, int newStrength, int newHit);
 // Initialize creature to new type, strength, hit points
 // Also add appropriate accessor and mutator functions
 // for type, strength, and hit points
 int getDamage();
 // Returns amount of damage this creature
 // inflicts in one round of combat
};
Here is an implementation of the getSpecies( ) function:
string Creature::getSpecies()
{
 switch (type)
 {
 case 0: return "Human";
 case 1: return "Cyberdemon";
 case 2: return "Balrog";
 case 3: return "Elf";
 }
 return "Unknown";
}
The getDamage( ) function outputs and returns the damage this creature can
inflict in one round of combat. The rules for calculating the damage are as follows:
■ Every creature inflicts damage that is a random number r, where 0<r<= strength.
■ Demons have a 5% chance of inflicting a demonic attack, which is an additional 50 damage points. Balrogs and Cyberdemons are demons.
■ Elves have a 10% chance to inflict a magical attack that doubles the normal
amount of damage.
■ Balrogs are very fast, so they get to attack twice
An implementation of getDamage( ) is given here:
int Creature::getDamage( )
{
 int damage;
 // All creatures inflict damage, which is a
 // random number up to their strength
 damage = (rand( ) % strength) + 1;
 cout << getSpecies( ) << " attacks for " <<
 damage << "points!" << endl;
 // Demons can inflict damage of 50 with a 5% chance
 if ((type = 2) || (type == 1))
 if ((rand( ) % 100) < 5)
 {
 damage = damage + 50;
 cout << "Demonic attack inflicts 50 "
 << "additional damage points!" << endl;
 }
 // Elves inflict double magical damage with a 10% chance
 if (type == 3)
 {
 if ((rand( ) % 10)==0)
 {
 cout << "Magical attack inflicts " << damage<<
 "additional damage points!" << endl;
 damage = damage * 2;
 }
 }
 // Balrogs are so fast they get to attack twice
 if (type == 2)
 {
 int damage2 = (rand() % strength) + 1;
 cout << "Balrog speed attack inflicts " << damage2 <<
 "additional damage points!" << endl;
 damage = damage + damage2;
 }
 return damage;
}
One problem with this implementation is that it is unwieldy to add new creatures.
Rewrite the class to use inheritance, which will eliminate the need for the variable
type. The Creature class should be the base class. The classes Demon, Elf, and
Human should be derived from Creature. The classes Cyberdemon and Balrog
should be derived from Demon. You will need to rewrite the getSpecies( ) and
getDamage( ) functions so they are appropriate for each class.
For example, the getDamage( ) function in each class should only compute the
damage appropriate for that object. The total damage is then calculated by combining the results of getDamage( ) at each level of the inheritance hierarchy. As an
example, invoking getDamage( ) for a Balrog object should invoke getDamage(
) for the Demon object, which should invoke getDamage( ) for the Creature
object. This will compute the basic damage that all creatures inflict, followed by
the random 5% damage that demons inflict, followed by the double damage that
balrogs inflict.
Also include mutator and accessor functions for the private variables. Write a main
function that contains a driver to test your classes. It should create an object for
each type of creature and repeatedly outputs the results of getDamage( ). First,
make the getDamage( ) function virtual. Then, make a function in your main
program, battleArena(Creature &creature1, Creature &creature2), that
takes two Creature objects as input. The function should calculate the damage
done by creature1, subtract that amount from creature2’s hit points, and vice
versa. If both creatures end up with zero or less hit points, then the battle is a tie.
Otherwise, at the end of a round, if one creature has positive hit points but the
other does not, then the battle is over. The function should loop until the battle is
either a tie or over. Since the getDamage( ) function is virtual, it should invoke
the getDamage( ) function defined for the specific creature. Test your program
with several battles involving different creatures.
*/

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

	battleArena(anElf, aBalrog);
	battleArena(aHuman, aCyberdemon);
	battleArena(aBalrog, aCyberdemon);
	battleArena(anElf, aHuman);

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
		
}
