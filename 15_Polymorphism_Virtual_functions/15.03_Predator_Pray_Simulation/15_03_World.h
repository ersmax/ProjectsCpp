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
		void eatAnt(Organism *theDoodlebug, const Position& newPosition);
		//   Postcondition: allow a Doodlebug to change position and eat an Ant
		void changePosition(Organism* theOrganism, const Position& newPosition);
		//   Postcondition: allow an Ant/Doodlebug to change position to a newPosition
		void die(Organism* theOrganism);
		//   Postcondition: if the remaining life of the Doodlebug reaches 0, then it dies
	private:
		Organism *board[N_ROWS][N_COLS];
		int nAnts;
		int nDoodlebugs;
		std::mt19937 rng;
		void initialize();
		void placeRandom(Organism *newOrganism);
		void initializeFlags() const;
		//   Postcondition: set the played flag of each organism to false, since they 
		// have not played yet
		void doodlebugsTurn();
		void antsTurn();
	};

} // myGame

#endif // WORLD_15_03_H
