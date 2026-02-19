#include <iostream>
#include <cstdlib>
#include <cmath>

class Money
{
public:
	Money() : dollars(0), cents(0) {};
	Money(const double amount) : dollars(dollarsPart(amount)), cents(centsPart(amount)) {};
	Money(int theDollars, int theCents);
	Money(const int theDollars) : dollars(theDollars), cents(0) {};
	double getAmount() const { return (dollars + cents * 0.01); }
	int getDollars() const { return dollars; }
	int getCents() const { return cents; }
	const Money percent(int percentFigure) const;
	//   Precondition: percentFigure is between 0 and 100
	//	 Postcondition: returns a percentage of the money amount in the calling object. 
	// For example, if percentFigure is 10, then the value returned is 10% of the amount 
	// of money represented by the calling object.

	friend const Money operator +(const Money& amount1,
								  const Money& amount2);
	//   Precondition: amount1 and amount2 are valid Money objects
	//   Postcondition: returns the sum of amount1 and amount2

	friend const Money operator -(const Money& amount1,
								  const Money& amount2);
	//   Postcondition: returns the difference of amount1 and amount2

	friend bool operator ==(const Money& amount1,
							const Money& amount2);
	//   Postcondition: returns true if amount1 and amount2 are equal amounts of money

	friend bool operator <(const Money& amount1,
						   const Money& amount2);
	//   Postcondition: returns true if amount1 is less than amount2

	friend bool operator <=(const Money& amount1,
							const Money& amount2);
	//   Postcondition: returns true if amount1 is less than or equal to amount2

	friend bool operator >(const Money& amount1,
						  const Money& amount2);
	//   Postcondition: returns true if amount1 is greater than amount2

	friend bool operator >=(const Money& amount1,
							const Money& amount2);
	//   Postcondition: returns true if amount1 is greater than or equal to amount2

	friend const Money operator -(const Money& amount);
	//   Postcondition: returns the negative of amount

	friend std::ostream& operator <<(std::ostream& outputStream,
									 const Money& amount);
	//   Precondition: outputStream is cout, amount is a valid Money object
	//   Postcondition: amount is sent to the output stream in the form $dollars.cents (e.g. $3.45).

	friend std::istream& operator >>(std::istream& inputStream,
									 Money& amount);
	//   Precondition: inputStream is cin, amount is a valid Money object
	//   Postcondition: amount is set to the value read from the input stream. 
	// The input should be in the form $dollars.cents (e.g. $3.45).

private:
	//   A negative amount is represented as negative dollars
	// and negative cents. Eg. -$4.50 is represented as -4 and -50
	int dollars, cents;
	int dollarsPart(const double amount) const { return static_cast<int>(amount); }
	int centsPart(double amount) const;
	int round(double number) const;
};

int main( )
{
	Money yourAmount, myAmount(10, 9);
	std::cout << "Enter amount of money: \n";
	std::cin >> yourAmount;
	std::cout << "Your amount is " << yourAmount << '\n';
	std::cout << "My amount is " << myAmount << '\n';

	if (yourAmount == myAmount)
		std::cout << "We have the same amount\n";
	else
		std::cout << "One of us is richer\n";

	Money ourAmount = myAmount + yourAmount;
	Money diffAmount = myAmount - yourAmount;
	std::cout << yourAmount << " + " << myAmount << " equals " << ourAmount << '\n';
	std::cout << yourAmount << " - " << myAmount << " equals " << diffAmount << '\n';

	std::cout << "The 10% of your amount is: " << yourAmount.percent(10) << '\n';
	std::cout << "The 10% of my amount is: " << myAmount.percent(10) << '\n';

	std::cout << '\n';
	return 0;
}

const Money Money::percent(const int percentFigure) const
{
	const double amountDiscount = (0.01 * percentFigure) * (dollars + cents * 0.01);
	return Money(amountDiscount);
}

const Money operator +(const Money& amount1, const Money& amount2)
{
	const int allCents1 = amount1.cents + amount1.dollars * 100;
	const int allCents2 = amount2.cents + amount2.dollars * 100;
	const int allCents = allCents1 + allCents2;
	const int absAllCents = std::abs(allCents);
	int totDollars = absAllCents / 100;
	int totCents = absAllCents % 100;
	// The % and / can misbehave with negative values
	if (allCents < 0)
	{
		totDollars = -totDollars;
		totCents = -totCents;
	}
	return Money(totDollars, totCents);
}

const Money operator -(const Money& amount1, const Money& amount2)
{
	const int allCents1 = amount1.cents + amount1.dollars * 100;
	const int allCents2 = amount2.cents + amount2.dollars * 100;
	const int allCents = allCents1 - allCents2;
	const int absAllCents = std::abs(allCents);
	int totDollars = absAllCents / 100;
	int totCents = absAllCents % 100;
	// The % and / can misbehave with negative values
	if (allCents < 0)
	{
		totDollars = -totDollars;
		totCents = -totCents;
	}
	return Money(totDollars, totCents);
}

const Money operator -(const Money& amount)
{
	return Money(-amount.dollars, -amount.cents);
}

bool operator ==(const Money& amount1, const Money& amount2)
{
	return ((amount1.dollars == amount2.dollars) &&
			(amount1.cents == amount2.cents));
}

bool operator <(const Money& amount1, const Money& amount2)
{
	return (amount1.dollars < amount2.dollars ||
		(amount1.dollars == amount2.dollars && amount1.cents < amount2.cents));
}

bool operator <=(const Money& amount1, const Money& amount2)
{
	return (amount1.dollars < amount2.dollars ||
		   (amount1.dollars == amount2.dollars && amount1.cents <= amount2.cents));
}

bool operator >(const Money& amount1, const Money& amount2)
{
	return (amount1.dollars > amount2.dollars ||
		   (amount1.dollars == amount2.dollars && amount1.cents > amount2.cents));
}

bool operator >=(const Money& amount1, const Money& amount2)
{
	return (amount1.dollars > amount2.dollars ||
		   (amount1.dollars == amount2.dollars && amount1.cents >= amount2.cents));
}


std::ostream& operator <<(std::ostream& outputStream, const Money& amount)
{
	const int absDollars = std::abs(amount.dollars);
	const int absCents = std::abs(amount.cents);
	if (amount.dollars < 0 || amount.cents < 0)
		outputStream << "-$ ";
	else
		outputStream << "$ ";
	outputStream << absDollars;

	if (absCents >= 10)
		outputStream << "." << absCents;
	else
		outputStream << ".0" << absCents;
	
	return outputStream;
}

std::istream& operator >>(std::istream& inputStream, Money& amount)
{
	char dollarSign;
	inputStream >> dollarSign;
	if (dollarSign != '$')
	{
		std::cout << "No dollar sign in Money input\n";
		std::exit(-1);
	}
	double amountMoney;
	inputStream >> amountMoney;
	amount.dollars = amount.dollarsPart(amountMoney);
	amount.cents = amount.centsPart(amountMoney);
	
	return inputStream;
}

Money::Money(const int theDollars, const int theCents)
{
	if ((theDollars < 0 && theCents > 0) || 
		(theDollars > 0 && theCents < 0))
	{
		std::cout << "Inconsistent money data\n";
		std::exit(-1);
	}
	dollars = theDollars;
	cents = theCents;
}


int Money::centsPart(const double amount) const
{
	const double centsAmount = amount * 100;
	int intCents = round(std::fabs(centsAmount)) % 100;
	if (amount < 0)
		intCents = -intCents;
	return intCents;
}

int Money::round(const double number) const
{
	return static_cast<int>(std::floor(number + 0.5));
}
