#ifndef GAME_14_12_H
#define GAME_14_12_H

#include <vector>
#include "../14.11_Cards/14_11_Hand.h"


namespace myNamespaceBlackjack
{
	constexpr int N_PLAYERS = 3;
	// 0 = dealer, 1 - .. = new player


	class Game
	{
	using Hand = myNamespaceCards::Hand;
	using Card = myNamespaceCards::Card;
	using Deck = myNamespaceCards::Deck;

	public:
		Game();
		//   Postcondition: Shuffle the shoe and deal two cards to each player and the dealer.
		void play();
		//   Postcondition: run one blackjack round


	private:
		void dealInitial();
		//   Postcondition: Deal two cards to each player and the dealer.
		void playerTurn(Hand& hand);
		//   Postcondition: Run the player's turn, 
		// allowing them to hit or stand until they bust, get blackjack, or choose to stand.
		void dealerTurn();
		//   Postcondition: Run the dealer's turn, allowing them to hit until they reach a score of 17 or higher.
		// If all players are busted, the dealer does not take a turn and wins the round.
		void resolveRound() const;
		//   Postcondition: Determine the outcome of the round for each player, 
		// comparing their hand values to the dealer's hand value and printing the results.

		int handValue(const Hand& hand) const;
		//   Precondition: The hand contains valid cards.
		//   Postcondition: Calculate the total value of the hand, counting Aces as 1 or 11 as appropriate.
		int handValueHidden(const Hand& hand) const;
		//   Postcondition: Calculate the total value of the hand, counting only the visible cards (not the hidden card).
		// This function is useful to show the points of the dealer to the players excluding the hidden card.
		int handValue(const Hand& hand, int visibleCards) const;
		//   Postcondition: Calculate the total value of the hand, counting only the specified number of visible cards.
		bool isBust(const Hand& hand) const;
		//   Postcondition: Return true if the total value of the hand exceeds 21, indicating that the player has busted.
		bool isBlackjack(const Hand& hand) const;
		//   Postcondition: Return true if the hand contains exactly two cards and the total value is 21, indicating a blackjack.
		bool isTwentyone(const Hand& hand) const;
		//   Postcondition: Return true if the total value of the hand is exactly 21, indicating a score of 21.
		// This function is useful to check if the player has reached 21 points during their turn, so as not to ask 
		// the user to stand or hit, and to end the player's turn immediately, if they reached already 21 points.

		void printHiddenCardsHouse(const Hand& hand);
		//   Postcondition: Print the cards of the dealer's hand, showing all cards except the last one as hidden (e.g., "[*]").
		// This function is useful to show the cards of the dealer to the players, while keeping one card hidden until the dealer's turn is over.
		
		Deck shoe;
		//   Postcondition: Initialize the shoe with a standard deck of 52 cards, to shuffle next in the Game() constructor.
		Hand hands[N_PLAYERS];
		// dealer + player
		
	};

} // myNamespaceBlackjack

#endif// GAME_14_12_H 
