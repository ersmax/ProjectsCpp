/*
Do Programming Project 14.11 and extend the program to play five-card stud
poker between two hands. Add more functions as necessary to implement your
program. For an additional challenge, incorporate a betting component.

Note of implementation: I decided to implement Texas hold'em poker
*/

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