#include <iostream>

class Rectangle
{
public:
	Rectangle() : height(5.0), width(5.0) {}
	Rectangle(const double widthLength, const double heightLength) : height(0.0), width(0.0) 
														 { setWidth(widthLength); setHeight(heightLength); }
	void setWidth(double widthLength);
	//  Precondition: widthLength is non-negative
	void setHeight(double heightLength);
	//  Precondition: heightLength is non-negative
	double getHeight() const { return height; }
	double getWidth() const { return width; }
	double getArea() const { return height * width; }
	void displaySides() const;
	void displayArea() const;
private:
	static bool validate(const double length) { return (length >= 0); }
	// Postcondition: return true if length is non-negative
	double height;
	double width;
};

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

void Rectangle::displaySides() const
{
	std::cout << "Height of rectangle: " << height
			  << ", width of rectangle: " << width << '\n';
}

void Rectangle::displayArea() const
{
	std::cout << "Area of rectangle: " << getArea() << '\n';
}

int main( )
{
	const Rectangle aRectangle;
	std::cout << "Height: " << aRectangle.getHeight() << '\n'
			  << "Width: " << aRectangle.getWidth() << '\n';
	
	try
	{
		const Rectangle anotherRectangle(10,2);
		anotherRectangle.displaySides();
		anotherRectangle.displayArea();
	} catch (const std::invalid_argument& e)
	{
		std::cout << "Error creating rectangle: " << e.what() << '\n';
	}

	std::cout << '\n';
	return 0;
}