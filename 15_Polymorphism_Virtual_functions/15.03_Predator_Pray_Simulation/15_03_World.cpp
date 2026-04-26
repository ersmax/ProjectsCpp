#include <iostream>
#include <random>
#include "15_03_World.h"


namespace myGame
{
	World::World() : nAnts(INITIAL_ANTS), nDoodlebug(INITIAL_DOODLEBUGS)
	{ 
		for (int row = 0; row < N_ROWS; row++)
			for (int col = 0; col < N_COLS; col++)
				board[row][col] = EMPTY;
		initialize();
	}

	void World::initialize()
	{
		placeRandom(DOODLEBUG, nDoodlebug);
		placeRandom(ANT, nAnts);
	}

	void World::placeRandom(const char creature, const int numCreatures)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> rowDist(0, N_ROWS - 1);
		std::uniform_int_distribution<int> colDist(0, N_COLS - 1);
		
		int placed = 0;
		while (placed < numCreatures)
		{
			const int row = rowDist(gen);
			const int col = colDist(gen);
			if (board[row][col] == EMPTY)
			{
				board[row][col] = creature;
				placed++;
			}
		}
	}

	void World::output() const
	{
		std::cout << '.';
		for (int col = 0; col < N_COLS; col++)
			std::cout << '_' << '.';
		std::cout << '\n';

		for (int row = 0; row < N_ROWS; row++)
		{
			std::cout << '|';
			for (int col = 0; col < N_COLS; col++)
			{
				std::cout << board[row][col];
				std::cout << '|';
			}
			std::cout << '\n';

		}
		std::cout << '\'';
		for (int col = 0; col < N_COLS; col++)
			std::cout << '-' << '\'';
		std::cout << '\n';
	}

} // myGame
