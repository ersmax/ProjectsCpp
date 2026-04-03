#ifndef CASH_PAYMENT_14_06_H
#define CASH_PAYMENT_14_06_H

#include "14_06_Payment.h"

namespace myNamespacePayment
{
	class CashPayment : public Payment
	{
	public:
		CashPayment();
		CashPayment(float theAmount);
		static void paymentDetails(std::ostream& outputStream);
		friend std::ostream& operator <<(std::ostream& outputStream, const CashPayment& aPayment);
	};


} // myNamespacePayment

#endif // CASH_PAYMENT_14_06_H
