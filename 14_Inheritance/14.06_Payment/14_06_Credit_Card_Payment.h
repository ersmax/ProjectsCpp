#ifndef CREDIT_CARD_PAYMENT_14_06_H
#define CREDIT_CARD_PAYMENT_14_06_H

#include "14_06_Payment.h"
#include "14_06_Expiration_Date.h"

namespace myNamespacePayment
{
	using myNamespaceDate::ExpirationDate;

	class CreditCardPayment : public Payment
	{
	public:
		CreditCardPayment();
		CreditCardPayment(	float theAmount,
							const std::string& theCardName,
							const std::string& theCardNumber,
							const ExpirationDate& theExpiration);
		void setCardName(const std::string& theCardName);
		void setCardNumber(const std::string& theCardNumber);
		void setExpiration(const ExpirationDate& theExpirationDate);
		const std::string& getCardName() const;
		const std::string& getCardNumber() const;
		const ExpirationDate& getExpirationDate() const;
		void paymentDetails(std::ostream& outputStream) const;
		friend std::istream& operator >>(std::istream& inputStream, CreditCardPayment& aCard);
		friend std::ostream& operator <<(std::ostream& outputStream, const CreditCardPayment& aCard);
	private:
		std::string cardName;
		std::string cardNumber;
		ExpirationDate expiration;
	};

	
} // myNamespacePayment

#endif // CREDIT_CARD_PAYMENT_14_06_H
