#include <iostream>
#include <vector>
#include "14_11_Hand.h"

constexpr int CARDS_HAND = 5;

using myNamespaceCards::Card;
using myNamespaceCards::Hand;
using myNamespaceCards::Deck;

void createHand(Deck& theDeck, std::vector<Hand>& hands);
void returnHand(Deck& theDeck, std::vector<Hand>& hands);

int main ( )
{
	Deck aDeck;
	std::vector<Hand> hands;
	for (int idx = 0; idx < 2; idx++)
	{
		Hand aHand;
		hands.push_back(aHand);
	}
	
	aDeck.shuffle();
	createHand(aDeck, hands);
	std::cout << "The hand 1 is:\n" << hands[0] << '\n';
	std::cout << "The hand 1 sorted is:\n" << hands[0].sort() << '\n';
	std::cout << "The hand 2 is:\n" << hands[1] << '\n';
	std::cout << "The hand 2 sorted is:\n" << hands[1].sort() << '\n';
	std::cout << "Remaining card in the deck (unsorted):\n" << aDeck << '\n';
	std::cout << "Remaining card in the deck (sorted):\n" << aDeck.sort() << '\n';

	returnHand(aDeck, hands);
	aDeck.sort();
	std::cout << "Sorted cards in the deck:\n" << aDeck << '\n';
	std::cout << "Total card in the deck: " << aDeck.getNumberCards() << '\n';
	std::cout << "Total card in hand 1: " << hands[0].getNumberCards() << '\n';
	std::cout << "Total card in hand 2: " << hands[1].getNumberCards() << '\n';

	std::cout << '\n';
	return 0;
}

void createHand(Deck& theDeck, std::vector<Hand>& hands)
{
	if (static_cast<size_t>(theDeck.getNumberCards()) < hands.size() * CARDS_HAND )
	{
		std::cout << "Not enough cards in the deck\n";
		return;
	}    
	int nCards = 0;
	while (nCards < CARDS_HAND)
	{
		for (size_t idx = 0; idx < hands.size(); idx++)
		{
			Card theCard = theDeck.remove();
			hands[idx].add(theCard);
		}
		nCards++;
	}
}

void returnHand(Deck& theDeck, std::vector<Hand>& hands)
{
	for (Hand& hand : hands)
		while (hand.getNumberCards() > 0) 
		{
			Card theCard = hand.remove();
			theDeck.add(theCard);
		}
}
                                                  