Define a class for complex numbers. A complex number is a number of the form
a + b*i 
where for our purposes, a and b are numbers of type double, and i is a number
that represents the quantity 1-1. Represent a complex number as two values
of type double. Name the member variables real and imaginary. (The variable
for the number that is multiplied by i is the one called imaginary.) Call the class
Complex. Include a constructor with two parameters of type double that can be
used to set the member variables of an object to any values. 
Include a constructor that has only a single parameter of type double; call this parameter realPart
and define the constructor so that the object will be initialized to realPart + 0*i.
Include a default constructor that initializes an object to 0 (that is, to 0 + 0*i).
Overload all the following operators so that they correctly apply to the type
Complex: ==, +, −, *, >>, and <<. You should also write a test program to test your
class. Hints: To add or subtract two complex numbers, add or subtract the two
member variables of type double. The product of two complex numbers is given
by the following formula:
(a + b*i)*(c + d*i) =  = (a*c - b*d ) + (a*d + b*c)*i
In the interface file, you should define a constant i as follows:
const Complex i(0, 1);

---

## Implementation Logic

### Class Design
The `Complex` class encapsulates two `double` member variables:
- `real`: stores the real part of the complex number
- `imaginary`: stores the imaginary part (coefficient of i)

Both are private to ensure encapsulation and data hiding.

### Constructors
Three constructors provide flexible initialization:

1. **Default Constructor**: `Complex()` - Initializes to 0 + 0*i using member initializer list
2. **Two-Parameter Constructor**: `Complex(double, double)` - Sets both real and imaginary parts
3. **Single-Parameter Constructor**: `Complex(double)` - Sets real part, imaginary defaults to 0
   - Enables implicit conversion from `double` to `Complex`, allowing mixed arithmetic like `3.5 + aComplex`

### Operator Overloading Strategy

#### Friend Functions vs Member Functions
**Arithmetic operators (+, -, \*)** are implemented as **friend functions** rather than member functions:
- **Reason**: Enables symmetric operations and automatic type conversions for both operands
- **Example**: Both `aComplex + 3.5` and `3.5 + aComplex` work because the single-parameter constructor converts `3.5` to `Complex(3.5, 0)`
- If these were member functions, only `aComplex + 3.5` would work (left operand must be Complex object)

**Equality operator (==)** is a **member function**:
- Only needs access to compare member variables
- Asymmetric conversion is acceptable for equality checks

### Operator Implementations

#### Addition (`operator+`)
- Adds corresponding real parts: `firstNumber.real + secondNumber.real`
- Adds corresponding imaginary parts: `firstNumber.imaginary + secondNumber.imaginary`
- Returns new `Complex` object with summed values

#### Subtraction (`operator-`)
- Subtracts corresponding real parts: `firstNumber.real - secondNumber.real`
- Subtracts corresponding imaginary parts: `firstNumber.imaginary - secondNumber.imaginary`
- Returns new `Complex` object with differences

#### Multiplication (`operator*`)
Uses the mathematical formula: `(a + bi)(c + di) = (ac - bd) + (ad + bc)i`
- Real part: `(a*c - b*d)` = `firstNumber.real * secondNumber.real - firstNumber.imaginary * secondNumber.imaginary`
- Imaginary part: `(a*d + b*c)` = `firstNumber.real * secondNumber.imaginary + firstNumber.imaginary * secondNumber.real`

#### Equality (`operator==`)
- Returns `true` only if both real AND imaginary parts match exactly
- Uses short-circuit AND (`&&`) for efficiency

#### Stream Insertion (`operator<<`)
Formats output based on sign of imaginary part:
- If `imaginary >= 0`: outputs as `"a + b*i"` (e.g., `3 + 4*i`)
- If `imaginary < 0`: outputs as `"a - b*i"` (e.g., `3 - 4*i`)
  - Negates the imaginary value to avoid double negative: `-(-4)` becomes `4`

#### Stream Extraction (`operator>>`)
Parses input in format `a+b` or `a-b`:
1. Reads real part (double)
2. Reads sign character ('+' or '-')
3. Reads imaginary part magnitude (double)
4. **Validation**: If sign is neither '+' nor '-', sets stream to fail state using `setstate(std::ios::failbit)`
5. Applies sign: if '-', negates the imaginary part
6. Updates the `Complex` object's member variables

### Helper Function: `inputComplex()`
Provides robust user input with error handling:
1. Creates temporary `Complex` object
2. Attempts to read using `operator>>`
3. **On failure**: 
   - Displays error message
   - Clears error flags with `cin.clear()`
   - Discards invalid input up to newline with `cin.ignore()`
   - Loops back to retry
4. **On success**: 
   - Discards any remaining input on line
   - Returns the valid `Complex` object

### Main Program Flow
1. Prompts for first complex number, uses `inputComplex()` for validated input
2. Prompts for second complex number, demonstrates direct `operator>>` usage
3. Tests equality operator (`==`) and displays result
4. Demonstrates all arithmetic operators:
   - Addition: `aComplex + anotherComplex`
   - Subtraction: `aComplex - anotherComplex`
   - Multiplication: `aComplex * anotherComplex`
5. Each operation uses `operator<<` to display results

### Forward Declaration Pattern
```cpp
class Complex;
extern const Complex i;
```
- Forward declares class before definition
- Declares constant `i` before class is complete
- Defines `i` after class: `const Complex i(0, 1);`
- This pattern allows the constant to be visible but prevents circular dependencies

### Key C++ Concepts Demonstrated
- **Operator overloading** for intuitive syntax
- **Friend functions** for symmetric binary operators
- **Member initializer lists** in constructors
- **Stream manipulators** for I/O
- **Input validation** and error recovery
- **const correctness** in parameters and member functions
- **Automatic type conversion** via single-parameter constructor

