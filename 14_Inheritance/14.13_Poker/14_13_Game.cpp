#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "14_13_Game.h"
#include "../14.11_Cards/14_11_Validation.h"

namespace
{
	using myNamespaceCards::NAMES;
	using myNamespaceCards::N_NAMES;
	using myNamespaceCards::SUITS;
	using myNamespaceCards::N_SUITS;
	using myNamespaceCards::Card;

	int highRank(const std::string& value, const std::string *array, const int size)
	//   Postcondition: return the ranking of a card number, where Ace values the most
	// e.g. 10, J, Q, K, Ace with "Ace" as value would return 13
	{
		for (int idx = 0; idx < size; idx++)
		{
			if (array[idx] == value && value == "Ace")
				return size;
			if (array[idx] == value)
				return idx;
		}
		return -1;
	}

	int lowRank(const std::string& value, const std::string array[], const int size)
	//   Postcondition: return the ranking of a card number, where Ace values the least
	// e.g. Ace, 2, 3, 4, 5 with "Ace" as value would return 0
	{
		for (int idx = 0; idx < size; idx++)
		{
			if (array[idx] == value && value == "Ace")
				return 0;
			if (array[idx] == value)
				return idx;
		}
		return -1;
	}

	int rankSuit(const std::string& value, const std::string array[], const int size)
	//   Postcondition: return the index of a card rank in the array (Clubs, Diamonds, Hearts, Spades)
	{
		for (int idx = 0; idx < size; idx++)
			if (array[idx] == value)
				return idx;
		return -1;
	}

}  // unnamed namespace


namespace myNamespacePoker
{
	
	Game::Game() : Game(2)
	{ /* Body intentionally left empty */ }

	Game::Game(const int thePlayers)
	{
		if (thePlayers < 2)
			throw std::invalid_argument("Number of players must be greater than 2\n");
		
		nPlayers = thePlayers;
		players.resize(nPlayers);
		smallBlind = 0;
		bigBlind = 1;
		roundBet = STARTING_BET;
		shoe.shuffle();
		initiateTurn();
	}


	void Game::initiateTurn()
	{
		constexpr int CARDS_PLAYER = 2;
		constexpr int CARDS_BOARD = 3;

		// reset the hand of each player in a new turn
		for (int idx = 0; idx < nPlayers; idx++)
			players[idx].clearHand();

		// pre-flop
		players[smallBlind].placeBet(roundBet);
		pot += roundBet;
		roundBet *= 2;
		players[bigBlind].placeBet(roundBet);
		pot += roundBet;

		// distribute the new cards 
		for (int idxCard = 0; idxCard < CARDS_PLAYER; idxCard++)
			for (int idxPlayer = 0; idxPlayer < nPlayers; idxPlayer++)
				players[idxPlayer].addCard(shoe.remove());

		for (int idxCard = 0; idxCard < CARDS_BOARD; idxCard++)
			board.push_back(shoe.remove());

		// set current player and bet
		currentBet = players[bigBlind].getBet();
		currentPlayer = (bigBlind + 1) % nPlayers;
	}

	void Game::play()
	{
		do
		{
			initiateTurn();
			playHand();
		} while (nPlayers == 1);
	}


	void Game::playHand()
	{
		for (int idx = 1; idx <= 3; idx++)
		{
			takeBets();
			board.push_back(shoe.remove());
		}
		resolveRound();
		resetRoundState();
	}

	void Game::takeBets()
	{
		using myNamespaceValidation::readName;

		bool someoneRaised;
		do
		{
			someoneRaised = false;
			showBoard(board);
			for (int idx = 0; idx < nPlayers; idx++)
			{
				const int idxPlayer = (currentPlayer + idx) % nPlayers;
				Player& thePlayer = players[idxPlayer];

				std::cout << "Player " << idxPlayer + 1 << " turn.\n";
				std::cout << "Money: " << thePlayer.getMoney() << '\n';

				if (thePlayer.hasFolded())
				{
					std::cout << "Status: Has folded\n";
					continue;
				}

				std::cout << "Current bet: " << thePlayer.getBet() << '\n'
						  << "Highest bet: " << currentBet << '\n';
				showHand(thePlayer);

				char choice{};
				do
				{
					std::cout << "Call (c), raise (r) or fold (f)?\n";
					readName(std::cin, choice);
				} while (choice != 'c' && choice != 'r' && choice != 'f');

				
				int callingBet = currentBet - thePlayer.getBet();
				switch (choice)
				{
				case 'c':
					callHand(thePlayer, callingBet);
					break;
				case 'r':
					raiseHand(thePlayer, callingBet);
					someoneRaised = true;
					break;
				case 'f':
					foldHand(thePlayer);
					break;
				default:
					std::cout << "Invalid choice\n";
					break;
				}
			}
		} while (someoneRaised && atLeastTwoBetting());
	}

	void Game::callHand(Player& thePlayer, const int callingBet)
	{
		thePlayer.placeBet(callingBet);
		pot += callingBet;
	}

	void Game::raiseHand(Player& thePlayer, const int callingBet)
	{
		using myNamespaceValidation::readName;
		using myNamespaceValidation::readNumber;

		if (thePlayer.getMoney() <= callingBet)
		{
			char choice;
			std::cout << "Player does not have enough money to raise. Go all in (y/n)?\n";
			readName(std::cin, choice);
			if (std::tolower(choice) == 'y')
			{
				const int allIn = thePlayer.getMoney();
				thePlayer.placeBet(allIn);
				pot += allIn;
			}
			else
			{
				std::cout << "Player folds\n";
				thePlayer.fold();
			}
			return;
		}

		int theDifference;
		do
		{
			std::cout << "Enter a bet (at least " << callingBet << "):\n";
			readNumber(std::cin, theDifference);
		} while (theDifference < callingBet);

		thePlayer.placeBet(theDifference);
		pot += theDifference;
		currentBet = thePlayer.getBet();
	}

	void Game::foldHand(Player& thePlayer)
	{
		std::cout << "Player folds\n";
		thePlayer.fold();
	}

	bool Game::atLeastTwoBetting() const
	{
		int count = 0;
		for (int idx = 0; idx < nPlayers; idx++)
			if (!players[idx].hasFolded())
				count++;
		if (count < 2) return false;
		return true;
	}

	void Game::showHand(const Player& thePlayer)
	{
		std::cout << thePlayer.getHand();
	}

	void Game::showBoard(const std::vector<Card>& theBoard)
	{
		for (size_t idx = 0; idx < theBoard.size(); idx++)
			std::cout << "Card " << idx + 1 << theBoard[idx];
	}

	void Game::resolveRound()
	{
		for (int idx = 0; idx < nPlayers; idx++)
		{
			int idxPlayer = (currentPlayer + idx) % nPlayers;
			Player& thePlayer = players[idxPlayer];
			const Hand& handPlayer = thePlayer.getHand();
			
			std::vector<Card> theHand;
			for (size_t idxCard = 0; idxCard < board.size(); idxCard++)
				theHand.push_back(board[idxCard]);
			for (int idxCard = 0; idxCard < handPlayer.getNumberCards(); idxCard++)
				theHand.push_back(handPlayer[idxCard]);
			setRanking(thePlayer, theHand);
		}
	}

	void Game::setRanking(Player& thePlayer, const std::vector<Card>& theHand)
	{
		if (isRoyalFlush(theHand))
			thePlayer.setRanking(1);
		else if (isStraightFlush(theHand))
			thePlayer.setRanking(2);
		else if (isFourOfAKind(theHand))
			thePlayer.setRanking(3);
		else if (isFlush(theHand))
			thePlayer.setRanking(4);
		else if (isFullHouse(theHand))
			thePlayer.setRanking(5);
		else if (isStraight(theHand))
			thePlayer.setRanking(6);
		else if (isThreeOfAKind(theHand))
			thePlayer.setRanking(7);
		else if (isTwoPair(theHand))
			thePlayer.setRanking(8);
		else if (isOnePair(theHand))
			thePlayer.setRanking(9);
		else if (isHighCard(theHand))
			thePlayer.setRanking(10);
	}

	// Ranking 1
	bool Game::isRoyalFlush(const std::vector<Card>& theHand)
	{
		using namespace myNamespaceCards;

		for (const std::string& suitCard : SUITS)
		{
			bool has10 = false;
			bool hasJ = false;
			bool hasQ = false;
			bool hasK = false;
			bool hasA = false;

			// look at the cards of the same suit only
			for (const Card& card : theHand)
			{
				if (card.getSuit() != suitCard)	continue;
				
				const std::string& name = card.getName();
				if (name == "10")			has10 = true;
				else if (name == "Jack")	hasJ = true;
				else if (name == "Queen")	hasQ = true;
				else if (name == "King")	hasK = true;
				else if (name == "Ace")		hasA = true;
			}
			if (has10 && hasJ && hasQ && hasK && hasA)
				return true;
		}
		return false;
	}

	// Ranking 2
	bool Game::isStraightFlush(const std::vector<Card>& theHand)
	{
		using namespace myNamespaceCards;
		for (const std::string& suit : SUITS)
		{
			std::vector<int> ranksHigh;		// 10, J, Q, K, Ace
			std::vector<int> ranksLow;		// Ace, 2, 3, 4, 5

			// Collect ranks of a specific suit
			for (const Card& card : theHand)
			{
				if (card.getSuit() != suit)	continue;
				int rankHigh = highRank(card.getName(), NAMES, N_NAMES);
				int rankLow = lowRank(card.getName(), NAMES, N_NAMES);
				
				ranksHigh.push_back(rankHigh);
				ranksLow.push_back(rankLow);
			}

			// Skip if deck does not have at least 5 cards of same suit
			if (ranksHigh.size() < 5)	continue;

			// Sort and remove duplicates for High rank
			std::sort(ranksHigh.begin(), ranksHigh.end());
			ranksHigh.erase(std::unique(ranksHigh.begin(), ranksHigh.end()), ranksHigh.end());

			// Sort and remove duplicates for Low rank
			std::sort(ranksLow.begin(), ranksLow.end());
			ranksLow.erase(std::unique(ranksLow.begin(), ranksLow.end()), ranksLow.end());


			// Look for 5 consecutive ranks (in high rank)
			int consecutive = 1;
			for (size_t idx = 1; idx < ranksHigh.size(); idx++)
			{
				if (ranksHigh[idx] == ranksHigh[idx - 1] + 1)
				{
					consecutive++;
					if (consecutive >= 5)	return true;
				}
				else if (ranksHigh[idx] != ranksHigh[idx - 1])
					consecutive = 1;
				
			}
			// Look for 5 consecutive ranks (in low rank: A, 2, 3, 4, 5)
			consecutive = 1;
			for (size_t idx = 1; idx < ranksLow.size(); idx++)
			{
				if (ranksLow[idx] == ranksLow[idx - 1] + 1)
				{
					consecutive++;
					if (consecutive >= 5)	return true;
				}
				else if (ranksLow[idx] != ranksLow[idx - 1])
					consecutive = 1;
			}

		}
		return false;
	}

	// Ranking 3
	bool Game::isFourOfAKind(const std::vector<Card>& theHand)
	{
		for (size_t idx = 0; idx < theHand.size() - 1; idx++)
		{
			const Card& card1 = theHand[idx];
			std::vector<std::string> suits;
			suits.push_back(card1.getSuit());

			for (size_t idx2 = idx + 1; idx2 < theHand.size(); idx2++)
			{
				const Card& card2 = theHand[idx2];
				// Different rank
				if (card1.getName() != card2.getName())	continue;

				// Suit already counted
				bool alreadySeen = false;
				for (const std::string& suit : suits)
				{
					if (suit == card2.getSuit())
					{
						alreadySeen = true;
						break;
					}
				}
				if (alreadySeen)	continue;
				
				suits.push_back(card2.getSuit());
			}
			
			if (suits.size() == 4)	return true;
		}

		return false;
	}

	// Ranking 4
	bool Game::isFullHouse(const std::vector<Card>& theHand)
	{
		int triples = 0;
		int couples = 0;
		int counts[N_NAMES] = { 0 };
		for (const Card& aCard : theHand)
		{
			const int idxCard = lowRank(aCard.getName(), NAMES, N_NAMES);
			counts[idxCard]++;
		}
		for (const int count : counts)
		{
			if (count >= 3)
				triples++;
			else if (count == 2)
				couples++;
		}

		return (triples >= 2 || (triples == 1 && couples >= 1));
	}

	// Ranking 5
	bool Game::isFlush(const std::vector<Card>& theHand)
	{
		int suits[N_SUITS] = {0};
		for (const Card& aCard : theHand)
		{
			const int idxSuit = rankSuit(aCard.getSuit(), SUITS, N_SUITS);
			if (idxSuit >= 0 && idxSuit < N_SUITS)
				suits[idxSuit]++;
		}
		for (const int suit : suits)
			if (suit >= 5)
				return true;
		
		return false;
	}

	// Ranking 6
	bool Game::isStraight(const std::vector<Card>& theHand)
	{
		// TODO
	}

	// Ranking 7
	bool Game::isThreeOfAKind(const std::vector<Card>& theHand)
	{
		// TODO
	}

	// Ranking 8
	bool Game::isTwoPair(const std::vector<Card>& theHand)
	{
		// TODO
	}

	// Ranking 9
	bool Game::isOnePair(const std::vector<Card>& theHand)
	{
		// TODO
	}

	// Ranking 10
	bool Game::isHighCard(const std::vector<Card>& theHand)
	{
		// TODO
	}

	void Game::resetRoundState()
	{
		// TODO : roundState is adjusted every time a player is eliminated
		// TODO : currentPlayer is the player next to CurrentPlayer
		// TODO : smallBlind is moved by 1 position
	}

} // myNamespacePoker