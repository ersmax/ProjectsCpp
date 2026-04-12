#include <iostream>
#include "14_12_Game.h"


int main( )
{
	using myNamespaceBlackjack::Game;
	Game aGame;
	aGame.play();

	std::cout << '\n';
	return 0;
}