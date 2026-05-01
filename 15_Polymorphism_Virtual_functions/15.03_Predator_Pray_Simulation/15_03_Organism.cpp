#include "15_03_Organism.h"

namespace myGame
{
	Organism::Organism() : position({ -1, -1 }), played(false), rng(std::random_device{}())
	{ /* Body left empty */ }

	void Organism::play() { played = true; }

	bool Organism::hasPlayed() const { return played; }

	const Position& Organism::getPosition() const { return position; }

	void Organism::setPosition(const Position& thePosition) { position = thePosition; }

	const Position& Organism::chooseRandomPosition(const std::vector<Position>& thePositions) const
	{
		const int numberNeighbors = static_cast<int>(thePositions.size());
		
		std::uniform_int_distribution<int> idxPositions(0, numberNeighbors - 1);
		const int idxPosition = idxPositions(rng);
		const Position& randomPosition = thePositions[idxPosition];
		
		return randomPosition;
	}

} // myGame
