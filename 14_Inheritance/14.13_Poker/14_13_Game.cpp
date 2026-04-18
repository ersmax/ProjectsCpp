#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include "14_13_Game.h"
#include "../14.11_Cards/14_11_Validation.h"

namespace
{
	using myNamespaceCards::NAMES;
	using myNamespaceCards::N_NAMES;
	using myNamespaceCards::SUITS;
	using myNamespaceCards::N_SUITS;
	using myNamespaceCards::Card;
	using myNamespaceCards::Hand;
	using myNamespacePoker::Player;


	constexpr int CARDS_BEST_DECK = 5;
	constexpr double MONEY_EPSILON = 1e-9;

	const char* rankingToString(const int ranking)
	{
		switch (ranking)
		{
		case 10: return "Royal Flush";
		case 9: return "Straight Flush";
		case 8: return "Four of a Kind";
		case 7: return "Full House";
		case 6: return "Flush";
		case 5: return "Straight";
		case 4: return "Three of a Kind";
		case 3: return "Two Pair";
		case 2: return "One Pair";
		case 1: return "High Card";
		default: return "Unknown";
		}
	}

	void showWinningHand(const Player& thePlayer)
	{
		std::cout << "Winning hand type: " << rankingToString(thePlayer.getRanking()) << '\n';
		std::cout << "Winning hand:\n";

		const Hand& winningHand = thePlayer.getWinningHand();
		for (int idx = 0; idx < winningHand.getNumberCards(); idx++)
			std::cout << "  [" << idx + 1 << "] " << winningHand[idx].getSuit() << " " << winningHand[idx].getName() << '\n';
	}

	void printSection(const std::string& title)
	{
		std::cout << "\n========== " << title << " ==========\n";
	}

	int rankForComparison(const Card& card)
	{
		int rank = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (NAMES[idx] == card.getName())
			{
				rank = idx;
				break;
			}
		return (rank == 0) ? 13 : rank;
	}

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


	bool findStraightInSortedCards(const std::vector<Card>& sortedCards, Player& thePlayer)
	{
		if (sortedCards.size() < 5)
			return false;

		// Check for Straight flush (check only first three with idx, since we need at least 5)
		// Hence, idx <= sortedCards.size() - 5, that is (7 -5) = 2, idx = 0, idx = 1, idx = 2
		for (size_t idx = 0; idx <= sortedCards.size() - 5; idx++)
		{
			std::vector<Card> possibleStraight;
			possibleStraight.push_back(sortedCards[idx]);
			int lastRank = lowRank(sortedCards[idx].getName(), NAMES, N_NAMES);

			for (size_t idx2 = idx + 1; idx2 < sortedCards.size(); idx2++)
			{
				int currentRank = lowRank(sortedCards[idx2].getName(), NAMES, N_NAMES);

				// Check if cards are consecutive
				if (currentRank == lastRank + 1)
				{
					possibleStraight.push_back(sortedCards[idx2]);
					lastRank = currentRank;

					// Copy the best Hand and return true ("hand is a Straight flush")
					if (possibleStraight.size() == 5)
					{
						Hand theBestHand;
						for (size_t idx3 = 0; idx3 < possibleStraight.size(); idx3++)
							theBestHand.add(possibleStraight[idx3]);

						thePlayer.storeBestHand(theBestHand);
						return true;
					}
				}
				else
					break;	// cards are same suit but not consecutive ranks
			}
		}
		return false;
	}

}  // unnamed namespace


namespace myNamespacePoker
{
	
	Game::Game() : Game(std::vector<Player>{Player("Player 1", 100), Player("Player 2", 100) })
	{ /* Body intentionally left empty */ }

	Game::Game(const std::vector<Player>& thePlayers)
	{
		if (thePlayers.size() < 2)
			throw std::invalid_argument("Number of players must be greater than 2\n");
		
		nPlayers = static_cast<int>(thePlayers.size());
		players = thePlayers;
		pot = 0;
		smallBlind = 0;
		bigBlind = 1;
		roundBet = STARTING_BET;
		currentBet = 0;
		currentPlayer = 0;
	}


	void Game::initiateTurn()
	{
		constexpr int CARDS_PLAYER = 2;
		constexpr int CARDS_BOARD = 3;
		const int cardsNeeded = (nPlayers * CARDS_PLAYER) + CARDS_BEST_DECK;

		if (shoe.getNumberCards() < cardsNeeded)
			shoe = Deck();

		printSection("New Hand");

		shoe.shuffle();

		// reset the hand of each player in a new turn
		for (int idx = 0; idx < nPlayers; idx++)
			players[idx].resetTurn();

		// pre-flop
		const double smallBlindBet = roundBet;
		const double bigBlindBet = roundBet * 2;
		const double smallBlindPreviousBet = players[smallBlind].getBet();
		players[smallBlind].placeBet(smallBlindBet);
		const double smallBlindPaid = players[smallBlind].getBet() - smallBlindPreviousBet;
		pot += smallBlindPaid;

		const double bigBlindPreviousBet = players[bigBlind].getBet();
		players[bigBlind].placeBet(bigBlindBet);
		const double bigBlindPaid = players[bigBlind].getBet() - bigBlindPreviousBet;
		pot += bigBlindPaid;

		std::cout << "Small blind: Player " << smallBlind + 1 << " (" << players[smallBlind].getName() << ") $" << smallBlindPaid;
		if (smallBlindPaid + MONEY_EPSILON < smallBlindBet)
			std::cout << " (all in)";
		std::cout << "\n";

		std::cout << "Big blind:   Player " << bigBlind + 1   << " (" << players[bigBlind].getName()   << ") $" << bigBlindPaid;
		if (bigBlindPaid + MONEY_EPSILON < bigBlindBet)
			std::cout << " (all in)";
		std::cout << "\n";

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
		} while (nPlayers > 1);
	}


	void Game::playHand()
	{
		printSection("Flop Betting");
		takeBets();
		if (!atLeastTwoBetting())
		// If there are no players left that call or raise (3 cards on deck), ends Poker round immediately
		{
			resolveRound();
			resetRoundState();
			return;
		}

		board.push_back(shoe.remove());
		printSection("Turn Betting");
		takeBets();
		if (!atLeastTwoBetting())
		// If there are no players left that call or raise (4 cards on deck), ends Poker round immediately
		{
			resolveRound();
			resetRoundState();
			return;
		}

		board.push_back(shoe.remove());
		printSection("River Betting");
		takeBets();
		printSection("Showdown");
		resolveRound();
		resetRoundState();
	}

	void Game::takeBets()
	{
		using myNamespaceValidation::readName;

		if (!atLeastTwoBetting())
			return;

		bool someoneRaised;
		do
		{
			someoneRaised = false;
			bool endRoundEarly = false;
			showBoard(board);
			for (int idx = 0; idx < nPlayers; idx++)
			{
				const int idxPlayer = (currentPlayer + idx) % nPlayers;
				Player& thePlayer = players[idxPlayer];

				std::cout << "\n-- Player " << idxPlayer + 1 << " (" << players[idxPlayer].getName() << ") turn --\n";
				std::cout << "Balance: $" << thePlayer.getMoney() << '\n';

				if (thePlayer.hasFolded())
				{
					std::cout << "Status: Folded\n";
					continue;
				}

				std::cout << "Current bet: $" << thePlayer.getBet() << '\n'
						  << "Highest bet: $" << currentBet << '\n';
				showHand(thePlayer);

				char choice{};
				do
				{
					std::cout << "Call (c), raise (r) or fold (f)?\n";
					readName(std::cin, choice);
				} while (choice != 'c' && choice != 'r' && choice != 'f');

				
				double callingBet = currentBet - thePlayer.getBet();
				callingBet = std::max<double>(callingBet, 0);
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

				if (!atLeastTwoBetting())
				{
					std::cout << "Only one active player remains in betting.\n";
					endRoundEarly = true;
					break;
				}
			}

			if (endRoundEarly)
				break;
		} while (someoneRaised && atLeastTwoBetting());
	}

	void Game::callHand(Player& thePlayer, const double callingBet)
	{
		const double safeCallingBet = std::max(0.0, callingBet);
		const double previousBet = thePlayer.getBet();
		thePlayer.placeBet(safeCallingBet);
		pot += (thePlayer.getBet() - previousBet);
	}

	void Game::raiseHand(Player& thePlayer, const double callingBet)
	{
		using myNamespaceValidation::readName;
		using myNamespaceValidation::readNumber;

		const double safeCallingBet = std::max(0.0, callingBet);

		if (thePlayer.getMoney() <= safeCallingBet + MONEY_EPSILON)
		{
			char choice;
			std::cout << "Player does not have enough money to raise. Go all in (y/n)?\n";
			readName(std::cin, choice);
			if (std::tolower(choice) == 'y')
			{
				const double allIn = thePlayer.getMoney();
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
			std::cout << "Enter a bet (at least " << safeCallingBet << "):\n";
			readNumber(std::cin, theDifference);
		} while (theDifference < safeCallingBet);

		const double previousBet = thePlayer.getBet();
		thePlayer.placeBet(theDifference);
		pot += (thePlayer.getBet() - previousBet);
		currentBet = thePlayer.getBet();
	}

	void Game::foldHand(Player& thePlayer)
	{
		std::cout << thePlayer.getName() << " folds.\n";
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
		const Hand& hand = thePlayer.getHand();
		std::cout << "Hand:\n";
		for (int idx = 0; idx < hand.getNumberCards(); idx++)
			std::cout << "  [" << idx + 1 << "] " << hand[idx].getSuit() << " " << hand[idx].getName() << '\n';
	}

	void Game::showBoard(const std::vector<Card>& theBoard)
	{
		std::cout << "\nBoard (" << theBoard.size() << " cards):\n";
		for (size_t idx = 0; idx < theBoard.size(); idx++)
			std::cout << "  [" << idx + 1 << "] " << theBoard[idx].getSuit() << " " << theBoard[idx].getName() << '\n';
	}

	void Game::resolveRound()
	{
		// give a ranking to each player's hand. Skip players that folded 
		for (int idx = 0; idx < nPlayers; idx++)
		{
			const int idxPlayer = (currentPlayer + idx) % nPlayers;
			Player& thePlayer = players[idxPlayer];
			if (thePlayer.hasFolded())	continue;
			thePlayer.resetBestHand();
			thePlayer.resetRanking();

			const Hand& handPlayer = thePlayer.getHand();
			std::vector<Card> theHand;
			for (size_t idxCard = 0; idxCard < board.size(); idxCard++)
				theHand.push_back(board[idxCard]);
			for (int idxCard = 0; idxCard < handPlayer.getNumberCards(); idxCard++)
				theHand.push_back(handPlayer[idxCard]);
			setRanking(thePlayer, theHand, handPlayer);
		}
		// Find the highest ranking. Skip players that folded 
		int maxRanking = 0;
		for (int idx = 0; idx < nPlayers; idx++)
		{
			Player& thePlayer = players[idx];
			
			if (thePlayer.hasFolded())	continue;
			maxRanking = std::max(maxRanking, thePlayer.getRanking());
		}
		//   Determine the winner by comparing the ranking. Skip players that folded 
		std::vector<int> winnerIndexes;
		for (int idx = 0; idx < nPlayers; idx++)
		{
			int idxPlayer = (currentPlayer + idx) % nPlayers;
			Player& thePlayer = players[idxPlayer];
			if (thePlayer.hasFolded())	continue;
			if (thePlayer.getRanking() == maxRanking)
				winnerIndexes.push_back(idxPlayer);
			else
				handleLoss(thePlayer);
		}
		// Break the ties with higher card rank. If equal, split the pot equally.
		if (winnerIndexes.size() == 1)
		{
			Player& winner = players[winnerIndexes[0]];
			winner.win(pot);
			showWinningHand(winner);
		}
		else
			payTieWinners(pot, winnerIndexes);
	}

	void Game::handleLoss(Player& thePlayer)
	{
		thePlayer.lose();
	}

	void Game::payTieWinners(const double& thePot, const std::vector<int>& contenderIndexes)
	{
		if (contenderIndexes.empty())
			return;

		std::vector<int> bestIndexes;
		for (const int idx : contenderIndexes)
		{
			if (bestIndexes.empty())
			{
				bestIndexes.push_back(idx);
				continue;
			}

			// If new Player has higher Poker hand (the comparison is > 0), 
			// update the bestIndexes vector to contain only the new Player index.
			// If equal Poker hand, add the new Player index to the bestIndexes vector.
			const int comparison = compareBestHands(players[idx], players[bestIndexes[0]]);
			if (comparison > 0)
			{
				bestIndexes.clear();
				bestIndexes.push_back(idx);
			}
			else if (comparison == 0)
				bestIndexes.push_back(idx);
		}

		// If bestIndexes has more than one index, it means that 2 or more players have equal hands, so we split the pot equally 
		const double equalWin = thePot / static_cast<int>(bestIndexes.size());
		if (bestIndexes.size() > 1)
			std::cout << "Tie between " << bestIndexes.size() << " players. Pot is split equally.\n";

		for (const int idx : bestIndexes)
		{
			players[idx].win(equalWin);
			showWinningHand(players[idx]);
		}
	}

	int Game::compareBestHands(const Player& leftPlayer, const Player& rightPlayer)
	{
		const Hand& leftHand = leftPlayer.getWinningHand();
		const Hand& rightHand = rightPlayer.getWinningHand();
		const int cardsToCompare = std::min(leftHand.getNumberCards(), rightHand.getNumberCards());

		for (int idx = 0; idx < cardsToCompare; idx++)
		{
			const int leftRank = rankForComparison(leftHand[idx]);
			const int rightRank = rankForComparison(rightHand[idx]);
			if (leftRank > rightRank)
				return 1;
			if (leftRank < rightRank)
				return -1;
		}
		return 0;
	}

	void Game::setRanking(Player& thePlayer, const std::vector<Card>& theHand, const Hand& handPlayer)
	{
		if (isRoyalFlush(theHand, thePlayer))
			thePlayer.setRanking(10);
		else if (isStraightFlush(theHand, thePlayer))
			thePlayer.setRanking(9);
		else if (isFourOfAKind(theHand, thePlayer))
			thePlayer.setRanking(8);
		else if (isFullHouse(theHand, thePlayer))
			thePlayer.setRanking(7);
		else if (isFlush(theHand, thePlayer))
			thePlayer.setRanking(6);
		else if (isStraight(theHand, thePlayer))
			thePlayer.setRanking(5);
		else if (isThreeOfAKind(theHand, thePlayer))
			thePlayer.setRanking(4);
		else if (isTwoPair(theHand, thePlayer))
			thePlayer.setRanking(3);
		else if (isOnePair(theHand, thePlayer))
			thePlayer.setRanking(2);
		else if (highCard(handPlayer, thePlayer))
			thePlayer.setRanking(1);
	}

	// Ranking 10
	bool Game::isRoyalFlush(const std::vector<Card>& theHand, Player& thePlayer)
	{
		using namespace myNamespaceCards;

		for (const std::string& suitCard : SUITS)
		{
			bool has10 = false;
			bool hasJ = false;
			bool hasQ = false;
			bool hasK = false;
			bool hasA = false;

			std::vector<Card> found(5);
			for (const Card& card : theHand)
			{
				// look at the cards of the same suit only
				if (card.getSuit() != suitCard)	continue;
				
				const std::string& name = card.getName();
				if (name == "10")
				{
					found[0] = card;
					has10 = true;
				}
				else if (name == "Jack")
				{
					found[1] = card;
					hasJ = true;
				}
				else if (name == "Queen")
				{
					found[2] = card;
					hasQ = true;
				}
				else if (name == "King")
				{
					found[3] = card;
					hasK = true;
				}
				else if (name == "Ace")
				{
					found[4] = card;
					hasA = true;
				}
			}
			if (has10 && hasJ && hasQ && hasK && hasA)
			{
				Hand theBestHand;
				for (const Card& card : found)	theBestHand.add(card);
				thePlayer.storeBestHand(theBestHand);
				return true;
			}
		}

		return false;
	}

	// Ranking 9
	bool Game::isStraightFlush(const std::vector<Card>& theHand, Player& thePlayer)
	{
		using namespace myNamespaceCards;
		bool isStraight = false;

		for (const std::string& suit : SUITS)
		{
			std::vector<Card> suitedCards;
			for (const Card& card : theHand)
				if (card.getSuit() == suit)
					suitedCards.push_back(card);

			if (suitedCards.size() < 5)	continue;

			
			// Case 1: Ace is the highest Rank in suitedCardsHigh (10, J, Q, K, Ace)
			// Sort the cards in ascending order, with Ace the highest rank card
			std::vector<Card> suitedCardsHigh = suitedCards;
			for (size_t idx = 0; idx < suitedCardsHigh.size(); idx++)
				for (size_t idx2 = idx + 1; idx2 < suitedCardsHigh.size(); idx2++)
				{
					int rank1 = highRank(suitedCardsHigh[idx].getName(), NAMES, N_NAMES);
					int rank2 = highRank(suitedCardsHigh[idx2].getName(), NAMES, N_NAMES);
					if (rank1 > rank2)
					{
						Card temp = suitedCardsHigh[idx];
						suitedCardsHigh[idx] = suitedCardsHigh[idx2];
						suitedCardsHigh[idx2] = temp;
					}
				}

			// Check for Straight flush (check only first three with idx, since we need at least 5)
			isStraight = findStraightInSortedCards(suitedCardsHigh, thePlayer);
			if (isStraight)	return true;
			
			// Case 2: Ace is the lowest Rank in suitedCardsLow	(Ace, 2, 3, 4, 5)
			for (size_t idx = 0; idx < suitedCards.size(); idx++)
				for (size_t idx2 = idx + 1; idx2 < suitedCards.size(); idx2++)
				{
					int rank1 = lowRank(suitedCards[idx].getName(), NAMES, N_NAMES);
					int rank2 = lowRank(suitedCards[idx2].getName(), NAMES, N_NAMES);
					if (rank1 > rank2)
					{
						Card temp = suitedCards[idx];
						suitedCards[idx] = suitedCards[idx2];
						suitedCards[idx2] = temp;
					}
				}
			isStraight = findStraightInSortedCards(suitedCards, thePlayer);
			if (isStraight)	return true;
		}
		return isStraight;
	}

	// Ranking 8
	bool Game::isFourOfAKind(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int counts[N_NAMES] = { 0 };
		bool isFour = false;

		// Count occurence of each rank
		for (size_t card = 0; card < theHand.size(); card++)
		{
			const int idx = lowRank(theHand[card].getName(), NAMES, N_NAMES);
			counts[idx]++;
		}

		// Find the rank that occurs 4 times
		int quadRank = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] == 4)
			{
				quadRank = idx;
				isFour = true;
				break;
			}
		if (!isFour)	return false;

		//   Find the kicker (highest card not part of the quad)
		// If Ace is kicker, it is the most valuable
		int kicker = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
		{
			if (idx != quadRank && counts[idx] > 0)
			{
				kicker = idx; 
				if (idx == 0)	
					break;
			}
		}

		// Add quad to the best hand of Player
		Hand bestHand;
		for (const Card& card : theHand)
		{
			const int idx = lowRank(card.getName(), NAMES, N_NAMES);
			if (idx == quadRank)
				bestHand.add(card);
		}
		// Add kicker to the best hand of Player
		for (const Card& card : theHand)
		{
			const int idx = lowRank(card.getName(), NAMES, N_NAMES);
			if (idx != quadRank && idx == kicker)
			{
				bestHand.add(card);
				break;
			}
		}
		thePlayer.storeBestHand(bestHand);
		return isFour;
	}

	// Ranking 7
	bool Game::isFullHouse(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int counts[N_NAMES] = { 0 };
		for (const Card& aCard : theHand)
		{
			const int idxCard = lowRank(aCard.getName(), NAMES, N_NAMES);
			if (idxCard >= 0)
				counts[idxCard]++;
		}

		int bestTriple = -1;
		int secondTriple = -1;
		int bestPair = -1;

		for (int idx = 0; idx < N_NAMES; idx++)
		{
			const int rankValue = (idx == 0) ? 13 : idx;

			if (counts[idx] >= 3)
			{
				if (rankValue > bestTriple)
				{
					secondTriple = bestTriple;
					bestTriple = rankValue;
				}
				else if (rankValue > secondTriple)
					secondTriple = rankValue;
			}

			if (counts[idx] >= 2 && rankValue > bestPair)
				bestPair = rankValue;
		}

		if (bestTriple == -1)
			return false;

		const int pairForHouse = (secondTriple != -1) ? secondTriple : bestPair;
		if (pairForHouse == -1 || pairForHouse == bestTriple)
			return false;

		// Store best hand
		Hand bestHand;
		int tripleCounter = 0;
		for (const Card& card : theHand)
		{
			int idxCard = highRank(card.getName(), NAMES, N_NAMES);
			if (idxCard == bestTriple && tripleCounter < 3)
			{
				bestHand.add(card);
				tripleCounter++;
			}
		}

		int pairCounter = 0;
		for (const Card& card : theHand)
		{
			int idxCard = highRank(card.getName(), NAMES, N_NAMES);
			if (idxCard == pairForHouse && pairCounter < 2)
			{
				bestHand.add(card);
				pairCounter++;
			}
		}

		thePlayer.storeBestHand(bestHand);

		return true;
	}

	// Ranking 6
	bool Game::isFlush(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int suits[N_SUITS] = {0};
		for (const Card& aCard : theHand)
		{
			const int idxSuit = rankSuit(aCard.getSuit(), SUITS, N_SUITS);
			suits[idxSuit]++;
		}
		int flushSuit = -1;
		for (int idx = 0; idx < N_SUITS; idx++)
			if (suits[idx] >= 5)
				flushSuit = idx;
		
		if (flushSuit == -1)	return false;
		
		// Collect those cards of the Flush suit and their ranks
		std::vector<std::pair<int, Card>> flushCards;
		for (const Card& aCard : theHand)
		{
			const int idxSuit = rankSuit(aCard.getSuit(), SUITS, N_SUITS);
			if (idxSuit == flushSuit)
			{
				int idxCard = lowRank(aCard.getName(), NAMES, N_NAMES);
				int rankCard = (idxCard == 0) ? 13 : idxCard;	// Ace value is 13
				flushCards.emplace_back(rankCard, aCard);
			}
		}

		// Sort by rank descending (Ace high)
		std::sort(flushCards.rbegin(), flushCards.rend());

		// Store the best 5 cards in the player's best hand
		Hand bestHand;
		for (int idx = 0; idx < CARDS_BEST_DECK; idx++)
			bestHand.add(flushCards[idx].second);
		
		thePlayer.storeBestHand(bestHand);
		return true;
	}

	// Ranking 5
	bool Game::isStraight(const std::vector<Card>& theHand, Player& thePlayer)
	{
		bool isStraight = false;

		// Case 1: Ace is the highest Rank (10, J, Q, K, Ace)
		std::vector<Card> cardsHigh = theHand;
		// Sort by high rank (Ace as 13)
		for (size_t idx = 0; idx < cardsHigh.size(); idx++)
			for (size_t idx2 = idx + 1; idx2 < cardsHigh.size(); idx2++)
			{
				int rank1 = highRank(cardsHigh[idx].getName(), NAMES, N_NAMES);
				int rank2 = highRank(cardsHigh[idx2].getName(), NAMES, N_NAMES);
				if (rank1 > rank2)
				{
					Card temp = cardsHigh[idx];
					cardsHigh[idx] = cardsHigh[idx2];
					cardsHigh[idx2] = temp;
				}
			}
		// Remove duplicates by rank
		std::vector<Card> uniqueHigh;
		for (const Card& card : cardsHigh)
		{
			bool found = false;
			for (const Card& unique : uniqueHigh)
				if (card.getName() == unique.getName())
					found = true;
			if (!found)
				uniqueHigh.push_back(card);
		}
		// store the bestHand in Player and returns if it is a straight
		// Ace is the highest, 2 is the lowest
		isStraight = findStraightInSortedCards(uniqueHigh, thePlayer);
		if (isStraight)	return true;

		// Case 2: Ace is the lowest Rank (Ace, 2, 3, 4, 5)
		std::vector<Card> cardsLow = theHand;
		// Sort by low rank (Ace as 0)
		for (size_t idx = 0; idx < cardsLow.size(); idx++)
			for (size_t idx2 = idx + 1; idx2 < cardsLow.size(); idx2++)
			{
				int rank1 = lowRank(cardsLow[idx].getName(), NAMES, N_NAMES);
				int rank2 = lowRank(cardsLow[idx2].getName(), NAMES, N_NAMES);
				if (rank1 > rank2)
				{
					Card temp = cardsLow[idx];
					cardsLow[idx] = cardsLow[idx2];
					cardsLow[idx2] = temp;
				}
			}
		// Remove duplicate by rank
		std::vector<Card> uniqueLow;
		for (const Card& card : cardsLow)
		{
			bool found = false;
			for (const Card& unique : uniqueLow)
				if (card.getName() == unique.getName())
					found = true;
			if (!found)
				uniqueLow.push_back(card);
		}
		// store the bestHand in Player and returns if it is a straight
		// Ace is lowest, King is Highest
		isStraight = findStraightInSortedCards(uniqueLow, thePlayer);
		if (isStraight)	return true;

		return false;
	}

	// Ranking 4
	bool Game::isThreeOfAKind(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int counts[N_NAMES] = { 0 };
		for (const Card& card : theHand) 
		{
			const int cardIdx = lowRank(card.getName(), NAMES, N_NAMES);
			counts[cardIdx]++;
		}

		// Find the tris
		int tris = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] == 3) 
			{
				if (idx == 0)		// Ace
				{
					tris = idx;
					break;
				}
				tris = idx;
			}
		if (tris == -1)	return false;

		// Find the highest and second-highest cards (not in tris)
		int highest = -1;
		for (int idx = 0; idx < N_NAMES; idx++) 
			if (counts[idx] > 0 && idx != tris)
			{
				if (idx == 0)		// Ace
				{
					highest = idx;
					break;
				}
				highest = idx;
			}
		int secondHighest = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] > 0 && idx != tris && idx != highest)
				secondHighest = idx;

		// Build best hand
		Hand bestHand;
		int trisCount = 0;
		for (const Card& card : theHand)
		{
			const int rankCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == tris && trisCount < 3)
			{
				bestHand.add(card);
				trisCount++;
			}
		}
		for (const Card& card : theHand)
		{
			const int rankCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == highest)
				bestHand.add(card);
		}
		for (const Card& card : theHand)
		{
			const int rankCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == secondHighest)
				bestHand.add(card);
		}
		
		// Store in order Tris, then Highest rank card, then Second-Highest rank card
		thePlayer.storeBestHand(bestHand);

		return true;
	}

	// Ranking 3
	bool Game::isTwoPair(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int counts[N_NAMES] = { 0 };
		for (const Card& card : theHand)
		{
			const int idxCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (idxCard >= 0)
				counts[idxCard]++;
		}

		int highestPair = -1;
		int secondPair = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] == 2)
			{
				const int rankValue = (idx == 0) ? 13 : idx;
				if (rankValue > highestPair)
				{
					secondPair = highestPair;
					highestPair = rankValue;
				}
				else if (rankValue > secondPair)
					secondPair = rankValue;
			}

		if (secondPair == -1)	return false;
		
		int highest = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] > 0)
			{
				const int rankValue = (idx == 0) ? 13 : idx;
				if (rankValue != highestPair && rankValue != secondPair && rankValue > highest)
					highest = rankValue;
			}
		if (highest == -1)	return false;

		// Build best hand
		Hand bestHand;
		int pairCount = 0;
		for (const Card& card : theHand)
		{
			const int rankCard = highRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == highestPair && pairCount < 2)
			{
				bestHand.add(card);
				pairCount++;
			}
		}
		pairCount = 0;
		for (const Card& card : theHand)
		{
			const int rankCard = highRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == secondPair && pairCount < 2)
			{
				bestHand.add(card);
				pairCount++;
			}
		}
		for (const Card& card : theHand)
		{
			const int rankCard = highRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == highest)
			{
				bestHand.add(card);
				break;
			}
		}
		thePlayer.storeBestHand(bestHand);
		// Store in order the Highest Pair, the second pair and highest card 

		return true;
	}

	// Ranking 2
	bool Game::isOnePair(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int counts[N_NAMES] = { 0 };
		for (const Card& card : theHand)
		{
			const int cardIdx = lowRank(card.getName(), NAMES, N_NAMES);
			if (cardIdx >= 0)
				counts[cardIdx]++;
		}

		int pair = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] == 2)
			{
				const int rankValue = (idx == 0) ? 13 : idx;
				pair = std::max(rankValue, pair);
			}
		if (pair == -1)	return false;
		
		int highest = -1;
		int secondHighest = -1;
		int thirdHighest = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] > 0)
			{
				const int rankValue = (idx == 0) ? 13 : idx;
				if (rankValue == pair)
					continue;

				if (rankValue > highest)
				{
					thirdHighest = secondHighest;
					secondHighest = highest;
					highest = rankValue;
				}
				else if (rankValue > secondHighest)
				{
					thirdHighest = secondHighest;
					secondHighest = rankValue;
				}
				else if (rankValue > thirdHighest)
					thirdHighest = rankValue;
			}

		if (highest == -1 || secondHighest == -1 || thirdHighest == -1)
			return false;
		
		// Build best hand: Pair first, then the highest, second-highest, and third-highest rank card
		Hand bestHand;
		int pairCount = 0;
		for (const Card& card : theHand)
		{
			const int rankCard = highRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == pair && pairCount < 2)
			{
				bestHand.add(card);
				pairCount++;
			}
		}
		for (const Card& card : theHand)
		{
			const int rankCard = highRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == highest)
			{
				bestHand.add(card);
				break;
			}
		}
		for (const Card& card : theHand)
		{
			const int rankCard = highRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == secondHighest)
			{
				bestHand.add(card);
				break;
			}
		}
		for (const Card& card : theHand)
		{
			const int rankCard = highRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == thirdHighest)
			{
				bestHand.add(card);
				break;
			}
		}
		thePlayer.storeBestHand(bestHand);

		return true;
	}

	// Ranking 1
	bool Game::highCard(const Hand& handPlayer, Player& thePlayer)
	{
		std::vector<Card> allCards;
		allCards.reserve(static_cast<size_t>(handPlayer.getNumberCards() + board.size()));
		for (int idx = 0; idx < handPlayer.getNumberCards(); idx++)
			allCards.push_back(handPlayer[idx]);
		for (const Card& card : board)
			allCards.push_back(card);

		std::sort(allCards.begin(), allCards.end(), [](const Card& leftCard, const Card& rightCard)
		{
			const int leftRank = rankForComparison(leftCard);
			const int rightRank = rankForComparison(rightCard);
			if (leftRank != rightRank)
				return leftRank > rightRank;
			return rankSuit(leftCard.getSuit(), SUITS, N_SUITS) > rankSuit(rightCard.getSuit(), SUITS, N_SUITS);
		});

		Hand bestHand;
		for (int idx = 0; idx < CARDS_BEST_DECK && idx < static_cast<int>(allCards.size()); idx++)
			bestHand.add(allCards[idx]);

		thePlayer.storeBestHand(bestHand);
		return true;
	}

	void Game::resetRoundState()
	{
		pot = 0;
		board.clear();

		const int oldPlayers = nPlayers;
		std::vector<Player> remainingPlayers;
		remainingPlayers.reserve(players.size());
		for (Player& player : players)
		{
			if (!player.isEliminated())
				remainingPlayers.push_back(player);
			else
				std::cout << "Player " << player.getName() << " is eliminated.\n";
		}

		players = remainingPlayers;
		nPlayers = static_cast<int>(players.size());

		if (nPlayers <= 1)
			return;

		if (nPlayers < oldPlayers)
			roundBet *= 2;

		smallBlind = (smallBlind + 1) % nPlayers;
		bigBlind = (smallBlind + 1) % nPlayers;
		currentPlayer = (bigBlind + 1) % nPlayers;
		currentBet = 0;
	}

} // myNamespacePoker