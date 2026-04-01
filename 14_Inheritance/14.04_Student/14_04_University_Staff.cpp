#include "14_04_University_Staff.h"
#include "14_04_Input_Validation.h"

namespace myNamespaceUniversity
{
	UniversityStaff::UniversityStaff() : name("No Name")
	{ /* Body intentionally left empty */ }

	UniversityStaff::UniversityStaff(std::string theName) : name(std::move(theName))
	{ /* Body intentionally left empty */ }

	const std::string& UniversityStaff::getName() const { return name; }

	std::istream& operator >>(std::istream& inputStream, UniversityStaff& aStaff)
	{
		std::cout << "Enter University staff name:\n";
		myNamespaceValidation::readName(inputStream, aStaff.name);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const UniversityStaff& aStaff)
	{
		outputStream << aStaff.name;
		return outputStream;
	}
}
