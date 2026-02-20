/*
Cumulatively modify the example from Display 8.7 as follows.
a. In Display 8.7, replace the private char members first and second with an
array of char of size 100 and a private data member named size.
Provide a default constructor that initializes size to 10 and sets the first 10 of
the char positions to '#'. (This only uses 10 of the possible 100 slots.)
Provide an accessor function that returns the value of the private member size.
Test.
b. Add an operator[] member that returns a char& that allows the user to access
or to set any member of the private data array using a non-negative index that
is less than size.
Test.
c. Add a constructor that takes an int argument, sz, that sets the first sz members of the char array to '#'.
Test.
d. Add a constructor that takes an int argument, sz, and an array of char of size
sz. The constructor should set the first sz members of the private data array to
the sz members of the argument array of char.
Test.
NOTES: When you test, you should test with known good values, with data on
boundaries and with deliberately bad values. You are not required to put checks
for index out of bounds errors in your code, but that would be a nice touch. Error
handling alternatives: Issue an error message then die (that is, call exit(1)) or give
the user another chance to make a correct entry.
*/

#include <iostream>
#include <cstdlib>

constexpr int MAX = 100;

class Char
{
public:
	Char() : size(10) { setMembers(); }
	Char(const int sz) { setMembers(sz); }
	Char(const char myArray[], const int sz) { setMembers(myArray, sz); }
	int getSize() const { return size; }
	void output();
	char& operator [](int idx);
	const char& operator [](int idx) const;
	int askPosition() const;
private:
	char characters[MAX];
	int size;
	void setMembers();
	void setMembers(int chosenSize);
	void setMembers(const char myArray[], int sizeArray);
};

char inputValidation();
int numberValidation();
bool validSize(int number);
bool validSize(const Char& myChar, int index);
int chooseSize();
void buildArray(char myArray[], int size);
void testOperator(Char& myChar);

int main( )
{
	Char aCharacter;
	const Char& constRef = aCharacter;
	std::cout << aCharacter.getSize() << '\n';
	aCharacter.output();

	std::cout << "Changing content:\n";
	const int position = aCharacter.askPosition();
	aCharacter[position] = inputValidation();
	std::cout << "Changed character: " << constRef[position] << '\n';
	aCharacter.output();

	Char anotherCharacter(chooseSize());
	anotherCharacter.output();

	char charArray[MAX];
	const int size = chooseSize();
	buildArray(charArray, size);
	Char anotherCharacter3(charArray, size);
	anotherCharacter3.output();
	
	testOperator(anotherCharacter3);
	anotherCharacter3.output();

	std::cout << '\n';
	return 0;
}

void testOperator(Char& myChar)
{
	std::cout << "Modifying an index element using operator[].\n";
	std::cout << "Current size: " << myChar.getSize() << '\n';
	if (myChar.getSize() <= 0)
	{
		std::cout << "Not sufficient items to test. Ending\n";
		return;
	}
	std::cout << "Enter a valid index to replace\n";
	int idx;
	do
		idx = numberValidation();
	while (!validSize(myChar, idx));

	std::cout << "Old item at index " << idx << ": " << myChar[idx] << '\n';
	myChar[idx] = inputValidation();
	std::cout << "New item at index " << idx << ": " << myChar[idx] << '\n';
}

int chooseSize()
{
	int size;
	do
	{
		std::cout << "Choose a valid size (0-" << MAX << ")\n";
		size = numberValidation();
	} while (!validSize(size));
	return size;
}

bool validSize(const int number)
{
	return (number >= 0 && number <= MAX);
}

bool validSize(const Char& myChar, const int index)
{
	return (index >= 0 && index < myChar.getSize());
}

void buildArray(char myArray[], const int size)
{
	for (int idx = 0; idx < size; idx++)
		myArray[idx] = inputValidation();
}

char inputValidation()
{
	char newChar;
	while (true)
	{
		std::cout << "Enter a valid character:\n";
		if (!(std::cin >> newChar))
		{
			std::cout << "Not a valid character\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return newChar;
	}
}

int numberValidation()
{
	int number;
	while (true)
	{
		if (!(std::cin >> number))
		{
			std::cout << "Not a valid number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return number;
	}
}

char& Char::operator [](int idx)
{
	// ask idx again if original idx is out of bounds
	while (idx < 0 || idx >= size)
		idx = askPosition();
	
	return characters[idx];
}

const char& Char::operator [](const int idx) const
{
	if (idx < 0 || idx >= size)
	{
		std::cerr << "Error: Index out of bounds\n";
		std::exit(1);
	}
	std::cout << "Debug message: calling R-Value\n";
	return characters[idx];
}

int Char::askPosition() const
{
	int idx;
	std::cout << "Enter idx you want to access between 0 and " << size - 1 << ":\n";
	do
	{
		idx = numberValidation();
	} while (idx < 0 || idx >= size);
	return idx;
}

void Char::setMembers()
{
	for (int idx = 0; idx < size; idx++)
		characters[idx] = '#';
}

void Char::setMembers(const int chosenSize)
{
	if (chosenSize < 0 || chosenSize > MAX)
		throw std::invalid_argument("The chosen size is not valid\n");
	size = chosenSize;
	setMembers();
}

void Char::setMembers(const char myArray[], const int sizeArray)
{
	if (sizeArray < 0 || sizeArray > MAX)
		throw std::invalid_argument("The chosen size is not valid\n");
	size = sizeArray;
	for (int idx = 0; idx < sizeArray; idx++)
		characters[idx] = myArray[idx];
}

void Char::output()
{
	for (int idx = 0; idx < size; idx++)
		std::cout << characters[idx] << " ";
	std::cout << '\n';
}
