#include <stdexcept>
#include <iostream>
#include "14_09_Game.h"

namespace myNamespaceRPG
{
	Game::Game() : creatures(nullptr), numberCreatures(0), turn(0)
	{ /* Body intentionally left empty */ }


	Game::Game(const CreaturePtr*& theCreatures, const int theSize) : creatures(theCreatures), numberCreatures(theSize), turn(0)
	{ /* Body intentionally left empty */ }

	Game::~Game()
	{
		for (int idx = 0; idx < numberCreatures; idx++)
			delete creatures[idx];
		delete [] creatures;
	}

	const Creature& Game::operator[](const int index) const
	{
		if (index < 0 || index >= numberCreatures)
			throw std::out_of_range("Not a valid index\n");
		return *creatures[index];
	}

	void Game::playNextTurn()
	{
		if (numberCreatures == 0)
		{
			std::cout << "No creatures in this game\n";
			return;
		}

		std::cout << "Turn: " << ++turn << '\n';
		
		for (int idx = 0; idx < numberCreatures; idx++)
		{
			std::cout << idx + 1 << "). " << creatures[idx]->getSpecies() 
					  << ". Damage: " << creatures[idx]->getDamage();
		}

	}
} // myNamespaceRPG