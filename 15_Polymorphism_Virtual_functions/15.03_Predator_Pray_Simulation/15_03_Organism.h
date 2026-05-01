#ifndef ORGANISM_15_03_H
#define ORGANISM_15_03_H

#include <random>

namespace myGame
{
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
		void setPosition(const Position& thePosition);
		void play();
		bool hasPlayed() const;
		const Position& chooseRandomPosition(const std::vector<Position>& thePositions) const;
		const Position& getPosition() const;
	private:
		Position position;
		mutable std::mt19937 rng;
		bool played;
	};

} // myGame

#endif // ORGANISM_15_03_H
