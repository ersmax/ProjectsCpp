Add temporary, administrative, permanent, and other classifications of employees
to the hierarchy from Displays 14.1, 14.3, and 14.4. Implement and test this
hierarchy.
Test all member functions. A user interface with a menu would be a nice
touch for your test program.

---

## Overview

This folder contains a small console application used to practice a *has-a*
relationship between a `Menu` class and various `Employee`-derived types.
The code focuses on building a simple text menu that lets the user add and
display employees of different specialisations using polymorphism.

The main pieces are:
- `14.02_Menu.h` / `14.02_Menu.cpp`: definition and implementation of class
  `myNamespaceMenu::Menu`, which owns and manages employees.
- `14_02_Application.cpp`: the `main` function and a simple test loop that
  drives the `Menu`.

Although the original exercise talks about several categories (temporary,
permanent, etc.), this practice project concentrates on three concrete types:
`HourlyEmployee`, `SalariedEmployee`, and `Administrator`.

## Menu Class Logic (`14.02_Menu.h` / `14.02_Menu.cpp`)

### Stored data and relationships

`Menu` has a *has-a* relationship with employees:

- It owns a `std::vector<std::unique_ptr<Employee>> employees;` that stores
  polymorphic `Employee` objects on the heap.
- Each element in the vector actually points to one of the derived classes:
  `HourlyEmployee`, `SalariedEmployee`, or `Administrator`.
- Three `static int` counters keep track of how many employees of each broad
  category have been added:
  - `hourlyEmployees`
  - `salariedEmployees`
  - `administratorEmployees`

Because the vector stores pointers to the base class `Employee`, the program
can call `printCheck()` virtually and let each derived type provide its own
behaviour.

### Input helpers (unnamed namespace)

The implementation file defines several helper functions in an unnamed
namespace, so they have internal linkage and are only visible inside
`14.02_Menu.cpp`:

- `choiceValidation()`: safely reads a single character choice from `std::cin`,
  handling invalid input and clearing the stream.
- `nameValidation()`: reads a non-empty line of text; it loops until the user
  enters something valid.
- `numberValidation()`: reads a positive `double` value and rejects invalid or
  non-positive numbers.
- `addAdministrator()`, `addSalaried()`, `addHourly()`: build a local
  `Administrator`, `SalariedEmployee`, or `HourlyEmployee`, fill it with user
  input, and return it **by value**. These functions encapsulate all the
  prompting and validation logic for creating one employee of each type.

There are also helper functions to show only certain types of employees from
the internal vector:

- `showAdministrators(const std::vector<std::unique_ptr<Employee>>& employees)`
  uses `dynamic_cast<Administrator*>` on each element and calls
  `printCheck()` only on actual administrators.
- `showSalaried(...)` uses `dynamic_cast<SalariedEmployee*>` to show employees
  that are of the `SalariedEmployee` hierarchy (this includes
  `Administrator`, because it derives from `SalariedEmployee`).
- `showHourly(...)` uses `dynamic_cast<HourlyEmployee*>` to show only hourly
  employees.
- `showAll(...)` simply calls `e->printCheck()` on each element in the
  vector, relying on virtual dispatch.

These helpers keep most of the low-level logic out of the `Menu` member
functions, so those members remain short and focused on high-level behaviour.

### Adding employees (`Menu::addEmployee`)

`Menu::addEmployee()` asks the user which type of employee to add and then
creates and stores an instance of the chosen type:

1. It prompts:
   > Add Hourly employee ('h'), Salaried employee ('s') or Administrator ('a')?
2. It reads the choice via `choiceValidation()`.
3. A `switch` on the choice decides which helper to call:
   - For `'a'`, it calls `addAdministrator()` to get an `Administrator` value,
     wraps it in `std::unique_ptr<Administrator>`, and `push_back`s it into the
     `employees` vector as a polymorphic `Employee`. It also increments both
     `salariedEmployees` and `administratorEmployees`.
   - For `'s'`, it calls `addSalaried()`, wraps the result in
     `std::unique_ptr<SalariedEmployee>`, stores it, and increments
     `salariedEmployees`.
   - For `'h'`, it calls `addHourly()`, wraps it in `std::unique_ptr<HourlyEmployee>`,
     stores it, and increments `hourlyEmployees`.
   - Any other character prints an error message and does nothing.

The important point is that `Menu` owns the employees through
`std::unique_ptr<Employee>`, which avoids object slicing and ensures proper
destruction without manual `delete` calls.

### Showing employees (`Menu::showEmployee`)

`Menu::showEmployee()` asks what subset of employees to display and delegates
to the appropriate helper:

1. It prompts:
   > Show Hourly employee ('h'), Salaried employee ('s'), Administrator ('a'), or Everybody ('e')?
2. It reads a choice via `choiceValidation()`.
3. A `switch` on that choice calls one of the four show functions:
   - `'a'` → `showAdministrators(employees)`
   - `'s'` → `showSalaried(employees)`
   - `'h'` → `showHourly(employees)`
   - `'e'` → `showAll(employees)`
   - anything else prints an error message.

Because `Employee::printCheck()` is virtual, each derived class prints its own
style of “check” when called through the `Employee*` pointer.

### Counting employees (`Menu::getNumberEmployees`)

`Menu::getNumberEmployees()` prints a small summary:

- Total number of employees stored in the vector.
- Number of hourly employees.
- Number of salaried employees, along with how many of those are
  administrators.

This uses the static counters maintained in `addEmployee()` and the
`employees.size()` of the vector.

## Application Logic (`14_02_Application.cpp`)

The file `14_02_Application.cpp` provides a very small driver around the
`Menu` class.

- `main()` creates a single `Menu aMenu;` instance.
- It then enters a loop that calls `test(aMenu)` and asks the user if they
  want to repeat:
  - Input `'y'` (case-insensitive) keeps the loop running.
  - Any other answer exits.

The `test(Menu& myMenu)` function performs one operation per iteration:

1. It asks:
   > Add ('a') or show ('s') employees?
2. It reads a choice using its own local `choiceValidation()` helper.
3. If the user chooses:
   - `'a'` → it calls `myMenu.addEmployee()` to add one new employee.
   - `'s'` → it calls `myMenu.showEmployee()` to display selected employees.
   - anything else → prints an error message.

This separation means `main()` and `test()` handle the user interaction flow
and repetition, while the `Menu` class encapsulates all the knowledge about
how employees are stored, created, and displayed.

## Notes on the Exercise vs. the Implementation

The original textbook exercise mentions more classifications (temporary,
administrative, permanent, etc.). In this practice implementation, the focus
is on:

- practicing a *has-a* relationship: `Menu` *has* a collection of
  `Employee`-derived objects;
- using `std::unique_ptr` and polymorphism to avoid object slicing;
- organising input and display logic via small helper functions in an unnamed
  namespace, rather than following the book’s specification exactly.

As a result, the program is mainly a training example that exercises
inheritance, virtual functions, dynamic casting, and resource management in a
controlled, menu-driven console application.

