#include "14_04_Student.h"
#include "14_04_Input_Validation.h"

namespace myNamespaceUniversity
{
	Student::Student()	: universityName("No University"), registrationNumber(0), proctor(UniversityStaff())
	{ /* body intentionally left empty */ }

	Student::Student(std::string theName, const int theNumber, const UniversityStaff& theProctor)
						: universityName(std::move(theName)), registrationNumber(theNumber), proctor(theProctor)
	{ /* body intentionally left empty */ }

	std::istream& operator >>(std::istream& inputStream, Student& aStudent)
	{
		using myNamespaceValidation::readName, myNamespaceValidation::readNumber, myNamespaceValidation::readObject;
		std::cout << "Enter university name:\n";
		readName(inputStream, aStudent.universityName);
		std::cout << "Enter student registration number:\n";
		readNumber(inputStream, aStudent.registrationNumber);
		readObject(inputStream, aStudent.proctor);
		// Alternative implementation:
		// inputStream >> aStudent.proctor;
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Student& aStudent)
	{
		outputStream << "\nUniversity name: " << aStudent.universityName << '\n';
		outputStream << "Student number: " << aStudent.registrationNumber << '\n';
		outputStream << "Proctor " << aStudent.proctor;
		return outputStream;
	}

	const std::string& Student::getUniversity() const { return universityName; }

	int Student::getRegistration() const { return registrationNumber; }

	const std::string& Student::getProctor() const { return (proctor.getName()); }

} // myNamespaceUniversity
