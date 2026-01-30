/*
You operate several hot dog stands distributed throughout town. Define a class
named HotDogStand that has a member variable for the hot dog stand’s ID number 
and a member variable for how many hot dogs the stand sold that day. Create
a constructor that allows a user of the class to initialize both values.
Also create a function named JustSold that increments the number of hot dogs
the stand has sold by one. This function will be invoked each time the stand sells a
hot dog so that you can track the total number of hot dogs sold by the stand. Add
another function that returns the number of hot dogs sold.
Finally, add a static variable that tracks the total number of hot dogs sold by all
hot dog stands and a static function that returns the value in this variable. Write
a main function to test your class with at least three hot dog stands that each sell a
variety of hot dogs.
*/

#include <iostream>
#include <string>

class HotDogStand
{
public:
	HotDogStand() : standID("A" + std::to_string(nextID++)), soldStand(0) {}
	HotDogStand(const std::string& id) : soldStand(0) { setId(id); }
	HotDogStand(const std::string& id, const int soldItems) { setId(id); setSoldItems(soldItems); }
	void justSold() { soldStand++; totalSold++; }
	//  Postcondition: Increments the number of hot dogs sold by this stand and the total sold.
	std::string getId() { return standID; }
	int getSoldStand() const { return soldStand; }
	static int getTotalSold() { return totalSold; };
private:
	void setId(const std::string& id);
	//  Postcondition: Sets the stand ID to id if valid; otherwise, throws an exception.
	void setSoldItems(int soldItems);
	//  Postcondition: Sets the number of hot dogs sold by this stand to soldItems if valid;
	// otherwise, throws an exception. Also, increments the total number of hot dogs sold.
	std::string standID;
	int soldStand;
	static int totalSold;
	static int nextID;		
	// Static counter for auto-generating IDs
};

int HotDogStand::totalSold = 0;
int HotDogStand::nextID = 1010;

int main( )
{
	try
	{
		HotDogStand aStand;
		HotDogStand anotherStand("B10", 10);
		HotDogStand aThirdStand("A0");
		aStand.justSold();
		anotherStand.justSold();
		aThirdStand.justSold();
		aStand.justSold();
		std::cout << "The stand " << aStand.getId()
				  << " sold: " << aStand.getSoldStand() << " hot dogs today.\n";
		std::cout << "The stand " << anotherStand.getId()
				  << " sold: " << anotherStand.getSoldStand() << " hot dogs today.\n";
		std::cout << "The stand " << aThirdStand.getId() 
				  << " sold: " << aThirdStand.getSoldStand() << " hot dogs today.\n";

	} catch (const std::invalid_argument& e) {
		std::cout << "Error assigning id: " << e.what() << '\n';
	}
	
	std::cout << "In total, " << HotDogStand::getTotalSold() << " hot dogs were sold today.\n";
	
	std::cout << '\n';
	return 0;
}

void HotDogStand::setId(const std::string& id)
{
	if (id.length() >= 2 && id[0] == 'A' && id[1] >= '1')
		throw std::invalid_argument("Reserved ID.\n");
	standID = id;
}

void HotDogStand::setSoldItems(const int soldItems)
{
	if (soldItems < 0)
		throw std::invalid_argument("Items sold must be greater or equal to 0.\n");
	soldStand = soldItems;
	totalSold += soldItems;
}