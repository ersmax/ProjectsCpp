#include <iostream>
#include <random>
#include "15_03_World.h"


namespace myGame
{
	World::World() : nAnts(INITIAL_ANTS), nDoodlebug(INITIAL_DOODLEBUGS), rng(std::random_device{}())
	{ 
		for (int row = 0; row < N_ROWS; row++)
			for (int col = 0; col < N_COLS; col++)
				board[row][col] = nullptr;
		initialize();
	}

	World::~World()
	{
		for (int row = 0; row < N_ROWS; row++)
			for (int col = 0; col < N_COLS; col++)
			{
				delete board[row][col];
				board[row][col] = nullptr;
			}
	}

	void World::initialize()
	{
		placeRandom(DOODLEBUG, nDoodlebug);
		placeRandom(ANT, nAnts);
	}

	void World::placeRandom(const char creature, const int numCreatures)
	{
		std::uniform_int_distribution<int> rowDist(0, N_ROWS - 1);
		std::uniform_int_distribution<int> colDist(0, N_COLS - 1);
		
		int placed = 0;
		while (placed < numCreatures)
		{
			const int row = rowDist(rng);
			const int col = colDist(rng);
			Position thePosition;
			thePosition.x = row;
			thePosition.y = col;
			if (board[row][col] == nullptr)
			{
				board[row][col] = new Organism(thePosition, creature);
				placed++;
			}
		}
	}

	char World::symbolAt(const int row, const int col) const
	{
		const Organism *theOrganism = board[row][col];
		
		if (theOrganism == nullptr)
			return EMPTY;
		
		return theOrganism->getSymbol();
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
				std::cout << symbolAt(row, col);
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
