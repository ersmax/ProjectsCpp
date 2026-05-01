#include <iostream>
#include "15_03_Doodlebug.h"

#include "15_03_World.h"

namespace myGame
{
	Doodlebug::Doodlebug() : Organism()
	{ /* Body intentionally left empty */ }

	char Doodlebug::getCreature() const { return creature; }

	void Doodlebug::move(World& theWorld)
	{
		// Case 1: There are ants as neighbors
		const std::vector<Position>& neighbors = theWorld.neighborAnts(this);
		if (World::doodlebugCanEat(neighbors))
		{
			const Position& newPosition = chooseRandomPosition(neighbors);
			theWorld.eatAnt(this, newPosition);
			Organism::play();
			return;
		}

		// Case 2: There are free cells nearby
		const std::vector<Position>& freePosition = theWorld.freePositions(this);
		if (World::canMoveToFreePosition(freePosition))
		{
			const Position& newPosition = Organism::chooseRandomPosition(freePosition);
			theWorld.changePosition(this, newPosition);
			Organism::play();
			return;
		}
		
		// Case 3: All cells are occupied by other Doodlebugs
		Organism::play();
	}

	

} // myGame