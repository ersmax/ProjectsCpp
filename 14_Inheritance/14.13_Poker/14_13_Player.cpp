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

	void Player::placeBet(const double theBet)
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

	double Player::getBet() const { return bet; }

	double Player::getMoney() const { return money; }

	void Player::fold() { folded = true; }

	const Hand& Player::getHand() const { return hand; }

	void Player::setRanking(const int theRanking) { ranking = theRanking; }

	int Player::getRanking() const { return ranking; }

	void Player::win(const double thePot)
	{
		money += thePot;
		std::cout << "Player " << namePlayer << " wins " << thePot 
				  << ". New balance: " << money << '\n';
	}

	void Player::storeBestHand(const Hand& theHand)
	{
		for (const Card& card : theHand)
			bestHand.add(card);
	}

} // myNamespacePoker
