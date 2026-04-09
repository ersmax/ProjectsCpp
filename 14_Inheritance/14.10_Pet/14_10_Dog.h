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
		//   Postcondition: returns the lifespan of the dog based on its weight
		void print(std::ostream& outputStream) const override;
		//   Postcondition: outputs the name, age, weight, breed of the dog to outputStream
		friend std::istream& operator >>(std::istream& inputStream, Dog& aDog);
		//   Postcondition: inputs the name, age, weight, breed of the dog from inputStream
		friend std::ostream& operator <<(std::ostream& outputStream, const Dog& aDog);
		//   Postcondition: outputs the name, age, weight, breed of the dog from outputStream
	private:
		std::string breed;
	};

} // myNamespacePet

#endif // DOG_14_10_H
