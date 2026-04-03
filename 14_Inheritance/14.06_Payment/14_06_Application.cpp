/*
Define a class named Payment that contains a member variable of type float that
stores the amount of the payment and appropriate accessor and mutator functions.
Also create a member function named paymentDetails that outputs an English
sentence describing the amount of the payment.
Next, define a class named CashPayment that is derived from Payment. This class
should redefine the paymentDetails function to indicate that the payment is in
cash. Include appropriate constructor(s).
Define a class named CreditCardPayment that is derived from Payment. This
class should contain member variables for the name on the card, expiration date,
and credit card number. Include appropriate constructor(s). Finally, redefine the
paymentDetails function to include all credit card information in the printout.
Create a main function that creates at least two CashPayment and two
CreditCardPayment
objects with different values and calls to paymentDetails
for each.
*/

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