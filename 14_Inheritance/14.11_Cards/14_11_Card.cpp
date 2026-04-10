#include <iostream>
#include "14_11_Card.h"
#include "14_11_Validation.h"

namespace
{
	using myNamespaceCards::SUITS;
	using myNamespaceCards::NAMES;

	bool validSuit(const std::string& theSuit)
	{
		for (const std::string& aSuit : SUITS)
			if (aSuit == theSuit)
				return true;
		return false;
	}

	bool validName(const std::string& theName)
	{
		for (const std::string& aName : NAMES)
			if (aName == theName)
				return true;
		return false;
	}

	int indexOf(const std::string& value, const std::string *array, const int size)
	{
		for (int idx = 0; idx < size; idx++)
			if (array[idx] == value)
				return idx;
		return -1;
	}

} // unnamedNamespace


namespace myNamespaceCards
{
	Card::Card() : suit(SUITS[0]), name(NAMES[0])
	{ /* Body intentionally left empty */ }

	Card::Card(const std::string& theSuit, const std::string& theName) 
	{
		if (validSuit(theSuit) && validName(theName))
		{
			suit = theSuit;
			name = theName;
		}
	}

	const std::string& Card::getSuit() const { return suit; }

	const std::string& Card::getName() const { return name; }

	bool Card::operator <(const Card& card2) const
	{
		const int nameCard = indexOf(name, NAMES, N_NAMES);
		const int nameCard2 = indexOf(card2.name, NAMES, N_NAMES);
		if (nameCard != nameCard2)
			return (nameCard < nameCard2);

		const int suitCard = indexOf(suit, SUITS, N_SUITS);
		const int suitCard2 = indexOf(card2.suit, SUITS, N_SUITS);
		return suitCard < suitCard2;
	}

	bool Card::operator ==(const Card& card2) const
	{
		return (name == card2.name && suit == card2.suit);
	}

	std::istream& operator >>(std::istream& inputStream, Card& aCard)
	{
		std::cout << "Enter a suit among these:\n";
		for (int idx = 0; idx < N_SUITS - 1; idx++)
			std::cout << SUITS[idx] << ", ";
		std::cout << SUITS[N_SUITS - 1] << '\n';

		using myNamespaceValidation::readName;
		std::string aSuit;
		readName(inputStream, aSuit);
		if (!validSuit(aSuit))
		{
			std::cout << "Suit not valid\n";
			return inputStream;
		}
		std::string aName;
		readName(inputStream, aName);
		if (!validName(aName))
		{
			std::cout << "Name not valid\n";
			return inputStream;
		}
		aCard.suit = aSuit;
		aCard.name = aName;
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Card& aCard)
	{
		outputStream << aCard.suit << " " << aCard.name << '\n';
		return outputStream;
	}
} // myNamespaceCards