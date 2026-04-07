#include <iostream>
#include <stdexcept>
#include "14_09_Game_Builder.h"

namespace myNamespaceRPG
{
	GameBuilder::GameBuilder() : creatures(nullptr), numberCreatures(0)
	{ /* Body intentionally left empty */ }

	GameBuilder::GameBuilder(const GameBuilder& anotherGame) : numberCreatures(anotherGame.numberCreatures)
	{
		creatures = new Creature[anotherGame.numberCreatures];
		for (int idx = 0; idx < numberCreatures; idx++)
			creatures[idx] = anotherGame.creatures[idx];
	}

	GameBuilder& GameBuilder::operator =(const GameBuilder& anotherGame)
	{
		if (this == &anotherGame)	return *this;
		if (numberCreatures != anotherGame.numberCreatures)
		{
			delete [] creatures;
			creatures = new Creature[anotherGame.numberCreatures];
		}
		numberCreatures = anotherGame.numberCreatures;
		for (int idx = 0; idx < numberCreatures; idx++)
			creatures[idx] = anotherGame.creatures[idx];
		return *this;
	}

	GameBuilder::~GameBuilder() { delete [] creatures; }

	const Game GameBuilder::build()
	{
		Game newGame(creatures, numberCreatures);
		// Transfer ownership of the dynamic array to Game

		creatures = nullptr;	
		// Builder no longer owns the array. Prevents double delete in its destructor
		numberCreatures = 0;
		return newGame;
	}

	const Creature& GameBuilder::operator[](const int index) const
	{
		if (index < 0 || index >= numberCreatures)
			throw std::out_of_range("Invalid index\n");
		return creatures[index];
	}
	
	void GameBuilder::showCreatures() const
	{
		for (int idx = 0; idx < numberCreatures; idx++)
			std::cout << idx + 1 << ") " << creatures[idx] << '\n';
	}

	void GameBuilder::addCreature(const Creature& newCreature)
	{
		const CreaturePtr temp = new Creature[numberCreatures + 1];
		for (int idx = 0; idx < numberCreatures; idx++)
			temp[idx] = creatures[idx];
		temp[numberCreatures] = newCreature;
		numberCreatures++;
		delete [] creatures;
		creatures = temp;
	}

	void GameBuilder::deleteCreature(const int index)
	{
		showCreatures();
		const CreaturePtr temp = new Creature[numberCreatures - 1];
		int newIdx = 0;
		for (int idx = 0; idx < numberCreatures; idx++)
			if (idx != index)
				temp[newIdx++] = creatures[idx];
		numberCreatures--;
		delete [] creatures;
		creatures = temp;
	}

} // myNamespaceRPG
