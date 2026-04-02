#include <iostream>
#include "14_05_Billing.h"

int main( )
{
	using myNamespaceClinic::Billing;
	using myNamespacePeople::Patient;
	using myNamespaceEmployees::Doctor;
	
	Patient patient1;
	
	std::cout << "Enter patient's data.\n";
	std::cin >> patient1;

	Doctor doctor2;
	doctor2.readData();
	Patient patient2(doctor2);

	Billing aBill(doctor2, patient1.getName());
	std::cout << aBill;

	Billing aBill2;
	std::cin >> aBill2;
	std::cout << aBill2;

	std::cout << "Grand total: " << aBill.getAmountDue() + aBill2.getAmountDue() << '\n';

	std::cout << '\n';
	return 0;
}