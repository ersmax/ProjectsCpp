#include "14_06_Cash_Payment.h"
#include "14_06_Credit_Card_Payment.h"

int main()
{
	using myNamespacePayment::CashPayment;

	const CashPayment aPayment(25.2f);
	std::cout << aPayment;

	CashPayment aPayment2;
	std::cin >> aPayment2;
	std::cout << aPayment2;

	using myNamespacePayment::CreditCardPayment;
	using myNamespaceDate::ExpirationDate;
	ExpirationDate aDate(12, 2030);
	CreditCardPayment aPayment3(30.2f, "Mastercard", "1234567890", aDate);
	std::cout << aPayment3;

	CreditCardPayment aPayment4;
	aPayment4 = aPayment3;
	std::cout << aPayment4;

	CreditCardPayment aPayment5;
	std::cin >> aPayment5;
	std::cout << aPayment5;

	std::cout << '\n';
	return 0;
}