Define a Pet class that stores the pet’s name, age, and weight. Add appropriate
constructors, accessor functions, and mutator functions. Also define a function
named getLifespan that returns a string with the value “unknown lifespan.”
Next, define a Dog class that is derived from Pet. The Dog class should have a
private member variable named breed that stores the breed of the dog. Add mutator
and accessor functions for the breed variable and appropriate constructors.
Redefine the getLifespan function to return “Approximately 7 years” if the dog’s
weight is over 100 pounds and “Approximately 13 years” if the dog’s weight is
under 100 pounds.
Next, define a Rock class that is derived from Pet. Redefine the getLifespan
function to return “Thousands of years.”
Finally, write a test program that creates instances of pet rocks and pet dogs that
exercise the inherited and redefined functions.

---

## Implementation Overview

This project implements the specification using a small class hierarchy and an orchestrator class that manages polymorphic pets.

### Core Domain Classes

- `Pet` (`14_10_Pet.h/.cpp`)
  - Stores `name`, `age`, and `weight`.
  - Provides constructors and simple accessors (`getName`, `getAge`, `getWeight`).
  - Implements `virtual const std::string& getLifespan() const`, which returns a shared constant string ("Unknown lifespan").
  - Defines `virtual void print(std::ostream&) const` that writes name/age/weight to an output stream. This allows for a polymorphic print function that derived classes can extend.
  - Overloads `operator>>` to read a pet from a stream using the validation helpers, and `operator<<` to call `print` (enabling polymorphic output through the virtual function).

- `Dog` (`14_10_Dog.h/.cpp`)
  - Derives from `Pet` and adds a `breed` member.
  - Provides constructors (default and parameterized) and a `getBreed` accessor.
  - Overrides `getLifespan`:
    - Returns "Approximately 7 years" if `weight > 100`.
    - Returns "Approximately 13 years" otherwise.
  - Overrides `print(std::ostream&) const` to first call `Pet::print` and then append the dog's breed. This enables polymorphic printing of dog details, namely the breed, in addition to the base pet information.
  - Overloads `operator>>` to read base `Pet` data and then read the `breed`. Its `operator<<` simply calls the virtual `print`.

- `Rock` (`14_10_Rock.h/.cpp`)
  - Derives from `Pet` without adding new data members.
  - Overrides `getLifespan` to return the constant string "Thousands of years".

### Input Validation Helpers

- `Validation` (`14_10_Validation.h/.cpp`)
  - Provides `readNumber(std::istream&, int&)` and `readName(std::istream&, std::string&)`.
  - Both functions loop until valid input is received, clearing the stream and discarding invalid data when necessary.
  - These helpers are used by `Pet`, `Dog`, and `Orchestrator` to keep input code concise and robust.

### Orchestrator / Container

- `Orchestrator` (`14_10_Orchestrator.h/.cpp`)
  - Manages a dynamically-sized collection of `Pet*` (`PetPtr`). The array of pointers is owned by `Orchestrator`.
  - Data members:
    - `PetPtr* things;` – dynamic array of pointers to polymorphic `Pet` objects (`Dog`, `Rock`, etc.).
    - `int numberThings;` – current number of stored pets.
  - Construction and lifetime:
    - Default constructor initializes an empty collection (`things == nullptr`, `numberThings == 0`).
    - Destructor deletes each stored `Pet` and then deletes the pointer array, so the class owns and cleans up its pets.
  - Modifying operations:
    - `void addThing()` – prompts the user to choose between "Dog" and "Rock", allocates the appropriate derived object with `new`, reads it from `std::cin` via the corresponding `operator>>`, and passes the result to `addThingHelper`.
    - `void addThingHelper(const PetPtr& aPet)` – allocates a new pointer array of size `numberThings + 1`, copies existing pointers, appends the new pointer, deletes the old array, and updates `things`/`numberThings`.
    - `void deleteThing()` – if the container is non-empty, prints the current contents via `operator<<`, asks the user for an index, validates it, and calls `deleteThingHelper` on success.
    - `void deleteThingHelper(int index)` – deletes the selected `Pet`, creates a new pointer array of size `numberThings - 1`, copies all remaining pointers, deletes the old array, and decrements `numberThings`.
  - Access and output:
    - `const Pet& operator[](int index) const` – returns a reference to the `Pet` at the given index, performing bounds checking and throwing `std::out_of_range` if invalid.
    - `friend std::ostream& operator<<(std::ostream&, const Orchestrator&)` – iterates over all stored pets, printing for each:
      - The object number.
      - The `Pet` (or derived) details via `outputStream << pet;` which calls the virtual `print` function.
      - The lifespan string via `pet.getLifespan()` (which is overridden in `Dog` and `Rock`).
    - `friend std::istream& operator>>(std::istream&, Orchestrator&)` – repeatedly calls `addThing()` and asks the user if they want to add more pets.

Overall, `Orchestrator` demonstrates manual management of a polymorphic collection using raw pointers, dynamic arrays, and helper functions to add and remove elements.

### Application Flow

- `main` (`14_10_Application.cpp`)
  - Creates an `Orchestrator` instance `aSet`.
  - Calls `std::cin >> aSet;` to let the user add an initial set of pets via `Orchestrator`'s extraction operator.
  - Enters an interactive loop:
    - `1` – add a new `Dog` or `Rock` (`Orchestrator::addThing`).
    - `2` – delete an existing pet by index (`Orchestrator::deleteThing`).
    - `3` – view all pets and their lifespans (`operator<<(std::ostream&, const Orchestrator&)`).
    - `4` – exit the program.

This design exercises inheritance and virtual functions (`Pet` → `Dog` / `Rock`), polymorphic behavior in `getLifespan` and `print`, and an owning container (`Orchestrator`) that stores and manages a heterogeneous collection of `Pet` objects through base-class pointers.


