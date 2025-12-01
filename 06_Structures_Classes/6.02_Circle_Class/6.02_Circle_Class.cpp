#include <iostream>
#include <numbers>

class Circle
{
public:
	void setRadius(double circleRadius);
	//  Precondition: circleRadius is a double value representing the radius of the circle.
	//  Postcondition: sets the radius of the circle to circleRadius if it is non-negative.
	double getRadius() const;
	//  Postcondition: returns the radius of the circle.
	void showResults();
	//  Postcondition: computes and displays the diameter, area, and circumference of the circle.
private:
	double radius = 0;
	double area = 0;
	double diameter = 0;
	double circumference = 0;
	void compute();
	//  Postcondition: computes the diameter, area, and circumference of the circle based on its radius.
};

int main( )
{
	Circle circle1;
	std::cout << "My circle\n";
	circle1.setRadius(25.0);
	std::cout << "Radius: " << circle1.getRadius() << "\n";
	circle1.showResults();
	std::cout << "\n";
	return 0;
}

void Circle::setRadius(const double circleRadius)
{
	if (circleRadius < 0)
	{
		std::cout << "Radius cannot be negative\n";
		return;
	}
	radius = circleRadius;
}

double Circle::getRadius() const
{
	return radius;
}

void Circle::compute()
{
	diameter = radius * 2;
	area = std::numbers::pi * radius * radius;
	circumference = std::numbers::pi * diameter;
}

void Circle::showResults()
{
	compute();
	std::cout << "Diameter: " << diameter << "\n"
			  << "Area: " << area << "\n"
			  << "Circumference: " << circumference << "\n";
}
