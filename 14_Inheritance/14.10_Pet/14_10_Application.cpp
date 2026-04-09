#include "14_10_Orchestrator.h"
#include "14_10_Validation.h"

using myNamespacePet::Orchestrator;

void test(Orchestrator& anOrchestrator, int& choice);

int main( )
{
	Orchestrator aSet;

	std::cout << "Enter a set:\n";
	std::cin >> aSet;
	
	int choice;
	do 
	{
		test(aSet, choice);
	} while (choice != 4);
	
	std::cout << '\n';
	return 0;
}

void test(Orchestrator& anOrchestrator, int& choice)
{
	using myNamespaceValidation::readNumber;
	std::cout << "Do you wish to add (1), delete (2), view (3) or exit (4)?\n";
	readNumber(std::cin, choice);
	switch (choice)
	{
	case 1:
		anOrchestrator.addThing(std::cin);
		break;
	case 2: 
		anOrchestrator.deleteThing();
		break;
	case 3:
		std::cout << anOrchestrator;
		break;
	case 4:
	default:
		break;
	}
}
