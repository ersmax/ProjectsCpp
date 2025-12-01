#include <iostream>
#include <string>
#include <limits>

constexpr int SIZE = 100;

class Point
{
public:
	void setCoordinates(double coordinate1, double coordinate2);
	//   Precondition: coordinate1 and coordinate2 are valid inputs from user
	//   Postcondition: sets x to coordinate1 and y to coordinate2
	double getX() const;
	double getY() const;
	void moveCoordinates(double offsetCoordinate1, double offsetCoordinate2);
	//   Precondition: offsetCoordinate1 and offsetCoordinate2 are valid inputs from user
	//   Postcondition: adds offsetCoordinate1 to x and offsetCoordinate2 to y
	void rotatePoint();
	//   Postcondition: rotates the point 90 degrees counterclockwise around the origin

private:
	double x = 0;
	double y = 0;
};

void askCoordinates(Point points[], int maxSize, int& size);
//  Precondition: points is an array of Point objects of size maxSize	
//  Postcondition: fills the points array with user-provided coordinates

double inputData();
//  Postcondition: returns a valid double input from the user

void showCoordinates(const Point points[], int size);
//  Precondition: points is an array of Point objects of size at least size
//  Postcondition: displays the coordinates of each Point in the points array

void rotate(Point points[], int size);
//  Precondition: points is an array of Point objects of size at least size
//  Postcondition: rotates each Point in the points array 90 degrees counterclockwise around the origin

void move(Point points[], int size, double offsetX, double offsetY);
//  Precondition: points is an array of Point objects of size at least size
//  Postcondition: moves each Point in the points array by offsetX on the x-axis and offsetY on the y-axis


int main( )
{
	Point points[SIZE];
	int size = 0;
	askCoordinates(points, SIZE, size);
	showCoordinates(points, size);
	std::cout << "Rotating 90 degrees\n";
	rotate(points, size);
	showCoordinates(points, size);
	std::cout << "Moving by +10 on x-axis and +1 on y-axis\n";
	move(points, size, 10, 1);
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

void rotate(Point points[], const int size)
{
	for (int idx = 0; idx < size; ++idx)
		points[idx].rotatePoint();
}

void move(Point points[], const int size, const double offsetX, const double offsetY)
{
	for (int idx = 0; idx < size; ++idx)
		points[idx].moveCoordinates(offsetX, offsetY);
}
