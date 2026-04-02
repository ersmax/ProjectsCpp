#include "14_05_Patient.h"

#include "../14.04_Student/14_04_Input_Validation.h"

namespace myNamespacePeople
{
	Patient::Patient() : Person(), physician()
	{ /* Body intentionally left empty */ }

    Patient::Patient(const Doctor& aDoctor, const std::string& theName) : Person(theName), physician(aDoctor)
	{ /* Body intentionally left empty */ }

	const Doctor& Patient::getPhysician() const { return physician; }

	std::istream& operator >>(std::istream& inputStream, Patient& thePatient)
	{
		// read full name
		if (thePatient.getName() == "No name")
			inputStream >> static_cast<Person&>(thePatient);
		// read primary physician 
		if (thePatient.physician.getName() == "No name")
			thePatient.physician.readData();
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Patient& thePatient)
	{
		outputStream << static_cast<const Person&>(thePatient);
		outputStream << "Doctor name: " << thePatient.physician.getName() << '\n';
		outputStream << "Specialty: " << thePatient.physician.getSpecialty() << '\n';
		outputStream << "Fee: " << thePatient.physician.getFee() << '\n'; 
		return outputStream;
	}
} // myNamespacePeople
