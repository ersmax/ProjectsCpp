#include <stdexcept>
#include <iostream>
#include "14_09_Game.h"
#include "14_09_Human.h"
#include "14_09_Cyberdemon.h"
#include "14_09_Balrog.h"
#include "14_09_Elf.h"

namespace myNamespaceRPG
{
	Game::Game() : creatures(nullptr), numberCreatures(0), turn(0)
	{ /* Body intentionally left empty */ }


	Game::Game(const CreaturePtr* theCreatures, const int theSize) : creatures(theCreatures), numberCreatures(theSize), turn(0)
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
		
		int damageHumans = 0, damageCyberdemons = 0, damageBalrogs = 0, damageElves = 0;
		for (int idx = 0; idx < numberCreatures; idx++)
		{
			const CreaturePtr creature = creatures[idx];
			const std::string& species = creature->getSpecies();
			
			std::cout << idx + 1 << "). ";
			const int damage = creature->getDamage();
			
			if (Human* human = dynamic_cast<Human*>(creature))
				// Downcast: non-null if creature's dynamic type is Human (or derived from Human)
				damageHumans += damage;
			else if (Cyberdemon *cyberdemon = dynamic_cast<Cyberdemon*>(creature))
				damageCyberdemons += damage;
			else if (Balrog *balrog = dynamic_cast<Balrog*>(creature))
				damageBalrogs += damage;
			else if (Elf *elf = dynamic_cast<Elf*>(creature))
				damageElves += damage;
		}
		std::cout << "Damage Humans: " << damageHumans << '\n';
		std::cout << "Damage Cyberdemons: " << damageCyberdemons << '\n';
		std::cout << "Damage Balrogs: " << damageBalrogs << '\n';
		std::cout << "Damage Elves: " << damageElves << '\n' << '\n';
		std::cout << "Ready for the next turn\n\n";
	}
} // myNamespaceRPG