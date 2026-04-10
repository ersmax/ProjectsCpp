#ifndef HAND_14_11_H
#define HAND_14_11_H

#include "14_11_Deck.h"

namespace myNamespaceCards
{
	class Hand : public Deck
	{
	public:
		Hand();
		//   Postcondition: Set the hand to an empty set of cards.
		// This calls the emptyDeck function of the Deck class to set the number of cards in the hand to 0.
	};


} // myNamespaceCards

#endif // HAND_14_11_H
