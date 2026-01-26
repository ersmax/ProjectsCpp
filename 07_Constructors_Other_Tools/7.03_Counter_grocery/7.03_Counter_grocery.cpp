
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
	Counter() : limit(LIMIT), current(0) {};
	Counter(const int userLimit) : current(0) { setLimit(userLimit); }
	void incr(const int number)	{ if (overflow(number)) return; current += number; }
	void decr(int number); 
	void reset() { current = 0; overflowFlag = false; }
	bool getOverflow() const { return overflowFlag; };
	int getCurrent() const { return current; }
private:
	void setLimit(int userLimit);
	bool overflow(int addend);
	bool underflow(const int subtrahend) const { return ((current - subtrahend) < 0); }
	int limit;
	int current;
	bool overflowFlag = false;
};

void showMenu();
char makeChoice();
int inputValidation();
void menuSubmission(const char& choice, Counter& myCounter);

int main()
{
	char answer;
	Counter aCounter, anotherCounter(4999);
	do
	{
		showMenu();
		std::cout << "Counter 1 current value: " << aCounter.getCurrent() << '\n';
		const char choice1 = makeChoice();
		menuSubmission(choice1, aCounter);
		std::cout << "Counter 1 new value: " << aCounter.getCurrent() << '\n';

		std::cout << "Counter 2 current value: " << anotherCounter.getCurrent() << '\n';
		const char choice2 = makeChoice();
		menuSubmission(choice2, anotherCounter);
		std::cout << "Counter 2 new value: " << anotherCounter.getCurrent() << '\n';

		std::cout << "Exit? (y/n)\n";
		std::cin >> answer;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (answer != 'y');

	std::cout << '\n';
	return 0;
}

bool Counter::overflow(const int addend)
{
	 if ((current + addend) > limit)
	 {
		current = limit;
		overflowFlag = true;
		return true;
	 }
	 return false;
}

void Counter::setLimit(const int userLimit)
{
	if ((userLimit >= 0) && (userLimit <= 9999))
		limit = userLimit;
	else
		throw std::invalid_argument("Limit must be between 0 and 9999");
}

void Counter::decr(const int number)
{
	if (number == 0)	return;
	if (underflow(number)) 
		current = 0; 
	else 
		current -= number;
	if (current < limit)
		overflowFlag = false;
}

void showMenu()
{
	std::cout	<< "Menu\n"
				<< "a) Increment cents\n"
				<< "s) Increment tens of cents\n"
				<< "d) Increment dollars\n"
				<< "f) Increment tens of dollars\n"
				<< "z) Decrement cents\n"
				<< "x) Decrement tens of cents\n"
				<< "c) Decrement dollars\n"
				<< "v) Decrement tens of dollars\n"
				<< "o) Show overflow\n";
}

char makeChoice()
{
	char input;
	while (true)
	{
		std::cout << "Enter a choice: ('e' to exit)\n";
		if (!(std::cin >> input))
		{
			std::cout << "Not a proper choice\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (input == 'e') return input;
		
		for (const char& choice : CHOICES)
			if (choice == input)
				return input;
		
		std::cout << "Not a valid choice.\n";
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
				myCounter.incr(inputValidation() * 1);
				break;
			case 's':
				myCounter.incr(inputValidation() * 10);
				break;
			case 'd':
				myCounter.incr(inputValidation() * 100);
				break;
			case 'f':
				myCounter.incr(inputValidation() * 1000);
				break;
			case 'z':
				myCounter.decr(inputValidation() * 1);
				break;
			case 'x':
				myCounter.decr(inputValidation() * 10);
				break;
			case 'c':
				myCounter.decr(inputValidation() * 100);
				break;
			case 'v':
				myCounter.decr(inputValidation() * 1000);
				break;
			case 'o':
				{
				if (myCounter.getOverflow())
					std::cout << "Overflow\n";
				else
					std::cout << "No overflow\n";
				break;
				}
			default:
				std::cout << "No choice\n";
				break;
		}
	}
