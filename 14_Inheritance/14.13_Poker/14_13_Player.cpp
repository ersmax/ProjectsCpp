#include <stdexcept>
#include <iostream>
#include "14_13_Player.h"
#include "../14.11_Cards/14_11_Validation.h"

namespace myNamespacePoker
{
	void Player::addCard(const Card& theCard)
	{
		hand.add(theCard);
	}

	void Player::placeBet(const int theBet)
	{
		if (theBet < 0)
			throw std::out_of_range("Bet cannot be less than 0\n");
		if (theBet >= money)
		{
			std::cout << "All in!\n";
			bet += money;
			money = 0;
		}
		else
		{
			money -= theBet;
			bet += theBet;
		}
	}

	bool Player::hasFolded() const { return folded; }

	int Player::getBet() const { return bet; }

	int Player::getMoney() const { return money; }

	void Player::fold() { folded = true; }

	const Hand& Player::getHand() const { return hand; }

	void Player::setRanking(const int theRanking) { ranking = theRanking; }

} // myNamespacePoker
