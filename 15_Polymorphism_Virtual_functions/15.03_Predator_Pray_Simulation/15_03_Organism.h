#ifndef ORGANISM_15_03_H
#define ORGANISM_15_03_H

#include <random>

namespace myGame
{
	// Turns for an ant to reproduce and for a Doodlebug to starve without eating
	constexpr int LIFE_CYCLE = 3;	

	class World;

	struct Position
	{
		int x;
		int y;
	};

	class Organism
	{
	public:
		Organism();
		Organism(const Organism& anotherOrganism) = default;
		Organism& operator=(const Organism& anotherOrganism) = default;
		virtual ~Organism() = default;
		virtual void move(World& theWorld) = 0;
		virtual char getCreature() const = 0;
		void setBreedTime(int theTime);
		void decreaseBreedTime();
		virtual void resetBreedTime() = 0;
		int getBreedTime() const;
		void setPosition(const Position& thePosition);
		void play();
		void initializePlay();
		bool hasPlayed() const;
		const Position& chooseRandomPosition(const std::vector<Position>& thePositions) const;
		const Position& getPosition() const;
	private:
		Position position;
		mutable std::mt19937 rng;	
		bool played;
		int breedTime;
	};

} // myGame

#endif // ORGANISM_15_03_H
