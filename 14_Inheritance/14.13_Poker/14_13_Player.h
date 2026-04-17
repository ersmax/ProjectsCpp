#ifndef PLAYER_14_13_H
#define PLAYER_14_13_H

#include <vector>
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
		Player(const std::string& theName, double theMoney);
		void resetTurn();
		//   Postcondition: calling the emptyDeck() function to move to the next round
		void resetBestHand();
		//   Postcondition: clear the best evaluated hand from the previous resolution
		void resetRanking();
		//   Postcondition: reset ranking to the default non-ranked state
		bool isEliminated() const;
		//   Postcondition: returns true if player has no money left
		void win(double thePot);
		void lose();
		void setRanking(int theRanking);
		int getRanking() const;
		double getMoney() const;
		const std::string& getName() const;
		bool hasFolded() const;
		void fold();
		void placeBet(double theBet);
		//   Postcondition: allow Game class to set up the bet in each round
		void resetBetForStreet();
		//   Postcondition: resets current street contribution to 0
		double getBet() const;
		//   Postcondition: returns the bet
		void addCard(const Card& theCard);
		//   Postcondition: add a card to the player's hand;
		const Hand& getHand() const;
		const Hand& getWinningHand() const;
		void storeBestHand(const Hand& theHand);
	private:
		std::string namePlayer;
		double money;
		double bet;
		Hand hand;
		//   Postcondition: hold the player's current 2-card hand
		bool folded;
		int ranking;
		Hand bestHand;	
	};


} // myNamespacePoker


#endif // PLAYER_14_13_H
