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

#include <iomanip>
#include <iostream>
#include <string>

class Television;

typedef std::string *StringPtr;
typedef const std::string *ConstStringPtr;
typedef Television *TvPtr;
typedef const Television *ConstTvPtr;

const std::string MENU =		"a. Add a new tv model\n"
								"b. Enter a standard model and a number of that item\n"
								"c. Print all tv models\n"
								"d. Enter a tv ID to change characteristics\n"
								"e. Enter a tv ID to remove it\n"
								"f. Exit\n"
								"Enter an option:\n";
constexpr int N_PORTS = 4;
const std::string PORTS[N_PORTS] = {"HDMI", "DISPLAY PORT", "USB A", "USB C"};

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
	Television(const Television& secondTv);
	Television& operator =(const Television& secondTv);
	friend std::istream& operator >>(std::istream& inputStream, Television& newTelevision);
	friend std::ostream& operator <<(std::ostream& outputStream, const Television& myTelevision);
private:
	std::string displayType;
	double dimension;
	StringPtr connectivitySupport;
	int sizeConnectivity;
	void setDimension(const double inches) { dimension = (inches >= 1.0) ? inches : throw std::invalid_argument("Not a valid size\n"); }

};


bool menu(TvPtr& tvList, int& size);
char enterInput();
char inputValidation();
void addTelevisions(TvPtr& tvList, int& size, bool multipleTvs);
void showTelevision(const TvPtr& tvList, int size);
void changeCharacteristics(TvPtr& tvList, int& size, bool deleteFlag);
void showId(const ConstTvPtr& tvList, int size);
int selectId(const ConstTvPtr& tvList, int size);
void changeTelevision(const TvPtr& tvList, int size, int id);
void deleteTv(TvPtr& tvList, int& size, const int idDelete);


std::string enterName(std::istream& inputStream, const std::string& prompt = "Enter name:\n");
double enterNumber(std::istream& inputStream, const std::string& prompt = "Enter number:\n");

StringPtr enterPorts(std::istream& inputStream, int& sizeNewPorts);
void printPorts();
bool isDuplicate(const ConstStringPtr& newPorts, const int size, const std::string& port);
bool addPort(StringPtr& newPorts, int& size, const std::string& port);

int main( )
{
	TvPtr tvList = nullptr;
	int size = 0;
	while (menu(tvList, size)) {};

	delete [] tvList;
	std::cout << '\n';
	return 0;
}

Television& Television::operator =(const Television& secondTv)
{
	if (this == &secondTv)	return *this;
	displayType = secondTv.displayType;
	dimension = secondTv.dimension;
	delete [] connectivitySupport;
	sizeConnectivity = secondTv.sizeConnectivity;
	if (sizeConnectivity == 0)
		connectivitySupport = nullptr;
	else
	{
		connectivitySupport = new std::string[sizeConnectivity];
		for (int idx = 0; idx < sizeConnectivity; idx++)
			connectivitySupport[idx] = secondTv.connectivitySupport[idx];
	}
	return *this;
}

Television::Television(const Television& secondTv) :	displayType(secondTv.displayType),
														dimension(secondTv.dimension),
														sizeConnectivity(secondTv.sizeConnectivity)
{
	if (sizeConnectivity == 0)
		connectivitySupport = nullptr;
	else
	{
		connectivitySupport = new std::string[sizeConnectivity];
		for (int idx = 0; idx < sizeConnectivity; idx++)
			connectivitySupport[idx] = secondTv.connectivitySupport[idx];
	}
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
		{
			constexpr bool multiple = false;
			addTelevisions(tvList, size, multiple);
			break;
		}
		case 'b':
		{
			constexpr bool multiple = true;
			addTelevisions(tvList, size, multiple); 
			break;
		}
		case 'c':
			showTelevision(tvList, size);
			break;
		case 'd':
		{
			constexpr bool deleteFlag = false;
			changeCharacteristics(tvList, size, deleteFlag);
			break;
		}
		case 'e':
		{
			constexpr bool deleteFlag = true;
			changeCharacteristics(tvList, size, deleteFlag);
			break;
		}
		case 'f':
			return false;
		default:
			return false;
	}
	return true;
}

void changeCharacteristics(TvPtr& tvList, int& size, const bool deleteFlag)
{
	showId(tvList, size);
	const int id = selectId(tvList, size);
	if (id == -1)
	{
		std::cout << "Empty list\n";
		return;
	}
	if (deleteFlag)
		deleteTv(tvList, size, id);
	else
		changeTelevision(tvList, size, id);
}

void deleteTv(TvPtr& tvList, int& size, const int idDelete)
{
	if (size == 1)
	{
		delete[] tvList;
		tvList = nullptr;
		size = 0;
		std::cout << "Last item deleted. List is empty\n";
		return;
	}
	
	const TvPtr temp = new Television[size - 1];
	for (int idx = 0, idxNew = 0; idx < size; idx++)
		if (idx != idDelete)
			temp[idxNew++] = tvList[idx];

	size--;
	delete [] tvList;
	tvList = temp;
}

void showId(const ConstTvPtr& tvList, const int size)
{
	std::cout << "List IDs:\n";
	for (int idx = 0; idx < size - 1; idx++)
		std::cout << idx + 1 << ", ";
	std::cout << size << '\n';
}

int selectId(const ConstTvPtr& tvList, const int size)
{	
	if (size == 0)	return -1;
	int idSelected = static_cast<int>(enterNumber(std::cin));
	idSelected--;	// 0-base index
	while (idSelected < 0 || idSelected >= size)
	{
		std::cout << "Index not valid. Please choose one of the valid IDs among these:\n";
		showId(tvList, size);
		idSelected = static_cast<int>(enterNumber(std::cin));
		idSelected--;
	}
	return idSelected;
}

void changeTelevision(const TvPtr& tvList, const int size, const int id)
{
	std::cout << std::setw(15) << "ID: " << id + 1 << '\n';
	std::cout << tvList[id];
	Television newTelevision;
	std::cin >> newTelevision;
	tvList[id] = newTelevision;
}

void showTelevision(const TvPtr& tvList, const int size)
{
	for (int idx = 0; idx < size; idx++)
		std::cout << std::setw(15) << "ID: " << idx + 1 << tvList[idx] << '\n';
}

void addTelevisions(TvPtr& tvList, int& size, const bool multipleTvs)
{
	if (multipleTvs)	std::cout << "How many new televisions?\n";

	const int numberTvs = (multipleTvs == true) ? static_cast<int>(enterNumber(std::cin, "")) : 1;
		
	const TvPtr temp = new Television[size + numberTvs];
	for (int idx = 0; idx < size; idx++)
		temp[idx] = tvList[idx];
	
	Television newTelevision;
	std::cout << "Enter new television.\n";
	std::cin >> newTelevision;

	for (int idx = 0; idx < numberTvs; idx++)
	{
		/* Initialize with the overloaded assignment operator (deep copy) */
		// temp[size + idx] = newTelevision;

		/* Explicitly use the copy constructor to create new object (deep copy) */
		const Television copyTv(newTelevision);
		temp[size + idx] = copyTv;
	}
	size += numberTvs;
	delete [] tvList;
	tvList = temp;
}

std::ostream& operator <<(std::ostream& outputStream, const Television& myTelevision)
{
	outputStream << std::setw(18) << "Type: " << myTelevision.displayType << '\n';
	outputStream << std::setw(18) << "Dimension: " << myTelevision.dimension << '\n';
	outputStream << std::setw(18) << "Connectivity: ";
	for (int idx = 0; idx < myTelevision.sizeConnectivity; idx++)
	{
		outputStream << myTelevision.connectivitySupport[idx];
		if (idx != myTelevision.sizeConnectivity - 1)
			outputStream << ", ";
		else
			outputStream << "\n";
	}
	return outputStream;
}

std::istream& operator >>(std::istream& inputStream, Television& newTelevision)
{
	const std::string newDisplayType = enterName(inputStream, "Enter model name:\n");
	const double newDimension = enterNumber(inputStream, "Enter display in inches:\n");
	int sizeNewPorts = 0;
	const StringPtr newPorts = enterPorts(inputStream, sizeNewPorts);
	newTelevision.displayType = newDisplayType;
	newTelevision.dimension = newDimension;
	
	delete [] newTelevision.connectivitySupport;
	newTelevision.connectivitySupport = newPorts;
	newTelevision.sizeConnectivity = sizeNewPorts;
	return inputStream;
}

StringPtr enterPorts(std::istream& inputStream, int& sizeNewPorts)
{
	StringPtr newPorts = nullptr;
	char answer = 'y';
	while (std::tolower(answer) == 'y')
	{
		printPorts();
		std::string port = enterName(inputStream, "Enter port name:\n");
		if (isDuplicate(newPorts, sizeNewPorts, port))	continue;

		if (!addPort(newPorts, sizeNewPorts, port))
			std::cout << "Invalid port. Please enter one of the listed ports as shown\n";
		
		if (sizeNewPorts == N_PORTS)	break;
		
		std::cout << "Add another port? (y/n)\n";
		answer = enterInput();
	}
	return newPorts;
}

bool addPort(StringPtr& newPorts, int& size, const std::string& port)
{
	StringPtr temp = new std::string[size + 1];
	for (int idx = 0; idx < size; idx++)
		temp[idx] = newPorts[idx];

	bool found = false;
	for (int idx = 0; idx < N_PORTS; idx++)
		if (port == PORTS[idx])
		{
			found = true;
			temp[size] = port;
			break;
		}
	if (!found)
	{
		delete [] temp;
		return false;
	}
	size++;
	delete [] newPorts;
	newPorts = temp;
	return true;
}

bool isDuplicate(const ConstStringPtr& newPorts, const int size, const std::string& port)
{
	bool duplicatePort = false;
	for (int idx = 0; idx < size; idx++)
		if (port == newPorts[idx])
		{
			std::cout << "Port already entered. Please enter a different port\n";
			duplicatePort = true;
			break;
		}
	return duplicatePort;
}

void printPorts()
{
	std::cout << "Enter a new port among these\n";
	for (int idx = 0; idx < N_PORTS - 1; idx++)
		std::cout << "\"" << PORTS[idx] << "\", ";
	std::cout << "\"" << PORTS[N_PORTS - 1] << '\n';
}

std::string enterName(std::istream& inputStream, const std::string& prompt)
{
	std::string name;
	while (true)
	{
		std::cout << prompt;
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

double enterNumber(std::istream& inputStream, const std::string& prompt)
{
	double number;
	while (true)
	{
		std::cout << prompt;
		if (!(inputStream >> number))
		{
			std::cerr << "Not a valid number\n";
			inputStream.clear();
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (number < 1.0)
		{
			std::cout << "At least number greater than or equal to 1\n";
			continue;
		}
		return number;
	}
}

char enterInput()
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
		return letter;
	}
}

char inputValidation()
{
	while (true)
	{
		const char letter = std::tolower(enterInput());
		if (letter >= 'a' && letter <= 'f')
			return letter;
		std::cout << "Not a valid choice. Retry\n";
	}
}

