#include <stdexcept>
#include <iostream>
#include "14_10_Dog.h"
#include "14_10_Validation.h"

namespace myNamespacePet
{
	constexpr int BIG_SIZE = 100;
	constexpr std::string SMALL_SIZE = "Approximately 7 years";
	constexpr std::string LARGE_SIZE = "Approximately 13 years";

	Dog::Dog() : Pet(), breed("No breed")
	{ /* Body intentionally left empty */ }

	Dog::Dog(const std::string& theName, const int theAge, const int theWeight, const std::string& theBreed) : Pet(theName, theAge, theWeight)
	{
		if (theBreed.empty())	throw std::invalid_argument("Not a valid dog's breed");
		breed = theBreed;
	}

	const std::string& Dog::getBreed() const { return breed; }

	const std::string& Dog::getLifespan() const
	{
		if (getWeight() < BIG_SIZE)	return SMALL_SIZE;
		return LARGE_SIZE;
	}

	std::istream& operator >>(std::istream& inputStream, Dog& aDog)
	{
		inputStream >> dynamic_cast<Pet&>(aDog);
		std::cout << "Enter dog's breed:\n";
		using myNamespaceValidation::readName;
		readName(inputStream, aDog.breed);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Dog& aDog)
	{
		outputStream << dynamic_cast<const Pet&>(aDog);
		outputStream << "Dog's breed: " << aDog.breed;
		return outputStream;
	}

} // myNamespacePet
