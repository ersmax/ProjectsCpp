#include "14_05_Billing.h"
#include "../14.04_Student/14_04_Input_Validation.h"

constexpr double VAT = 0.22;

namespace myNamespaceClinic
{
    Billing::Billing() : aPatient(), aDoctor(), amountDue(0)
	// Calling default constructor Patient() for aPatient() and Doctor() for aDoctor
	{ /* Body intentionally left empty */ }

    Billing::Billing(const Doctor& theDoctor, const std::string& theName)
					: aPatient(theDoctor, theName), aDoctor(theDoctor)
	{
		setAmountDue();
	}

	std::istream& operator >>(std::istream& inputStream, Billing& aBill)
	{
		inputStream >> aBill.aPatient;
		aBill.aDoctor = aBill.aPatient.getPhysician();
		aBill.setAmountDue();
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Billing& aBill)
	{
		// Print patient data and doctor's name, speciality and fee (no VAT)
		outputStream << aBill.aPatient;
		// Print amount due (with VAT)
		outputStream << "Amount due: " << aBill.amountDue << '\n';
		return outputStream;
	}

	void Billing::setAmountDue() { amountDue = aDoctor.getFee() * (1 + VAT); }

	double Billing::getAmountDue() const { return amountDue; }

	const Patient& Billing::getPatient() const { return aPatient; }

	const Doctor& Billing::getDoctor() const { return aDoctor; }
	
} // myNamespaceClinic
