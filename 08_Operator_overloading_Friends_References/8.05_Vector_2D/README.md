Write the definition for a class named Vector2D that stores information about a
two-dimensional vector. The class should have functions to get and set the x and
y components, where x and y are integers.
Next, overload the * operator so that it returns the dot product of two vectors. The
dot product of two-dimensional vectors A and B is equal to
(Ax * Bx) + (Ay * By).
Finally, write a main subroutine that tests the * operation.

---

## Code Logic Explanation

### Class Design: Vector2D
The `Vector2D` class represents a mathematical 2D vector with two integer components (x, y).

**Private Members:**
- `int x` - the x-component of the vector
- `int y` - the y-component of the vector

**Constructors:**
- `Vector2D()` - Default constructor initializing both components to 0: (0, 0)
- `Vector2D(const int num1)` - Single-parameter constructor setting x = num1, y = 0
- `Vector2D(const int num1, const int num2)` - Two-parameter constructor setting x = num1, y = num2

**Member Functions:**
- `void setX()` / `void setY()` - Use `inputValidation()` to prompt user for valid integer input
- `int getX() const` / `int getY() const` - Return the x and y components respectively
- `int operator*(const Vector2D& secondVector) const` - **Dot product operator**
  - Takes another Vector2D as parameter
  - Returns the scalar result: `(x * secondVector.x) + (y * secondVector.y)`
  - Marked `const` because it doesn't modify the current object

**Friend Functions:**
- `operator>>` - **Input stream operator** for reading vectors in format `[x, y]`
  - Reads characters: `[`, x-value, `,`, y-value, `]`
  - Validates format (checks for correct brackets and comma)
  - Sets stream fail bit if format is invalid
  - Directly accesses private members x and y (friend access)

- `operator<<` - **Output stream operator** for printing vectors
  - Outputs in format: `[x, y]`
  - Directly accesses private members x and y (friend access)

### Helper Functions

**`inputValidation()`:**
- Prompts user for a valid integer
- Loops until valid input is received
- Clears error flags and ignores invalid input on failure
- Returns the validated integer

**`vectorValidation()`:**
- Uses the overloaded `>>` operator to read a Vector2D
- Loops until valid vector format `[x, y]` is entered
- Handles input errors by clearing the stream and prompting again
- Returns the validated Vector2D object

### Main Program Flow

1. **First Vector Input:**
   - Prompts user to enter first vector in format `[x, y]`
   - Uses `vectorValidation()` which internally calls `operator>>` to parse the input
   - Stores result in `const Vector2D aVector`

2. **Second Vector Input:**
   - Prompts user to enter second vector
   - Creates default Vector2D object `aVector2`
   - Uses `std::cin >> aVector2` (calls overloaded `operator>>`)

3. **Output Results:**
   - Displays both vectors using overloaded `operator<<`
   - Computes and displays the dot product using overloaded `operator*`
   - The expression `aVector * aVector2` calls the overloaded multiplication operator

### Example Execution:
```
Input: [3, 4] and [1, 2]
Output:
  First vector: [3, 4]
  Second vector: [1, 2]
  Inner product: 11

Calculation: (3 × 1) + (4 × 2) = 3 + 8 = 11
```

### Key C++ Concepts Demonstrated:
- **Operator Overloading** - `*`, `>>`, `<<` operators
- **Friend Functions** - Allow external functions to access private members
- **Const Correctness** - `const` member functions and parameters
- **Input Validation** - Robust error handling for user input
- **Stream Manipulation** - Custom I/O operators for custom types
- **Constructor Overloading** - Multiple constructors with different parameters

---

