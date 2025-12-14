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
#include <limits>

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
	int getPepperoni() const;
	int getCheese() const;
	double computePice();
    int inputValidation(int min, int max);
};

int main( )
{
	Pizza aPizza;
	aPizza.setType();
	aPizza.setSize();
	aPizza.setTopping();
	aPizza.outputDescription();
	
	std::cout << "\n";
	return 0;
}


void Pizza::setType()
{
	std::cout << "Choose type of pizza.\n";
	for (int idx = 0; idx < N_TYPES; ++idx)
		std::cout << idx + 1 << ") " << PIZZA_TYPE[idx] << "\n";

	std::cout << "Enter your choice:\n";
    const int choice = inputValidation(1, N_TYPES);
    type = PIZZA_TYPE[choice - 1];
}

void Pizza::setSize()
{
	std::cout << "Choose size of pizza.\n";
	for (int idx = 0; idx < N_SIZES; ++idx)
		std::cout << idx + 1 << ") " << PIZZA_SIZE[idx] << "\n";

	std::cout << "Enter your choice:\n";
    const int choice = inputValidation(1, N_SIZES);
    size = PIZZA_SIZE[choice - 1];
}

void Pizza::setTopping()
{
	std::cout << "Enter portion of pepperoni.\n"
				 "(0 = none, 1 = regular, 2 = extra)\n";
	std::cout << "Enter your choice:\n";
    pepperoni = inputValidation(0, 2);
	std::cout << "Enter portion of cheese topping.\n"
				 "(0 = none, 1 = regular, 2 = extra)\n";
	std::cout << "Enter your choice:\n";
    cheese = inputValidation(0, 2);
}

int Pizza::inputValidation(const int min, const int max)
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
        if (choice < min || choice > max) {
            std::cout << "Wrong choice\n";
            continue;
        }
        return choice;
	}
}

void Pizza::outputDescription()
{
	std::cout << getSize() << " Pizza " << getType()
		<< " with " << getPepperoni() << " pepperoni"
		<< " and " << getCheese() << " cheese\n";
}

std::string Pizza::getSize()
{
	return size;
}

std::string Pizza::getType()
{
	return type;
}

int Pizza::getPepperoni() const
{
	return pepperoni;
}

int Pizza::getCheese() const
{
	return cheese;
}
