#include "11.03_Rainbow.h"

namespace
{
	bool validateColor(const std::string& colorName);
	//    Precondition: colorName is a string entered by the user. 
	//    Postcondition: Returns true if colorName is in the menu of colors, false otherwise.

	bool validateColor(const int color);
	//    Precondition: color is an integer entered by the user.
	//    Postcondition: Returns true if color is in the menu of colors, false otherwise.

	bool setColorName(const std::string& colorName, int& theColor);
	//    Precondition: colorName is a string entered by the user. theColor is an integer variable.
	//	  Postcondition: If colorName is in the menu of colors, theColor is set to the corresponding color code and true is returned.

	bool setColorCode(int colorCode, int& theColor);
	//    Precondition: colorCode is an integer entered by the user. theColor is an integer variable.
	//    Postcondition: If colorCode is in the menu of colors, theColor is set to colorCode and true is returned.

	std::string nameInput(std::istream& inputStream);
	//    Precondition: inputStream is open and ready for input.
	//    Postcondition: A string is read from inputStream and returned.

	int colorInput(std::istream& inputStream);
	//    Precondition: inputStream is open and ready for input.
	//    Postcondition: An integer is read from inputStream and returned.

	bool setColorName(std::istream& inputStream, int& theColor);
	//    Precondition: inputStream is open and ready for input. theColor is an integer variable.
	//    Postcondition: A string or an integer is read from inputStream. 
	// The input from the user repeats until a valid string or integer is entered (true is returned).
	// If the string or integer entered by the user is in the menu of colors, 
	// theColor is set to the corresponding color code and true is returned. Otherwise, false is returned.

} // unnamed namespace

namespace myNamespace
{
	RainbowColor::RainbowColor() : color(COLOR_CODE[0])
	{ /* Body intentionally left empty */ }

	RainbowColor::RainbowColor(const char colorName) 
	{
		if (!(validateColor(colorName)))
			throw std::invalid_argument("Not a valid color name\n");
		
		for (int idx = 0; idx < COLOR.size(); idx++)
			if (*COLOR[idx].begin() == colorName)
			{
				color = COLOR_CODE[idx];
				break;
			}
	}

	RainbowColor::RainbowColor(const int colorCode)
	{
		if (validateColor(colorCode))
			color = colorCode;
		else
			throw std::invalid_argument("Not a valid color code\n");
	}


	int RainbowColor::getColorCode() const { return color; }

	const std::string& RainbowColor::getColorName() const
	{
		for (int idx = 0; idx < COLOR_CODE.size(); idx++)
			if (COLOR_CODE[idx] == color)
				return COLOR[idx];
		
		static const std::string invalid = "Not a valid color name";
		return invalid;
	}

	const RainbowColor RainbowColor::nextColor() const
	{
		size_t idx = 0;
		while (COLOR_CODE[idx] != color)	idx++;

		if (idx == COLOR_CODE.size() - 1)
			return RainbowColor(COLOR_CODE[0]);

		return RainbowColor(COLOR_CODE[idx + 1]);
	}

	std::istream& operator >>(std::istream& inputStream, RainbowColor& myColor)
	{
		while (!setColorName(inputStream, myColor.color));
		return inputStream;
	}

} // namespace myNamespace

namespace
{
	bool validateColor(const std::string& colorName)
	{
		for (const std::string& color : COLOR)
			if (!color.empty() && color == colorName)
				return true;
		return false;
	}

	bool validateColor(const int color)
	{
		for (const int colorCode : COLOR_CODE)
			if (colorCode == color)
				return true;
		return false;
	}

	bool setColorName(const std::string& colorName, int& theColor)
	{
		if (!validateColor(colorName))	return false;

		for (int idx = 0; idx < COLOR.size(); idx++)
			if (*COLOR[idx].begin() == *colorName.begin())
			{
				theColor = COLOR_CODE[idx];
				return true;
			}

		return false;
	}

	bool setColorCode(const int colorCode, int& theColor)
	{
		if (!validateColor(colorCode))		return false;

		for (const int color : COLOR_CODE)
			if (color == colorCode)
			{
				theColor = colorCode;
				return true;
			}

		return false;
	}

	std::string nameInput(std::istream& inputStream)
	{
		std::string name;
		while (true)
		{
			std::cout << "Enter color name:\n";
			if (!(inputStream >> name))
			{
				std::cout << "Wrong input\n";
				inputStream.clear();
				inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return name;
		}
	}

	int colorInput(std::istream& inputStream)
	{
		int colorCode;
		while (true)
		{
			std::cout << "Enter color code:\n";
			if (!(inputStream >> colorCode))
			{
				std::cout << "Wrong input\n";
				inputStream.clear();
				inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return colorCode;
		}
	}

	bool setColorName(std::istream& inputStream, int& theColor)
	{
		int colorCode;
		std::string colorName;
		char choice;

		do
		{
			std::cout << "Enter color Name ('n') or Color code ('c')?\n";
			std::cin >> choice;
		} while (std::tolower(choice) != 'n' && std::tolower(choice) != 'c');

		switch (choice)
		{
		case 'n':
			colorName = nameInput(inputStream);
			if (setColorName(colorName, theColor))
				break;
			return false;
		case 'c':
			colorCode = colorInput(inputStream);
			if (setColorCode(colorCode, theColor))
				break;
			return false;
		default:
			std::cout << "Not a valid choice\n";
			return false;
		}

		return true;
	}

} // unnamed namespace