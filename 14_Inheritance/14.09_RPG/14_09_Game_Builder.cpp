#include <iostream>
#include <stdexcept>
#include "14_09_Game_Builder.h"
#include "14_09_Human.h"
#include "14_09_Cyberdemon.h"
#include "14_09_Balrog.h"
#include "14_09_Elf.h"

#include "14_09_Validation.h"

namespace myNamespaceRPG
{
	typedef Human *HumanPtr;
	typedef Cyberdemon *CyberdemonPtr;
	typedef Balrog *BalrogPtr;
	typedef Elf *ElfPtr;


	GameBuilder::GameBuilder() : creatures(nullptr), numberCreatures(0)
	{ /* Body intentionally left empty */ }

	GameBuilder::GameBuilder(const GameBuilder& anotherGame) : numberCreatures(anotherGame.numberCreatures)
	{
		creatures = new CreaturePtr[anotherGame.numberCreatures];
		for (int idx = 0; idx < numberCreatures; idx++)
			creatures[idx] = anotherGame.creatures[idx];
	}

	GameBuilder& GameBuilder::operator =(const GameBuilder& anotherGame)
	{
		if (this == &anotherGame)	return *this;
		if (numberCreatures != anotherGame.numberCreatures)
		{
			delete [] creatures;
			creatures = new CreaturePtr[anotherGame.numberCreatures];
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
		return *creatures[index];
	}
	
	void GameBuilder::showCreatures() const
	{
		for (int idx = 0; idx < numberCreatures; idx++)
			std::cout << idx + 1 << ") " << creatures[idx] << '\n';
	}

	void GameBuilder::addCreature()
	{
		std::cout << "Enter a creature to add among these:\n"
				  << "1. Humans\n2. Cyberdemon\n3. Balrog\n4. Elf\n";	// 14_09_Creature.h
		using myNamespaceValidation::readNumber;
		int choice;
		readNumber(std::cin, choice);
		switch (choice)
		{
		case 1:
			{
				const HumanPtr aHuman = new Human;
				std::cout << "Enter new Human player:\n";
				std::cin >> *aHuman;
				addCreatureHelper(aHuman);
				break;
			}
		case 2:
			{
				const CyberdemonPtr aCyberdemon = new Cyberdemon;
				std::cout << "Enter new Cyberdemon player:\n";
				std::cin >> *aCyberdemon;
				addCreatureHelper(aCyberdemon);
				break;
			}
		case 3:
			{
				const BalrogPtr aBalrog = new Balrog;
				std::cout << "Enter new Balrog player:\n";
				std::cin >> *aBalrog;
				addCreatureHelper(aBalrog);
				break;
			}
		case 4:
			{
				const ElfPtr anElf = new Elf;
				std::cout << "Enter new Elf player:\n";
				std::cin >> *anElf;
				addCreatureHelper(anElf);
				break;
			}
		default:
			std::cout << "Not a valid choice\n";
			break;
		}
	}

	void GameBuilder::addCreatureHelper(const CreaturePtr& newCreature)
	{
		CreaturePtr *temp = new CreaturePtr[numberCreatures + 1];
		for (int idx = 0; idx < numberCreatures; idx++)
			temp[idx] = creatures[idx];
		temp[numberCreatures] = newCreature;
		numberCreatures++;
		delete [] creatures;
		creatures = temp;
	}

	void GameBuilder::deleteCreature()
	{
		if (numberCreatures <= 0)
		{
			std::cout << "There are no creatures\n";
			return 0;
		}
		showCreatures();
		std::cout << "Enter index of creature to delete:\n";
		using myNamespaceValidation::readNumber;
		int index;
		readNumber(std::cin, index);
		index--; // Zero-normalize
		if (index >= 0 && index < numberCreatures)
			deleteCreatureHelper(index);
		else
			std::cout << "Index not valid\n";
	}

	void GameBuilder::deleteCreatureHelper(const int index)
	{
		CreaturePtr *temp = new CreaturePtr[numberCreatures - 1];
		int newIdx = 0;
		for (int idx = 0; idx < numberCreatures; idx++)
			if (idx != index)
				temp[newIdx++] = creatures[idx];
		numberCreatures--;
		delete [] creatures;
		creatures = temp;
	}

} // myNamespaceRPG
