#ifndef DOODLEBUG_15_03_H
#define DOODLEBUG_15_03_H

#include "15_03_Organism.h"

namespace myGame
{
	// turns for a doodlebug to reproduce
	constexpr int REPRODUCTION_TIME = 8;

	class Doodlebug : public Organism
	{
	public:
		Doodlebug();
		virtual void move(World& theWorld) override final;
		//   Postcondition: allows the Doodlebug to move according to the rules of the game,
		// and updates the position of the Doodlebug in the world.
		virtual char getCreature() const override final;
		//   Postcondition: returns the character representing the Doodlebug
		virtual void resetBreedTime() override final;
		//   Postcondition: resets the breedTime of the Doodlebug to the initial value, which is 8
		void resetTurnsStarvation();
		//   Postcondition: resets the turnsToStarvation of the Doodlebug to the initial value, which is 3
		void increaseStarvation();
		//   Postcondition: increases the turnsToStarvation of the Doodlebug by 1
		int getStarvation() const;
		//   Postcondition: returns the turnsToStarvation of the Doodlebug
	private:
		char creature = 'X';
		int turnsToStarvation;
		//   This is the number of turns left that the Doodlebug can survive without eating an Ant.
	};

} // myGame


#endif // DOODLEBUG_15_03_H
