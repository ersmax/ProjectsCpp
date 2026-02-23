#include <iostream>		// for std::cout, std::cin, std::cerr
#include <fstream>		// for std::ifstream
#include <string>		// for std::string
#include <random>		// for std::random_device, std::mt19937, std::uniform_int_distribution
#include <limits>		// for std::numeric_limits
#include <algorithm>	// for std::max
#include <cctype>		// for std::tolower
#include <filesystem>

const std::string PATH = "../../../../08_Operator_overloading_Friends_References/8.09_Box_Produce/Utilities/Produce.txt";
const std::string SEPARATOR = std::string(20, '-') + "\n";
constexpr int BOX_ITEMS = 3;

struct RepeatedString
{
	RepeatedString() = default;
	RepeatedString(const std::string& myString, const int counter) : aString(myString), count(counter) {}
	std::string aString;
	int count;
};

class FruitsVegetables
{
	public:
		FruitsVegetables() {};
		FruitsVegetables(const std::string& itemName) : name(itemName) {};
		friend std::ostream& operator <<(std::ostream& outputStream, const FruitsVegetables& item);
	private:
		std::string name;
};

class BoxOfProduce
{
	public:
		BoxOfProduce() {};
		BoxOfProduce(const std::vector<FruitsVegetables>& newBox) : aBox(newBox) {};
		void addNewItem(const FruitsVegetables& item) { aBox.push_back(item); }
		int getSize() const { return (static_cast<int>(aBox.size())); }
		FruitsVegetables& operator[](const int index) { return aBox[index]; };
		const BoxOfProduce operator +(const BoxOfProduce& secondBox) const;
		//   Postcondition: Returns a new BoxOfProduce object 
		// that combines the vector contents of both operand BoxOfProduce objects.

		friend std::ostream& operator <<(std::ostream& outputStream, const BoxOfProduce& box);
		//   Postcondition: Outputs all items in the box to the outputStream.
	private:
		std::vector<FruitsVegetables> aBox;
		
};

const RepeatedString operator *(const std::string& myString, int countTimes);
//   Precondition: countTimes is a non-negative integer.
//   Postcondition: Returns a RepeatedString object that contains the string myString repeated countTimes times.

std::ostream& operator <<(std::ostream& outputStream, const RepeatedString& myString);
//   Precondition: myString is a RepeatedString object.
//   Postcondition: Outputs the string myString.aString repeated myString.count times to the outputStream.

void processFile(const std::string& filePath, std::vector<FruitsVegetables>& shopList);
//   Precondition: filePath is the path to a text file that contains a list of fruits and vegetables, 
// one per line. shopList is an empty vector of FruitsVegetables objects.
// Postcondition: shopList is filled with FruitsVegetables objects created from the items in the text file.

BoxOfProduce randomSelection(const std::vector<FruitsVegetables>& shopList);
//   Precondition: shopList is a vector of FruitsVegetables objects.
//   Postcondition: Returns a BoxOfProduce object that contains three items randomly selected from shopList.

void showList(const std::vector<FruitsVegetables>& shopList);
//   Postcondition: Outputs the contents of shopList to the console, 
// with each item numbered starting from 1.

bool userWishChange();
//   Postcondition: Prompts the user to enter 'y' or 'n' to indicate whether they wish to change the selection.

void handleChange(const std::vector<FruitsVegetables>& shopList, BoxOfProduce& aBox);
//   Precondition: shopList is a vector of FruitsVegetables objects, and aBox is a BoxOfProduce object.
//   Postcondition: Prompts the user to choose whether to change an item in aBox or add a new item from shopList,
// and updates aBox accordingly.

void changeItem(const std::vector<FruitsVegetables>& shopList, BoxOfProduce& aBox);
//   Postcondition: Prompts the user to select an item in aBox to change and an item in shopList to replace it with,
// and updates aBox accordingly.

void addItem(const std::vector<FruitsVegetables>& shopList, BoxOfProduce& aBox);
//   Postcondition: Prompts the user to select an item in shopList to add to aBox, and updates aBox accordingly.

int itemValidation();
//   Postcondition: Prompts the user to enter an integer and validates the input, returning the integer value.

char inputValidation();
//   Postcondition: Prompts the user to enter a character and validates the input, returning the character value.


int main( )
{
	std::vector<FruitsVegetables> shopList;
	processFile(PATH, shopList);
	
	BoxOfProduce box1 = randomSelection(shopList);
	std::cout << "Initial box:\n" << box1 << SEPARATOR;
	while (userWishChange())
	{
		showList(shopList);
		handleChange(shopList, box1);
		std::cout << SEPARATOR * 2 << "Updated box:\n" << box1 << SEPARATOR * 2;
	}
	BoxOfProduce box2 = randomSelection(shopList);
	std::cout << "Initial box:\n" << box2 << SEPARATOR;
	while (userWishChange())
	{
		showList(shopList);
		handleChange(shopList, box2);
		std::cout << SEPARATOR * 2 << "Updated box:\n" << box2 << SEPARATOR * 2;
	}
	BoxOfProduce aNewBox = box1 + box2;
	// handleChange(shopList, aNewBox);		// can be changed: object is copied to a variable
	// handleChange(shopList, box1 + box2); // cannot be changed: object is not copied to a variable
	std::cout << "The two boxes together are:\n" << box1 + box2 << SEPARATOR * 2 << '\n';

	std::cout << '\n';
	return 0;
}

const BoxOfProduce BoxOfProduce::operator +(const BoxOfProduce& secondBox) const
{
	std::vector<FruitsVegetables> newBox = aBox;
	newBox.insert(newBox.end(), secondBox.aBox.begin(), secondBox.aBox.end());
	return BoxOfProduce(newBox);
	//for (const FruitsVegetables& item : secondBox.aBox)
	//	newBox.push_back(item);
}

void handleChange(const std::vector<FruitsVegetables>& shopList, BoxOfProduce& aBox)
{
	std::cout << "Change list or add items?\n"
			  << "1. Change box list\n"
			  << "2. Add item\n"
			  << "Enter choice:\n";

	switch (itemValidation())
	{
		case 1: 
			changeItem(shopList, aBox);
			break;
		case 2:
			addItem(shopList, aBox);
			break;
		default:
			std::cout << "Choice not valid\n";
			break;
	}
}

void changeItem(const std::vector<FruitsVegetables>& shopList, BoxOfProduce& aBox)
{
	std::cout << "Enter item in the box to change (1-" << aBox.getSize() << "):\n";
	int boxIndex = itemValidation();
	--boxIndex; // convert to zero index
	if (boxIndex < 0 || boxIndex >= aBox.getSize())
	{
		std::cerr << "Invalid item\n";
		std::cout << SEPARATOR;
		return;
	}
	std::cout << "Enter item in the list to change (1-" << shopList.size() << "):\n";
	int listIndex = itemValidation();
	--listIndex; // convert to zero index
	if (listIndex < 0 || listIndex >= shopList.size())
	{
		std::cerr << "Invalid item\n";
		std::cout << SEPARATOR;
		return;
	}
	aBox[boxIndex] = shopList[listIndex];
}

void addItem(const std::vector<FruitsVegetables>& shopList, BoxOfProduce& aBox)
{
	std::cout << "Enter item in the list to add (1-" << shopList.size() << "):\n";
	int listIndex = itemValidation();
	--listIndex; // convert to zero index
	if (listIndex < 0 || listIndex >= shopList.size())
	{
		std::cerr << "Invalid item\n";
		std::cout << SEPARATOR;
		return;
	}
	aBox.addNewItem(shopList[listIndex]);
}

BoxOfProduce randomSelection(const std::vector<FruitsVegetables>& shopList)
{
	BoxOfProduce aNewBox;
	
	std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<size_t>distribution(0, shopList.size() - 1);
	for (int idx = 0; idx < BOX_ITEMS; idx++)
	{
		const size_t randomIdx = distribution(engine);
		const FruitsVegetables& newProduce = shopList[randomIdx];
		aNewBox.addNewItem(newProduce);	// push_back make a copy
	}
	return aNewBox;
}

void processFile(const std::string& filePath, std::vector<FruitsVegetables>& shopList)
{
	std::ifstream inputStream;
	// Attempt to open file
	inputStream.open(filePath);
	if (!inputStream)
	{
		std::cerr << "Error opening the file\n";
		std::cerr << "Current working directory: " << std::filesystem::current_path() << '\n';
		return;
	}
	// Parse file
	std::string name;
	while (std::getline(inputStream, name))
	{
		if (name.empty())	continue;
		FruitsVegetables newItem(name);
		shopList.push_back(newItem);
	}
	// Close file
	inputStream.close();
}

std::ostream& operator <<(std::ostream& outputStream, const FruitsVegetables& item)
{
	outputStream <<  item.name;
	return outputStream;
}

std::ostream& operator <<(std::ostream& outputStream, const BoxOfProduce& box)
{
	for (int idx = 0; idx < box.aBox.size(); idx++)
		outputStream << idx + 1 << ". "<< box.aBox[idx] << '\n';
	return outputStream;
}

char inputValidation()
{
	char answer;
	while (true)
	{
		if (!(std::cin >> answer))
		{
			std::cout << "Invalid input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}
	return answer;
}

int itemValidation()
{
	int value;
	while (true)
	{
		if (!(std::cin >> value))
		{
			std::cout << "Invalid input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}
	return value;
}

bool userWishChange()
{
	std::cout << "Change selection? (y/n)\n";
	char answer = static_cast<char>(std::tolower(inputValidation()));
	if (answer == 'y') return true;
	return false;
}

void showList(const std::vector<FruitsVegetables>& shopList)
{
	std::cout << "Shop List:\n";
	for (int idx = 0; idx < shopList.size(); idx++)
		std::cout << idx + 1 << ". " << shopList[idx] << "\n";
	std::cout << SEPARATOR;
}

const RepeatedString operator *(const std::string& myString, const int countTimes)
{
	RepeatedString aString = {myString, countTimes};
	return aString;
	return RepeatedString(myString, countTimes); // similar
}

std::ostream& operator <<(std::ostream& outputStream, const RepeatedString& myString)
{
	for (int idx = 0; idx < myString.count; idx++)
		outputStream << myString.aString;
	return outputStream;
}
