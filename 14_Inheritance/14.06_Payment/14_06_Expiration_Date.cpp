#include "14_06_Expiration_Date.h"
#include "14_06_Validation.h"

namespace
{
	bool validDate(const int aMonth, const int aYear)
	{
		if (aMonth > 0 && aMonth <= 12 && aYear >= 2000 && aYear <= 2100)
			return true;
		return false;
	}
}

namespace myNamespaceDate
{
	ExpirationDate::ExpirationDate() : month(1), year(2000)
	{ /* Body intentionally left empty */ }

	ExpirationDate::ExpirationDate(const int theMonth, const int theYear)
	{
		if (!validDate(theMonth, theYear))
			throw std::invalid_argument("Date not valid\n");
		setExpiration(theMonth, theYear);
	}

	void ExpirationDate::setExpiration(const int theMonth, const int theYear)
	{
		if (!validDate(theMonth, theYear))
		{
			std::cout << "Date not valid\n";
			return;
		}
		month = theMonth;
		year = theYear;
	}

	int ExpirationDate::getMonthExpiration() const { return month; }

	int ExpirationDate::getYearExpiration() const { return year; }

	std::istream& operator >>(std::istream& inputStream, ExpirationDate& theDate)
	{
		using myNamespaceValidation::readNumber;
		do
		{
			std::cout << "Enter expiration date of the credit card.\n";
			std::cout << "Enter month:\n";
			readNumber(inputStream, theDate.month);
			std::cout << "Enter year:\n";
			readNumber(inputStream, theDate.year);
			if (!validDate(theDate.month, theDate.year))
				std::cout << "Not a valid date. Retry\n";
		} while (!validDate(theDate.month, theDate.year));
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const ExpirationDate& theDate)
	{
		outputStream << "Expiration date: " << theDate.month
					 << '/' << theDate.year << '\n';
		return outputStream;
	}
} // myNamespaceDate