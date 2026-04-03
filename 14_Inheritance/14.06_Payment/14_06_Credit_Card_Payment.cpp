#include "14_06_Credit_Card_Payment.h"
#include "14_06_Validation.h"

namespace 
{
	int digitToInt(const char c) { return (static_cast<int>(c) - static_cast<int>('0')); }

	bool validCardNumber(const std::string& cardNumber)
	{
		for (const char& c : cardNumber)
			if (digitToInt(c) < 0 || digitToInt(c) > 9)
				return false;
		return true;
	}

} // unnamed namespace

namespace myNamespacePayment
{
	CreditCardPayment::CreditCardPayment() : Payment(), 
											cardName("No name"), 
											cardNumber("0000000000000000"),
											expiration(01, 2000)
	{ /* Body intentionally left empty */ }

	CreditCardPayment::CreditCardPayment(	const float theAmount,
											const std::string& theCardName, 
											const std::string& theCardNumber, 
											const ExpirationDate& theExpiration) 
											: Payment(theAmount), cardName(theCardName), expiration(theExpiration)
	{
		if (!validCardNumber(theCardNumber))
			throw std::invalid_argument("Not a valid card number\n");
		setCardNumber(theCardNumber);
	}

	void CreditCardPayment::setCardNumber(const std::string& theCardNumber)
	{
		if (!validCardNumber(theCardNumber))
			std::cout << "Not a valid card number\n";
		cardNumber = theCardNumber;
	}
	
	void CreditCardPayment::setCardName(const std::string& theCardName)
	{
		if (theCardName.empty())
		{
			std::cout << "Card name cannot be empty\n";
			return;
		}
		cardName = theCardName;
	}

	void CreditCardPayment::setExpiration(const ExpirationDate& theExpirationDate) { expiration = theExpirationDate; }

	const std::string& CreditCardPayment::getCardName() const { return cardName; }

	const std::string& CreditCardPayment::getCardNumber() const { return cardNumber; }

	const ExpirationDate& CreditCardPayment::getExpirationDate() const { return expiration; }

	void CreditCardPayment::paymentDetails(std::ostream& outputStream) const
	{
		outputStream << "The payment is made by card. Details:\n";
		outputStream << "Credit card name: " << cardName << '\n';
		outputStream << "Credit card number: " << cardNumber << '\n';
		outputStream << expiration << '\n';
	}

	std::istream& operator >>(std::istream& inputStream, CreditCardPayment& aCard)
	{
		using myNamespaceValidation::readNumber;
		using myNamespaceValidation::readInput;
		inputStream >> dynamic_cast<Payment&>(aCard);
		while (true)
		{
			std::cout << "Enter a valid card name:\n";
			readInput(inputStream, aCard.cardName);
			if (!aCard.cardName.empty())	break;
			std::cout << "Card name cannot be empty\n";
		}
		while (true)
		{
			std::cout << "Enter a valid card number:\n";
			readInput(inputStream, aCard.cardNumber);
			if (validCardNumber(aCard.cardNumber))	break;
			std::cout << "Invalid card number. Retry\n";
		}
		inputStream >> aCard.expiration;
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const CreditCardPayment& aCard)
	{
		outputStream << dynamic_cast<const Payment&>(aCard);
		aCard.paymentDetails(outputStream);
		return outputStream;
	}
} // myNamespacePayment
