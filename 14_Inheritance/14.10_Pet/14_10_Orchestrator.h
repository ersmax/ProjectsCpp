#ifndef ORCHESTRATOR_14_10_H
#define ORCHESTRATOR_14_10_H

#include <iostream>
#include "14_10_Pet.h"

namespace myNamespacePet
{

	typedef Pet *PetPtr;

	class Orchestrator
	{
	public:
		Orchestrator();
		~Orchestrator();
		const Pet& operator [](int index) const;
		//   Postcondition: returns the pet object at the specified index.
		void deleteThing();
		//   Postcondition: deletes the pet object at the specified index.
        void addThing(std::istream& inputStream);
		//   Postcondition: adds a pet object to the collection of pet objects.
		friend std::ostream& operator <<(std::ostream& outputStream, const Orchestrator& aOrchestrator);
		//   Postcondition: outputs the pet objects in the collection of pet objects.
		// Make use of the virtual print function of the Pet class to output the pet objects in the collection of pet objects.
		// The virtual function allows the correct polymorphic behavior to occur when outputting the pet objects in the collection of pet objects.
		friend std::istream& operator >>(std::istream& inputStream, Orchestrator& aOrchestrator);
		//   Postcondition: inputs the pet objects in the collection of pet objects.
		// Make use of the overloaded input operator of the Pet class to input the pet objects in the collection of pet objects.
	private:
		void addThingHelper(const PetPtr& aPet);
		//   Postcondition: adds a pet object to the collection of pet objects.
		// A pointer is passed to allow for dynamic binding to occur when adding pet objects to the collection of pet objects.
		void deleteThingHelper(int index);
		//   Postcondition: deletes the pet object at the specified index.
		PetPtr *things;
		int numberThings;
	};
		
} // myNamespacePet

#endif // ORCHESTRATOR_14_10_H
