#include "14_06_Payment.h"
#include "14_06_Validation.h"

namespace myNamespacePayment
{
	Payment::Payment() : amountPayment(0)
	{ /* Body intentionally left empty */ }

	Payment::Payment(const float theAmount)
	{
		if (theAmount < 0.0)
			throw std::invalid_argument("Amount should be positive\n");
		setAmount(theAmount);
	}

	void Payment::setAmount(const float theAmount)
	{
		if (theAmount < 0.0)
		{
			std::cout << "Amount should be positive\n";
			return;
		}
		amountPayment = theAmount;
	}

	float Payment::getAmountPayment() const { return amountPayment; }

	std::istream& operator >>(std::istream& inputStream, Payment& aPayment)
	{
		using myNamespaceValidation::readNumber;
		do
		{
			std::cout << "Enter amount of payment:\n";
			readNumber(inputStream, aPayment.amountPayment);
			if (aPayment.amountPayment < 0.0)	std::cout << "Amount should be positive\n";
		} while (aPayment.amountPayment < 0.0);
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const Payment& aPayment)
	{
		outputStream << "The amount to pay is: " << aPayment.amountPayment << '\n';
		return outputStream;
	}

	void Payment::paymentDetails(std::ostream& outputStream) 
	{
		throw std::invalid_argument("Payment details CALLED FOR AN UNDIFFERENTIATED PAYMENT\n");
	}

} // myNamespacePayment
