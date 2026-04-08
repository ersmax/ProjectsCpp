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
		// one round of combat. The damage is computed as a random number in the range [1, strength].
		virtual const std::string& getSpecies() const = 0;
		//   Postcondition: Return the string "Human", "Cyberdemon", "Balrog", or "Elf" as appropriate.
		// This function is pure virtual because the base class Creature does not have a species. 
		// It is implemented in each derived class.
		int getStrength() const;
		//   Postcondition: Return the strength of this creature
		int getHitpoints() const;
		//   Postcondition: Return the hit points of this creature
		friend std::istream& operator >>(std::istream& inputStream, Creature& aCreature);
		//   Postcondition: Read strength and hit points for this creature from the input stream.
		friend std::ostream& operator <<(std::ostream& outputStream, const Creature& aCreature);
		//   Postcondition: Output strength and hit points for this creature to the output stream.
	private:
		int strength;
		//   Precondition: how much damage we can inflict
		int hitpoints;
		//   Precondition: how much damage we can sustain
	};

} // myNamespaceRPG


#endif // CREATURE_14_09_H