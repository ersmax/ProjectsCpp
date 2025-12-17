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
*/

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <limits>
#include <algorithm>
#include <cctype>

const std::string PATH = "./06_Structures_Classes/6.12_Mystery_Box/Utilities/Produce.txt";
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
bool openFile(const std::string& pathFile, std::ifstream& inputStream);
void closeFile(std::ifstream& inputStream);
void parseFile(std::ifstream& inputStream, FruitsVegetables produceList[], int maxSize, int& sizeList);
void randomSelection(const FruitsVegetables produceList[], int sizeList, BoxOfProduce& box);
void showProduceList(const FruitsVegetables produceList[], int sizeList);
bool substitute(const FruitsVegetables produceList[], int sizeList, BoxOfProduce& box);
char inputValidation();
int itemValidation();


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
		std::cerr << "Error opening the file\n";
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
