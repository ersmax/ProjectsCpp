#include <iostream>
#include "15_03_Doodlebug.h"

namespace myGame
{
	Doodlebug::Doodlebug() : Organism()
	{ /* Body intentionally left empty */ }

	char Doodlebug::getCreature() const { return creature; }

	void Doodlebug::move()
	{
		std::cout << "Calling Doodlebug::move()\n";
	}

} // myGame