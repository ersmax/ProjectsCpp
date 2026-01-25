#include <iostream>		// For std::cout, std::cin
#include <string>		
#include <vector>		
#include <iomanip>		// For std::setw
#include <cctype>		// For std::tolower
#include <limits>		// For std::numeric_limits

const std::vector<int> COLOR_CODE = { 0x9400D3, 0x8B00FF,
									 0x0000FF, 0x00FF00,
									 0xFFFF00, 0xFF7F00, 0xFF0000 };
const std::vector<std::string> COLOR = { "Purple", "Violet",
										 "Blue", "Green",
										 "Yellow", "Orange", "Red" };

class RainbowColor
{
public:
	RainbowColor() { colorCode = COLOR_CODE[0]; colors++; }
	RainbowColor(char colorLetter);
	RainbowColor(int colorNumCode);
	static int readColorCode();
	//  Postcondition: read a valid integer color
	static char readColor();
	//  Postcondition: read a valid char for color
	std::string getColor() const;
	//  Postcondition: return the name of the color code
	int outputColorCode() const { return colorCode; }
	RainbowColor nextColor() const;
	//  Postcondition: return the name of the next color
	static int getNumberColors();
	//  Postcondition: return the total number of colors added so far
private:
	static int getColorCode(char colorLetter);
	int colorCode;
	static int colors;
};

int RainbowColor::colors = 0;

void showColors();
//  Postcondition: show the colors code of rainbow 
bool validateCode(char colorInitial);
//  Postcondition: check whether the character is in the menu of colors
bool validateCode(int colorCode);
//  Postcondition: check whether the number is in the menu of colors

int main()
{
	showColors();
	const int codeColor = RainbowColor::readColorCode();
	const char initialColor = RainbowColor::readColor();
	const RainbowColor aColor(codeColor);
	const RainbowColor anotherColor(initialColor);
	std::cout << "First, you entered: " << aColor.getColor() << '\n'
		<< "Next color (object created) is: " << aColor.nextColor().getColor() << '\n';
	std::cout << "Then, you entered: " << anotherColor.getColor() << '\n'
		<< "Next color (object created) created is: " << anotherColor.nextColor().getColor() << '\n';
	std::cout << "The total number of colors added is: " << RainbowColor::getNumberColors() << '\n';
	std::cout << '\n';
	return 0;
}


RainbowColor::RainbowColor(const char colorLetter)
{
	if (validateCode(colorLetter))
	{
		colorCode = getColorCode(colorLetter);
		colors++;
	}
	else
		std::cout << "Not a valid code. Retry\n";
}

RainbowColor::RainbowColor(const int colorNumCode)
{
	if (validateCode(colorNumCode))
	{
		colorCode = colorNumCode;
		colors++;
	}
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
	return "Unknown";
}

int RainbowColor::readColorCode()
{
	int code;
	while (true)
	{
		std::cout << "Enter a valid number code:\n";
		if (!(std::cin >> code))
		{
			std::cout << "Not a valid number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for (const int color : COLOR_CODE)
			if (code == color)
				return code;
		std::cout << "Not a valid code\n";
	}
}

char RainbowColor::readColor()
{
	char code;
	while (true)
	{
		std::cout << "Enter a valid initial for color code:\n";
		if (!(std::cin >> code))
		{
			std::cout << "Not a valid initial\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		for (const std::string& color : COLOR)
			if (std::tolower(code) == std::tolower(color[0]))
				return code;
		std::cout << "Not a valid initial\n";
	}
}

RainbowColor RainbowColor::nextColor() const
{
	int idx = 0;
	while (idx < COLOR_CODE.size() && COLOR_CODE[idx] != colorCode)
		++idx;
	if (idx == COLOR_CODE.size() - 1)
		return RainbowColor(COLOR_CODE[0]);
	return RainbowColor(COLOR_CODE[idx + 1]);
}

int RainbowColor::getNumberColors()
{
	return colors;
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