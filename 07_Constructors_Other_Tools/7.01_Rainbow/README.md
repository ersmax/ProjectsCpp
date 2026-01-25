Define a class called RainbowColor that is an abstract data type for a color in the visible spectrum 
of light. 
Your class will have a member variable of type int to represent
a color. Include all the following member functions: a constructor to set the color
using the first letter in the name of the color as an argument, a constructor to set the
color using an integer as an argument, a default constructor, an input function that
reads the color as an integer, an input function that outputs the color as an integer,
an output function that outputs the name of the color, and a member function that
returns the next color in the spectrum as a value of type RainbowColor. Embed your
class definition in a test program.


----

# Design Decisions Summary

## Rainbow Class Implementation - Two Approaches

This project demonstrates two different design patterns for handling user input 
and object initialization.

### Why Two Implementations?

The assignment requirement for "input functions" is ambiguous:
- **Interpretation 1:** Static functions that gather input before object creation
- **Interpretation 2:** Instance methods that modify existing objects

Both interpretations are valid, demonstrating different C++ design patterns:
- **Static approach** prioritizes **single initialization** and **const correctness**
- **Modifier approach** prioritizes **OOP principles** and **flexibility**

### Key Learning Points

1. **Constructor Initialization:** Objects should be fully initialized in constructors
2. **Const Correctness:** Immutable objects should be declared `const`
3. **Exception Safety:** Throw exceptions for invalid constructor arguments
4. **Static vs Instance:** Choose based on whether functionality belongs to class or object


# Common Implementation (Shared Code)

Both files share the following components:

#### Data Structures
Parallel vectors mapping RGB color codes to color names in rainbow spectrum order.

#### Common Member Functions

**Constructors (Same signature, different error handling):**
- `RainbowColor()` - Default constructor (initializes to Purple in 0.99, uninitialized in 7.01)
- `RainbowColor(char colorLetter)` - Initialize from first letter (case-insensitive)
- `RainbowColor(int colorNumCode)` - Initialize from RGB code

**Output Functions:**
- `std::string getColor() const` - Returns color name
- `int outputColorCode() const` - Returns RGB integer code

**Utility Functions:**
- `RainbowColor nextColor() const` - Returns next color in spectrum (wraps to Purple after Red)
- `static int getNumberColors()` - Returns count of objects created
- `static int getColorCode(char)` - Private helper converting letter to RGB code

**Global Helper Functions:**
- `void showColors()` - Displays formatted table of all rainbow colors
- `bool validateCode(char)` - Validates color letter
- `bool validateCode(int)` - Validates RGB code (overloaded)

---

## Approach 1: Static Input Functions (0.99_Rainbow_Static.cpp)

### Design Philosophy
**Validate input BEFORE object creation** - ensures all objects are valid from construction.

### Key Differences

#### Static Input Methods
```cpp
static int readColorCode();   // Returns validated RGB code 
static char readColor();       // Returns validated color letter
```
These are **class-level functions** that:
- Read and validate user input
- Return validated values
- Don't require an object instance to call

#### Usage Pattern
```cpp
// Step 1: Get validated input (no object needed) 
const int codeColor = RainbowColorreadColorCode(); 
const char initialColor = RainbowColorreadColor();
// Step 2: Create object with validated data 
const RainbowColor aColor(codeColor); 
const RainbowColor anotherColor(initialColor);
// Step 3: Use object 
std::cout << aColor.getColor();
```
#### Constructor Error Handling
```cpp
RainbowColorRainbowColor(const char colorLetter) { 
   if (validateCode(colorLetter)) 
   {
      colorCode = getColorCode(colorLetter); 
      colors++; 
   } else 
      std::cout << "Not a valid code. Retry\n";  
}
```

### Advantages
**Single initialization** - Object created with final value  
**Const correctness** - Objects can be `const` since no modification needed  
**Always valid input** - Input validation happens before construction  
**No wasted initialization** - Default constructor not used unnecessarily

### Disadvantages
**Not OOP** - Static functions aren't part of object behavior  
**No flexibility** - Can't change color after creation without creating new object

---

## Approach 2: Instance Modifier Functions (7.01_Rainbow.cpp)

### Design Philosophy
**Create object first, then populate with data** - traditional modifier pattern.

### Key Differences

#### Instance Input Methods
```cpp
void readColorCode();   // Reads input and sets colorCode 
void readColor();       // Reads input and sets colorCode
```

These are **instance methods** (so called `modifiers`) that:
- Read and validate user input
- Modify the existing object's state
- Require an object instance to call

#### Usage Pattern
```cpp
// Step 1: Create objects with default constructor 
RainbowColor aColor; 
RainbowColor anotherColor;
// Step 2: Populate objects with input 
aColor.readColorCode(); 
anotherColor.readColor();
// Step 3: Use objects 
std::cout << aColor.getColor();
```
#### Constructor Error Handling (Exception-based)
```cpp
RainbowColorRainbowColor(const char colorLetter) 
{ 
   if (validateCode(colorLetter)) 
   { 
      colorCode = getColorCode(colorLetter); 
      colors++; 
   } 
   else 
      throw stdinvalid_argument("Invalid color letter");  // prevent object creation
}
```
#### Default Constructor Issue
```cpp
RainbowColor() { colors++; }  //  colorCode left uninitialized
```

**Note:** This creates objects in an uninitialized state until `readColor()` or `readColorCode()` is called.

### Advantages
**Real OOP** - Objects manage their own state  
**Flexibility** - Can change color multiple times after creation  
**Exception safety** - Parameterized constructors throw exceptions on invalid input  
**Clear separation** - Input logic is instance behavior

### Disadvantages
**Verbosity** - Default constructor creates object, then modifier sets value  
**Uninitialized state** - Default constructor doesn't initialize `colorCode`  
**Can't be const** - Objects must be mutable to call modifier functions  

---

## Example Output

Both implementations produce similar output:

```
Colors         Code
Purple         9699539
Violet         9109759
Blue           255
Green          65280
Yellow         16776960
Orange         16744192
Red            16711680
Enter a valid number code:
255 
Enter a valid initial for color code: p
First, you entered: Blue 
Next color is: Green 
Then, you entered: Purple 
Next color is: Violet 
The total number of colors added is: 4
```

---
