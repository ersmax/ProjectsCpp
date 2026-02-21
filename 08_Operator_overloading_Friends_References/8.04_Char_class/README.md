Cumulatively modify the example from Display 8.7 as follows.
a. In Display 8.7, replace the private char members first and second with an
array of char of size 100 and a private data member named size.
Provide a default constructor that initializes size to 10 and sets the first 10 of
the char positions to '#'. (This only uses 10 of the possible 100 slots.)
Provide an accessor function that returns the value of the private member size.
Test.
b. Add an operator[] member that returns a char& that allows the user to access
or to set any member of the private data array using a non-negative index that
is less than size.
Test.
c. Add a constructor that takes an int argument, sz, that sets the first sz members of the char array to '#'.
Test.
d. Add a constructor that takes an int argument, sz, and an array of char of size
sz. The constructor should set the first sz members of the private data array to
the sz members of the argument array of char.
Test.
NOTES: When you test, you should test with known good values, with data on
boundaries and with deliberately bad values. You are not required to put checks
for index out of bounds errors in your code, but that would be a nice touch. Error
handling alternatives: Issue an error message then die (that is, call exit(1)) or give
the user another chance to make a correct entry.

---

## Code Logic Explanation

### Class Design: `Char`

**Private Members:**
- `char characters[MAX]` - Fixed-size array that can hold up to 100 characters
- `int size` - Tracks how many positions in the array are actually being used (0 to MAX)

**Constructors:**
1. **Default Constructor** `Char()` - Initializes size to 10 and fills first 10 positions with '#'
2. **Size Constructor** `Char(int sz)` - Creates a Char object with custom size, filled with '#'
3. **Array Constructor** `Char(const char myArray[], int sz)` - Copies user-provided array into the object

**Key Member Functions:**
- `operator[]` - Two overloaded versions:
  - **Non-const version**: Returns `char&` for both reading and writing. If index is out of bounds, it prompts the user to enter a valid index (interactive error recovery)
  - **Const version**: Returns `const char&` for reading only. If index is out of bounds, it prints an error and exits the program
- `getSize()` - Returns the current size (number of characters in use)
- `output()` - Displays all characters currently in the array
- `askPosition()` - Helper function that prompts user for a valid index

### Main Program Flow

1. **Test Default Constructor:**
   - Creates a `Char` object with default size (10)
   - Creates a const reference to test const `operator[]`
   - Displays size and contents
   - Allows user to modify one character by index
   - Demonstrates both non-const (for writing) and const (for reading) versions of `operator[]`

2. **Test Size Constructor:**
   - Prompts user to choose a custom size
   - Creates a `Char` object initialized with '#' characters
   - Displays the contents

3. **Test Array Constructor:**
   - Prompts user to choose a size
   - Asks user to input characters one by one to build an array
   - Creates a `Char` object initialized with the user's array
   - Displays the contents

4. **Test `operator[]` Functionality:**
   - Calls `testOperator()` function which:
     - Asks user for a valid index
     - Shows the old character at that index
     - Prompts for a new character
     - Replaces the character at that index
     - Shows the new character

### Error Handling Strategy

**Boundary Testing:**
- Size validation ensures values are between 0 and MAX (100)
- Index validation ensures values are between 0 and size-1

**Error Recovery:**
- **Interactive approach** (non-const `operator[]`): If invalid index, asks user to re-enter
- **Termination approach** (const `operator[]`): If invalid index, exits program
- **Exception approach** (constructors): Throws `std::invalid_argument` for invalid sizes
- **Input validation**: All user inputs are validated with error messages and retry loops

### Utility Functions

- `inputValidation()` - Ensures user enters a valid character with input stream error handling
- `numberValidation()` - Ensures user enters a valid integer with input stream error handling
- `validSize(int)` - Checks if a number is a valid size (0-100)
- `validSize(const Char&, int)` - Checks if an index is valid for a specific Char object
- `chooseSize()` - Prompts user for a valid size and validates it
- `buildArray()` - Fills an array with user-entered characters

### Design Decisions

1. **Fixed vs Dynamic Array**: Uses a fixed-size array (100) with a separate size tracker rather than dynamic allocation
2. **Dual Error Handling**: Non-const `operator[]` recovers from errors interactively, while const version terminates (const objects shouldn't trigger interactive user input)
3. **Member Initializer Lists**: Uses modern C++ initialization in constructors
4. **Helper Functions**: Delegates initialization logic to private `setMembers()` overloads to avoid code duplication
5. **Const Correctness**: Provides both const and non-const versions of `operator[]` to support const objects
6. **Comprehensive Validation**: All user inputs are validated with detailed error messages and retry mechanisms


### Overloading based on L-Value versus R-Value Context
It is important to notice how the array access operator [] has been overloaded differently,
depending when it is used as an l-value (non-const version) or as an r-value (const version). 
The non-const version allows the user to modify the character at the specified index, 
while the const version only allows reading the character. 

This design ensures that const objects cannot be modified through the operator[], when querying,
while still providing flexibility for non-const objects.