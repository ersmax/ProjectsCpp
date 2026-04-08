#include "14_10_Rock.h"

namespace myNamespacePet
{
	constexpr std::string FOREVER = "Thousands of years";
	
	Rock::Rock() : Pet()
	{ /* Body intentionally left empty */ }

	Rock::Rock(const std::string& theName, const int theAge, const int theWeight) : Pet(theName, theAge, theWeight)
	{ /* Body intentionally left empty */ }

	const std::string& Rock::getLifespan() const { return FOREVER; }

} // myNamespacePet
