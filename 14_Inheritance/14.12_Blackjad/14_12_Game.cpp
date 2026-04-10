#include <iostream>
#include "14_12_Game.h"
#include "../14.11_Cards/14_11_Validation.h"


namespace myNamespaceBlackjack
{
	constexpr int DEALER = 0;
	constexpr int HOUSE_STAND = 17;

	Game::Game() 
	{
		shoe.shuffle();
		dealInitial();
	}

	void Game::play()
	{
		for (int idx = 1; idx < N_PLAYERS; idx++)
			playerTurn(hands[idx]);

		bool allBusted = true;
		for (int idx = 0; idx < N_PLAYERS; idx++)
		{
			if (!isBust(hands[idx]))
			{
				allBusted = false;
				break;
			}
		}
		if (allBusted)
		{
			std::cout << "The House wins\n";
			return;
		}

		dealerTurn();
		resolveRound();
	}


	void Game::resolveRound()
	{
		
		const Hand& dealerHand = hands[DEALER];
		std::cout << "Dealer's hand:\n" << dealerHand << '\n';
		std::cout << "Dealer's score: " << handValue(dealerHand) << '\n';
		if (isBlackjack(dealerHand))
			std::cout << "Dealer has scored blackjack\n";
		if (isBust(dealerHand))
			std::cout << "Dealer is busted\n";
		std::cout << '\n';

		for (int idx = 1; idx < N_PLAYERS; idx++)
		{
			const Hand& playerHand = hands[idx];
			
			std::cout << "Player " << idx << " hand:\n" << playerHand;
			std::cout << "Player " << idx << " score:\n" << handValue(playerHand);

			if (isBlackjack(playerHand))
				std::cout << "Player " << idx << " has scored blackjack\n";
			if (isBust(playerHand))
				std::cout << "Player " << idx << " is busted\n";
			std::cout << '\n';

			/* FINAL RESULTS */
			// 1) Player bust
			std::cout << "Result for the player " << idx << ":\n";
			if (isBust(playerHand))
			{
				std::cout << "Player LOST (player bust)\n";
				continue;
			}
			// 2) Dealer bust
			if (isBust(dealerHand))
			{
				std::cout << "Player WIN (dealer bust)\n";
				continue;
			}
			// 3) Player only blackjack 
			// TODO
			// 4) Dealer only blackjack
			// TODO
			// 5) Compare totals
			// TODO

		}


	}


	void Game::dealInitial()
	{
		constexpr int CARDS = 2;
		for (int idx = 0; idx < CARDS; idx++)
			for (int idxPlayer = N_PLAYERS - 1; idxPlayer >= 0; idxPlayer--)
			{
				Card newCard = shoe.remove();
				hands[idxPlayer].add(newCard);
			}
	}

	void Game::dealerTurn()
	{
		int houseScore;
		do
		{
			std::cout << "Cards of the House:\n" << hands[DEALER];
			houseScore = handValue(hands[DEALER]);
			std::cout << "Current House Score: " << houseScore << '\n';
			
			if (houseScore < HOUSE_STAND)
			{
				Card aCard = shoe.remove();
				hands[DEALER].add(aCard);
				std::cout << "New card: " << aCard;
			}

		} while (houseScore < HOUSE_STAND);
	}

	void Game::playerTurn(Hand& hand)
	{
		using myNamespaceValidation::readName;
		while (true)
		{
			std::cout << "Cards of the player:\n" << hand;
			std::cout << "Current Player Score: " << handValue(hand) << '\n';
			std::cout << "Cards of the House:\n";
			printHiddenCardsHouse(hands[DEALER]);
			std::cout << "Score of the house: " << handValueHidden(hands[DEALER]) << '\n';

			std::cout << "Draw new card (hit)? Enter 'h'\n";
			std::cout << "Don't draw anything (stand)? Enter 's'\n";
			char choice;
			readName(std::cin, choice);

			switch (choice)
			{
			case 'h':
			{
				std::cout << "Player draw\n";
				Card aCard = shoe.remove();
				hand.add(aCard);
				std::cout << "New card drawn: " << aCard;
				break;
			}
			case 's':
				std::cout << "Player stands\n";
				return;
			default:
				std::cout << "Not a valid choice. Retry\n";
				break;
			}
			if (isBust(hand) && choice == 'h')
			{
				std::cout << "Player's current cards:\n" << hand;
				std::cout << "Player's current score:\n" << handValue(hand) << "\n\n";
				std::cout << "Player is busted\n";
				return;
			}
		}
	}

	void Game::printHiddenCardsHouse(const Hand& hand)
	{
		int numberCards = hand.getNumberCards() - 1;	// print all except last
		for (int idx = 0; idx < numberCards; idx++)
			std::cout << "Card " << idx + 1 << ": " << hand[idx];
		std::cout << "Card " << hand.getNumberCards() << ": " << "[*]\n";
	}

	int Game::handValue(const Hand& hand) const
	{
		return handValue(hand, hand.getNumberCards());
	}

	int Game::handValueHidden(const Hand& hand) const
	{
		return handValue(hand, hand.getNumberCards() - 1);
		// do not show the points of the last hidden card
	} 

	int Game::handValue(const Hand& hand, const int visibleCards) const
	{
		int points = 0;
		int aces = 0;
		for (int idx = 0; idx < visibleCards; idx++)
		{
			const Card& aCard = hand[idx];
			const std::string& name = aCard.getName();
			if (name == "Ace")
			{
				points += 11;
				++aces;
			}
			else if (name == "Jack" || name == "Queen" || name == "King")
				points += 10;
			else
				points += std::stoi(name);
		}

		while (points > 21 && aces > 0)
		{
			points -= 10;	// an Ace value can be either 1 or 11
			--aces;
		}

		return points;
	}

	bool Game::isBlackjack(const Hand& hand) const
	{
		return (hand.getNumberCards() == 2 && handValue(hand) == 21);
	}

	bool Game::isBust(const Hand& hand) const
	{
		return handValue(hand) > 21;
	}
} // myNamespaceBlackjack