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
		//   Postcondition: Print all cards in the deck
		void shuffle();
		//   Postcondition: Shuffle the cards in the deck. 
		// The Fisher-Yates shuffle algorithm is used.
		void add(const Card& aCard);
		//   Postcondition: Add a new card to the deck. 
		void emptyDeck();
		//   Postcondition: Set the number of cards in the deck to 0.
		const Card remove();
		//   Postcondition: Remove a card from the deck. 
		// This removes the first card stored in the dynamic array and returns it.
		Deck& sort();
		//   Postcondition: Sort cards by name (Ace, 2, 3, etc.)
		// Break ties by suit (Clubs, Diamonds, Hearts, Spades).
		const Card& operator [](int idx) const;
		//   Postcondition: Return the card at the specified index.
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
