#ifndef DOG_14_10_H
#define DOG_14_10_H

#include "14_10_Pet.h"

namespace myNamespacePet
{
	class Dog : public Pet
	{
	public:
		Dog();
		Dog(const std::string& theName, int theAge, int theWeight, const std::string& theBreed);
		const std::string& getBreed() const;
		const std::string& getLifespan() const override;
		friend std::istream& operator >>(std::istream& inputStream, Dog& aDog);
		friend std::ostream& operator <<(std::ostream& outputStream, const Dog& aDog);
	private:
		std::string breed;
	};

} // myNamespacePet

#endif // DOG_14_10_H
