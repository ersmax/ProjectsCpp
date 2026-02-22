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
	private:
		std::vector<FruitsVegetables> aBox;
		
};

void processFile(const std::string& filePath, std::vector<FruitsVegetables>& shopList);
void randomSelection(const std::vector<FruitsVegetables>& shopList, BoxOfProduce& aBox);

int main( )
{
	std::vector<FruitsVegetables> shopList;
	processFile(PATH, shopList);
	
	std::cout << '\n';
	return 0;
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
	outputStream << item.name;
	return outputStream;
}
