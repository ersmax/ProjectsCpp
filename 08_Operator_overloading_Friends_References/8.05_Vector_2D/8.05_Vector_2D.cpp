#include <iostream>
#include <limits>

int inputValidation();

class Vector2D
{
public:
	Vector2D() : x(0), y(0) {};
	Vector2D(const int num1) : x(num1), y(0) {};
	Vector2D(const int num1, const int num2) : x(num1), y(num2) {};
	void setX() { x = inputValidation(); }
	void setY() { y = inputValidation(); }
	int getX() const { return x; }
	int getY() const { return y; }
	int operator *(const Vector2D& secondVector) const 
						{ return (x * secondVector.x + y * secondVector.y); }
	friend std::istream& operator >>(std::istream& inputStream, Vector2D& aVector);
	//   Precondition: inputStream contains a vector in the format [x, y], where x and y are integers.
	//   Postcondition: aVector is set to the value read from inputStream.

	friend std::ostream& operator <<(std::ostream& outputStream, const Vector2D& aVector);
	//   Precondition: aVector is a Vector2D object.
	//   Postcondition: aVector is sent to the output stream in the format [x, y], 
	// where x and y are the components of aVector.
private:
	int x;
	int y;
};

int inputValidation();
//   Postcondition: Asks the user for a valid integer and returns it.

Vector2D vectorValidation();
//   Postcondition: Asks the user for a valid vector in the format [x, y] and returns it.

int main( )
{
	std::cout << "Enter a vector of size 2 (format [x, y]:\n";
	const Vector2D aVector = vectorValidation();
	std::cout << "Enter another vector of size 2 (format [x, y]:\n";
	Vector2D aVector2;
	std::cin >> aVector2;

	std::cout << "First vector: " << aVector << '\n';
	std::cout << "Second vector: " << aVector2 << '\n';
	std::cout << "Inner product: " << aVector * aVector2 << '\n';

	std::cout << '\n';
	return 0;
}

std::istream& operator >>(std::istream& inputStream, Vector2D& aVector)
{
	int num1, num2;
	char bracket1, comma, bracket2;
	inputStream >> bracket1 >> num1 >> comma >> num2 >> bracket2;
	if (bracket1 != '[' || comma != ',' || bracket2 != ']')
	{
		// mark the stream as failed
		inputStream.setstate(std::ios::failbit);
		return inputStream;
	}
	aVector.x = num1;
	aVector.y = num2;
	return inputStream;
}

std::ostream& operator <<(std::ostream& outputStream, const Vector2D& aVector)
{
	outputStream << "[" << aVector.x << ", " << aVector.y << "]";
	return outputStream;
}

Vector2D vectorValidation()
{
	Vector2D myVector;
	while (true)
	{
		if (!(std::cin >> myVector))
		{
			std::cout << "Not a valid vector\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return myVector;
	}
}

int inputValidation()
{
	int number;
	while (true)
	{
		std::cout << "Enter a valid number:\n";
		if (!(std::cin >> number))
		{
			std::cout << "Error\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return number;
	}
}