#ifndef DOCTOR_14_03_H
#define DOCTOR_14_03_H

#include "../14.01_Administrator/14_01_Salaried_Employee.h"
using myNamespaceEmployees::SalariedEmployee;

namespace myNamespaceEmployees
{
	class Doctor : public SalariedEmployee
	{
	public:
		Doctor();
		Doctor(	const std::string& theName, const std::string& theSsn, double theWeeklySalary,
				const std::string& theSpecialty, double theFee);
		Doctor(const Doctor& aDoctor) = default;
		//   Precondition: the default copy constructor is used, 
		// since there are no dynamic variables involved
		const std::string& getSpecialty() const;
		double getFee() const;
		void readData();
		void printCheck() override;
		Doctor& operator =(const Doctor& aDoctor) = default;
		//   Precondition: the default assignment operator is used, 
		// since there are no dynamic variables involved
	private:
		std::string specialty;
		double fee;
	};
}


#endif // DOCTOR_14_03_H

