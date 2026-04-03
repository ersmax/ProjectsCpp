#ifndef EXPIRATION_DATE_14_06_H
#define EXPIRATION_DATE_14_06_H

#include <iostream>

namespace myNamespaceDate
{
	class ExpirationDate
	{
	public:
		ExpirationDate();
		ExpirationDate(int theMonth, int theYear);
		void setExpiration(int theMonth, int theYear);
		int getMonthExpiration() const;
		int getYearExpiration() const;
		friend std::istream& operator >>(std::istream& inputStream, ExpirationDate& theDate);
		friend std::ostream& operator <<(std::ostream& outputStream, const ExpirationDate& theDate);
	private:
		int month;
		int year;
	};
}

#endif // EXPIRATION_DATE_14_06_H
