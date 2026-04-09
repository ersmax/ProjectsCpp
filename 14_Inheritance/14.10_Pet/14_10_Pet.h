#ifndef PET_14_10_H
#define PET_14_10_H

#include <string>

namespace myNamespacePet
{
	class Pet
	{
	public:
		Pet();
		Pet(const std::string& theName, int theAge, int theWeight);
		virtual ~Pet() = default;
		//  Postcondition: Destroys the Pet object.
		// Virtual due to the fact that the Pet class is a base class for other classes. 
		// This allows for the correct destructor to be called when deleting an object of a derived class 
		// through a pointer to the base class.
		virtual const std::string& getLifespan() const;
		//   Postcondition: returns the lifespan of the pet.
		// Virtual due to the fact that behavior of this function is different for different types of pets.
		const std::string& getName() const;
		int getAge() const;
		int getWeight() const;
		virtual void print(std::ostream& outputStream) const;
		//   Postcondition: outputs the name, age, and weight of the pet to outputStream.
		// Virtual due to the fact that behavior of this function is different for different types of pets.
		friend std::istream& operator >>(std::istream& inputStream, Pet& aPet);
		//   Postcondition: inputs the name, age, and weight of the pet from inputStream.
		friend std::ostream& operator <<(std::ostream& outputStream, const Pet& aPet);
		//   Postcondition: calls the print function to output details of the pet to outputStream.
	private:
		std::string name;
		int age;
		int weight;
	};

} // myNamespacePet

#endif // PET_14_10_H