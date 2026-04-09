/*
Use inheritance and classes to represent a deck of playing cards.Create a Card class
that stores the suit(Clubs, Diamonds, Hearts, Spades) and name(e.g., Ace, 2, 10,
Jack) along with appropriate accessors, constructors, and mutators.
Next, create a Deck class that stores a vector of Card objects.The default constructor
should create objects that represent the standard 52 cards and store them in the
vector.The Deck class should have functions to :
■ Print every card in the deck.
■ Shuffle the cards in the deck.You can implement this by randomly swapping
every card in the deck.
■ Add a new card to the deck.This function should take a Card object as a
parameter
and add it to the vector.
■ Remove a card from the deck.This removes the first card stored in the vector
and returns it.
■ Sort the cards in the deck ordered by name.
Next, create a Hand class that represents the cards in a hand. Hand should be derived
from Deck. This is because a hand is like a specialized version of a deck; we can
print, shuffle, add, remove, and sort cards in a hand just like cards in a deck. The
default constructor should set the hand to an empty set of cards.
Finally, write a main function that creates a deck of cards, shuffles the deck, and
creates two hands of five cards each. The cards should be removed from the deck
and added to the hand. Test the sort and print functions for the hands and the
deck. Finally, return the cards in the hand to the deck and test to ensure that the
cards have been properly returned.
You may add additional functions or class variables as desired to implement your
solution.
*/

#include <iostream>
#include "14_11_Hand.h"

using myNamespaceCards::Hand;
using myNamespaceCards::Deck;

void createHand(Deck& theDeck, Hand& theHand);
void returnHand(Deck& theDeck, Hand& theHand);

int main ( )
{
	Deck aDeck;
	Hand hand1, hand2;
	
	aDeck.shuffle();
	createHand(aDeck, hand1);
	createHand(aDeck, hand2);
	std::cout << "The hand 1 is:\n" << hand1 << '\n';
	std::cout << "The hand 1 sorted is:\n" << hand1.sort() << '\n';
	std::cout << "The hand 2 is:\n" << hand2 << '\n';
	std::cout << "The hand 2 sorted is:\n" << hand2.sort() << '\n';
	std::cout << "Remaining card in the deck (unsorted):\n" << aDeck << '\n';
	std::cout << "Remaining card in the deck (sorted):\n" << aDeck.sort() << '\n';

	returnHand(aDeck, hand1);
	returnHand(aDeck, hand2);
	aDeck.sort();
	std::cout << "Sorted cards in the deck:\n" << aDeck << '\n';
	std::cout << "Total card in the deck: " << aDeck.getNumberCards() << '\n';
	std::cout << "Total card in hand 1: " << hand1.getNumberCards() << '\n';
	std::cout << "Total card in hand 2: " << hand2.getNumberCards() << '\n';

	std::cout << '\n';
	return 0;
}