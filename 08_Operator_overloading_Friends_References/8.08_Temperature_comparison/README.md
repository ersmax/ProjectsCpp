Do Programming Project 6.10 in Playground, the definition of a Temperature class, 
except overload ==, << and >> as member operators. The == operator should return true if the
two temperature values are identical, while << should output the temperature in
Fahrenheit and >> should input the temperature in Fahrenheit. Create appropriate
tests for the overloaded operators.
Fahrenheit = (9/5)*Celsius + 32

---

## Program Logic

### Overview
This program implements a `Temperature` class that can store temperatures 
in either Fahrenheit ('F') or Celsius ('C'), with overloaded operators for comparison, input, and output. 
The program demonstrates proper operator overloading using both member functions and friend functions.

### Class Structure

#### Private Members
- `double degrees` - Stores the temperature value
- `char scale` - Stores the scale ('F' for Fahrenheit, 'C' for Celsius)

#### Private Helper Methods
1. **`set(double newDegrees, char newScale)`**
   - Validates that the scale is either 'F' or 'C'
   - Throws `std::invalid_argument` if the scale is invalid
   - Sets the member variables

2. **`fahrenheitToCelsius()`**
   - Converts Fahrenheit temperature to Celsius
   - Formula: `Celsius = (Fahrenheit - 32) / (9/5)`
   - Throws exception if current scale is not 'F'

3. **`celsiusToFahrenheit()`**
   - Converts Celsius temperature to Fahrenheit
   - Formula: `Fahrenheit = (9/5) * Celsius + 32`
   - Throws exception if current scale is not 'C'

### Operator Overloading

#### 1. Equality Operator (`operator==`) - Member Function
- **Purpose**: Compares two temperatures for equality
- **Logic**:
  - Uses assertions to verify both temperatures have valid scales ('C' or 'F')
  - Converts both temperatures to Fahrenheit for comparison
  - Uses ternary operator: if already in Fahrenheit, use directly; otherwise convert
  - Compares the Fahrenheit values with epsilon tolerance (1e-6) to handle floating-point precision
- **Why member function**: The equality operator naturally fits as a member function since it compares the current object with another

#### 2. Input Operator (`operator>>`) - Friend Function
- **Purpose**: Reads temperature from input stream
- **Logic**:
  - Reads a double value (degrees) and a character (scale)
  - Validates that the scale is 'F' or 'C'
  - If invalid, sets the stream's failbit flag to indicate failure
  - If valid, directly sets the temperature's private members
  - Returns the input stream for chaining
- **Why friend function**: Must be non-member to allow natural syntax `std::cin >> temperature` (not `temperature >> std::cin`)
- **Why friend**: Needs direct access to private members `degrees` and `scale` for efficiency

#### 3. Output Operator (`operator<<`) - Friend Function
- **Purpose**: Writes temperature to output stream in Fahrenheit
- **Logic**:
  - If temperature is already in Fahrenheit, outputs degrees and 'F'
  - If temperature is in Celsius, converts to Fahrenheit first, then outputs
  - Always outputs in Fahrenheit format regardless of internal storage
  - Returns the output stream for chaining
- **Why friend function**: Must be non-member to allow natural syntax `std::cout << temperature` (not `temperature << std::cout`)
- **Why friend**: Needs direct access to private members `degrees` and `scale`

### Main Program Flow

1. **Input Phase**:
   - Prompts user to enter three temperatures
   - Uses `temperatureValidation()` helper function for each input
   - Handles invalid input with error messages and retry logic

2. **Display Phase**:
   - Outputs all three temperatures in Fahrenheit (via `operator<<`)

3. **Comparison Phase**:
   - Compares all three pairs of temperatures using `operator==`
   - Displays which temperatures are equal
   - Correctly identifies equal temperatures even if stored in different scales (e.g., 0°C equals 32°F)

### Helper Function: `temperatureValidation()`
- **Purpose**: Robust input validation with error recovery
- **Logic**:
  - Loops until valid input is received
  - Uses `operator>>` to attempt reading a temperature
  - If input fails:
    - Displays error message
    - Clears error flags with `std::cin.clear()`
    - Ignores remaining invalid input with `std::cin.ignore()`
    - Continues loop for retry
  - If successful, clears remaining input buffer and returns the temperature

### Error Handling

1. **Input Validation** (in `operator>>`):
   - Sets stream failbit for invalid scales
   - Allows the calling code to detect and handle errors

2. **Construction Validation** (in `set()`):
   - Throws `std::invalid_argument` for invalid scales
   - Caught by try-catch block in `main()`

3. **Conversion Validation**:
   - `fahrenheitToCelsius()` throws if not in Fahrenheit
   - `celsiusToFahrenheit()` throws if not in Celsius
   - Prevents logical errors from incorrect conversions

4. **Assertions** (in `operator==`):
   - Debug-time checks to verify scales are valid
   - Can be disabled with `#define NDEBUG`

### Key Design Decisions

1. **Stream Operators as Friends**:
   - Cannot be member functions because the left operand must be the stream (not the Temperature object)
   - Friend access allows efficient direct manipulation of private members
   - This is the standard C++ idiom for stream operators

2. **Epsilon Comparison**:
   - Uses `EPSILON = 1e-6` for floating-point comparisons
   - Avoids precision errors inherent in floating-point arithmetic
   - Example: 0.1 + 0.2 might not exactly equal 0.3

3. **Always Output in Fahrenheit**:
   - Consistent output format regardless of internal storage
   - Simplifies user experience
   - Meets requirement: "output the temperature in Fahrenheit"

4. **Conversion on Demand**:
   - Temperatures stored in their original scale
   - Converted only when needed (for comparison or output)
   - More efficient than converting on input

---

