#include <iostream>
#include "15_03_Ant.h"

namespace myGame
{
	Ant::Ant() : Organism()
	{ /* Body intentionally left empty */ }

	char Ant::getCreature() const { return creature; }

	void Ant::move()
	{
		std::cout << "Calling Ant::move()\n";
	}
} // myGame