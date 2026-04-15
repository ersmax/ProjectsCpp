#ifndef PLAYER_14_13_H
#define PLAYER_14_13_H

#include "../14.11_Cards/14_11_Hand.h"

namespace myNamespacePoker
{
	using Hand = myNamespaceCards::Hand;
	using Card = myNamespaceCards::Card;

	constexpr int DECK_SIZE = 5;

	class Player
	{
	public:
		Player();
		//   Postcondition: set the current player's name, money, etc.
		Player(const std::string& theName, double money);
		void clearHand();
		//   Postcondition: calling the emptyDeck() function to move to the next round
		void win(double thePot);
		void setRanking(int theRanking);
		int getRanking() const;
		double getMoney() const;
		bool hasFolded() const;
		void fold();
		void placeBet(double theBet);
		//   Postcondition: allow Game class to set up the bet in each round
		double getBet() const;
		//   Postcondition: returns the bet
		void addCard(const Card& theCard);
		//   Postcondition: add a card to the player's hand;
		const Hand& getHand() const;
		void storeBestHand(int cardRanks[], int size);
	private:
		Hand hand;
		//   Postcondition: hold the player's current 2-card hand
		double money;
		double bet;
		std::string namePlayer;
		bool folded;
		int ranking;
		int bestHand[DECK_SIZE] = {0};	
	};


} // myNamespacePoker


#endif // PLAYER_14_13_H
