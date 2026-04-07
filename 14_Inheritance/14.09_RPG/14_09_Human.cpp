#include "14_09_Human.h"

namespace myNamespaceRPG
{
	Human::Human() : Creature(), name("Human")
	{ /* Body intentionally left empty */ }

	Human::Human(const int newStrength, const int newHit) : Creature(newStrength, newHit), name("Human")
	{ /* Body intentionally left empty */ }

	int Human::getDamage() const { return Creature::getDamage(); }

	const std::string& Human::getSpecies() const { return name; }

} // myNamespaceRPG
