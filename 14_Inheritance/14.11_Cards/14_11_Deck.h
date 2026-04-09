#ifndef DECK_14_10_H
#define DECK_14_10_H

#include "14_11_Card.h"

namespace myNamespaceCards
{
	typedef Card *CardPtr;

	inline constexpr int DECK_SIZE = 52;

	class Deck
	{
	public:
		Deck();
		//   Postcondition: Create a deck with all 52 cards
		Deck(const Deck& anotherDeck);
		~Deck();
		Deck& operator =(const Deck& anotherDeck);
		int getNumberCards() const;
		void print(std::ostream& outputStream) const;
		void shuffle() const;
		void add(const Card& aCard);
		void emptyDeck();
		const Card remove();
		void sort() const;
		//   Postcondition: Sort cards by name (Ace, 2, 3, etc.)
		// Break ties by suit (Clubs, Diamonds, Hearts, Spades).
		friend std::ostream& operator <<(std::ostream& outputStream, const Deck& aDeck);
		//   Postcondition: Print all cards in the deck
		friend std::istream& operator >>(std::istream& inputStream, Deck& aDeck);
		//   Postcondition: add cards to the default deck as long as the user wishes
		// (checking also that the card is not already in the deck).
	private:
		CardPtr deck;
		int numberCards;
	};

	
} // myNamepspaceCards

#endif // DECK_14_10_H
