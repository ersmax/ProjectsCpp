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
	Rectangle() : height(5.0), width(5.0) {}
	Rectangle(double widthLength, double heightLength); 
	void setWidth(double widthLength);
	void setHeight(double heightLength);
	double getHeight() const { return height; }
	double getWidth() const { return width; }
private:
	static bool validate(const double length) { return (length >= 0); }
	double height;
	double width;
};

Rectangle::Rectangle(const double widthLength, 
					 const double heightLength) : height(0.0), width(0.0)
{
	setWidth(widthLength);
	setHeight(heightLength);
}

void Rectangle::setWidth(const double widthLength)
{
	if (validate(widthLength))
		width = widthLength;
	else
		throw std::invalid_argument("Invalid width");
}

void Rectangle::setHeight(const double heightLength)
{
	if (validate(heightLength))
		height = heightLength;
	else
		throw std::invalid_argument("Invalid height");
}

int main( )
{
	const Rectangle aRectangle;
	std::cout << "Height: " << aRectangle.getHeight() << '\n'
			  << "Width: " << aRectangle.getWidth() << '\n';
	
	try
	{
		const Rectangle anotherRectangle(10,2);
		std::cout << "Height: " << anotherRectangle.getHeight() << '\n'
			      << "Width: " << anotherRectangle.getWidth() << '\n';
	} catch (const std::invalid_argument& e)
	{
		std::cout << "Error creating rectangle: " << e.what() << '\n';
	}

	std::cout << '\n';
	return 0;
}