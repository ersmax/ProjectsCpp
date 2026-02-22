// define NDEBUG        // uncomment this line to disable assertions
#include <iostream>
#include <limits>
#include <cassert>

constexpr int LIMIT = 9999;
constexpr char CHOICES[] = {'a', 's', 'd', 'f', 'z', 'x', 'c', 'v', 'o'};

class Counter
{
public:

	Counter() : limit(LIMIT), current(0) {};
	Counter(const int userLimit) : current(0) { setLimit(userLimit); }
	void incr(int number);
	//  Precondition: number >= 0 and <= 9
	//  Postcondition: increment current by number, unless that would cause an underflow
	// Overflow sets current to limit and set the overflowFlag to true
	
	void decr(int number); 
	//  Precondition: number >= 0 and <= 9
	//  Postcondition: decrement current by number, unless that would cause an underflow.
	// Underflow sets current to 0

	void reset() { current = 0; overflowFlag = false; }
	bool getOverflow() const { return overflowFlag; };
	int getCurrent() const { return current; }
private:
	void setLimit(int userLimit);
	//  Postcondition: sets limit to userLimit if userLimit is between 0 and 9999
	bool overflow(int addend);
	//  Postcondition: returns true if adding addend to current would exceed limit
	bool underflow(const int subtrahend) const { return ((current - subtrahend) < 0); }
	int limit;
	int current;
	bool overflowFlag = false;
};

void showMenu();
//  Postcondition: displays the menu options to the user
char makeChoice();
//  Postcondition: prompts the user to enter a choice and returns the choice
int numberValidation();
//  Postcondition: prompts the user to enter a number between 0 and 9 and returns the number
void menuSubmission(const char& choice, Counter& myCounter);
//  Precondition: choice is a valid menu option, myCounter is a Counter object
//  Postcondition: performs the action corresponding to choice on myCounter

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

void Counter::incr(const int number)
{
	assert(number >= 0 && number <= 9);
	if (overflow(number)) return; 
	current += number;
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
	if (number == 0)		return;
	if (underflow(number))	current = 0; 
	else					current -= number;
	if (current < limit)	overflowFlag = false;
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

int numberValidation()
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
				myCounter.incr(numberValidation() * 1);
				break;
			case 's':
				myCounter.incr(numberValidation() * 10);
				break;
			case 'd':
				myCounter.incr(numberValidation() * 100);
				break;
			case 'f':
				myCounter.incr(numberValidation() * 1000);
				break;
			case 'z':
				myCounter.decr(numberValidation() * 1);
				break;
			case 'x':
				myCounter.decr(numberValidation() * 10);
				break;
			case 'c':
				myCounter.decr(numberValidation() * 100);
				break;
			case 'v':
				myCounter.decr(numberValidation() * 1000);
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
