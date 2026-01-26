/*
Define a class called Rectangle that has two member variables of type double to
represent the width and height of a rectangle. Include these member functions:
a constructor to construct the Rectangle class using width and height as arguments, 
a default constructor that initializes both width and height to 5, and a
member function each to set width and height. Also include a member function
that computes the area of the rectangle, and output functions to display the width,
height, and area of the rectangle.
*/


#include <iostream>

class Rectangle
{
public:
	Rectangle() : height(5), width(5) {}
	Rectangle(int widthLength, int heightLength); 
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	void setWidth(int widthLength);
	void setHeight(int heightLength);
private:
	static bool validate(const int length) { return (length >= 0); }
	int height;
	int width;
};

Rectangle::Rectangle(const int widthLength, const int heightLength)
{
	try
	{
		setWidth(widthLength);
		setHeight(heightLength);
	} catch (const std::invalid_argument& e) {
		std::cout << "Error: " << e.what() << '\n';
	}
}

void Rectangle::setWidth(const int widthLength)
{
	if (validate(widthLength))
		width = widthLength;
	else
		throw std::invalid_argument("Invalid number");
}

void Rectangle::setHeight(const int heightLength)
{
	if (validate(heightLength))
		height = heightLength;
	else
		throw std::invalid_argument("Invalid number");
}

int main( )
{
	const Rectangle aRectangle;
	std::cout << "Height: " << aRectangle.getHeight() << '\n'
			  << "Width: " << aRectangle.getWidth() << '\n';
	
	const Rectangle anotherRectangle(10,2);
	std::cout << "Height: " << anotherRectangle.getHeight() << '\n'
			  << "Width: " << anotherRectangle.getWidth() << '\n';

	std::cout << '\n';
	return 0;
}