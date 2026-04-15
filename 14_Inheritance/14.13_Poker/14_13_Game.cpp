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

	void Game::handleTies(double& thePot, std::vector<Player>& thePlayers)
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
		const double equalWin = thePot / static_cast<int>(thePlayers.size());
		for (Player& player : thePlayers)
			player.win(equalWin);
		std::cout << "Equal win for each player!\n";
	}



	void Game::setRanking(Player& thePlayer, const std::vector<Card>& theHand, const Hand& handPlayer)
	{
		if (isRoyalFlush(theHand))
			thePlayer.setRanking(10);
		else if (isStraightFlush(theHand, thePlayer))
			thePlayer.setRanking(9);
		else if (isFourOfAKind(theHand, thePlayer))
			thePlayer.setRanking(8);
		else if (isFlush(theHand, thePlayer))
			thePlayer.setRanking(7);
		else if (isFullHouse(theHand, thePlayer))
			thePlayer.setRanking(6);
		else if (isStraight(theHand))
			thePlayer.setRanking(5);
		else if (isThreeOfAKind(theHand))
			thePlayer.setRanking(4);
		else if (isTwoPair(theHand))
			thePlayer.setRanking(3);
		else if (isOnePair(theHand))
			thePlayer.setRanking(2);
		else if (highCard(handPlayer))
			thePlayer.setRanking(1);
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
	bool Game::isStraightFlush(const std::vector<Card>& theHand, Player& thePlayer)
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

			// Initialize best hand for Player
			int best[CARDS_BEST_DECK] = {0};
			size_t startRank = 0;

			// Look for 5 consecutive ranks (in high rank) and store the best hand in Player 
			int consecutive = 1;
			for (size_t idx = 1; idx < ranksHigh.size(); idx++)
			{
				if (ranksHigh[idx] == ranksHigh[idx - 1] + 1)
				{
					consecutive++;
					if (consecutive == 2)	startRank = idx - 1;

					if (consecutive >= 5)
					{
						for (int idx2 = 0; idx2 < CARDS_BEST_DECK; idx2++)
							best[idx2] = ranksHigh[startRank + idx2];
						thePlayer.storeBestHand(best, CARDS_BEST_DECK);

						return true;
					}
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
					if (consecutive == 2)	startRank = idx - 1;

					if (consecutive >= 5)
					{
						for (int idx2 = 0; idx2 < CARDS_BEST_DECK; idx2++)
							best[idx2] = ranksLow[startRank + idx2];
						thePlayer.storeBestHand(best, CARDS_BEST_DECK);

						return true;
					}
				}
				else if (ranksLow[idx] != ranksLow[idx - 1])
					consecutive = 1;
			}

		}
		return false;
	}

	// Ranking 3
	bool Game::isFourOfAKind(const std::vector<Card>& theHand, Player& thePlayer)
	{
		int counts[N_NAMES] = { 0 };
		bool isFour = false;
		for (const Card& card : theHand)
		{
			const int idxRank = lowRank(card.getName(), NAMES, N_NAMES);
			counts[idxRank]++;
		}

		int quadRank = -1;
		for (int idx = 0; idx < N_NAMES; idx++)
		{
			if (counts[idx] >= 4)
			{
				quadRank = idx;
				isFour = true;
				break;
			}
		}
		if (!isFour)	return false;

		// Find the Max Card, where Ace has index 0 and values the most (13)
		int kicker = -1;
		for (int idx = N_NAMES - 1; idx >= 0; idx--)
			if (idx != quadRank && counts[idx] > 0)
			{
				kicker = idx;
				break;
			}
		if (kicker == 0)	kicker = 13;	// Ace = 13

		// Store the 4 similar cards and the max rank card (different from the four)
		int bestSequence[CARDS_BEST_DECK] = {0};
		for (int idx = 0; idx < 4; idx++)
			bestSequence[idx] = quadRank;
		bestSequence[CARDS_BEST_DECK - 1] = kicker;
		thePlayer.storeBestHand(bestSequence, CARDS_BEST_DECK);
		
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
		// Store best hand rank
		int bestHand[CARDS_BEST_DECK] = {0};
		if (triples == 2)
		{
			const int max = std::max(tripleRank[0], tripleRank[1]);
			const int min = std::min(tripleRank[0], tripleRank[1]);
			// Use higher triple as the three and the lower as pair
			for (int idx = 0; idx < 3; idx++)
				bestHand[idx] = max;
			for (int idx = 3; idx < CARDS_BEST_DECK; idx++)
				bestHand[idx] = min;
			thePlayer.storeBestHand(bestHand, CARDS_BEST_DECK);
			return true;
		}
		if (triples == 1 && couples >= 1)
		{
			// Find the highest pair not overlapping with the triple
			const int triple = tripleRank[0];
			int highestPair = -1;
			for (int idx = 0; idx < idxPairRank; idx++)
				if (pairRank[idx] != triple)
					highestPair = std::max(highestPair, pairRank[idx]);

			// Use the triple and the highest pair as value of best hand
			for (int idx = 0; idx < 3; idx++)
				bestHand[idx] = triple;
			for (int idx = 3; idx < CARDS_BEST_DECK; idx++)
				bestHand[idx] = highestPair;
			thePlayer.storeBestHand(bestHand, CARDS_BEST_DECK);
			return true;
		}

		return false;
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
		std::vector<int> bestHand;
		for (const Card& aCard : theHand)
		{
			const int idxSuit = rankSuit(aCard.getSuit(), SUITS, N_SUITS);
			if (idxSuit == flushSuit)
			{
				int idxCard = lowRank(aCard.getName(), NAMES, N_NAMES);
				int rankCard = (idxCard == 0) ? 13 : idxCard;	// Ace value is 13
				bestHand.push_back(rankCard);
			}
		}

		std::sort(bestHand.rbegin(), bestHand.rend());
		int theBestHand[5] = {0};
		for (int idx = 0; idx < CARDS_BEST_DECK; idx++)
			theBestHand[idx] = bestHand[idx];
		thePlayer.storeBestHand(theBestHand, CARDS_BEST_DECK);

		return true;
	}

	// Ranking 6
	bool Game::isStraight(const std::vector<Card>& theHand, Player& thePlayer)
	{
		std::vector<int> rankLowOrder;
		std::vector<int> rankHighOrder;
		
		for (const Card& card : theHand)
		{
			const std::string& cardName = card.getName();
			const int cardLowRank = lowRank(cardName, NAMES, N_NAMES);
			const int cardHighRank = highRank(cardName, NAMES, N_NAMES);
			rankLowOrder.push_back(cardLowRank);
			rankHighOrder.push_back(cardHighRank);
		}
		// Sort and remove duplicate for low ordered rank cards
		std::sort(rankLowOrder.begin(), rankLowOrder.end());
		rankLowOrder.erase(std::unique(rankLowOrder.begin(), rankLowOrder.end()), rankLowOrder.end());
		// Sort and remove duplicate for high ordered rank cards
		std::sort(rankHighOrder.begin(), rankHighOrder.end());
		rankHighOrder.erase(std::unique(rankHighOrder.begin(), rankHighOrder.end()), rankHighOrder.end());

		// Check whether ranks are in order for High Rank (Ace values the most)
		int count = 1;
		int startRank = -1;
		int bestHand[CARDS_BEST_DECK] = {0};
		for (size_t idx = 1; idx < rankHighOrder.size(); idx++) {
			if (rankHighOrder[idx] == rankHighOrder[idx - 1] + 1) 
			{
				count++;
				if (count == 2)	startRank = static_cast<int>(idx - 1);
				if (count >= 5) 
				{
					for (int idxBest = 0; idxBest < CARDS_BEST_DECK; idxBest++)
						bestHand[idxBest] = startRank + idxBest;
					thePlayer.storeBestHand(bestHand, CARDS_BEST_DECK);
					return true;
				}
			}
			else
				count = 1;
		}
		// Check whether ranks are in order for Low Rank (Ace values the least)
		count = 1;
		startRank = -1;
		for (size_t idx = 1; idx < rankLowOrder.size(); idx++) {
			if (rankLowOrder[idx] == rankLowOrder[idx - 1] + 1)
			{
				count++;
				if (count == 2)	startRank = static_cast<int>(idx - 1);
				if (count >= 5)
				{
					for (int idxBest = 0; idxBest < CARDS_BEST_DECK; idxBest++)
						bestHand[idxBest] = startRank + idxBest;
					thePlayer.storeBestHand(bestHand, CARDS_BEST_DECK);
					return true;
				}
			}
			else
				count = 1;
		}
		return false;
	}

	// Ranking 7
	bool Game::isThreeOfAKind(const std::vector<Card>& theHand)
	{
		int counts[N_NAMES] = { 0 };
		for (const Card& card : theHand) 
		{
			const int cardIdx = lowRank(card.getName(), NAMES, N_NAMES);
			counts[cardIdx]++;
		}
		for (const int count : counts)
			if (count >= 3)	return true;

		return false;
	}

	// Ranking 8
	bool Game::isTwoPair(const std::vector<Card>& theHand)
	{
		int pairs = 0;
		int counts[N_NAMES] = {0};
		for (const Card& card : theHand)
		{
			const int idxCard = lowRank(card.getName(), NAMES, N_NAMES);
			counts[idxCard]++;
		}
		for (const int count : counts)
			if (count >= 2)
				pairs++;

		return (pairs >= 2);
	}

	// Ranking 9
	bool Game::isOnePair(const std::vector<Card>& theHand)
	{
		int counts[N_NAMES] = { 0 };
		for (const Card& card : theHand)
		{
			const int cardIdx = lowRank(card.getName(), NAMES, N_NAMES);
			counts[cardIdx]++;
		}
		for (const int count : counts)
			if (count >= 2)	return true;

		return false;
	}

	// Ranking 10
	int Game::highCard(const Hand& handPlayer)
	{
		int higherRank = 0;
		for (const Card& card : handPlayer)
		{
			const int highRankCard = highRank(card.getName(), NAMES, N_NAMES);
			higherRank = std::max(higherRank, highRankCard);
		}
		return higherRank;
	}

	void Game::resetRoundState()
	{
		// TODO : roundState is adjusted every time a player is eliminated
		// TODO : currentPlayer is the player next to CurrentPlayer
		// TODO : smallBlind is moved by 1 position
	}

} // myNamespacePoker