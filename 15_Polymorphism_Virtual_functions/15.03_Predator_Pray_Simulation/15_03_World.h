#ifndef WORLD_15_03_H
#define WORLD_15_03_H

#include <random>
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
	private:
		Organism *board[N_ROWS][N_COLS];
		int nAnts;
		int nDoodlebug;
		std::mt19937 rng;
		void initialize();
		void placeRandom(Organism *newOrganism);
		char creatureAt(const Position& thePosition) const;
	};

} // myGame

#endif // WORLD_15_03_H
