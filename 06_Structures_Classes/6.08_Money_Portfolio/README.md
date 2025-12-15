Define a class named Money that stores a monetary amount. The class should have
two private integer variables, one to store the number of dollars and another to
store the number of cents. Add accessor and mutator functions to read and set both
member variables. Add another function that returns the monetary amount as a
double. Write a program that tests all of your functions with at least two different
Money objects.
Comments on the provided implementation (`6.08_Money_Portfolio.cpp`):

---

# Overview:
- The program defines a `Money` class with private members `dollars` and `cents`.
- Public mutators `setDollars()` and `setCents()` read validated non-negative integers from standard input using `inputValidation()`.
- Accessors `getDollars()` and `getCents()` return the stored values.
- `inputValidation()` repeatedly reads from `std::cin` until a non-negative integer is entered; it clears and ignores invalid input.
- `convertMoney()` returns the monetary amount as a `double`. It normalizes values where `cents >= 100` by adding `getCents() / 100` (integer division) to dollars and then adds the fractional cents using `getCents() % 100` converted to a `double` and divided by `100.0`.
- `main()` reads dollars and cents for a single `Money` object and prints the converted amount. The exercise requests testing with at least two `Money` objects, so add a second object and similar prints to fully meet the requirement.

## Notes:
- Negative inputs are rejected by `inputValidation()`.
- Large `cents` values are handled by the normalization in `convertMoney()` (for example, `dollars=3, cents=150` yields `4.50`).
- The conversion uses integer division for the whole-dollar portion of `cents` and a `double` cast for the leftover cents fraction to ensure the returned value includes cents.