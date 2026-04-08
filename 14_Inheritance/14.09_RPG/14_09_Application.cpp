#include <iostream>
#include "14_09_Game.h"
#include "14_09_Game_Builder.h"
#include "14_09_Validation.h"

int main( )
{
	using myNamespaceRPG::GameBuilder;
	using myNamespaceValidation::readNumber;
	GameBuilder aGame;
	while (true)
	{
		bool exit = false;
		int answer;
		std::cout << "Add new creatures (1), Delete creature (2) or play (3)?\n";
		readNumber(std::cin, answer);
		switch (answer)
		{
		case 1:
			aGame.addCreature();
			break;
		case 2:
			aGame.deleteCreature();
			break;
		case 3:
			exit = true;
			break;
		default:
			std::cout << "Choice not valid\n";
			break;
		}
		if (exit)	break;
	}
	using myNamespaceRPG::Game;
	using myNamespaceValidation::readLetter;
	Game newGame = aGame.build();

	char answer;
	do 
	{
		newGame.playNextTurn();
		std::cout << "Continue playing? (y/n)\n";
		readLetter(std::cin, answer);
	} while (std::tolower(answer) == 'y');

	std::cout << '\n';
	return 0;
}
