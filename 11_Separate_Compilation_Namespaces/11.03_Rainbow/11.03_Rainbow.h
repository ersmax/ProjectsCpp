#ifndef RAINBOW_11_03_H
#define RAINBOW_11_03_H

#include <iostream>
#include <vector>
#include <string>

namespace
{
	const std::vector<int> COLOR_CODE = { 0x9400D3, 0x8B00FF,
										 0x0000FF, 0x00FF00,
										 0xFFFF00, 0xFF7F00, 0xFF0000 };
	const std::vector<std::string> COLOR = { "Purple", "Violet",
											 "Blue", "Green",
											 "Yellow", "Orange", "Red" };
}// unnamed Namespace


namespace myNamespace
{
	class RainbowColor
	{
	public:
		RainbowColor();
		RainbowColor(int colorCode);
		RainbowColor(char colorName);
		int getColorCode() const;
		const std::string& getColorName() const;
		const RainbowColor nextColor() const;
		friend std::istream& operator >>(std::istream& inputStream, RainbowColor& myColor);
	private:
		int color;
	}; 
	
} // myNamespace

#endif

