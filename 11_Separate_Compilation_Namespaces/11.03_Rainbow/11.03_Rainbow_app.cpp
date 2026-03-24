#include <iomanip>
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




