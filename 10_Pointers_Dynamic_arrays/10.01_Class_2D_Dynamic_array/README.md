Write a class TwoD that implements the
two - dimensional dynamic array of doubles using ideas from this display in its
constructors.You should have a private member of type pointer to double to point
to the dynamic array, and two int(or unsigned int) values that are MaxRows and
MaxCols.
You should supply a default constructor for which you are to choose a default
maximum row and column sizes and a parameterized constructor that allows the
programmer to set maximum row and column sizes.
Further, you should provide a void member function that allows setting a particular row 
and column entry and a member function that returns a particular row and
column entry as a value of type double.
Remark: It is difficult or impossible(depending on the details) to overload[] so
it works as you would like for two - dimensional arrays.So simply use accessor and
mutator functions using ordinary function notation.
Overload the + operator as a friend function to add two two - dimensional arrays.
This function should return the TwoD object whose ith row, jth column element is
the sum of the ith row, jth column element of the left - hand operand TwoD object
and the ith row, jth column element of the right - hand operand TwoD object.
Provide a copy constructor, an overloaded operator =, and a destructor.
Declare class member functions that do not change the data as const members.

---

# Logic and Structure of 10.01_Class_2D_Dynamic_array.cpp

## Overview
This program implements a class `TwoD` that manages a two-dimensional dynamic array of doubles. 
It demonstrates dynamic memory allocation, operator overloading, and interactive input/output for 2D arrays,
as well as matrix operations (addition of two 2D arrays). 
The class includes constructors, a destructor, and member functions for accessing and modifying array elements.

## Main Components

### 1. Class Members
- `DoublePtr *arrayPtr;`
  - Pointer to an array of pointers, each pointing to a row of doubles (i.e., a dynamic 2D array).
- `int maxRows, maxCols;`
  - Number of rows and columns in the array.

### 2. Constructors and Destructor
- **Default and Parameterized Constructors**
  - Allocate memory for the array with specified dimensions and initialize all elements to zero.
- **Copy Constructor**
  - Creates a deep copy of another `TwoD` object.
- **Destructor**
  - Deallocates all dynamically allocated memory to prevent leaks.

### 3. Operator Overloading
- **operator[]**
  - Allows access to a specific row, enabling syntax like `array[row][col]`.
- **operator+ (friend)**
  - Adds two `TwoD` objects element-wise, returning a new `TwoD` object. Throws an exception if sizes differ.
- **operator<< and operator>> (friend)**
  - For output: prints the array in a readable format.
  - For input: reads values into the array, validates each row, and ignores extra input.
  - the extraction operator validates that the whole row of numbers is valid before storing it in the array. 
	If any number in the row is invalid, the entire row is rejected and the user is prompted to re-enter that row.
	For this purpose, a dynamically allocated temporary array is used to store the input for the row until it is validated.

### 4. Member Functions
- **changeValue()**
  - Prompts the user for row, column, and new value, then updates the array.
- **getValue()**
  - Prompts the user for row and column, then returns the value at that position.
- **getRows(), getCols()**
  - Return the number of rows and columns.

### 5. Helper Functions
- **setGrid()**
  - Allocates and initializes the 2D array.
- **createGrid()**
  - Allocates memory for the array based on current dimensions. 
  - Helper functions to setGrid()
- **validateInput(), validateNumber()**
  - Validate and return user input for integers and doubles.
- **getCoordinates()**
  - Prompts the user for valid row and column indices, returns them as a dynamically allocated array.

## Program Flow
1. **Create TwoD objects** with specified sizes.
2. **Input values** interactively for each object using `operator>>`.
3. **Display arrays** using `operator<<`.
4. **Add arrays** using `operator+` and display the result.
5. **Query and modify values** interactively using `getValue()` and `changeValue()`.

## Comments on Logic
- Dynamic memory is managed carefully to avoid leaks.
- This means that every dynamic variable is deallocated in the destructor, as well as
  temporary dynamic variable in the calling function `getValue()`, `changeValue()`, and the overloaded `operator >>`.
- Input is robust: each row is validated before being stored.
- Operator overloading provides intuitive syntax for array access, addition, and I/O.
- Exception handling ensures that only arrays of matching sizes can be added.

---

