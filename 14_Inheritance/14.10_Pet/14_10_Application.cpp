/*
Define a Pet class that stores the pet’s name, age, and weight. Add appropriate
constructors, accessor functions, and mutator functions. Also define a function
named getLifespan that returns a string with the value “unknown lifespan.”
Next, define a Dog class that is derived from Pet. The Dog class should have a
private member variable named breed that stores the breed of the dog. Add mutator
and accessor functions for the breed variable and appropriate constructors.
Redefine the getLifespan function to return “Approximately 7 years” if the dog’s
weight is over 100 pounds and “Approximately 13 years” if the dog’s weight is
under 100 pounds.
Next, define a Rock class that is derived from Pet. Redefine the getLifespan
function to return “Thousands of years.”
Finally, write a test program that creates instances of pet rocks and pet dogs that
exercise the inherited and redefined functions.
*/

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
