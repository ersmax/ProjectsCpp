#ifndef GAME_14_12_H
#define GAME_14_12_H

#include <vector>
#include "../14.11_Cards/14_11_Hand.h"


namespace myNamespaceBlackjack
{
	constexpr int N_PLAYERS = 2;
	// 0 = dealer, 1 = new player

	class Game
	{
		using myNamespaceCards::Deck;
		using myNamespaceCards::Hand;
		using myNamespaceCards::Card;

	public:
		Game();
		void play();
		//   Postcondition: run one blackjack round


	private:
		void dealInitial();
		void playerTurn(Hand& hand);
		void dealerTurn();
		void resolveRound();

		int handValue(const Hand& hand) const;
		int handValueHidden(const Hand& hand) const;
		int handValue(const Hand& hand, int visibleCards) const;
		bool isBust(const Hand& hand) const;
		bool isBlackjack(const Hand& hand) const;

		void printHiddenCardsHouse(const Hand& hand);
		
		Deck shoe;
		Hand hands[N_PLAYERS];
		// dealer + player
		
	};

} // myNamespaceBlackjack

#endif// GAME_14_12_H 
