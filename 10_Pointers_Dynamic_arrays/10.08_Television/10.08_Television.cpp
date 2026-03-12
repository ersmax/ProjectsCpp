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

class Television;

typedef std::string *StringPtr;
typedef Television *TvPtr;

constexpr const char *MENU =	"a. Add a new tv model\n"
								"b. Print all tv models\n"
								"c. Enter a tv's name to change characteristics\n"
								"d. Enter a tv to remove it\n"
								"e. Exit\n"
								"Enter an option:\n";
constexpr int N_PORTS = 4;
constexpr std::string PORTS[N_PORTS] = {"HDMI", "DISPLAY PORT", "USB A", "USB C"};

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
	friend std::istream& operator >>(std::istream& inputStream, Television& newTelevision);
private:
	std::string displayType;
	double dimension;
	StringPtr connectivitySupport;
	int sizeConnectivity;
	void setDimension(const double inches) { dimension = (inches >= 1.0) ? inches : throw std::invalid_argument("Not a valid size\n"); }

};


bool menu(TvPtr& tvList, int& size);
char inputValidation();
void addTelevision(TvPtr& tvList, int& size);
std::string enterName(std::istream& inputStream);

int main( )
{
	TvPtr tvList = nullptr;
	int size = 0;
	while (menu()) {};

	delete [] tvList;
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

bool menu(TvPtr& tvList, int& size)
{
	std::cout << MENU;
	switch (char answer = inputValidation())
	{
		case 'a':
			addTelevision(tvList, size);
			break;
		case 'b':
			break;
		case 'c':
			break;
		case 'd':
			break;
		case 'e':
			return false;
		default:
			return false;
	}
	return true;
}

std::istream& operator >>(std::istream& inputStream, Television& newTelevision)
{
	const std::string newDisplayType = enterName(inputStream);
	const double newDimension = enterNumber(inputStream);
	StringPtr newPorts = enterPorts(inputStream);
	// TODO
}

std::string enterName(std::istream& inputStream)
{
	std::string name;
	while (true)
	{
		std::cout << "Enter name:\n";
		if (!std::getline(inputStream, name))
		{
			std::cerr << "Not a valid model name\n";
			inputStream.clear();
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (name.empty())
		{
			std::cout << "Model must have a name\n";
			continue;
		}
		return name;
	}
}

//std::string nameValidation()
//{
//	std::string model;
//	while (true)
//	{
//		if (!std::getline(, model))
//	}
//}

void addTelevision(TvPtr& tvList, int& size)
{
	const TvPtr temp = new Television[size + 1];
	for (int idx = 0; idx < size; idx++)
		temp[idx] = tvList[idx];
	
	Television newTelevision;
	std::cout << "Enter new television.\n";
	std::cin >> newTelevision;
	temp[size] = newTelevision;
	size++;
	delete [] tvList;
	tvList = temp;
}

char inputValidation()
{
	char answer;
	while (true)
	{
		if (!(std::cin >> answer))
		{
			std::cout << "Not a valid choice\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		char letter = std::tolower(answer);
		if (letter >= 'a' && letter <= 'e')
			return letter;
		std::cout << "Not a valid choice. Retry\n";
	}
}

