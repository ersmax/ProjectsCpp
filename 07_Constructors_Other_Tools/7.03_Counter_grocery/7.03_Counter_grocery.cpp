
	//My mother always took a little red counter to the grocery store. The counter was
	//used to keep tally of the amount of money she would have spent so far on that visit
	//to the store if she bought everything in the basket. The counter had a four-digit
	//display, increment buttons for each digit, and a reset button. An overflow indicator
	//came up red if more money was entered than the $99.99 it would register. (This
	//was a long time ago.)

	//Write and implement the member functions of a class Counter that simulates and
	//slightly generalizes the behavior of this grocery store counter. The constructor should
	//create a Counter object that can count up to the constructor’s argument. That is,
	//Counter(9999) should provide a counter that can count up to 9999.
	//A newly constructed counter displays a reading of 0. The member function void reset( );
	//sets the counter’s number to 0. The member function void incr1( ); increments
	//the units digits by 1, void incr10( ); increments the tens digit by 1, and void
	//incr100( ); and void incr1000( ); increment the next two digits, respectively.
	//Accounting for any carrying when you increment should require no further action than
	//adding an appropriate number to the private data member. A member function bool
	//overflow( ); detects overflow. (Overflow is the result of incrementing the counter’s
	//private data member beyond the maximum entered at counter construction.)

	//Use this class to provide a simulation of my mother’s little red clicker. Even though
	//the display is an integer, in the simulation, the rightmost (lower order) two digits
	//are always thought of as cents and tens of cents, the next digit is dollars, and the
	//fourth digit is tens of dollars.

	//Provide keys for cents, dimes, dollars, and tens of dollars. Unfortunately, no choice of
	//keys seems particularly mnemonic. One choice is to use the keys asdfo: a for cents,
	//followed by a digit 1 to 9; s for dimes, followed by a digit 1 to 9; d for dollars, followed
	//by a digit 1 to 9; and f for tens of dollars, again followed by a digit 1 to 9. Each entry
	//(one of asdf followed by 1 to 9) is followed by pressing the Return key. Any overflow
	//is reported after each operation. Overflow can be requested by pressing the o key.


#include <iostream>

constexpr int LIMIT = 9999;
constexpr char CHOICES[] = {'a', 's', 'd', 'f', 'z', 'x', 'c', 'v', 'o'};

class Counter
{
public:
	Counter() : limit(LIMIT) {};
	Counter(const int userLimit) { setLimit(userLimit); }
	void incr1()	{ if (overflow(1)) return; current += 1; }
	void decr1()	{ if (underflow(1)) current = 0; else current -= 1; }
	void incr10()	{ if (overflow(10)) return; current += 10; }
	void decr10()	{ if (underflow(10)) current = 0; else current -= 10; }
	void incr100()	{ if (overflow(100)) return; current += 100; }
	void decr100()	{ if (underflow(100)) current = 0; else current -= 100; }
	void incr1000() { if (overflow(1000)) return; current += 1000; }
	void decr1000() { if (underflow(1000)) current = 0; else current -= 1000; }
	void reset()	{ current = 0; }
	bool getOverflow() const { return overflowFlag; };
private:
	void setLimit(int userLimit);
	bool overflow(int addend);
	bool underflow(const int subtrahend) const { return ((current - subtrahend) < 0); }
	int limit;
	int current;
	bool overflowFlag = false;
};

char makeChoice();
int inputValidation();
void menuSubmission(char choice);

int main()
{
	std::cout << '\n';
	return 0;
}

bool Counter::overflow(const int addend) const
{
	 if ((current + addend) > limit)
	 {
		current = limit;
		overflowFlag = true;
	 }
}

void Counter::setLimit(const int userLimit)
{
	if ((userLimit >= 0) && (userLimit <= 9999))
	{
		limit = userLimit;
		current = 0;
	}
	else
		throw std::invalid_argument("Limit must be between 0 and 9999");
}

char makeChoice()
{
	char input;
	while (true)
	{
		std::cout << "Enter a choice:\n";
		if (!(std::cin >> input))
		{
			std::cout << "Not a proper choice\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for (const char& choice : CHOICES)
			if (choice == input)
				return input;
		std::cout << "Not a valid choice.\n";
		break;
	}
}

int inputValidation()
{
	int input;
	while (true)
	{
		std::cout << "Enter a valid input (0-9):\n";
		if (!(std::cin >> input))
		{
			std::cout << "Not a proper input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (input >= 0 && input <= 9)
			return input;
		std::cout << "Not a valid input.\n";
	}
}

void menuSubmission(const char& choice, Counter& myCounter)
	{
		switch (choice)
		{
			case 'a':
				myCounter.incr1(inputValidation());
				break;
			case 's':
			case 'd':
			case 'f':
			case 'z':
			case 'x':
			case 'c':
			case 'v':
			case 'o':
		}
	}
