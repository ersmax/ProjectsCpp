Give the definition of a class named Doctor whose objects are records for a clinic’s
doctors. This class will be a derived class of the class SalariedEmployee given
in Display 14.4. A Doctor record has the doctor’s specialty (such as Pediatrician,
Obstetrician, General Practitioner, etc., so use type string) and office visit fee
(use type double). Be sure your class has a reasonable complement of constructors
and accessor methods, an overloaded assignment operator, and a copy constructor.
Write a driver program to test all your methods.

---

## Implementation overview

The implementation for this exercise is split across three files:

- `14_03_Doctor.h` defines the `Doctor` class, derived from `SalariedEmployee`.
- `14_03_Doctor.cpp` implements the `Doctor` behavior and input helpers.
- `14_03_Application.cpp` contains a small driver program that exercises `Doctor` and its copy semantics.

### Doctor class

`Doctor` extends `SalariedEmployee` by adding:

- `std::string specialty` – the doctor’s medical specialty.
- `double fee` – the office visit fee.

The class provides:

- A default constructor that creates a salaried employee with salary 0, specialty set to "No specialty", and fee 0.
- A parameterized constructor that takes name, SSN, weekly salary, specialty, and fee. The constructor validates the specialty against a fixed list ("Pediatrician", "Obstetrician", "General practitioner"). If the specialty is not in this list (case-normalized), it throws `std::invalid_argument`.
- A defaulted copy constructor and defaulted copy-assignment operator, which perform member-wise copy (safe here because all members are value types or standard library types with correct copy semantics).
- Accessors `getSpecialty()` and `getFee()`.
- `readData()`, which interactively reads a doctor’s details from `std::cin`.
- An overridden `printCheck()` that prints a textual "check" for the doctor, including name, weekly net pay, SSN, specialty, and office visit fee.

### Input and validation helpers

`14_03_Doctor.cpp` also defines several helper functions in an unnamed namespace:

- `inputValidation()` reads a non-empty line from `std::cin`, looping until valid input is provided.
- `capitalize(std::string&)` converts the first character of the string to uppercase and the remaining characters to lowercase, used to normalize user input for specialties.
- `readChoice(const std::string&, const std::vector<std::string>&)` repeatedly prompts the user to choose a value from a fixed list (for example the supported specialties). It displays all options, reads a line, normalizes it with `capitalize`, and returns it once it matches one of the allowed options.
- `numberValidation()` reads a `double` from `std::cin`, validates that it is a numeric value and strictly greater than `0.0`, and discards invalid input or leftover characters on the line. It loops until a valid number is entered.

`Doctor::readData()` uses these helpers to:

1. Read the doctor’s name and SSN using `inputValidation()`.
2. Read the weekly salary using `numberValidation()`, then set both the salary and net pay in the base class.
3. Ask the user to choose a valid specialty from the predefined list using `readChoice()`.
4. Read the office visit fee using `numberValidation()` and store it in `fee`.

### Check printing

`Doctor::printCheck()` prints a formatted receipt-like output:

- A separator line of underscores.
- A payee line with the doctor’s name.
- A line showing the weekly amount (`getNetPay()`).
- A check stub that prints the SSN, the doctor’s specialty, and the office visit fee.

This mirrors the style of the original `SalariedEmployee::printCheck()`, but adds the doctor-specific fields.

### Driver program

`14_03_Application.cpp` demonstrates the `Doctor` class and its copy behavior:

1. It default-constructs a `Doctor` object `joe` and calls `joe.readData()` to populate it from user input.
2. It creates `joe2` as a copy of `joe` using copy initialization (`Doctor joe2 = joe;`) and prints `joe2`’s check.
3. It creates `joe3` as another copy using direct initialization (`Doctor joe3(joe2);`) and prints `joe3`’s check.

This sequence verifies that the defaulted copy constructor correctly copies all the base-class and derived-class state, and that each copied `Doctor` prints the same logical check information as the original.

