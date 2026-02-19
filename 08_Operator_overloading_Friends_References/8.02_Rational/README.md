Define a class for rational numbers. A rational number is a number that can be
represented as the quotient of two integers. For example, 1/2, 3/4, 64/2, and so
forth are all rational numbers. (By 1/2 and so on we mean the everyday fraction,
not the integer division this expression would produce in a C++ program.)
Represent rational numbers as two values of type int, one for the numerator and
one for the denominator. Call the class Rational. Include a constructor with
two arguments that can be used to set the member variables of an object to any
legitimate values. Also include a constructor that has only a single parameter of
type int; call this single parameter wholeNumber and define the constructor so
that the object will be initialized to the rational number wholeNumber/1. Include
a default constructor that initializes an object to 0 (that is, to 0/1). Overload
the input and output operators >> and <<. Numbers are to be input and output
in the form 1/2, 15/32, 300/401, and so forth. Note that the numerator, the
denominator, or both may contain a minus sign, so −1/2, 15/−32, and −300/−401
are also possible inputs. Overload all the following operators so that they correctly
apply to the type Rational: ==, <, <=, >, >=, +, −, *, and /. Write a test program
to test your class. Hints: Two rational numbers a/b and c/d are equal if a*d equals
c*b. If b and d are positive rational numbers, a/b is less than c/d provided a*d
is less than c*b. You should include a function to normalize the values stored
so that, after normalization, the denominator is positive and the numerator and
denominator are as small as possible. For example, after normalization 4/-8 would
be represented the same as −1/2.

---

## Implementation Logic

### Class Structure

The `Rational` class represents a fraction with:
- **Private members**: `numerator` (int), `denominator` (int)
- **Three constructors**:
  - Default: initializes to 0/1
  - Single parameter: creates wholeNumber/1
  - Two parameters: creates numerator/denominator, validates, and normalizes
- **Helper methods**: `setDenominator()`, `normalize()`
- **Overloaded operators**: arithmetic (+, -, *, /), comparison (==, !=, <, <=, >, >=), stream (<<, >>)

### Key Functions

#### 1. **normalize()**
Ensures rational numbers are in canonical form:
- Makes denominator positive (moves sign to numerator if needed)
- Reduces fraction to lowest terms using GCD
- Example: 4/-8 → -4/8 → -1/2

#### 2. **findGcd(int, int)**
Implements Euclidean algorithm:
- Handles negative numbers using `std::abs()`
- Returns positive GCD
- Base case: if divisor is 0, return dividend

#### 3. **findLcm(int, int)**
Calculates Least Common Multiple:
- Formula: LCM(a,b) = |a × b| / GCD(a,b)
- Returns 0 if either input is 0
- Used in addition operator for common denominator

### Operator Implementations

#### Arithmetic Operators
- **Addition (+)**: Finds LCM of denominators, converts both fractions, adds numerators
  - Formula: a/b + c/d = (a×(LCM/b) + c×(LCM/d)) / LCM
- **Subtraction (-)**: Uses cross-multiplication
  - Formula: a/b - c/d = (a×d - c×b) / (b×d) 
- **Multiplication (*)**: Multiplies numerators and denominators
  - Formula: a/b × c/d = (a×c) / (b×d)
- **Division (/)**: Multiplies by reciprocal, throws exception for division by zero
  - Formula: a/b ÷ c/d = (a×d) / (b×c)

All arithmetic operators call constructor which normalizes the result, that is 
the constructor Rational(numerator, denominator) will take care of normalization (terms reduction).

#### Comparison Operators
- **Equality (==)**: Cross-multiplies to compare
  - a/b == c/d if a×d == c×b
- **Less than (<)**: Cross-multiplies
  - a/b < c/d if a×d < c×b
- **Other comparisons**: Implemented in terms of < and ==
  - operator> uses: secondOperand < *this
  - operator>= uses: secondOperand <= *this
  - operator!= uses: !(*this == secondOperand)

#### Stream Operators
- **Output (<<)**: Prints in format "numerator/denominator"
- **Input (>>)**: 
  - Reads: numerator, slash character, denominator
  - Validates: slash must be '/', denominator cannot be 0
  - Sets `failbit` if invalid
  - Normalizes valid input

### Input Validation

**inputRational()** function:
- Provides user-friendly input with retry loop
- Uses `operator>>` for actual parsing
- Checks stream state: `if (!(std::cin >> r))`
- On failure:
  - Prints error message
  - Clears error state: `std::cin.clear()`
  - Discards bad input: `std::cin.ignore()`
  - Loops for retry
- On success:
  - Consumes remaining newline
  - Returns valid Rational object

### Error Handling

1. **Constructor validation**: `setDenominator()` throws `std::invalid_argument` if denominator is 0
2. **Division by zero**: `operator /` throws exception if divisor numerator is 0
3. **Stream errors**: `operator >>` sets `failbit` for invalid format or zero denominator
4. **Main function**: Wraps operations in try-catch block

### Test Program Features

- Creates rational numbers using both `inputRational()` (with retry) and `operator >>` (one attempt)
- Demonstrates all four arithmetic operations
- Tests inequality comparison
- Shows exception handling for invalid input

---

