/*
Define a class called RainbowColor that is an abstract data type for a color in the visible spectrum 
of light. 
Your class will have a member variable of type int to represent
a color. Include all the following member functions: a constructor to set the color
using the first letter in the name of the color as an argument, a constructor to set the
color using an integer as an argument, a default constructor, an input function that
reads the color as an integer, an input function that outputs the color as an integer,
an output function that outputs the name of the color, and a member function that
returns the next color in the spectrum as a value of type RainbowColor. Embed your
class definition in a test program.
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>

const std::vector<int> COLOR_CODE = { 0x9400D3, 0x8B00FF, 
							     	 0x0000FF, 0x00FF00, 
									 0xFFFF00, 0xFF7F00, 0xFF0000};
const std::vector<std::string> COLOR = { "Purple", "Violet", 
										 "Blue", "Green", 
										 "Yellow", "Orange", "Red" };

class RainbowColor 
{
public:
	RainbowColor() { colorCode = COLOR_CODE[0]; }	
	RainbowColor(char colorLetter);			
	RainbowColor(int colorNumCode);
	int readColor();
	//  Postcondition: read a valid integer color
	char readColorInt();
	//  Postcondition: read a valid char for color
	std::string getColor() const;
	//  Postcondition: return the name of the color code
	std::string nextColor();
	//  Postcondition: return the name of the next color
private:
	static int getColorCode(char colorLetter);
	int colorCode;
};

void showColors();
//  Postcondition: show the colors code of rainbow 
bool validateCode(char colorInitial);
//  Postcondition: check whether the character is in the menu of colors
bool validateCode(int colorCode);
//  Postcondition: check whether the number is in the menu of colors

int main() 
{
	showColors();
	RainbowColor aColor('p');
	std::cout << aColor.getColor();
	std::cout << '\n';
	return 0;
}


RainbowColor::RainbowColor(const char colorLetter) 
{
	if (validateCode(colorLetter)) 
		colorCode = getColorCode(colorLetter);
	else
		std::cout << "Not a valid code. Retry\n";
}

RainbowColor::RainbowColor(const int colorNumCode)
{
	if (validateCode(colorNumCode))
		colorCode = colorNumCode;
	else
		std::cout << "Not a valid code. Retry\n";
}

int RainbowColor::getColorCode(const char colorLetter)
{
	for (int idx = 0; idx < COLOR.size(); idx++)
	{
		if (std::tolower(COLOR[idx][0]) == std::tolower(colorLetter))
			return (COLOR_CODE[idx]);
	}
	return -1;
}

std::string RainbowColor::getColor() const
{
	for (int idx = 0; idx < COLOR.size(); idx++)
		if (COLOR_CODE[idx] == colorCode)
			return COLOR[idx];
	return "Unknown\n";
}

int RainbowColor::readColor()
{
	// TODO
}

char RainbowColor::readColorInt()
{
	// TODO
}

std::string RainbowColor::nextColor()
{
	// TODO
}

bool validateCode(const char colorInitial)
{
	for (std::string color : COLOR)
		if (std::tolower(color[0]) == std::tolower(colorInitial))
			return true;
	return false;
}

bool validateCode(const int colorCode) 
{
	for (const int color : COLOR_CODE)
		if (color == colorCode)
			return true;
	return false;
}

void showColors() 
{
	std::cout << std::left << std::setw(15) << "Colors" 
			  << std::setw(10) << "Code" << '\n' 
			  << std::string(25, '-') << '\n';
	
	for (int idx = 0; idx < COLOR.size(); idx++)
		std::cout << std::setw(15) << COLOR[idx]
				  << std::setw(10) << COLOR_CODE[idx] << '\n';
}

