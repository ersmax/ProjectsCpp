#include <iostream>
#include <string>
#include "15_03_World.h"

int main( )
{
	using myGame::World;
	World aGame;
	std::string line;

	aGame.output();
	while (true)
	{
		std::cout << "Press Enter to continue (Ctrl+Z to quit)\n";
		if (!std::getline(std::cin, line))
			break;

		aGame.next();
		aGame.output();
	}

	std::cout << '\n';
	return 0;
}
