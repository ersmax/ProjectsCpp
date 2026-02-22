/*
Your Community Supported Agriculture (CSA) farm delivers a box of fresh fruits
and vegetables to your house once a week. For this Programming Project, define
the class BoxOfProduce that contains exactly three bundles of fruits or vegetables.
You can represent the fruits or vegetables as an array of type string. Add accessor
and mutator functions to get or set the fruits or vegetables stored in the array. Also
write an output function that displays the complete contents of the box on the
console.
Next, write a main function that creates a BoxOfProduce with three items
randomly selected from this list:
Broccoli
Tomato
Kiwi
Kale
Tomatillo
This list should be stored in a text file that is read in by your program. For now
you can assume that the list contains exactly five types of fruits or vegetables.
Do not worry if your program randomly selects duplicate produce for the three
items. Next, the main function should display the contents of the box and allow
the user to substitute any one of the five possible fruits or vegetables for any of the
fruits or vegetables selected for the box. After the user is done with substitutions
output the final contents of the box to be delivered.

Programming Project 6.12 asked you to write a BoxOfProduce class that stored
three bundles of fruits or vegetables (stored in an array of strings of size 3) to ship
to a customer. Rewrite this class to use a vector instead of an array 
and add appropriate constructors, mutators, and accessors. The class should have a function
to add additional fruits or vegetables to the box so there could be more than three
bundles in one box. The output function should output all items in the box.
Overload the + operator to return a new BoxOfProduce object that combines
the vector contents of both operand BoxOfProduce objects. Test your functions
and + operator from the main function. You do not have to implement the rest
of Programming Project 6.12 for this Programming Project, only the changes to
the BoxOfProduce class.
*/

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
		void addNewItem(const FruitsVegetables& item) { aBox.push_back(item); }
		void changeContent(const int index, const FruitsVegetables& itemSwapped) { aBox[index] = itemSwapped; }
		int getSize() const { return (static_cast<int>(aBox.size())); }
		friend std::ostream& operator <<(std::ostream& outputStream, const BoxOfProduce& box);
	private:
		std::vector<FruitsVegetables> aBox;
		
};

const RepeatedString operator *(const std::string& myString, const int countTimes);
std::ostream& operator <<(std::ostream& outputStream, const RepeatedString& myString);

void processFile(const std::string& filePath, std::vector<FruitsVegetables>& shopList);
BoxOfProduce randomSelection(const std::vector<FruitsVegetables>& shopList);
void showList(const std::vector<FruitsVegetables>& shopList);
bool userWishChange();
void changeItem(const std::vector<FruitsVegetables>& shopList, BoxOfProduce& aBox);
int itemValidation();
char inputValidation();


int main( )
{
	std::vector<FruitsVegetables> shopList;
	processFile(PATH, shopList);
	
	BoxOfProduce box1 = randomSelection(shopList);
	
	showList(shopList);
	std::cout << "Initial box:\n" << box1 << SEPARATOR;
	
	bool userChange = userWishChange();
	while (userChange)
	{
		changeItem(shopList, box1);
		std::cout << SEPARATOR << "Updated box:\n" << box1 << SEPARATOR;
		userChange = userWishChange();
		if (userChange)
		{
			showList(shopList);
			std::cout << box1 << SEPARATOR;
		}
	}
	
	std::cout << '\n';
	return 0;
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
	aBox.changeContent(boxIndex, shopList[listIndex]);
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
