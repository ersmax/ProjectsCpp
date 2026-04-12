#ifndef GAME_14_13_H
#define GAME_14_13_H

#include "vector"
#include "14_13_Player.h"


namespace myNamespacePoker
{
	using myNamespaceCards::Deck;


	class Game
	{
	public:
		Game();
		//   Postcondition: create new game, shuffle cards
		void playRound();
		//   Postcondition: distribute card, handle betting and pot

	private:
		void resetRoundState();
		//   Postcondition: reset players's hand, pots and betting
		void takeBets();
		//   Postcondition: ask players how much to bet (or skip),
		// update their money and the pot
		void distributeCards();
		//   Postcondition: distribute cards to each player
		void showHands();
		//   Postcondition: show each player's hand
		void resolveRound();
		//   Postcondition: evaluate hands, determine winner, pay out from pot



		Deck deck;
		//   Postcondition: create a deck of 52 cards
		std::vector<Player> players;
		int pot;
	};

} // myNamespacePoker


#endif // GAME_14_13_H
