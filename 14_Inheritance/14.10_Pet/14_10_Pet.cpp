#include <iostream>
#include <stdexcept>
#include "14_10_Pet.h"
#include "14_10_Validation.h"


namespace myNamespacePet
{
	constexpr std::string UNKNOWN = "Unknown lifespan";

	Pet::Pet() : name("No name"), age(0), weight(0)
	{ /* Body intentionally left empty */ }

	Pet::Pet(const std::string& theName, const int theAge, const int theWeight)
	{
		if (theName.empty() || theAge < 0 || theWeight < 0)
			throw std::invalid_argument("Invalid parameters\n");
		name = theName;
		age = theAge;
		weight = theWeight;
	}

	const std::string& Pet::getLifespan() const
	{
		return UNKNOWN;
	}

	const std::string& Pet::getName() const { return name; }

	int Pet::getAge() const { return age; }

	int Pet::getWeight() const { return weight; }

	std::istream& operator >>(std::istream& inputStream, Pet& aPet)
	{
		using myNamespaceValidation::readName;
		using myNamespaceValidation::readNumber;
		std::cout << "Enter name:\n";
		readName(inputStream, aPet.name);
		std::cout << "Enter age:\n";
		readNumber(inputStream, aPet.age);
		std::cout << "Enter weight:\n";
		readNumber(inputStream, aPet.weight);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Pet& aPet)
	{
		outputStream << "Name: " << aPet.name << '\n';
		outputStream << "Age: " << aPet.age << '\n';
		outputStream << "Weight: " << aPet.weight << '\n';
		return outputStream;
	}

} // myNamespacePet
