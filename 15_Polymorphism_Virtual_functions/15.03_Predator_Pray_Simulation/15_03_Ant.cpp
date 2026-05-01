#include <iostream>
#include "15_03_Ant.h"

#include "15_03_World.h"

namespace myGame
{
	Ant::Ant() : Organism()
	{
		setBreedTime(LIFE_CYCLE);
	}

	void Ant::resetBreedTime()
	{
		setBreedTime(LIFE_CYCLE);
	}

	char Ant::getCreature() const { return creature; }

	void Ant::move(World& theWorld)
	{
		decreaseBreedTime();
		Organism::play();

		// Case 1: there are free cells nearby
		const std::vector<Position> freePositions = theWorld.freePositions(this);
		if (World::canMoveToFreePosition(freePositions))
		{
			const Position& newPosition = Organism::chooseRandomPosition(freePositions);
			theWorld.changePosition(this, newPosition);
			return;
		}

		// Case 2: there are no free cells: just return
		return;
	}

} // myGame