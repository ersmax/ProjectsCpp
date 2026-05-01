#include <iostream>
#include "15_03_Doodlebug.h"

#include "15_03_World.h"

namespace myGame
{
	Doodlebug::Doodlebug() : Organism(), turnsToStarvation(LIFE_CYCLE)
	{
		Organism::setBreedTime(REPRODUCTION_TIME);
	}

	void Doodlebug::increaseStarvation() { turnsToStarvation--; }

	void Doodlebug::resetTurnsStarvation() { turnsToStarvation = LIFE_CYCLE; }

	int Doodlebug::getStarvation() const { return turnsToStarvation; }

	void Doodlebug::resetBreedTime()
	{
		Organism::setBreedTime(REPRODUCTION_TIME);
	}

	char Doodlebug::getCreature() const { return creature; }

	void Doodlebug::move(World& theWorld)
	{
		Organism::play();
		Organism::decreaseBreedTime();

		// Case 1: There are ants as neighbors
		const std::vector<Position> neighbors = theWorld.neighborAnts(this);
		if (World::doodlebugCanEat(neighbors))
		{
			const Position& newPosition = Organism::chooseRandomPosition(neighbors);
			theWorld.eatAnt(this, newPosition);
			resetTurnsStarvation();
			return;
		}

		// Case 2: There are free cells nearby
		const std::vector<Position> freePosition = theWorld.freePositions(this);
		if (World::canMoveToFreePosition(freePosition))
		{
			const Position& newPosition = Organism::chooseRandomPosition(freePosition);
			theWorld.changePosition(this, newPosition);
			increaseStarvation();
			return;
		}
		
		// Case 3: All cells are occupied by other Doodlebugs
		increaseStarvation();
	}

	

} // myGame