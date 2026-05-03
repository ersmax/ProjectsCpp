#include "15_04_Human.h"

namespace myRPG
{
	Human::Human() : Creature()
	{ /* Body intentionally left empty */ }

	Human::Human(const int theStrength, const int theHitpoints) : Creature(theStrength, theHitpoints)
	{ /* Body intentionally left empty */ }

	const std::string& Human::getSpecies() const { return species; }

} // myRPG
