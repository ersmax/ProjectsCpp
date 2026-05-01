#include <iostream>
#include "15_03_Ant.h"

#include "15_03_World.h"

namespace myGame
{
	Ant::Ant() : Organism()
	{ /* Body intentionally left empty */ }

	char Ant::getCreature() const { return creature; }

	void Ant::move(World& theWorld)
	{
		// Case 1: there are free cells nearby
		const std::vector<Position> freePositions = theWorld.freePositions(this);
		if (World::canMoveToFreePosition(freePositions))
		{
			const Position& newPosition = Organism::chooseRandomPosition(freePositions);
			theWorld.changePosition(this, newPosition);
			Organism::play();
			return;
		}

		// Case 2: there are no free cells
		Organism::play();
	}

} // myGame