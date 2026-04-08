#ifndef CREATURE_14_09_H
#define CREATURE_14_09_H

#include <string>

constexpr int MAX_STRENGTH = 100;
constexpr int MAX_HITPOINTS = 100;
constexpr int MAX_CREATURES = 4;
//	1 = Human	| 2 = Cyberdemon	| 3 = Balrog	| 4 = Elf

namespace myNamespaceRPG
{
	class Creature
	{
	public:
		Creature();
		//   Postcondition: Initialize to human, 10 strength, 10 hit points
		Creature(int newStrength, int newHit);
		//   Postcondition: Initialize creature with specified strength and hit points
		virtual ~Creature() = default;
		virtual int getDamage() const;
		//   Postcondition: Returns amount of damage this creature inflicts in 
		// one round of combat.
		virtual const std::string& getSpecies() const = 0;
		int getStrength() const;
		int getHitpoints() const;
		friend std::istream& operator >>(std::istream& inputStream, Creature& aCreature);
		friend std::ostream& operator <<(std::ostream& outputStream, const Creature& aCreature);
	private:
		int strength;
		//   Precondition: how much damage we can inflict
		int hitpoints;
		//   Precondition: how much damage we can sustain
	};

} // myNamespaceRPG


#endif // CREATURE_14_09_H