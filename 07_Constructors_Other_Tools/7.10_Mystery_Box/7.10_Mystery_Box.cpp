/*
 First, complete Programming Project 6.12. Modify the main function with a loop
so that the user determines how many BoxOfProduce objects are created. Each box
should contain three bundles of fruits or vegetables selected randomly from this
list: tomatillo, broccoli, tomato, kiwi, and kale. Add a menu so the user can decide
when to stop creating boxes. The menu should allow the user to make substitutions
for the randomly selected items in a box.

You would like to throw in a free recipe flyer for salsa verde if the box contains
tomatillos. However, there are only 5 recipe flyers. Add a static member variable
to the BoxOfProduce class that counts the number of recipe flyers remaining and
initialize it to 5. Also add a member variable that indicates whether or not the box
contains a recipe flyer and modify the output function to also print “salsa verde
recipe” if the box contains a recipe flyer. Finally, add logic inside the class so that if
the box contains at least one order of tomatillos then it automatically gets a recipe
flyer until all of the recipe flyers are gone. Note that a box should only get one
recipe flyer even if there are multiple orders of tomatillos.
Test your class by creating boxes with tomatillos from your menu until all of the
flyers are gone.
*/


#include <iostream>		// for std::cout, std::cin, std::cerr
#include <fstream>		// for std::ifstream
#include <string>		// for std::string
#include <random>		// for std::random_device, std::mt19937, std::uniform_int_distribution
#include <limits>		// for std::numeric_limits
#include <algorithm>	// for std::max
#include <cctype>		// for std::tolower
#include <filesystem>

const std::string PATH = "../../../../07_Constructors_Other_Tools/7.10_Mystery_Box/Utilities/Produce.txt";
const std::string SEPARATOR = std::string(20, '-') + "\n";
const std::string TOMATILLO = "tomatillo";
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
	BoxOfProduce() { nBox++; }
	void addContent(int idx, const FruitsVegetables& produce);
	//   Precondition: idx is a valid index between 0 and ITEMS - 1, produce is a FruitsVegetables object.
	//   Postcondition: adds produce to the box at index idx, and updates the number of items in the box.

	void changeContent(int idx, const FruitsVegetables& produce);
	//   Precondition: idx is a valid index between 0 and items - 1, produce is a FruitsVegetables object.
	//   Postcondition: changes the content of the box at index idx to produce

	const FruitsVegetables& getItem(int idx) const;
	//   Precondition: idx is a valid index between 0 and items - 1.
	//   Postcondition: returns the item in the box at index idx.

	void output() const;
	//   Postcondition: outputs the contents of the box, 
	// and if the box contains a recipe flyer, also outputs "salsa verde recipe".

	bool isValidIndex(int idx) const;
	//	 Postcondition: returns true if idx is a valid index between 0 and items - 1, false otherwise.

	static int getNumberBox() { return nBox; }
	static int getFlyersLeft() { return tomatilloFlyer; }
private:
	FruitsVegetables box[ITEMS];
	int items = 0;
	bool hasFlyer = false;
	static int nBox;
	static int tomatilloFlyer;
	static bool isTomatillo(const FruitsVegetables& produce);
	//   Postcondition: returns true if the name of produce is "tomatillo" (case-insensitive), false otherwise.

	bool hasTomatillo() const;
	//   Postcondition: returns true if the box contains at least one order of tomatillos, false otherwise.

	void giveFlyer();
	//   Postcondition: if the box does not already have a flyer and there are flyers left, 
	// gives the box a flyer and decrements the number of flyers left.

	void removeFlyer();
	//   Postcondition: if the box has a flyer, removes the flyer from the box 
	// and increments the number of flyers left.
};

int BoxOfProduce::nBox = 0;
int BoxOfProduce::tomatilloFlyer = 5;

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
//   Postcondition: returns a validated integer input from the user, greater than 0.

int addBoxes();
//   Postcondition: return the additional number of boxes input by the user,
// or 0 if the user does not want to add more boxes.

void fillBoxes(FruitsVegetables produceList[], int sizeList, 
			   std::vector<BoxOfProduce>& boxes, int& nBoxes);
//   Precondition: proudeList is an array of FruitsVegetables of size sizeList, 
// boxes is a vector of BoxOfProduce that contains the boxes created so far.
//   Postcondition: fill in each box with random items, 
// and allow the user to substitute items until they are satisfied.

int main()
{
	FruitsVegetables produceList[MAX];
	int sizeList = 0;
	if (!processFile(produceList, MAX, sizeList)) return -1;
	
	std::cout << "How many boxes?\n";
	int nBoxes = itemValidation();
	std::vector<BoxOfProduce> boxes;
	boxes.reserve(nBoxes);

	while (nBoxes > 0)
	{
		fillBoxes(produceList, sizeList, boxes, nBoxes);
		if (nBoxes == 0) {
			nBoxes = addBoxes();
			boxes.reserve(boxes.size() + nBoxes);
		}
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

void BoxOfProduce::giveFlyer()
{
	hasFlyer = true;
	tomatilloFlyer--;
}

void BoxOfProduce::removeFlyer()
{
	hasFlyer = false;
	tomatilloFlyer++;
}

bool BoxOfProduce::isTomatillo(const FruitsVegetables& produce)
{
	std::string name = produce.getName();
	std::transform(name.begin(), name.end(), name.begin(),
				  [](const unsigned char c) {return std::tolower(c); });
	if (name == TOMATILLO)
		return true;
	
	return false;
}

bool BoxOfProduce::hasTomatillo() const
{
	for (int idx = 0; idx < ITEMS; idx++)
	{
		if (isTomatillo(box[idx]))
			return true;
	}
	return false;
}

void BoxOfProduce::addContent(const int idx, const FruitsVegetables& produce)
{
	if (idx < 0 || idx >= ITEMS) {
		std::cerr << "Index out of bounds when adding to box\n";
		return;
	}
	box[idx] = produce;
	items = std::max(items, idx + 1);

	if (!hasFlyer && tomatilloFlyer > 0 && isTomatillo(produce))
		giveFlyer();
}

void BoxOfProduce::changeContent(const int idx, const FruitsVegetables& produce)
{
	if (idx >= 0 && idx < items)
	{
		box[idx] = produce;
		if (hasTomatillo() && !hasFlyer && tomatilloFlyer > 0)
			giveFlyer();
		if (hasFlyer && !hasTomatillo())
			removeFlyer();
	}
	std::cerr << "Element not in the box.\n";
}

const FruitsVegetables& BoxOfProduce::getItem(const int idx) const
{
	if (idx < 0 || idx >= items) {
		static FruitsVegetables empty;
		return empty;
	}
	return box[idx];
}

void BoxOfProduce::output() const
{
	for (int idx = 0; idx < items; ++idx)
		std::cout << idx + 1 << ". " << getItem(idx).getName() << "\n";
	if (hasFlyer)
	{
		std::cout << "salsa verde recipe\n"
				  << "Flyers left: " << tomatilloFlyer << '\n';
	}
}

bool BoxOfProduce::isValidIndex(const int idx) const
{
	return (idx >= 0 && idx < items);
}


void fillBoxes(FruitsVegetables produceList[], const int sizeList,
	std::vector<BoxOfProduce>& boxes, int& nBoxes)
{
	BoxOfProduce aBox;
	randomSelection(produceList, sizeList, aBox);

	while (true)
	{
		showProduceList(produceList, sizeList);
		std::cout << "Box n. " << BoxOfProduce::getNumberBox() << '\n';
		aBox.output();
		if (!substitute(produceList, sizeList, aBox))
			break;
	}
	boxes.push_back(aBox);
	nBoxes--;

}

int addBoxes()
{
	std::cout << "Add more boxes? (y/n)\n";
	char answer = inputValidation();
	answer = static_cast<char>(std::tolower(answer));
	if (answer == 'n')
		return 0;

	std::cout << "How many boxes to add?\n";
	return itemValidation();
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
		if (value < 0) continue;
		break;
	}
	return value;
}

