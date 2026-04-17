#include <algorithm>
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
	using myNamespaceCards::Hand;
	using myNamespacePoker::Player;


	constexpr int CARDS_BEST_DECK = 5;

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
		smallBlind = 0;
		bigBlind = 1;
		roundBet = STARTING_BET;
		play();
	}


	void Game::initiateTurn()
	{
		constexpr int CARDS_PLAYER = 2;
		constexpr int CARDS_BOARD = 3;

		shoe.shuffle();

		// reset the hand of each player in a new turn
		for (int idx = 0; idx < nPlayers; idx++)
			players[idx].resetTurn();

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
		// give a ranking to each player's hand. Skip players that folded 
		for (int idx = 0; idx < nPlayers; idx++)
		{
			int idxPlayer = (currentPlayer + idx) % nPlayers;
			Player& thePlayer = players[idxPlayer];
			if (thePlayer.hasFolded())	continue;

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
		std::vector<Player> theWinners;
		for (int idx = 0; idx < nPlayers; idx++)
		{
			int idxPlayer = (currentPlayer + idx) % nPlayers;
			Player& thePlayer = players[idx];
			if (thePlayer.hasFolded())	continue;
			if (thePlayer.getRanking() == maxRanking)
				theWinners.push_back(thePlayer);
			else
				handleLoss(thePlayer);
		}
		// Break the ties with higher card rank. If equal, split the pot equally.
		if (theWinners.size() == 1)
			theWinners[0].win(pot);
		else
			handleTies(pot, theWinners);
	}

	void Game::handleLoss(Player& thePlayer)
	{
		thePlayer.lose();
	}

	void Game::handleTies(const double& thePot, std::vector<Player>& thePlayers)
	{
		const int ranking = thePlayers[0].getRanking();
		switch (ranking)
		{
		case 10:
			royalFlushTie(thePot, thePlayers);
			break;
		case 9:
			straightFlushTie(thePot, thePlayers);
			break;
		case 8:
			fourOfAKindTie(thePot, thePlayers);
			break;
		case 7:
			fullHouseTie(thePot, thePlayers);
			break;
		case 6:
			flushTie(thePot, thePlayers);
			break;
		case 5:
			straightTie(thePot, thePlayers);
			break;
		case 4:
			threeOfAKindTie(thePot, thePlayers);
			break;
		case 3:
			twoPairTie(thePot, thePlayers);
			break;
		case 2:
			aPairTie(thePot, thePlayers);
			break;
		case 1:
			highCardTie(thePot, thePlayers);
			break;
		default:
			break;
		}
	}

	void Game::royalFlushTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		std::cout << "Equal win for each player!\n";
		
		const double equalWin = thePot / static_cast<int>(thePlayers.size());
		for (Player& player : thePlayers)
		{
			player.win(equalWin);
			std::cout << "Player " << player.getName() << " wins " << equalWin;
			std::cout << " with hands:\n";
			std::cout << player.getWinningHand() << '\n';
			std::cout << "Player total money: " << player.getMoney() << '\n';
		}
	}

	void Game::straightFlushTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::fourOfAKindTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::fullHouseTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::flushTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::straightTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::threeOfAKindTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::twoPairTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::aPairTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::highCardTie(const double& thePot, std::vector<Player>& thePlayers)
	{
		// TODO: handle the winners (split the pot) and losers with handleLoss
	}

	void Game::setRanking(Player& thePlayer, const std::vector<Card>& theHand, const Hand& handPlayer)
	{
		if (isRoyalFlush(theHand, thePlayer))
			thePlayer.setRanking(10);
		else if (isStraightFlush(theHand, thePlayer))
			thePlayer.setRanking(9);
		else if (isFourOfAKind(theHand, thePlayer))
			thePlayer.setRanking(8);
		else if (isFlush(theHand, thePlayer))
			thePlayer.setRanking(7);
		else if (isFullHouse(theHand, thePlayer))
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

			Hand theBestHand;
			std::vector<Card> found(5);

			// look at the cards of the same suit only
			for (const Card& card : theHand)
			{
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
			const int idx = lowRank(theHand[idx].getName(), NAMES, N_NAMES);
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
		for (size_t card = 0; card < theHand.size(); card++)
		{
			int idx = lowRank(theHand[card].getName(), NAMES, N_NAMES);
			if (idx == quadRank)
				bestHand.add(theHand[card]);
		}
		// Add kicker to the best hand of Player
		for (size_t card = 0; card < theHand.size(); card++)
		{
			int idx = lowRank(theHand[card].getName(), NAMES, N_NAMES);
			if (idx != quadRank && idx == kicker)
			{
				bestHand.add(theHand[card]);
				break;
			}

		}
		thePlayer.storeBestHand(bestHand);
		return isFour;
	}

	// Ranking 4
	bool Game::isFullHouse(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int triples = 0;
		int couples = 0;
		int counts[N_NAMES] = { 0 };
		for (const Card& aCard : theHand)
		{
			const int idxCard = lowRank(aCard.getName(), NAMES, N_NAMES);
			counts[idxCard]++;
		}
		int tripleRank[2] = { -1 };
		int idxTripleRank = 0;
		int pairRank[2] = { -1 };
		int idxPairRank = 0;
		for (int idx = 0; idx < N_NAMES; idx++)
		{
			if (counts[idx] >= 3)
			{
				triples++;
				if (idx == 0)	tripleRank[idxTripleRank++] = 13;	// Account for Ace
				else			tripleRank[idxTripleRank++] = idx;
			}
			else if (counts[idx] == 2)
			{
				couples++;
				if (idx == 0)	pairRank[idxPairRank++] = 13;	// Account for Ace
				else			pairRank[idxPairRank++] = idx;
			}

		}
		
		if (!(triples == 2 || (triples == 1 && couples >= 1)) )	return false;

		// Store best hand
		Hand bestHand;
		if (triples == 2)
		{
			// Use higher triple as the three and the lower as pair
			const int max = std::max(tripleRank[0], tripleRank[1]);
			const int min = std::min(tripleRank[0], tripleRank[1]);
			int tripleCounter = 0, pairCounter = 0;
			for (const Card& card : theHand)
			{
				int idxCard = highRank(card.getName(), NAMES, N_NAMES);
				if (idxCard == max && tripleCounter < 3)
				{
					bestHand.add(card);
					tripleCounter++;
				}
			}
			for (const Card& card : theHand)
			{
				int idxCard = highRank(card.getName(), NAMES, N_NAMES);
				if (idxCard == min & pairCounter < 2)
				{
					bestHand.add(card);
					pairCounter++;
				}
			}
		}
		else if (triples == 1 && couples >= 1)
		{
			// Find the highest pair not overlapping with the triple
			const int triple = tripleRank[0];
			const int pair = std::max(pairRank[0], pairRank[1]);
			int tripleCounter = 0, pairCounter = 0;
			for (const Card& card : theHand)
			{
				int idxCard = highRank(card.getName(), NAMES, N_NAMES);
				if (idxCard == triple && tripleCounter < 3)
				{
					bestHand.add(card);
					tripleCounter++;
				}
			}
			for (const Card& card : theHand)
			{
				int idxCard = highRank(card.getName(), NAMES, N_NAMES);
				if (idxCard == pair & pairCounter < 2)
				{
					bestHand.add(card);
					pairCounter++;
				}
			}
		}

		return true;
	}

	// Ranking 5
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

	// Ranking 6
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

	// Ranking 7
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
				if (idx == 0)
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
		
		thePlayer.storeBestHand(bestHand);
		// Store in order Tris, then Highest, then Second Highest

		return true;
	}

	// Ranking 8
	bool Game::isTwoPair(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int pairs = 0;
		int counts[N_NAMES] = {0};
		for (const Card& card : theHand)
		{
			const int idxCard = lowRank(card.getName(), NAMES, N_NAMES);
			counts[idxCard]++;
		}

		// Find the highest pair
		int highestPair = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] == 2)
			{
				if (idx == 0)		// Ace
				{
					highestPair = idx;
					break;
				}
				highestPair = idx;
			}
		if (highestPair == -1)	return false;
		// Find the next highest pair
		int secondPair = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] == 2 && idx != highestPair)
				secondPair = idx;
		if (secondPair == -1)	return false;
		
		// Find the highest card
		int highest = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] > 0 && idx!= highestPair && idx != secondPair)
			{
				if (idx == 0)		// Ace
				{
					highest = idx;
					break;
				}
				highest = idx;
			}

		// Build best hand
		Hand bestHand;
		int pairCount = 0;
		for (const Card& card : theHand)
		{
			const int rankCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == highestPair && pairCount < 2)
			{
				bestHand.add(card);
				pairCount++;
			}
		}
		pairCount = 0;
		for (const Card& card : theHand)
		{
			const int rankCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == secondPair && pairCount < 2)
			{
				bestHand.add(card);
				pairCount++;
			}
		}
		for (const Card& card : theHand)
		{
			const int rankCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == highest)
				bestHand.add(card);
		}
		thePlayer.storeBestHand(bestHand);
		// Store in order the Highest Pair, the second pair and highest card 

		return true;
	}

	// Ranking 9
	bool Game::isOnePair(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int counts[N_NAMES] = { 0 };
		for (const Card& card : theHand)
		{
			const int cardIdx = lowRank(card.getName(), NAMES, N_NAMES);
			counts[cardIdx]++;
		}

		// Find the pair
		int pair = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] == 2)
			{
				if (idx == 0)		// Ace
				{
					pair = idx;
					break;
				}
				pair = idx;
			}
		if (pair == -1)	return false;
		
		// Find the highest card
		int highest = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] > 0 && idx != pair )
			{
				if (idx == 0)		// Ace
				{
					highest = idx;
					break;
				}
				highest = idx;
			}
		// Find the second-highest card
		int secondHighest = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] > 0 && idx != pair && idx != highest)
				secondHighest = idx;

		// Find the third-highest card
		int thirdHighest = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
			if (counts[idx] > 0 && idx != pair && idx != highest && idx != secondHighest)
				thirdHighest = idx;
		
		// Build best hand: Pair first, then highest, second highest, and highest card
		Hand bestHand;
		int pairCount = 0;
		for (const Card& card : theHand)
		{
			const int rankCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == pair && pairCount < 2)
			{
				bestHand.add(card);
				pairCount++;
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
		for (const Card& card : theHand)
		{
			const int rankCard = lowRank(card.getName(), NAMES, N_NAMES);
			if (rankCard == thirdHighest)
				bestHand.add(card);
		}
		thePlayer.storeBestHand(bestHand);

		return true;
	}

	// Ranking 10
	bool Game::highCard(const Hand& handPlayer, Player& thePlayer)
	{
		// Find higher and lower rank cards in the hand of player
		int higherCardPlayer = -1;
		for (int idx = 0; idx < handPlayer.getNumberCards(); idx++)
		{
			const int lowRankCard = lowRank(handPlayer[idx].getName(), NAMES, N_NAMES);
			higherCardPlayer = std::max(higherCardPlayer, lowRankCard);
			if (lowRankCard == 0) // Ace
				break;
		}
		int lowerCardPlayer = 99;	
		for (int idx = 0; idx < handPlayer.getNumberCards();idx++)
		{
			const int highRankCard = higherCardPlayer(handPlayer[idx].getName(), NAMES, N_NAMES);
			lowerCardPlayer = std::min(lowerCardPlayer, highRankCard);
		}
		// Find the three highest cards in board
		int highestBoard = -1;
		for (const Card& card : board)
		{
			int cardRankBoard = lowerCardPlayer(card.getName(), NAMES, N_NAMES);
			if (cardRankBoard == 0)		// Ace
			{
				highestBoard = cardRankBoard;
				break;
			}
			if (cardRankBoard > highestBoard)
				highestBoard = cardRankBoard;
		}
		int secondHighestBoard = -1;
		for (const Card& card : board)
		{
			int cardRankBoard = lowerCardPlayer(card.getName(), NAMES, N_NAMES);
			if (cardRankBoard > secondHighestBoard && cardRankBoard != highestBoard)
				secondHighestBoard = cardRankBoard;
		}
		int thirdHighestBoard = -1;
		for (const Card& card : board)
		{
			int cardRankBoard = lowerCardPlayer(card.getName(), NAMES, N_NAMES);
			if (cardRankBoard > thirdHighestBoard && 
				cardRankBoard != highestBoard && 
				cardRankBoard != secondHighestBoard)
				
				thirdHighestBoard = cardRankBoard;
		}
		// Add the best Hand in this order: 
		// Player 1st highest, Player 2nd highest, Board 3 highest cards in desceding order
		Hand bestHand;
		for (int idx = 0; idx < handPlayer.getNumberCards(); idx++)
			if (higherCardPlayer == lowerCardPlayer(handPlayer[idx].getName(), NAMES, N_NAMES))
				bestHand.add(handPlayer[idx]);
		for (int idx = 0; idx < handPlayer.getNumberCards(); idx++)
			if (lowerCardPlayer == lowerCardPlayer(handPlayer[idx].getName(), NAMES, N_NAMES))
				bestHand.add(handPlayer[idx]);
		for (const Card& card : board)
			if (highestBoard == lowerCardPlayer(card.getName(), NAMES, N_NAMES))
				bestHand.add(card);
		for (const Card& card : board)
			if (secondHighestBoard == lowerCardPlayer(card.getName(), NAMES, N_NAMES))
				bestHand.add(card);
		for (const Card& card : board)
			if (thirdHighestBoard == lowerCardPlayer(card.getName(), NAMES, N_NAMES))
				bestHand.add(card);

		thePlayer.storeBestHand(bestHand);
		return true;
	}

	void Game::resetRoundState()
	{
		// TODO : thePot = 0
		// TODO : the hand of each player and board is emptied: cards return to the deck
		// TODO : roundState is adjusted every time a player is eliminated
		// TODO : if the player is eliminated (money == 0), then vector players is 
		//			resized to account for the less player. nPlayers gets reduced of course
		// TODO : currentPlayer is the player next to CurrentPlayer
		// TODO : smallBlind is moved by 1 position
		// TODO : the bet is increased by double amount if one player is eliminated
	}

} // myNamespacePoker