#ifndef PLAYER_14_13_H
#define PLAYER_14_13_H

#include "../14.11_Cards/14_11_Hand.h"

namespace myNamespacePoker
{
	using Hand = myNamespaceCards::Hand;
	using Card = myNamespaceCards::Card;

	class Player
	{
	public:
		Player();
		//   Postcondition: set the current player's name, money, etc.
		Player(const std::string& theName, int money);
		void clearHand();
		//   Postcondition: calling the emptyDeck() function to move to the next round
		void setRanking(int theRanking);
		int getMoney() const;
		bool hasFolded() const;
		void fold();
		void placeBet(int theBet);
		//   Postcondition: allow Game class to set up the bet in each round
		int getBet() const;
		//   Postcondition: returns the bet
		void addCard(const Card& theCard);
		//   Postcondition: add a card to the player's hand;
		const Hand& getHand() const;
	private:
		Hand hand;
		//   Postcondition: hold the player's current 2-card hand
		int money;
		int bet;
		std::string namePlayer;
		bool folded;
		int ranking;
	};


} // myNamespacePoker


#endif // PLAYER_14_13_H
