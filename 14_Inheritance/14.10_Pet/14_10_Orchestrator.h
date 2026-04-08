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
		const Pet& operator [](int index) const;
		void deleteThing();
        void addThing();
		friend std::ostream& operator <<(std::ostream& outputStream, const Orchestrator& aOrchestrator);
		friend std::istream& operator >>(std::istream& inputStream, Orchestrator& aOrchestrator);
	private:
		void addThingHelper(const PetPtr& aPet);
		void deleteThingHelper(int index);
		PetPtr *things;
		int numberThings;
	};
		
} // myNamespacePet

#endif // ORCHESTRATOR_14_10_H
