#include "15_03_Organism.h"

namespace myGame
{
	Organism::Organism(const Position& thePosition, const char theSymbol) : position(thePosition), symbol(theSymbol)
	{ /* Body left empty */ }

	const Position& Organism::getPosition() const { return position; }

	void Organism::setPosition(const Position& thePosition) { position = thePosition; }

	char Organism::getSymbol() const { return symbol; }

} // myGame
