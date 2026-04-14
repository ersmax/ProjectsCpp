```cpp
bool Game::isFullHouse(const std::vector<Card>& theHand)
{
	/* THE VERSION BELOW PROCEEDS TO COUNT BY DISTINGUISHING SUITS, if we had more than 2 decks */
	int triples = 0;
	int pair = 0;

	std::vector<std::string> doubles;
	// A list of card ranks that have been already accounted for doubles

	for (size_t idx = 0; idx < theHand.size() - 1; idx++)
	{
		const Card& card1 = theHand[idx];

		// Check card is not already considered for another double
		bool alreadySeen = false;
		for (const std::string& card : doubles) 
			if (card1.getName() == card) 
			{
				alreadySeen = true;
				break;
			}
		if (alreadySeen)	continue;

		// Compare with the next cards
		std::vector<std::string> suits;
		suits.push_back(card1.getSuit());

		for (size_t idx2 = idx + 1; idx2 < theHand.size(); idx2++)
		{
			const Card& card2 = theHand[idx2];

			// Skip different rank
			if (card1.getName() != card2.getName())	continue;

			// Suit already accounted for
			alreadySeen = false;
			for (const std::string& suit : suits)
			{
				if (card2.getSuit() == suit)
				{
					alreadySeen = true;
					break;
				}
			}
			if (alreadySeen)	continue;

			// Add card of the new suit and same rank
			suits.push_back(card2.getSuit());
			doubles.push_back(card1.getName());
		}
			
		if (suits.size() >= 3)
			triples++;
		else if (suits.size() == 2)
			pair++;
	}

	return (triples >= 2 || (triples == 1 && pair >= 1));
}
	
```