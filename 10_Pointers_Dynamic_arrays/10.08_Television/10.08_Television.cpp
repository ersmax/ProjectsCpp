/*
Create a class called Television that has member variables
displayType – A string that stores the television’s display type
dimension – A variable of type double that stores the dimension
of the television in inches.
connectivitySupport – A dynamic array of strings that stores the different
connectivity modes supported by the television
The class should have mutator and accessor functions to set and get the above
member variables. Include a constructor that takes arguments of type string,
double, and an array of strings to assign the three member variables. Also include
a copy constructor.
Embed your class in a test program that reads the input from the user to set displayType,
dimension, and connectivitySupport values by default for a television.
Your program should then read in input for the number of televisions. Your
program should create as many Television objects as required using the copy
constructor, and ask the user if customization is required for any television. If so,
use the mutator methods to set the values accordingly.
*/

#include <iostream>
#include <string>

typedef std::string *StringPtr;
typedef const std::string *ConstStringPtr;

class Television
{
public:
	Television() : displayType(""), dimension(22.0), connectivitySupport(nullptr), sizeConnectivity(0) {};
	Television(const std::string& name) :	displayType(name), dimension(22.0), 
											connectivitySupport(new std::string[1]{ "HDMI" }), sizeConnectivity(1) {}; 
	Television(const std::string& name, const double inches) :	displayType(name), 
																connectivitySupport(new std::string[1]{ "HDMI" }), sizeConnectivity(1)
																{
																	setDimension(inches);
																}
	Television(const std::string& name, const double inches, const ConstStringPtr connections, int size);
	~Television() { delete [] connectivitySupport; }
private:
	std::string displayType;
	double dimension;
	StringPtr connectivitySupport;
	int sizeConnectivity;
	void setDimension(const double inches) { dimension = (inches >= 1.0) ? inches : throw std::invalid_argument("Not a valid size\n"); }

};

int main( )
{
	std::cout << '\n';
	return 0;
}

Television::Television(const std::string& name, const double inches, const ConstStringPtr connections, const int size) : displayType(name)
{
	setDimension(inches);
	sizeConnectivity = size;
	connectivitySupport = new std::string[sizeConnectivity];
	for (int idx = 0; idx < sizeConnectivity; idx++)
		connectivitySupport[idx] = connections[idx];
}
