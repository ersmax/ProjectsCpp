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
		//   Postcondition: outputStream has been modified to include the details of a cash payment.
		friend std::ostream& operator <<(std::ostream& outputStream, const CashPayment& aPayment);
		//   Precondition: outputStream is open, aPayment is a valid CashPayment object.
		//   Postcondition: outputStream has been modified to include the details of aPayment. 
		// outputStream is returned.
	};


} // myNamespacePayment

#endif // CASH_PAYMENT_14_06_H
