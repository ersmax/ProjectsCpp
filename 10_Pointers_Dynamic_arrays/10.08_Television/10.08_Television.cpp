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
	//   Postcondition: The calling object has been assigned the values of the secondTv object. 
	// A deep copy is performed for the dynamic array.

	friend std::istream& operator >>(std::istream& inputStream, Television& newTelevision);
	//   Precondition: The input stream is open and ready for reading. 
	// The newTelevision object is passed by reference and will be modified by the function.
	//   Postcondition: The function reads the display type, dimension, and connectivity support from the input stream 
	// and assigns them to the newTelevision object.

	friend std::ostream& operator <<(std::ostream& outputStream, const Television& myTelevision);
	//   Precondition: The output stream is open and ready for writing. 
	// The myTelevision object is passed by reference and will not be modified by the function.
	//   Postcondition: The function writes the display type, dimension, and connectivity support of the myTelevision object
	// to the output stream in a formatted manner.

private:
	std::string displayType;
	double dimension;
	StringPtr connectivitySupport;
	int sizeConnectivity;
	void setDimension(const double inches) { dimension = (inches >= 1.0) ? inches : throw std::invalid_argument("Not a valid size\n"); }
};


bool menu(TvPtr& tvList, int& size);
//   Precondition: The tvList pointer is initialized to nullptr and size is initialized to 0.
//   Postcondition: The function displays a menu of options to the user and processes the user's input to perform various operations on the tvList.

char inputValidation();
//   Postcondition: The function continuously prompts the user for input until a valid character (between 'a' and 'f') is entered, 
// and returns the valid character. Used to ensure that the user selects a valid option from the menu.

char enterInput();
//   Postcondition: The function reads a single character input from the user, validates it, and returns the lowercase version of the character.

void addTelevisions(TvPtr& tvList, int& size, bool multipleTvs);
//   Precondition: The tvList pointer is initialized to nullptr and size is initialized to 0. 
// multipleTvs is a boolean that indicates whether the user wants to add multiple televisions or just one.
//   Postcondition: The function prompts the user to enter the details of a new television (or multiple televisions if multipleTvs is true),
// creates new Television objects using the copy constructor, and adds them to the tvList. The size variable is updated accordingly.

void showTelevision(const TvPtr& tvList, int size);
//   Postcondition: The function iterates through the tvList and prints the details of each television to the console in a formatted manner.

void changeCharacteristics(TvPtr& tvList, int& size, bool deleteFlag);
//   Precondition: The tvList pointer is initialized to nullptr and size is initialized to 0. 
// deleteFlag is a boolean that indicates whether the user wants to change the characteristics of a television or delete
//   Postcondition: The function displays the IDs of the televisions in the tvList, 
// prompts the user to select a television by its ID, and either changes the characteristics of the selected television (if deleteFlag is false) 
// or deletes the selected television from the list (if deleteFlag is true). The size variable is updated accordingly if a television is deleted.

void showId(const ConstTvPtr& tvList, int size);
//   Postcondition: The function iterates through the tvList and prints the IDs (1-based index) of each television to the console.

int selectId(const ConstTvPtr& tvList, int size);
//   Postcondition: The function prompts the user to enter a television ID, validates the input, 
// and returns the selected ID (0-based index) if it is valid.

void changeTelevision(const TvPtr& tvList, int size, int id);
//   Precondition: The tvList pointer is initialized to nullptr and size is initialized to 0. id is a valid index of the tvList.
//   Postcondition: The function displays the details of the television at the specified ID, prompts the user to enter new details for the television,
// and updates the television at the specified ID with the new details.

void deleteTv(TvPtr& tvList, int& size, int idDelete);
//   Precondition: The tvList pointer is initialized to nullptr and size is initialized to 0. idDelete is a valid index of the tvList.
//   Postcondition: The function deletes the television at the specified ID from the tvList, updates the size variable accordingly,
// and handles the case when the last television is deleted, resulting in an empty list.

std::string enterName(std::istream& inputStream, const std::string& prompt = "Enter name:\n");
//   Precondition: The inputStream is open and ready for reading. The prompt is a string that will be displayed to the user when asking for input.
//   Postcondition: The function prompts the user with the provided prompt, reads a line of input from the user, 
// validates it, and returns the input as a string.

double enterNumber(std::istream& inputStream, const std::string& prompt = "Enter number:\n");
//   Precondition: The inputStream is open and ready for reading. The prompt is a string that will be displayed to the user when asking for input.
//   Postcondition: The function prompts the user with the provided prompt, reads a number from the user, validates it, and returns the number as a double.

StringPtr enterPorts(std::istream& inputStream, int& sizeNewPorts);
//   Precondition: The inputStream is open and ready for reading. sizeNewPorts is initialized to 0.
//   Postcondition: The function prompts the user to enter port names, validates the input, 
// and returns a dynamic array of strings containing the entered port names.

void printPorts();
//   Precondition: Helper function of enterPorts.
//   Postcondition: The function prints the list of valid port names to the console.

bool isDuplicate(const ConstStringPtr& newPorts, int size, const std::string& port);
//   Precondition: Helper function of enterPorts.
// newPorts is a dynamic array of strings containing the currently entered port names, 
// size is the number of ports in the array, and port is the new port name to be checked for duplication.
//   Postcondition: The function checks if the provided port name already exists in the newPorts array and returns true if it is a duplicate,
// or false if it is not a duplicate.

bool addPort(StringPtr& newPorts, int& size, const std::string& port);
//   Precondition: Helper function of enterPorts.
//   Postcondition: The function checks if the provided port name is valid (exists in the predefined list of ports), 
// and if it is valid, adds it to the newPorts array, updates the size variable accordingly, and returns true. 
// If the port name is not valid, the function returns false and does not modify the newPorts array or size variable.

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

