#include <iostream>
#include <random>
#include <stdexcept>
#include "14_11_Deck.h"
#include "14_11_Validation.h"

namespace myNamespaceCards 
{

	Deck::Deck() 
	{
		deck = new Card[DECK_SIZE];
		numberCards = DECK_SIZE;

		using myNamespaceCards::Card;
		
		int idxCard = 0;
		for (int idx = 0; idx < N_NAMES; idx++)
			for (int idx2 = 0; idx2 < N_SUITS; idx2++)
				deck[idxCard++] = Card(SUITS[idx2], NAMES[idx]);
	}

	Deck::~Deck()
	{
		delete [] deck;
	}

	Deck::Deck(const Deck& anotherDeck) : numberCards(anotherDeck.numberCards)
	{
		deck = new Card[numberCards];
		for (int idx = 0; idx < numberCards; idx++)
			deck[idx] = anotherDeck.deck[idx];
	}

	Deck& Deck::operator =(const Deck& anotherDeck)
	{
		if (this == &anotherDeck)	return *this;
		if (numberCards != anotherDeck.numberCards)
		{
			delete [] deck;
			deck = new Card[anotherDeck.numberCards];
		}
		numberCards = anotherDeck.numberCards;
		for (int idx = 0; idx < numberCards; idx++)
			deck[idx] = anotherDeck.deck[idx];
		return *this;
	}

	void Deck::print(std::ostream& outputStream) const
	{
		for (int idx = 0; idx < numberCards; idx++)
			outputStream << "Card " << idx + 1 << ": " << deck[idx];
	}

	Deck& Deck::sort()
	{
		for (int idx = 0; idx < numberCards - 1; idx++)
		{
			int idxMinCard = idx;
			for (int idx2 = idx + 1; idx2 < numberCards; idx2++)
				if (deck[idx2] < deck[idxMinCard])
					idxMinCard = idx2;
			
			if (idxMinCard != idx)
			{
				const Card temp = deck[idx];
				deck[idx] = deck[idxMinCard];
				deck[idxMinCard] = temp;
			}
		}
		return *this;
	}

	void Deck::shuffle()
	{
		// ONE Rng per thread
		thread_local std::mt19937 rng{ std::random_device{}() };

		for (int idx = numberCards - 1; idx > 0; idx--)
		{
			std::uniform_int_distribution<int> dist(0, idx);
			const int idxRandom = dist(rng);
			// random index in [0, idx]

			// not thread safe
			// const int idxRandom = std::rand() % (idx + 1);

			const Card temp = deck[idx];
			deck[idx] = deck[idxRandom];
			deck[idxRandom] = temp;
		}	
	}

	void Deck::add(const Card& aCard)
	{
		CardPtr temp = new Card[numberCards + 1];
		for (int idx = 0; idx < numberCards; idx++)
			temp[idx] = deck[idx];
		temp[numberCards] = aCard;

		delete [] deck;
		deck = temp;
		numberCards++;
	}

	const Card Deck::remove()
	{
		Card removed = deck[0];
		
		CardPtr temp = new Card[numberCards - 1];
		int idxDelete = 0;
		for (int idx = 1; idx < numberCards; idx++)
			temp[idxDelete++] = deck[idx];

		delete [] deck;
		deck = temp;
		numberCards--;
		return removed;
	}

	void Deck::emptyDeck()
	{
		numberCards = 0;
	}

	int Deck::getNumberCards() const { return numberCards; }

	const Card& Deck::operator [](const int idx) const
	{
		if (numberCards < 0)
		{
			std::cout << "No cards in the deck\n";
			throw std::out_of_range("Not a valid index\n");
		}
		if (idx < 0 || idx >= numberCards)
		{
			std::cout << "No cards in the deck\n";
			throw std::out_of_range("Not a valid index\n");
		}
		return deck[idx];
	}

	std::istream& operator >>(std::istream& inputStream, Deck& aDeck)
	{
		char answer;
		do
		{
			Card aCard;
			std::cout << "Enter a card to add:\n";
			inputStream >> aCard;
			for (int idx = 0; idx < aDeck.numberCards; idx++)
				if (aDeck.deck[idx] == aCard)
				{
					std::cout << "Card already in the deck\n";
					return inputStream;
				}
			aDeck.add(aCard);
			std::cout << "Add more cards (y/n)\n?";
			using myNamespaceValidation::readName;
			readName(inputStream, answer);
		} while (std::tolower(answer) == 'y');
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Deck& aDeck)
	{
		aDeck.print(outputStream);
		return outputStream;
	}
} // myNamespaceCards