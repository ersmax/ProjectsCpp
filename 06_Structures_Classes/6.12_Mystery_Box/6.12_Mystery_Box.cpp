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

const std::string PATH = "./06_Structures_Classes/6.12_Mystery_Box/Utilities/Produce.txt";
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
	void setContent(int idx);
	std::string getContent(int idx);
	void output();
private:
	FruitsVegetables box[ITEMS];
	int items = 0;
};

bool processFile(FruitsVegetables produceList[], int maxSize, int& sizeList);
bool openFile(const std::string& pathFile, std::ifstream& inputStream);
void closeFile(std::ifstream& inputStream);
void parseFile(std::ifstream& inputStream, FruitsVegetables produceList[], int maxSize, int& sizeList);
///void randomSelection()


int main( )
{
	BoxOfProduce aBox;
	FruitsVegetables produceList[MAX];
	int sizeList = 0;

	if (!processFile(produceList, MAX, sizeList)) return -1;
	
	for (int idx = 0; idx < sizeList; idx++)
		std::cout << idx + 1 << " " << produceList[idx].getName() << "\n";

	// randomSelection(produceList, sizeList, aBox);

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
