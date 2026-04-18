#ifndef GAME_14_13_H
#define GAME_14_13_H

#include "vector"
#include "14_13_Player.h"


namespace myNamespacePoker
{
	using Deck = myNamespaceCards::Deck;
	using Card = myNamespaceCards::Card;

	constexpr double STARTING_BET = 10.0;

	class Game
	{
	public:
		Game();
		//   Postcondition: create new game with 2 standard players, having $ 100 each 
		Game(const std::vector<Player>& thePlayers);
		//   Postcondition: create new game with the players passed as parameter
		void play();
		//   Postcondition: distribute card, handle betting and pot

	private:
		void playHand();
		//   Postcondition: play one Texas Hold'em hand		
		void callHand(Player& thePlayer, const double callingBet);
		//   Postcondition: allows the player to call and bet the money in the last call
		void raiseHand(Player& thePlayer, const double callingBet);
		//   Postcondition: allows the player to raise the last bet
		void foldHand(Player& thePlayer);
		//   Postcondition: allows the player to skip this hand
		bool atLeastTwoBetting() const;
		//   Postcondition: returns true if at least two players are raising the bet
		// and have not folded
		void resetRoundState();
		//   Postcondition: reset players's hand, pots and betting
		void takeBets();
		//   Postcondition: ask players how much to bet (or skip),
		// update their money and the pot
		void initiateTurn();
		//   Postcondition: distribute 2 cards to each player and 3 on the board
		static void showHand(const Player& thePlayer);
		//   Postcondition: show each player's card 
		static void showBoard(const std::vector<Card>& theBoard);
		//   Postcondition: show the cards in the main board
		void resolveRound();
		//   Postcondition: evaluate hands, determine winner, pay out from pot, and the losses.
		// Make use of helper functions: setRanking, handleLoss, handleTies
		void setRanking(Player& thePlayer, const std::vector<Card>& theHand, const Hand& handPlayer);
		//   Postcondition: assign a rank to the poker hand hold by each player
		void handleLoss(Player& thePlayer);
		//   Postcondition: handle the case when a player loses the hand,
		// with subsequent loss of money and possibly the elimination from the Poker game
		void handleTies(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Precondition: thePot is the total amount to be won, 
		// and winnerIndexes is the vector of indexes of players with the same ranking hand.
		//   Postcondition: in case of equal poker hands, break the ties according to 
		// the highest cards rank if possible. Else split the plot equally
		static bool isRoyalFlush(const std::vector<Card>& theHand, Player& thePlayer);
		//   Precondition: theHand is the vector of cards to be evaluated for the player,
		// and thePlayer is the player for which the hand is evaluated.
		//   Postcondition: return true if the hand is a Royal Flush. 
		// Tie resolution is centralized in payTieWinners.
		static bool isStraightFlush(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: return true if the hand is a Straight Flush.
		// Tie resolution is centralized in payTieWinners.
		static bool isFourOfAKind(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: return true if the hand is a Four of a Kind.
		// Tie resolution is centralized in payTieWinners.
		static bool isFullHouse(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: return true if the hand is a Full House.
		// Tie resolution is centralized in payTieWinners.
		static bool isFlush(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: return true if the hand is a Flush.
		// Tie resolution is centralized in payTieWinners.
		bool isStraight(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: return true if the hand is a Straight.
		// Tie resolution is centralized in payTieWinners.
		bool isThreeOfAKind(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: return true if the hand is a Three of a Kind.
		// Tie resolution is centralized in payTieWinners.
		bool isTwoPair(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: return true if the hand is a Two Pair.
		// Tie resolution is centralized in payTieWinners.
		bool isOnePair(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: return true if the hand is a One Pair.
		// Tie resolution is centralized in payTieWinners.
		bool highCard(const Hand& handPlayer, Player& thePlayer);
		//   Postcondition: returns true to signal that the poker hand is evaluated as High Card, 
		// and set the best hand of the player to the 5 highest cards in hand and on board.
		// Two cards are those in hand of the player. The other three cards are those on the board.
		// Tie resolution is centralized in payTieWinners.
		int compareBestHands(const Player& leftPlayer, const Player& rightPlayer) const;
		//   Postcondition: compare the best hand of two players and return 1 if leftPlayer wins, 
		// -1 if rightPlayer wins, and 0 if there is a tie.
		void payTieWinners(const double& thePot, const std::vector<int>& contenderIndexes);
		//   Precondition: thePot is the total amount to be won, 
		// and contenderIndexes is the vector of indexes of players with the same ranking hand.
		//   Postcondition: in case of equal poker hands, break the ties according to 
		// the highest cards rank if possible. Else split the plot equally.
		

		Deck shoe;
		//   Postcondition: create a deck of 52 cards
		std::vector<Player> players;
		//   Postcondition: the vector of players holding 2 cards each
		std::vector<Card> board;
		//   Postcondition: this is the board with 3, 4, and 5 cards
		double pot;
		int nPlayers;
		int smallBlind;
		int bigBlind;
		double roundBet;
		double currentBet;
		int currentPlayer;

		
	};

} // myNamespacePoker


#endif // GAME_14_13_H
