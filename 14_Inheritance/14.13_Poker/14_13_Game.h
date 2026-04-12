#ifndef GAME_14_13_H
#define GAME_14_13_H

#include "vector"
#include "14_13_Player.h"


namespace myNamespacePoker
{
	using Deck = myNamespaceCards::Deck;
	using Card = myNamespaceCards::Card;


	class Game
	{
	public:
		Game();
		//   Postcondition: create new game, shuffle cards
		void play();
		//   Postcondition: distribute card, handle betting and pot

	private:
		void playHand();
		//   Postcondition: play one Texas Hold'em hand		
		void resetRoundState();
		//   Postcondition: reset players's hand, pots and betting
		void takeBets();
		//   Postcondition: ask players how much to bet (or skip),
		// update their money and the pot
		void initiateGame();
		//   Postcondition: distribute 2 cards to each player and 3 on the board
		void showHands();
		//   Postcondition: show each player's hand
		void resolveRound();
		//   Postcondition: evaluate hands, determine winner, pay out from pot

		Deck shoe;
		//   Postcondition: create a deck of 52 cards
		std::vector<Player> players;
		//   Postcondition: the vector of players holding 2 cards each
		std::vector<Card> board;
		//   Postcondition: this is the board with 3, 4, and 5 cards
		int pot;
	};

} // myNamespacePoker


#endif // GAME_14_13_H
