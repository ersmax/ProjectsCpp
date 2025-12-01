/*
The type Point is a fairly simple data type, but under another name (the template
class pair) this data type is defined and used in the C++ Standard Template Library,
although you need not know anything about the Standard Template Library
to do this exercise. Write a definition of a class named Point that might be used to
store and manipulate the location of a point in the plane. You will need to declare
and implement the following member functions:
a. A member function set that sets the private data after an object of this class is
created.
b. A member function to move the point by an amount along the vertical and
horizontal directions specified by the first and second arguments.
c. A member function to rotate the point by 90 degrees clockwise around the
origin.
d. Two const inspector functions to retrieve the current coordinates of the point.
Document these functions with appropriate comments. Embed your class in a test
program that requests data for several points from the user, creates the points, then
exercises the member functions.
*/

#include <iostream>
#include <string>

constexpr int SIZE = 100;

class Point
{
public:
	void setCoordinates(double coordinate1, double coordinate2);
	double getX() const;
	double getY() const;
	void moveCoordinates(double offsetCoordinate1, double offsetCoordinate2);
	void rotatePoint();

private:
	double x;
	double y;
};

void askCoordinates(Point points[], int maxSize, int& size);

double inputData();

void showCoordinates(const Point points[], int size);

int main( )
{
	Point points[SIZE];
	int size = 0;
	askCoordinates(points, SIZE, size);
	showCoordinates(points, size);
	
	std::cout << "\n";
	return 0;
}

void Point::setCoordinates(const double coordinate1, const double coordinate2)
{
	x = coordinate1; y = coordinate2;
}

void Point::moveCoordinates(const double offsetCoordinate1, const double offsetCoordinate2)
{
	x += offsetCoordinate1; y += offsetCoordinate2;
}

void Point::rotatePoint()
{
	std::swap(x, y);
	y = -y;
}

double Point::getX() const
{
	return x;
}

double Point::getY() const
{
	return y;
}

void askCoordinates(Point points[], const int maxSize, int& size)
{
	bool stop = false;
	std::string answer;

	while (size < maxSize && !stop)
	{
		std::cout << "Enter coordinate on x-axis:\n";
		const double xValue = inputData();
		std::cout << "Enter coordinate on y-axis:\n";
		const double yValue = inputData();
		points[size++].setCoordinates(xValue, yValue);

		std::cout << "Add more points? (yes/no)\n";
		std::cin >> answer;
		if (answer == "no")  stop = true;
	}
}

double inputData()
{
	double value;
	while (!(std::cin >> value)) {
		std::cout << "Wrong input\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return value;
}

void showCoordinates(const Point points[], const int size)
{
	for (int idx = 0; idx < size; ++idx)
		std::cout << "Point " << idx + 1 << " "
				  << "x-coordinate: " << points[idx].getX()
				  << ", y-coordinate: " << points[idx].getY() << "\n";
}
