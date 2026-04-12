#ifndef PLAYER_14_13_H
#define PLAYER_14_13_H

#include "../14.11_Cards/14_11_Hand.h"

namespace myNamespacePoker
{
	using Hand = myNamespaceCards::Hand;

	class Player
	{
	public:
		Player();
		//   Postcondition: set the current player's name, money, etc.
		Player(const std::string& theName, int money);
		void clearHand();
		//   Postcondition: calling the emptyDeck() function to move to the next round
		int getMoney() const;
		void placeBet();
		void win();
		void lose();

	private:
		Hand hand;
		//   Postcondition: hold the player's current 2-card hand
		int money;
		int currentBet;
		std::string namePlayer;
	};


} // myNamespacePoker


#endif // PLAYER_14_13_H
