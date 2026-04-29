#include "15_03_Organism.h"

namespace myGame
{
	Organism::Organism() : position({ -1, -1 }), moved(false)
	{ /* Body left empty */ }

	const Position& Organism::getPosition() const { return position; }

	void Organism::setPosition(const Position& thePosition) { position = thePosition; }

} // myGame
