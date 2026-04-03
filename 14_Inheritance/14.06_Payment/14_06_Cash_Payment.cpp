#include "14_06_Cash_Payment.h"

namespace myNamespacePayment
{
	CashPayment::CashPayment() : Payment()
	{ /* Body intentionally left empty */ }

	CashPayment::CashPayment(const float theAmount) : Payment(theAmount)
	{ /* Body intentionally left empty */ }

	void CashPayment::paymentDetails(std::ostream& outputStream)
	{
		outputStream << "The payment is in cash\n";
	}

	std::ostream& operator <<(std::ostream& outputStream, const CashPayment& aPayment)
	{
		outputStream << dynamic_cast<const Payment&>(aPayment);
		aPayment.paymentDetails(outputStream);
		return outputStream;
	}
}
