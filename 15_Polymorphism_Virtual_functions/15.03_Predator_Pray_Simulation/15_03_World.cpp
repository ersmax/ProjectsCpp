#include <iostream>
#include <random>
#include "15_03_World.h"

#include "15_03_Organism.h"
#include "15_03_Doodlebug.h"
#include "15_03_Ant.h"


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
		for (int doodlebug = 0; doodlebug < nDoodlebug; doodlebug++)
			placeRandom(new Doodlebug());
		
		for (int ant = 0; ant < nAnts; ant++)
			placeRandom(new Ant());
	}

	void World::placeRandom(Organism *newOrganism)
	{
		std::uniform_int_distribution<int> rowDist(0, N_ROWS - 1);
		std::uniform_int_distribution<int> colDist(0, N_COLS - 1);

		while (true)
		{
			const int row = rowDist(rng);
			const int col = colDist(rng);
			Position thePosition(row, col);
			if (board[thePosition.x][thePosition.y] == nullptr)
			{
				board[thePosition.x][thePosition.y] = newOrganism;
				newOrganism->setPosition(thePosition);
				break;
			}
		}
	}

	char World::creatureAt(const Position& thePosition) const
	{
		const Organism *theOrganism = board[thePosition.x][thePosition.y];
		if (theOrganism == nullptr)
			return EMPTY;
		return theOrganism->getCreature();
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
				Position thePosition{ row,col };
				std::cout << creatureAt(thePosition);
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
