#include "14_09_Cyberdemon.h"

namespace myNamespaceRPG
{
	Cyberdemon::Cyberdemon() : Demon(), name("Cyberdemon")
	{ /* Body intentionally left empty */ }

	Cyberdemon::Cyberdemon(const int newStrength, const int newHit) : Demon(newStrength, newHit), name("Cyberdemon")
	{ /* Body intentionally left empty */ }

	const std::string& Cyberdemon::getSpecies() const { return name; }

} // myNamespaceRPG
