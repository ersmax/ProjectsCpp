/*
Define a class called Pizza that has member variables to track the type of pizza
(either deep dish, hand tossed, or pan) along with the size (either small, medium,
or large) and the number of pepperoni or cheese toppings. You can use constants to
represent the type and size. Include mutator and accessor functions for your class.
Create a void function, outputDescription( ), that outputs a textual description
of the pizza object. Also include a function, computePrice( ), that computes the
cost of the pizza and returns it as a double according to the following rules:
Small pizza = $10 + $2 per topping
Medium pizza = $14 + $2 per topping
Large pizza = $17 + $2 per topping
Write a suitable test program that creates and outputs a description and price of
various pizza objects.
*/

#include <iostream>
#include <string>

const std::string PIZZA_TYPE[] = {"Deep Dish", "Hand Tossed", "Pan"};
constexpr int N_TYPES = 3;
const std::string PIZZA_SIZE[] = {"Small", "Medium", "Large"};
constexpr int N_SIZES = 3;

class Pizza
{
public:
	void setType();
	void setSize();
	void setTopping();
	void outputDescription();
private:
	std::string type = PIZZA_TYPE[0];
	std::string size = PIZZA_SIZE[0];
	int pepperoni = 0;
	int cheese = 0;
	std::string getType();
	std::string getSize();
	int getPepperoni();
	int getCheese();
	double computePice();
	int inputValidation(int size);
};

int main( )
{
	Pizza aPizza;
	aPizza.setType();
	
	std::cout << "\n";
	return 0;
}


void Pizza::setType()
{
	std::cout << "Choose type of pizza.\n";
	for (int idx = 0; idx < N_TYPES; ++idx)
		std::cout << idx + 1 << ") " << PIZZA_TYPE[idx];

	std::cout << "Enter your choice:\n";
	const int choice = inputValidation(N_TYPES);
	type = PIZZA_TYPE[choice];
}

int Pizza::inputValidation(const int size)
{
	int choice = 0;
	while (true)
	{
		if (!(std::cin >> choice))
		{
			std::cout << "Mistake\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (choice > 0 && choice <= size)
			return (--choice);
		std::cout << "Wrong choice\n";
	}
}
