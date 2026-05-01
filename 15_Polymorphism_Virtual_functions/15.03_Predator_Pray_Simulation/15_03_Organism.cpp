#include "15_03_Organism.h"

namespace myGame
{
	Organism::Organism() : position({ -1, -1 }), played(false), rng(std::random_device{}()), breedTime(0)
	{ /* Body left empty */ }

	void Organism::play() { played = true; }

	void Organism::initializePlay() { played = false; }

	bool Organism::hasPlayed() const { return played; }

	const Position& Organism::getPosition() const { return position; }

	void Organism::setPosition(const Position& thePosition) { position = thePosition; }

	void Organism::setBreedTime(const int theTime) { breedTime = theTime; }

	void Organism::decreaseBreedTime() { breedTime--; }

	int Organism::getBreedTime() const { return breedTime; }

	const Position& Organism::chooseRandomPosition(const std::vector<Position>& thePositions) const
	{
		const int numberPositions = static_cast<int>(thePositions.size());
		
		std::uniform_int_distribution<int> idxPositions(0, numberPositions - 1);
		const int idxPosition = idxPositions(rng);
		const Position& randomPosition = thePositions[idxPosition];
		
		return randomPosition;
	}

} // myGame
