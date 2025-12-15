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

---

# Overview:
The program defines a `Pizza` class that models a pizza order by storing its `type` 
(one of `Deep Dish`, `Hand Tossed`, `Pan`), `size` (`Small`, `Medium`, `Large`), 
and the number of `pepperoni` and `cheese` toppings (each 0..2 representing none, regular, extra).

## Constants:
`PIZZA_TYPE` and `PIZZA_SIZE` are arrays used to map numeric menu choices to human-readable strings.

## Input and validation:
`setType()`, `setSize()`, and `setTopping()` are mutator methods that prompt the user for choices. 
They call `inputValidation(min, max)` which reads an integer from `std::cin`, 
handles non-integer input by clearing and ignoring the rest of the line, and enforces the supplied inclusive range. `inputValidation` loops until a valid value is entered.

## Accessors and output:
- `getType()`, `getSize()`, `getPepperoni()`, and `getCheese()` return the corresponding member values.
- `outputDescription()` prints a human-readable description of the pizza (size, type, and topping counts) and the total price computed by `computePrice()`.

## Price computation:
`computePrice()` determines a base price from the pizza size: Small = $10, Medium = $14, Large = $17. 
It then adds $2 per topping (the sum of pepperoni and cheese counts) and returns the total as an `int`.

## Program flow:
`main()` creates a `Pizza` instance, calls the mutators to gather user choices, and then calls `outputDescription()` to display the final order and price.


