#ifndef CARD_14_11_H
#define CARD_14_11_H

#include <string>

namespace myNamespaceCards
{
	inline constexpr int N_SUITS = 4;
	inline constexpr int N_NAMES = 13;
	inline const std::string SUITS[N_SUITS] = { "Clubs", "Diamonds", "Hearts", "Spades" };
	inline const std::string NAMES[N_NAMES] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

	class Card
	{
	public:
		Card();
		//   Postcondition: Initialize the card to the Ace of Clubs.
		Card(const std::string& theSuit, const std::string& theName);
		const std::string& getSuit() const;
		const std::string& getName() const;
		bool operator <(const Card& card2) const;
		//   Postcondition: Compare cards by name (Ace, 2, 3, etc.). Break ties by suit (Clubs, Diamonds, Hearts, Spades).
		bool operator ==(const Card& card2) const;
		//   Postcondition: Return true if the suit and name of the cards are the same.
		friend std::istream& operator >>(std::istream& inputStream, Card& aCard);
		//   Postcondition: Read the suit and name of a card from the user. Check that the suit and name are valid.
		friend std::ostream& operator <<(std::ostream& outputStream, const Card& aCard);
		//   Postcondition: Print the suit and name of the card.
	private:
		std::string suit;
		std::string name;
	};

} // myNamespaceCards

#endif // CARD_14_11_H
