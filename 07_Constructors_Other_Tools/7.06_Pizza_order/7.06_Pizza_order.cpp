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
/*

/*
  This Programming Project requires you to first complete Programming Project 6.7
from Chapter 6, which is an implementation of a Pizza class. Add an Order class
that contains a private vector of type Pizza. This class represents a customer’s
entire order, where the order may consist of multiple pizzas. Include appropriate
functions so that a user of the Order class can add pizzas to the order (type is deep
dish, hand tossed, or pan; size is small, medium, or large; number of pepperoni or
cheese toppings). You can use constants to represent the type and size. Also write
a function that outputs everything in the order along with the total price. Write a
suitable test program that adds multiple pizzas to an order(s).
*/

// define NDEBUG        // uncomment this line to disable assertions
#include <iostream>
#include <string>
#include <limits>
#include <cassert>
#include <vector>

const std::string PIZZA_TYPE[] = { "Deep Dish", "Hand Tossed", "Pan" };
constexpr int N_TYPES = 3;
const std::string PIZZA_SIZE[] = { "Small", "Medium", "Large" };
constexpr int N_SIZES = 3;

class Pizza
{
public:
	Pizza() { setType(); setSize(); setTopping(); }
	void setType();
	//   Postcondition: The type of pizza is set.
	void setSize();
	//   Postcondition: The size of pizza is set.
	void setTopping();
	//   Postcondition: set the number of pepperoni and cheese toppings.
	void outputDescription() const;
	//   Postcondition: A description of the pizza is output.
	int computePrice() const;
	//  Postcondition: The price of the pizza is computed and returned.
private:
	std::string type = PIZZA_TYPE[0];
	std::string size = PIZZA_SIZE[0];
	int pepperoni = 0;
	int cheese = 0;
	std::string getType() const;
	std::string getSize() const;
	int getPepperoni() const;
	//  Postcondition: The number of pepperoni toppings is returned.
	int getCheese() const;
	//  Postcondition: The number of cheese toppings is returned.
	int inputValidation(int min, int max);
	//  Precondition: min <= max
	//  Postcondition: returns a validated integer input between min and max
};

class Order
{
public:
	Order() { setName("Order " + std::to_string(orderId++)); }
	Order(const std::string& fullName) { setName(fullName); }
	void addPizza() { const Pizza aPizza; anOrder.push_back(aPizza); totalPrice += aPizza.computePrice(); }
	//   Postcondition: Adds a pizza to the order and updates the total price.
	void showOrder() const {for (const auto& pizza : anOrder) pizza.outputDescription();}
	double getTotalPrice() const { return totalPrice; }
	std::string getId() { return nameOrder; }
private:
	void setName(const std::string& fullName) { nameOrder = fullName; }
	std::string nameOrder;
	std::vector<Pizza> anOrder;
	double totalPrice = 0.0;
	static int orderId;
};

int Order::orderId = 1;

int main()
{
	Order anOrder, anotherOrder;
	anOrder.addPizza();
	anOrder.addPizza();
	anotherOrder.addPizza();
	anotherOrder.addPizza();
	anotherOrder.addPizza();
	
	std::cout << anOrder.getId() << " price: " 
			  << anOrder.getTotalPrice() << '\n';
	anOrder.showOrder();

	std::cout << anotherOrder.getId() << " price: "
		<< anotherOrder.getTotalPrice() << '\n';
	anotherOrder.showOrder();

	std::cout << "\n";
	return 0;
}


void Pizza::setType()
{
	std::cout << "Choose type of pizza.\n";
	for (int idx = 0; idx < N_TYPES; ++idx)
		std::cout << idx + 1 << ") " << PIZZA_TYPE[idx] << "\n";

	std::cout << "Enter your choice:\n";

	assert(1 <= N_TYPES);
	const int choice = inputValidation(1, N_TYPES);
	type = PIZZA_TYPE[choice - 1];
}

void Pizza::setSize()
{
	std::cout << "Choose size of pizza.\n";
	for (int idx = 0; idx < N_SIZES; ++idx)
		std::cout << idx + 1 << ") " << PIZZA_SIZE[idx] << "\n";

	std::cout << "Enter your choice:\n";

	assert(1 <= N_SIZES);
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

void Pizza::outputDescription() const
{
	std::cout << getSize() << " Pizza " << getType()
		<< " with " << getPepperoni() << " pepperoni"
		<< " and " << getCheese() << " cheese\n";
	std::cout << "Total price: $" << computePrice() << "\n";
}

std::string Pizza::getSize() const
{
	return size;
}

std::string Pizza::getType() const
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

int Pizza::computePrice() const
{
	int total = 0;
	if (getSize() == PIZZA_SIZE[0]) total += 10;
	else if (getSize() == PIZZA_SIZE[1]) total += 14;
	else if (getSize() == PIZZA_SIZE[2]) total += 17;
	total += 2 * (getPepperoni() + getCheese());
	return total;
}
