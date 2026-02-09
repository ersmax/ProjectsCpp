#include <iostream>		// for std::cout, std::cin, std::cerr
#include <fstream>		// for std::ifstream
#include <string>		// for std::string
#include <random>		// for std::random_device, std::mt19937, std::uniform_int_distribution
#include <limits>		// for std::numeric_limits
#include <algorithm>	// for std::max
#include <cctype>		// for std::tolower
#include <filesystem>

const std::string PATH = "../../../../06_Structures_Classes/6.12_Mystery_Box/Utilities/Produce.txt";
const std::string SEPARATOR = std::string(20, '-') + "\n";
constexpr int ITEMS = 3;
constexpr int MAX = 1000;

class FruitsVegetables
{
public:
	void setName(const std::string& nameFruitVegetable);
	std::string getName() const;
private:
	std::string name;
};

class BoxOfProduce
{
public:
	void addContent(int idx, const FruitsVegetables& produce);
	bool changeContent(int idx, const FruitsVegetables& produce);
    const FruitsVegetables& getItem(int idx) const;
	void output();
	bool isValidIndex(int idx) const;
private:
	FruitsVegetables box[ITEMS];
	int items = 0;
};

bool processFile(FruitsVegetables produceList[], int maxSize, int& sizeList);
//   Precondition: produceList is an array of FruitsVegetables of size maxSize.
//   Postcondition: produceList is filled with the data read from the file, 
// and sizeList contains the number of items read.

bool openFile(const std::string& pathFile, std::ifstream& inputStream);
//   Precondition: pathFile is the path to the file to be opened.
//   Postcondition: inputStream is associated with the opened file.

void closeFile(std::ifstream& inputStream);
//   Precondition: inputStream is associated with an open file.
//   Postcondition: inputStream is closed.

void parseFile(std::ifstream& inputStream, 
			   FruitsVegetables produceList[], int maxSize, int& sizeList);
//   Precondition: inputStream is associated with an open file, 
// produceList is an array of FruitsVegetables of size maxSize.
//   Postcondition: produceList is filled with the data read from the file,
// and sizeList contains the number of items read.

void randomSelection(const FruitsVegetables produceList[], int sizeList, BoxOfProduce& box);
//   Precondition: produceList is an array of FruitsVegetables of size sizeList.
//   Postcondition: box is filled with ITEMS randomly selected items from produceList.

void showProduceList(const FruitsVegetables produceList[], int sizeList);
//   Precondition: produceList is an array of FruitsVegetables of size sizeList.
//   Postcondition: The contents of produceList are displayed on the console.

bool substitute(const FruitsVegetables produceList[], int sizeList, BoxOfProduce& box);
//   Precondition: produceList is an array of FruitsVegetables of size sizeList, box is a BoxOfProduce.
//   Postcondition: The user is prompted to substitute items in the box.

char inputValidation();
//   Postcondition: returns a validated character input from the user.

int itemValidation();
//   Postcondition: returns a validated integer input from the user.


int main( )
{
	BoxOfProduce aBox;
	FruitsVegetables produceList[MAX];
	int sizeList = 0;

	if (!processFile(produceList, MAX, sizeList)) return -1;
	randomSelection(produceList, sizeList, aBox);
	
	while (true)
	{
		showProduceList(produceList, sizeList);
		aBox.output();
		if (!substitute(produceList, sizeList, aBox))
			break;
	}
	std::cout << "\n";
	return 0;
}

void FruitsVegetables::setName(const std::string& nameFruitVegetable)
{
	name = nameFruitVegetable;
}

std::string FruitsVegetables::getName() const
{
	return name;
}

void BoxOfProduce::addContent(const int idx, const FruitsVegetables& produce)
{
    if (idx < 0 || idx >= ITEMS) {
        std::cerr << "Index out of bounds when adding to box\n";
        return;
    }
    box[idx] = produce;
    items = std::max(items, idx + 1);
}

bool BoxOfProduce::changeContent(const int idx, const FruitsVegetables& produce)
{
    if (idx >= 0 && idx < items)
	{
		box[idx] = produce;
		return true;
	}
	std::cerr << "Element not in the box\n";
	return false;
}

const FruitsVegetables& BoxOfProduce::getItem(const int idx) const
{
    if (idx < 0 || idx >= items) {
        static FruitsVegetables empty;
        return empty;
    }
    return box[idx];
}

void BoxOfProduce::output()
{
	for (int idx = 0; idx < items; ++idx)
		std::cout << idx + 1 << ". " << getItem(idx).getName() << "\n";
}

bool BoxOfProduce::isValidIndex(int idx) const
{
	return (idx >= 0 && idx < items);
}

bool processFile(FruitsVegetables produceList[], const int maxSize, int& sizeList)
{
	std::ifstream inputStream;
	if (!openFile(PATH, inputStream)) {
		std::cerr << "Error opening the file: " << PATH << "\n";
		std::cerr << "Current working directory: " << std::filesystem::current_path() << "\n";
		return false;
	}
	parseFile(inputStream, produceList, maxSize, sizeList);
	closeFile(inputStream);
	return true;
}

bool openFile(const std::string& pathFile, std::ifstream& inputStream)
{
	inputStream.open(pathFile);
	if (!inputStream) return false;
	return true;
}

void closeFile(std::ifstream& inputStream)
{
	inputStream.close();
}

void parseFile(std::ifstream& inputStream, FruitsVegetables produceList[], const int maxSize, int& sizeList)
{
	sizeList = 0;
	std::string name;
	while (std::getline(inputStream, name) && sizeList < maxSize)
	{
		if (name.empty()) continue;
		produceList[sizeList++].setName(name);
	}
}

void randomSelection(const FruitsVegetables produceList[], const int sizeList, BoxOfProduce& box)
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
	for (int idx = 0; idx < ITEMS; ++idx)
	{
		std::uniform_int_distribution<int>distribution(0, sizeList - 1);
		const int randomIdx = distribution(engine);
        const FruitsVegetables& produce = produceList[randomIdx];
		box.addContent(idx, produce);
	}
}

void showProduceList(const FruitsVegetables produceList[], const int sizeList)
{
	std::cout << "Current items on shop:\n";
	for (int idx = 0; idx < sizeList; idx++)
		std::cout << idx + 1 << " " << produceList[idx].getName() << "\n";
	std::cout << SEPARATOR;
}

bool substitute(const FruitsVegetables produceList[], const int sizeList, BoxOfProduce& box)
{
	std::cout << "Do you want to change items in the box (y/n)? \n";
	char answer = inputValidation();
	answer = static_cast<char>(std::tolower(answer));
	if (answer == 'n')	
		return false;
	
	int boxItem;
	std::cout << "Enter item in the box to change? (1-" << ITEMS << ")\n";
	boxItem = itemValidation();
	--boxItem;	// convert to zero-index
	if (!box.isValidIndex(boxItem))
	{
		std::cerr << "Invalid box item\n";
		std::cout << SEPARATOR;
		return true;
	}
	
	int listItem;
	std::cout << "Enter item in the list desired: (1-" << sizeList << ")\n";
	listItem = itemValidation();
	--listItem;
	if (listItem >= 0 && listItem < sizeList)
		box.changeContent(boxItem, produceList[listItem]);
	else
	{
		std::cerr << "Item not present in the list.\n";
		std::cout << SEPARATOR;		
	}

	return true;
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
