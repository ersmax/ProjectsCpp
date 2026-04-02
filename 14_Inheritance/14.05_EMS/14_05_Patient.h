#ifndef PATIENT_14_05_H
#define PATIENT_14_05_H

#include "14_05_Person.h"
#include "../14.03_Doctor/14_03_Doctor.h"


namespace myNamespacePeople
{
	using myNamespaceEmployees::Doctor;
	class Patient : public Person
	{
	public:
		Patient();
		Patient(const Doctor& aDoctor, const std::string& theName = "No name");
		Patient(const Patient& other) = default;
		Patient& operator =(const Patient& other) = default;
		const Doctor& getPhysician() const;
		friend std::istream& operator >>(std::istream& inputStream, Patient& thePatient);
		friend std::ostream& operator <<(std::ostream& outputStream, const Patient& thePatient);
	private:
		Doctor physician;
	};
} // myNamespacePeople

#endif
