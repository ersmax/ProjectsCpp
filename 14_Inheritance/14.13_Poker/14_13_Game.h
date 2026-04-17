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
		//   Postcondition: create new game, shuffle cards
		Game(const std::vector<Player>& thePlayers);
		//   Postcondition: create new game, shuffle cards and set nPlayers 
		void play();
		//   Postcondition: distribute card, handle betting and pot

	private:
		// TODO : dealFlop() for 3 cards, dealTurn() for 4 cards, dealRiver() for 5 cards?

		void playHand();
		//   Postcondition: play one Texas Hold'em hand		
		void callHand(Player& thePlayer, const double callingBet);
		//   Postcondition: allows the player to call and bet the money in the last call
		void raiseHand(Player& thePlayer, const double callingBet);
		//   Postcondition: allows the player to raise the last bet
		void foldHand(Player& thePlayer);
		//   Postcondition: allows the player to skip this hand
		bool atLeastTwoBetting() const;
		bool bettingRoundSettled() const;
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
		//   Postcondition: in case of equal poker hands, break the ties according to 
		// the highest cards rank if possible. Else split the plot equally
		static bool isRoyalFlush(const std::vector<Card>& theHand, Player& thePlayer);
		void royalFlushTie(const double& thePot, const std::vector<int>& winnerIndexes);
		static bool isStraightFlush(const std::vector<Card>& theHand, Player& thePlayer);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of Royal Flush tie. All players with straight flush wins, hence a tie.
		void straightFlushTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of Straight Flush Tie. The Player with the highest card wins.
		// Else there is a tie.
		static bool isFourOfAKind(const std::vector<Card>& theHand, Player& thePlayer);
		void fourOfAKindTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of Four of a kind tie. The Player with the highest card in the four wins.
		// To break ties, the highest rank of the fifth card (kicker) wins.
		// Else there is a tie.
		static bool isFullHouse(const std::vector<Card>& theHand, Player& thePlayer);
		void fullHouseTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of Full House tie. The player with the highest rank of tris wins.
		// To break ties, the player with the highest rank of pair wins.
		// Else there is a tie.
		static bool isFlush(const std::vector<Card>& theHand, Player& thePlayer);
		void flushTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of Flush tie. The player with the highest card in flush wins.
		// Else, the second, third, fourth and fifth cards are checked to break ties.
		bool isStraight(const std::vector<Card>& theHand, Player& thePlayer);
		void straightTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of Straight tie. The player with the highest card rank in a straight wins.
		// Else a tie happens.
		bool isThreeOfAKind(const std::vector<Card>& theHand, Player& thePlayer);
		void threeOfAKindTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of Three of a kind tie. The player with the highest rank in the tris wins.
		// Else the fourth and fifth cards are checked to break ties.
		bool isTwoPair(const std::vector<Card>& theHand, Player& thePlayer);
		void twoPairTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of two pair tie. The player with the highest rank in the first pair wins.
		// Else the second pair rank is checked, and eventually the last card to break ties.
		bool isOnePair(const std::vector<Card>& theHand, Player& thePlayer);
		void aPairTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of A Pair tie. The player with the highest rank in the pair wins.
		// Else the third, fourth and fifth cards are checked to break ties.
		bool highCard(const Hand& handPlayer, Player& thePlayer);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of A Pair tie. 
		void highCardTie(const double& thePot, const std::vector<int>& winnerIndexes);
		//   Postcondition: handle the winning of thePot and the losses of players in
		// case of a high Card Tie. The player with the highest rank on their hand wins.
		// If the players have same high card in hand, the second card in hand is checked.
		// If both cards in hand of the players have same ranks, the pot is split equally.
		int compareBestHands(const Player& leftPlayer, const Player& rightPlayer) const;
		void payTieWinners(const double& thePot, const std::vector<int>& contenderIndexes);
		

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
