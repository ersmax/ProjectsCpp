#include <iostream>
#include <random>
#include "15_03_World.h"

#include "15_03_Organism.h"
#include "15_03_Doodlebug.h"
#include "15_03_Ant.h"


namespace myGame
{
	World::World() : nAnts(INITIAL_ANTS), nDoodlebugs(INITIAL_DOODLEBUGS), rng(std::random_device{}())
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

	World::World(const World& anotherWorld) :
		nAnts(anotherWorld.nAnts),
		nDoodlebugs(anotherWorld.nDoodlebugs),
		rng(anotherWorld.rng)
	{
		for (int row = 0; row < N_ROWS; row++)
			for (int col = 0; col < N_COLS; col++)
				board[row][col] = deepCopyOrganism(anotherWorld.board[row][col]);
	}

	World& World::operator =(const World& anotherWorld)
	{
		if (this == &anotherWorld)	return *this;

		nAnts = anotherWorld.nAnts;
		nDoodlebugs = anotherWorld.nDoodlebugs;
		rng = anotherWorld.rng;

		for (int row = 0; row < N_ROWS; row++)
			for (int col = 0; col < N_COLS; col++)
			{
				delete board[row][col];
				board[row][col] = nullptr;
			}


		for (int row = 0; row < N_ROWS; row++)
			for (int col = 0; col < N_COLS; col++)
				board[row][col] = deepCopyOrganism(anotherWorld.board[row][col]);

		return *this;
	}

	Organism* World::deepCopyOrganism(const Organism* anotherOrganism)
	{
		if (anotherOrganism == nullptr)
			return nullptr;

		const Ant *ant = dynamic_cast<const Ant*>(anotherOrganism);
		if (ant != nullptr)
			return new Ant(*ant);

		const Doodlebug* doodlebug = dynamic_cast<const Doodlebug*>(anotherOrganism);
		if (doodlebug != nullptr)
			return new Doodlebug(*doodlebug);

		return nullptr;
	}


	void World::initialize()
	// Cannot create a local object because it gets destroyed out of scope
	{
		for (int doodlebug = 0; doodlebug < nDoodlebugs; doodlebug++)
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
				// we must assign new dynamic variable without dereferencing:
				// *board[x][y] = &newOrganism  : dereference a nullptr.
				// Moreover, if we fix the null pointer by assigning 
				// the address board[...] = &newOrganism; 
				// then the board will consist of dangling pointers 
				// pointing to destroyed local stack variables (if we used in the for loop:
				// for (int doodlebug = 0; doodlebug < nDoodlebug; doodlebug++)
				// {
				// 	  Doodlebug aDoodlebug; // Created locally on the STACK
				//	  placeRandom(aDoodlebug); 
				// } aDoodlebug is DESTROYED here at the end of the loop
				// And because World::~World() calls delete on the board items, 
				// it will try to delete stack memory, causing a crash.
				// Basically, &aDoodlebug points to an address on the stack, 
				// and calling delete on it creates undefined behavior.
				// It is literally trying to tell the heap manager to free 
				// a piece of memory that belongs to the stack frame.
				// So we use pointers do reference the dynamic variable on the heap.
				// Later, the destructor will return the heap memory to the freestore manager.
				board[thePosition.x][thePosition.y] = newOrganism;
				newOrganism->setPosition(thePosition);
				break;
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
				Organism *theOrganism = creatureAt({ row, col });
				if (theOrganism == nullptr)
					std::cout << EMPTY;
				else
					std::cout << theOrganism->getCreature();
				std::cout << '|';
			}
			std::cout << '\n';

		}
		std::cout << '\'';
		for (int col = 0; col < N_COLS; col++)
			std::cout << '-' << '\'';
		std::cout << '\n';
	}

	Organism* World::creatureAt(const Position& thePosition) const 
	{
		return board[thePosition.x][thePosition.y];
	}

	std::vector<Position> World::neighborAnts(const Organism *theOrganism) const
	{
		std::vector<Position> positionNearbyAnts;
		positionNearbyAnts.reserve(4);

		const Position organismPosition = theOrganism->getPosition();
		const Position candidates[4] = {
			{ organismPosition.x - 1, organismPosition.y }, // UP
			{ organismPosition.x + 1, organismPosition.y }, // DOWN
			{ organismPosition.x, organismPosition.y + 1 }, // RIGHT
			{ organismPosition.x, organismPosition.y - 1 }	  // LEFT
		};

		for (const Position& candidate : candidates)
		{
			if (!positionInBounds(candidate))
				continue;

			const Organism *neighbor = board[candidate.x][candidate.y];
			if (neighbor != nullptr && neighbor->getCreature() == 'O')
				positionNearbyAnts.push_back(candidate);
		}

		return positionNearbyAnts;
	}

	bool World::positionInBounds(const Position& thePosition) const
	{
		return (thePosition.x >= 0 && thePosition.x < N_ROWS &&
				thePosition.y >= 0 && thePosition.y < N_COLS);
	}

	bool World::doodlebugCanEat(const std::vector<Position>& neighborAnts)
	{
		return (!neighborAnts.empty());
	}

	std::vector<Position> World::freePositions(const Organism* theOrganism) const
	{
		std::vector<Position> freePositions;
		freePositions.reserve(4);

		const Position& organismPosition = theOrganism->getPosition();
		const Position candidates[4] = {
			{organismPosition.x - 1, organismPosition.y},	// UP
			{organismPosition.x + 1, organismPosition.y},	// DOWN
			{organismPosition.x, organismPosition.y + 1}, // RIGHT
			{organismPosition.x, organismPosition.y - 1}	// LEFT
		};

		for (const Position& candidate : candidates)
		{
			if (!positionInBounds(candidate))
				continue;

			const Organism *neighbor = board[candidate.x][candidate.y];
			if (neighbor == nullptr)
				freePositions.push_back(candidate);
		}
		return freePositions;
	}

	bool World::canMoveToFreePosition(const std::vector<Position>& freePositions)
	{
		return (!freePositions.empty());
	}

	void World::eatAnt(Organism *theDoodlebug, const Position& newPosition)
	{
		if (theDoodlebug == nullptr)	return;
		
		const Position& oldPosition = theDoodlebug->getPosition();
		const Organism *oldAnt = creatureAt(newPosition);
		if (oldAnt == nullptr)	return;

		delete oldAnt;
		board[newPosition.x][newPosition.y] = theDoodlebug;
		board[oldPosition.x][oldPosition.y] = nullptr;
		theDoodlebug->setPosition(newPosition);
		nAnts--;
	}

	void World::changePosition(Organism *theOrganism, const Position& newPosition)
	{
		//	if the Organism to move does not exist, or a Critter in new position already exists, 
		//	don't move at all
		if (theOrganism == nullptr)	return;
		if (creatureAt(newPosition) != nullptr)	return;		

		const Position& oldPosition = theOrganism->getPosition();
		board[newPosition.x][newPosition.y] = theOrganism;
		board[oldPosition.x][oldPosition.y] = nullptr;
		theOrganism->setPosition(newPosition);
	}

	void World::next()
	{
		initializeFlags();
		doodlebugsTurn();
		antsTurn();
	}

	void World::initializeFlags() const
	{
		for (int row = 0; row < N_ROWS; row++)
			for (int col = 0; col < N_COLS; col++)
			{
				Organism *theOrganism = board[row][col];
				if (theOrganism != nullptr)
				theOrganism->initializePlay();
			}
	}

	void World::doodlebugsTurn()
	{
		for (auto& row : board)
			for (const auto theOrganism : row)
			{
				if (theOrganism == nullptr || theOrganism->hasPlayed())	
					continue;

				Doodlebug *doodlebug = dynamic_cast<Doodlebug*>(theOrganism);
				if (doodlebug != nullptr)
				{
					// Move phase
					theOrganism->move(*this);
					
					// Breed phase
					const int timeToBreed = doodlebug->getBreedTime();
					if (timeToBreed == 0)
					{
						doodlebug->resetBreedTime();
						breed(doodlebug);
					}

					// Starvation phase
					const int livesLeft = doodlebug->getStarvation();
					if (livesLeft == 0)
						die(theOrganism);
				}
			}
	}

	void World::antsTurn()
	{
		for (auto& row : board)
			for (const auto theOrganism : row)
			{
				if (theOrganism == nullptr || theOrganism->hasPlayed())
					continue;

				Ant *ant = dynamic_cast<Ant*>(theOrganism);
				if (ant != nullptr)
				{
					// Move phase
					theOrganism->move(*this);

					// Breed phase
					const int timeToBreed = ant->getBreedTime();
					if (timeToBreed == 0)
					{
						ant->resetBreedTime();
						breed(ant);
					}
				}

			}
	}

	void World::die(Organism *theOrganism)
	{
		if (theOrganism == nullptr)	return;

		if (dynamic_cast<Doodlebug*>(theOrganism) != nullptr)
			nDoodlebugs--;
		else if (dynamic_cast<Ant*>(theOrganism) != nullptr)
			nAnts--;

		const Position thePosition = theOrganism->getPosition();	
		// do NOT return a reference here because theOrganism will be destroyed after this function call, and the reference will become dangling
		delete theOrganism;
		board[thePosition.x][thePosition.y] = nullptr;
	}

	
	void World::breed(Organism *theOrganism)
	{
		const std::vector<Position> neighborsPosition = freePositions(theOrganism);

		if (!canMoveToFreePosition(neighborsPosition))	return;	// no positions nearby

		const Position& randomPosition = theOrganism->chooseRandomPosition(neighborsPosition);

		Ant *ant = dynamic_cast<Ant*>(theOrganism);
		Doodlebug *doodlebug = dynamic_cast<Doodlebug*>(theOrganism);

		if (ant != nullptr)
		{
			Ant *newAnt = new Ant;
			board[randomPosition.x][randomPosition.y] = newAnt;
			newAnt->setPosition(randomPosition);
			newAnt->play();	// the newly born ant cannot play yet but wait next turn
			nAnts++;
		}
		else if (doodlebug != nullptr)
		{
			Doodlebug* newDoodlebug = new Doodlebug;
			board[randomPosition.x][randomPosition.y] = newDoodlebug;
			newDoodlebug->setPosition(randomPosition);
			newDoodlebug->play(); // the newly born doodlebug cannot play yet but wait next turn
			nDoodlebugs++;
		}
	}

} // myGame
