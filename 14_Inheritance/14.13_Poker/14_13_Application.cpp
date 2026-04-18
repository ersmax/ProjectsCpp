/* TEXAS HOLD'EM POKER */

#include <iostream>
#include "14_13_Game.h"

int main( )
{
	using myNamespacePoker::Game;
	using myNamespacePoker::Player;

	const Player alex("Alex", 100);
	const Player sara("Sara", 100);
	const Player marc("Marc", 100);
	std::vector<Player> players;
	players.push_back(alex);
	players.push_back(sara);
	players.push_back(marc);
	Game aGame(players);
	aGame.play();

	std::cout << '\n';
	return 0;
}