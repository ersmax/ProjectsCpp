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
	};
		
} // myNamespacePet

#endif // ROCK_14_10_H
