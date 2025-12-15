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
	//   Postcondition: The type of pizza is set.
	void setSize();
	//   Postcondition: The size of pizza is set.
	void setTopping();
	//   Postcondition: set the number of pepperoni and cheese toppings.
	void outputDescription();
	//   Postcondition: A description of the pizza is output.
private:
	std::string type = PIZZA_TYPE[0];
	std::string size = PIZZA_SIZE[0];
	int pepperoni = 0;
	int cheese = 0;
	std::string getType();
	std::string getSize();
	int getPepperoni() const;
	//  Postcondition: The number of pepperoni toppings is returned.
	int getCheese() const;
	//  Postcondition: The number of cheese toppings is returned.
	int computePrice();
	//  Postcondition: The price of the pizza is computed and returned.
    int inputValidation(int min, int max);
	//  Precondition: min <= max
	//  Postcondition: returns a validated integer input between min and max
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
	std::cout << "Total price: $" << computePrice() << "\n";
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

int Pizza::computePrice()
{
	int total = 0;
	if (getSize() == PIZZA_SIZE[0]) total += 10;
	else if (getSize() == PIZZA_SIZE[1]) total += 14;
	else if (getSize() == PIZZA_SIZE[2]) total += 17;
	total += 2 * (getPepperoni() + getCheese());
	return total;
}
