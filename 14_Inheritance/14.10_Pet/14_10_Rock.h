#ifndef ROCK_14_10_H
#define ROCK_14_10_H

#include "14_10_Pet.h"

namespace myNamespacePet
{
	class Rock : public Pet
	{
	public:
		Rock();
		Rock(const std::string& theName, int theAge, int theWeight);
		const std::string& getLifespan() const override;
		//   Postcondition: returns the lifespan of the rock based on its weight
		// Override due to the fact that behavior of this function is different for different types of pets.
	};
		
} // myNamespacePet

#endif // ROCK_14_10_H
