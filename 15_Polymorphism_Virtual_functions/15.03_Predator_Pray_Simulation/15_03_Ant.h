#ifndef ANT_15_03_H
#define ANT_15_03_H

#include "15_03_Organism.h"

namespace myGame
{
	class Ant : public Organism
	{
	public:
		Ant();
		virtual void move(World& theWorld) override final;
		//   Postcondition: allows the Ant to move according to the rules of the game, 
		// and updates the position of the Ant in the world.
		virtual char getCreature() const override final;
		//   Postcondition: returns the character representing the Ant
		virtual void resetBreedTime() override final;
		//   Postcondition: resets the breedTime of the Ant to the initial value, which is 3
	private:
		char creature = 'O';
	};

} // myGame


#endif // ANT_15_03_H
