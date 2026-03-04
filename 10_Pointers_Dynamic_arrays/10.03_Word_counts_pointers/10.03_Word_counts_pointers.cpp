/*
Write a program that accepts a line of text input from the user and checks if the
number of words counted from both end of the text is equal. Your program should
work by using two pointers. The ‘head’ pointer should be set to the address of the
first character in the string, and the ‘tail’ pointer should be set to the address of the
last character in the string (i.e., the character before the terminating null). The
program should keep incrementing the “head” pointer and keep decrementing
the “tail” pointer until the pointers reach the other end. On finding whitespace
characters while going across the string, increment the word counts and compare
them at the end.
*/

#include <iostream>
#include <string>

typedef const char *CharPtr;  // a pointer to a variable of type char that cannot be changed

int countFront(const std::string& aLine);
//   Postcondition: returns the number of words in aLine by counting from the front of the string.

int countBack(const std::string& aLine);
//   Postcondition: returns the number of words in aLine by counting from the back of the string.

int main( )
{
	std::string line;
	std::getline(std::cin, line);
	std::cout << countFront(line) << '\n'; 
	std::cout << countBack(line) << '\n';

	if (countFront(line) == countBack(line))
		std::cout << "Same # words\n" << countFront(line) << '\n';
	else
		std::cout << "Different # words\n" ;

	if (countFront(" a b a") == countBack(" a b a"))
		std::cout << "Same # words\n" << countFront("a b a") << '\n';
	else
		std::cout << "Different # words\n";

	if (countFront("ab a  ") == countBack("ab a  "))
		std::cout << "Same # words\n" << countFront("ab a  ") << '\n';
	else
		std::cout << "Different # words\n";

	if (countFront("") == countBack(""))
		std::cout << "Same # words\n" << countFront("") << '\n';
	else
		std::cout << "Different # words\n";

	if (countFront(" ") == countBack(" "))
		std::cout << "Same # words\n" << countFront(" ") << '\n';
	else
		std::cout << "Different # words\n";

	std::cout << '\n';
	return 0;
}

int countFront(const std::string& aLine)
{
	int counter = 0;
	CharPtr frontPtr = aLine.c_str();
	//   c_str() returns a pointer to a const C-style (no & address of operator needed)
	// null-terminated string representing the contents of the string. 
	// If the string is empty, &aLine.front() is undefined behavior.

	while (*frontPtr != '\0')
	{
		while (*frontPtr != '\0' && *frontPtr == ' ')
			frontPtr++;
		if (*frontPtr != '\0')
			counter++;
		while (*frontPtr != '\0' && *frontPtr != ' ')
			frontPtr++;
	}
	return counter;
}

int countBack(const std::string& aLine)
{
	if (aLine.empty()) return 0;
	int counter = 0;
	const CharPtr startLine = aLine.c_str();
	CharPtr backPtr = aLine.c_str() + aLine.length() - 1;
	while (backPtr >= startLine)
	{
		// skip spaces
		while (backPtr >= startLine && *backPtr == ' ')
			backPtr--;
		// start of word
		if (backPtr >= startLine)
			counter++;
		// end of word
		while (backPtr >= startLine && *backPtr != ' ')
			backPtr--;
	}
	return counter;
}



