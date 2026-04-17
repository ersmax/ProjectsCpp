#include <stdexcept>
#include <iostream>
#include "14_13_Player.h"
#include "../14.11_Cards/14_11_Validation.h"

namespace myNamespacePoker
{
	Player::Player() : Player("No Name", 100)
	{ /* body intentionally left empty */ }


	Player::Player(const std::string& theName, const double theMoney) : namePlayer(theName), money(theMoney)
	{
		bet = 0.0;
		folded = false;
		ranking = 0;
	}

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

	void Player::resetTurn()
	{
		bet = 0;
		folded = false;
		hand.emptyDeck();
		bestHand.emptyDeck();
		ranking = 0;
	}

	void Player::resetBestHand()
	{
		bestHand.emptyDeck();
	}

	void Player::resetRanking()
	{
		ranking = 0;
	}

	bool Player::isEliminated() const
	{
		return money <= 0;
	}

	bool Player::hasFolded() const { return folded; }

	double Player::getBet() const { return bet; }

	double Player::getMoney() const { return money; }

	void Player::fold() { folded = true; }

	const Hand& Player::getHand() const { return hand; }

	const Hand& Player::getWinningHand() const { return bestHand; }

	void Player::setRanking(const int theRanking) { ranking = theRanking; }

	int Player::getRanking() const { return ranking; }

	const std::string& Player::getName() const { return namePlayer; }

	void Player::win(const double thePot)
	{
		money += thePot;
		std::cout << "Player " << namePlayer << " wins " << thePot 
				  << ". New balance: " << money << '\n';
	}

	void Player::lose()
	{
		if (money <= 0)
			std::cout << "The player is eliminated\n";
	}

	void Player::storeBestHand(const Hand& theHand)
	{
		bestHand.emptyDeck();
		for (int idx = 0; idx < theHand.getNumberCards(); idx++)
			bestHand.add(theHand[idx]);
	}

} // myNamespacePoker
