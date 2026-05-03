#include "15_04_Cyberdemon.h"

namespace myRPG
{
	Cyberdemon::Cyberdemon() : Demon()
	{ /* Body intentionally left empty */}

	Cyberdemon::Cyberdemon(const int theStrength, const int theHitpoints) : Demon(theStrength, theHitpoints)
	{ /* Body intentionally left empty */ }

	const std::string& Cyberdemon::getSpecies() const { return species; }

} // myRPG