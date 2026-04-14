#ifndef GAME_14_13_H
#define GAME_14_13_H

#include "vector"
#include "14_13_Player.h"


namespace myNamespacePoker
{
	using Deck = myNamespaceCards::Deck;
	using Card = myNamespaceCards::Card;

	constexpr int STARTING_BET = 10;

	class Game
	{
	public:
		Game();
		//   Postcondition: create new game, shuffle cards
		Game(int thePlayers);
		//   Postcondition: create new game, shuffle cards and set nPlayers 
		void play();
		//   Postcondition: distribute card, handle betting and pot

	private:
		// TODO : dealFlop() for 3 cards, dealTurn() for 4 cards, dealRiver() for 5 cards?

		void playHand();
		//   Postcondition: play one Texas Hold'em hand		
		void callHand(Player& thePlayer, const int callingBet);
		//   Postcondition: allows the player to call and bet the money in the last call
		void raiseHand(Player& thePlayer, const int callingBet);
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
		//   Postcondition: evaluate hands, determine winner, pay out from pot
		void setRanking(Player& thePlayer, const std::vector<Card>& theHand);
		//   Postcondition: assign a rank to the poker hand hold by each player
		static bool isRoyalFlush(const std::vector<Card>& theHand);
		static bool isStraightFlush(const std::vector<Card>& theHand);
		static bool isFourOfAKind(const std::vector<Card>& theHand);
		static bool isFullHouse(const std::vector<Card>& theHand);
		static bool isFlush(const std::vector<Card>& theHand);
		bool isStraight(const std::vector<Card>& theHand);
		bool isThreeOfAKind(const std::vector<Card>& theHand);
		bool isTwoPair(const std::vector<Card>& theHand);
		bool isOnePair(const std::vector<Card>& theHand);
		bool isHighCard(const std::vector<Card>& theHand);

		Deck shoe;
		//   Postcondition: create a deck of 52 cards
		std::vector<Player> players;
		//   Postcondition: the vector of players holding 2 cards each
		std::vector<Card> board;
		//   Postcondition: this is the board with 3, 4, and 5 cards
		int pot;
		int nPlayers;
		int smallBlind;
		int bigBlind;
		int roundBet;
		int currentBet;
		int currentPlayer;

		
	};

} // myNamespacePoker


#endif // GAME_14_13_H
