#ifndef WORLD_15_03_H
#define WORLD_15_03_H

#include <random>
#include <vector>
#include "15_03_Organism.h"

namespace myGame
{
	constexpr int N_ROWS = 20;
	constexpr int N_COLS = 20;
	constexpr int INITIAL_ANTS = 100;
	constexpr int INITIAL_DOODLEBUGS = 5;
	constexpr char EMPTY = ' ';

	class World
	{
	public:
		World();
		~World();
		void output() const;
		void next();
	private:
		Organism *board[N_ROWS][N_COLS];
		int nAnts;
		int nDoodlebug;
		std::mt19937 rng;
		void initialize();
		void placeRandom(Organism *newOrganism);
		Organism* creatureAt(const Position& thePosition) const;
		std::vector<Position> neighborAnts(const Organism *theOrganism) const;
		//   Postcondition: returns a (possible) vector of ants that
		// are neighbors of the Doodlebug. Useful for the doodlebug to eat nearby ants.
		bool positionInBounds(const Position& thePosition) const;
		//   Postcondition: returns whether the position is within the board bounds
		static bool doodlebugCanEat(const std::vector<Position>& neighborAnts);
		//   Postcondition: return whether there is at least one ant as neighbor
		std::vector<Position> freePositions(const Organism* theOrganism) const;
		//   Postcondition: return a (possible) vector of free cells 
		// where the Organism (Ant/Doodlebug) can move without collision.
		static bool canMoveToFreePosition(const std::vector<Position>& freePositions);
		//   Postcondition: return whether there is at least one free cell to move
	};

} // myGame

#endif // WORLD_15_03_H
