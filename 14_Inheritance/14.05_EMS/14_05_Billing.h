#ifndef BILLING_14_05_H
#define BILLING_14_05_H

#include "../14.03_Doctor/14_03_Doctor.h"
#include "14_05_Patient.h"


namespace myNamespaceClinic
{

	using myNamespaceEmployees::Doctor;
	using myNamespacePeople::Patient;

	class Billing
	{
	public:
		Billing();
		Billing(const Doctor& theDoctor, const std::string& theName = "No name");
        Billing(const Billing& other) = default;
		Billing& operator =(const Billing& other) = default;
		void setAmountDue();
		//   Precondition: doctor fee has been set
		//   Postcondition: amountDue is doctor fee + VAT (22%)
		double getAmountDue() const;
		const Patient& getPatient() const;
		const Doctor& getDoctor() const;
		friend std::istream& operator >>(std::istream& inputStream, Billing& aBill);
		friend std::ostream& operator <<(std::ostream& outputStream, const Billing& aBill);
	private:
		Patient aPatient;
		Doctor aDoctor;
		double amountDue;
	}; 
} // myNamespaceClinic

#endif // BILLING_14_05_H
