#ifndef PAYMENT_14_06_H
#define PAYMENT_14_06_H

#include <iostream>

namespace myNamespacePayment
{
	class Payment
	{
	public:
		Payment();
		Payment(float theAmount);
		float getAmountPayment() const;
		void setAmount(float theAmount);
		static void paymentDetails(std::ostream& outputStream);
		friend std::istream& operator >>(std::istream& inputStream, Payment& aPayment);
		friend std::ostream& operator <<(std::ostream& outputStream, const Payment& aPayment);
	private:
		float amountPayment;
	};

} // myNamespacePayment

#endif // PAYMENT_14_06_H