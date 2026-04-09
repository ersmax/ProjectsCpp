#include <iostream>
#include <stdexcept>
#include "14_10_Orchestrator.h"
#include "14_10_Dog.h"
#include "14_10_Rock.h"
#include "14_10_Validation.h"

namespace myNamespacePet
{
	typedef Dog *DogPtr;
	typedef Rock *RockPtr;

	Orchestrator::Orchestrator() : things(nullptr), numberThings(0)
	{ /* Body intentionally left empty */ }

	Orchestrator::~Orchestrator()
	{
		for (int idx = 0; idx < numberThings; idx++)
			delete things[idx];
			// deallocate memory given to a dynamic object

		delete [] things;
	}

	void Orchestrator::addThing(std::istream& inputStream)
	{
		std::cout << "Enter 1 to add a Dog, 2 to add a Rock\n";
		int choice;
		using myNamespaceValidation::readNumber;
		readNumber(inputStream, choice);
		switch (choice)
		{
		case 1:
		{
			const DogPtr aDog = new Dog;
			std::cout << "Enter new Dog:\n";
			inputStream >> *aDog;
			addThingHelper(aDog);
			break;
		}
		case 2:
		{
			const RockPtr aRock = new Rock;
			std::cout << "Enter new Rock:\n";
			inputStream >> *aRock;
			addThingHelper(aRock);
			break;
		}
		default:
			std::cout << "Not a valid choice\n";
			break;
		}
	}

	void Orchestrator::addThingHelper(const PetPtr& aPet)
	{
		PetPtr *temp = new PetPtr[numberThings + 1];
		for (int idx = 0; idx < numberThings; idx++)
			temp[idx] = things[idx];
			// copy older pointers

		temp[numberThings] = aPet;
		delete [] things;
		things = temp;
		numberThings++;
	}

	void Orchestrator::deleteThing()
	{
		if (numberThings <= 0)
		{
			std::cout << "There are no things\n";
			return;
		}
		using myNamespaceValidation::readNumber;
		std::cout << *this;
		std::cout << "Enter index of Thing you wish to delete:\n";
		int choice;
		readNumber(std::cin, choice);
		choice--;
		if (choice < 0 || choice >= numberThings)
			std::cout << "Wrong index\n";
		else
			deleteThingHelper(choice);
	}

	void Orchestrator::deleteThingHelper(const int index)
	{
		delete things[index];
		// delete the pointers to the object and return the memory to the freestore
		
		PetPtr *temp = new PetPtr[numberThings - 1];
		int newIdx = 0;
		for (int idx = 0; idx < numberThings; idx++)
			if (idx != index)
				temp[newIdx++] = things[idx];

		delete [] things;
		things = temp;
		numberThings--;
	}

	const Pet& Orchestrator::operator[](const int index) const
	{
		if (index < 0 || index >= numberThings)
			throw std::out_of_range("Index out of bounds\n");
		return *things[index];
	}

	std::ostream& operator <<(std::ostream& outputStream, const Orchestrator& aOrchestrator)
	{
		for (int idx = 0; idx < aOrchestrator.numberThings; idx++)
		{
			const Pet& pet = aOrchestrator.operator[](idx);
			outputStream << "Object number " << idx + 1 << '\n';
			outputStream << pet;
			outputStream << "Lifetime: " << pet.getLifespan() << "\n\n";
		}
		return outputStream;
	}

	std::istream& operator >>(std::istream& inputStream, Orchestrator& aOrchestrator)
	{
		char answer;
		do
		{
			aOrchestrator.addThing(inputStream);
			std::cout << "Add more? (y/n)\n";
            inputStream >> answer;
		} while (std::tolower(static_cast<unsigned char>(answer)) == 'y');

		return inputStream;
	}

} // myNamespacePet