
/*  Programming Project 7.1
 Define a class called RainbowColor that is an abstract data type for a color in the visible
spectrum of light. Your class will have a member variable of type int to represent
a color. Include all the following member functions: a constructor to set the color
using the first letter in the name of the color as an argument, a constructor to set the
color using an integer as an argument, a default constructor, an input function that
reads the color as an integer, an input function that outputs the color as an integer,
an output function that outputs the name of the color, and a member function that
returns the next color in the spectrum as a value of type RainbowColor. Embed your
class definition in a test program.
*/

/*
Extend Programming Project 7.1 from Chapter 7 in which you implemented a RainbowColor
class by placing the class definition and implementation in a namespace,
then providing access to the names in the namespace. Test your code. To provide
access to names in namespaces, you may use local using declarations, such as
using std::cout;
or use local using directives such as
using namespace std;
inside a block, or qualify names using the names of namespaces, such as std::cout.
You may not use global namespace directives such as the following which are not
in a block and apply to the entire file:
using namespace std;
*/

#include <iomanip>
#include <iostream>
#include "11.03_Rainbow.h"


void showColors();

int main( )
{
	showColors();
	using myNamespace::RainbowColor;
	RainbowColor aColor, anotherColor;
	std::cout << "Enter a color:\n";
	std::cin >> aColor;
	std::cout << "Enter another color:\n";
	std::cin >> anotherColor;

	std::cout << "First colour entered: " << aColor.getColorName() << '\n';
	std::cout << "Next colour: " << aColor.nextColor().getColorName() << '\n';
	std::cout << "Second colour entered: " << anotherColor.getColorName() << '\n';
	std::cout << "Next colour: " << anotherColor.nextColor().getColorName() << '\n';

	std::cout << '\n';
	return 0;
}

void showColors()
{
	std::cout << std::left << std::setw(10) << "Color" << std::setw(15) << "Code" << '\n';
	for (int idx = 0; idx < COLOR.size(); idx++)
		std::cout << std::left << std::setw(10) << COLOR[idx] << std::setw(15) << COLOR_CODE[idx] << '\n';
	std::cout << std::string(25, '-') << '\n';
}




