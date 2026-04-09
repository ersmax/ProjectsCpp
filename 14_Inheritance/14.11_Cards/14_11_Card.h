#ifndef CARD_14_11_H
#define CARD_14_11_H

#include <string>

namespace myNamespaceCards
{
	inline constexpr int N_SUITS = 4;
	inline constexpr int N_NAMES = 13;
	inline const std::string SUITS[N_SUITS] = { "Clubs", "Diamonds", "Hearts", "Spades" };
	inline const std::string NAMES[N_NAMES] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "Jack", "Queen", "King" };

	class Card
	{
	public:
		Card();
		Card(const std::string& theSuit, const std::string& theName);
		const std::string& getSuit() const;
		const std::string& getName() const;
		bool operator <(const Card& card2) const;
		bool operator ==(const Card& card2) const;
		friend std::istream& operator >>(std::istream& inputStream, Card& aCard);
		friend std::ostream& operator <<(std::ostream& outputStream, const Card& aCard);
	private:
		std::string suit;
		std::string name;
	};

} // myNamespaceCards

#endif // CARD_14_11_H
