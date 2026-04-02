#include "14_05_Person.h"
#include "../14.04_Student/14_04_Input_Validation.h"

namespace myNamespacePeople
{
	Person::Person() : name("No name")
	{ /* Body intentionally left empty */ }

	Person::Person(std::string theName) : name(std::move(theName))
	{ /* Body intentionally left empty */ }

	const std::string& Person::getName() const { return name; }

	std::istream& operator >>(std::istream& inputStream, Person& aStaff)
	{
		using myNamespaceValidation::readName;

		std::cout << "Enter full name:\n";
		readName(inputStream, aStaff.name);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Person& aStaff)
	{
		outputStream << "Full name: " << aStaff.name << '\n';
		return outputStream;
	}
}
