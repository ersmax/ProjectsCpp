Define a class named MyInteger that stores an integer and has functions to get and
set the integer’s value. Then, overload the [] operator so that the index returns the
digit in position i, where i = 0 is the least-significant digit. If no such digit exists
then −1 should be returned.
For example, if x is of type MyInteger and is set to 418, then x[0] should return
8, x[1] should return 1, x[2] should return 4, and x[3] should return −1.

---

## Code Logic Explanation

### MyInteger Class

The `MyInteger` class encapsulates an integer value with the following components:

#### Constructors
- **Default constructor**: Initializes the integer to 0
- **Parameterized constructor**: Initializes the integer with a provided value

#### Member Functions
- **setNumber()**: Uses input validation to safely set the integer value
- **getNumber()**: Returns the current integer value

#### Operator Overloads

##### Subscript Operator `[]`
The core functionality extracts individual digits from the integer:

```
Algorithm for operator[](position):
1. If position is negative, return -1 (invalid)
2. Take absolute value of number to handle negative integers
3. Loop position times, dividing by 10 each iteration
   - If the number becomes 0 before reaching position, return -1
4. Return the remainder when divided by 10 (the digit at that position)
```

**Example**: For number 418:
- Position 0: 418 % 10 = 8 (least significant)
- Position 1: (418 / 10) % 10 = 41 % 10 = 1
- Position 2: (418 / 100) % 10 = 4 % 10 = 4
- Position 3: Returns -1 (no digit exists)

##### Stream Operators
- **operator>>**: Reads an integer from input stream and stores it in the MyInteger object
- **operator<<**: Outputs the integer value to the output stream

### Input Validation Function

The `inputValidation()` function ensures robust integer input:
1. Prompts user for input
2. Checks if input is a valid integer using `std::cin >> number`
3. If invalid:
   - Displays error message
   - Clears error flags with `std::cin.clear()`
   - Ignores invalid input up to newline
   - Repeats prompt
4. Returns valid integer when successful

### Main Program Flow

1. Creates a MyInteger object
2. Prompts user to enter an integer (using overloaded `>>` operator)
3. Displays the entered number (using overloaded `<<` operator)
4. Enters a loop to query digits:
   - Asks for a position
   - Uses `[]` operator to retrieve digit at that position
   - If position is invalid (returns -1), prompts to retry
   - If valid, displays the digit and its position, then exits loop

### Key Design Features

- **Encapsulation**: Integer value is private, accessed through public interface
- **Operator overloading**: Provides intuitive syntax for digit access and I/O
- **Friend functions**: Stream operators access private members while maintaining encapsulation
- **Robustness**: Input validation prevents invalid data entry
- **Negative number handling**: Uses absolute value to extract digits from negative integers

