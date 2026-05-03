#ifndef CREATURE_15_04_H
#define CREATURE_15_04_H
#include <string>

namespace myRPG
{
	constexpr int MAX_STRENGTH = 100;
	constexpr int MAX_HITPOINTS = 100;

	class Creature
	{
	public:
		Creature();
		virtual ~Creature() = default;
		Creature(int theStrength, int theHitpoints);
		virtual int getDamage();
		void setStrength(int theStrength);
		void setHitpoints(int theHitpoints);
		int getStrength() const;
		int getHitpoints() const;
		virtual const std::string& getSpecies() const = 0;
		//   Postcondition: returns the name of the creature.
		// Useful to make the class abstract
		friend std::istream& operator >>(std::istream& inputStream, Creature& theCreature);
		friend std::ostream& operator <<(std::ostream& outputStream, const Creature& theCreature);
	private:
		int strength;
		int hitpoints;
	};


} // myRPG

#endif // CREATURE_15_04_H
