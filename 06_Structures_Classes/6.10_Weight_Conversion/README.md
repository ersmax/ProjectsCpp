Create a class Weight that stores a weight internally in pounds. Create functions
setWeightPounds, setWeightKilograms, and setWeightOunces that
take an input weight in the specified weight scale, convert the weight to pounds
if required, and store that weight in the class’s member variable. Also, create
functions that return the stored weight in pounds, kilograms, and ounces.
Write a main function to test your class. Use the equations shown next to
convert between the weight scales.
1 pound = 16 ounces
1 kilogram = 2.21 pounds

---

# Weigth Conversion Class

## Class Design
The `Weight` class encapsulates weight data and provides a unified interface for working with different weight units
while storing everything internally in pounds.

**Member Variables:**
- `pounds` (double): Private member that stores the weight value internally in pounds (default initialized to 0)

**Public Interface:**
- **Mutators**: `setWeightPounds()`, `setWeightKilograms()`, `setWeightOunces()` 
  - Accept user input in the specified unit and convert/store as pounds
- **Accessors**: `getPounds()`, `getKilograms()`, `getOunces()` - Return the stored weight converted to the requested unit

**Private Helpers:**
- `convertPounds(int ounces)` - Overloaded function that converts ounces to pounds (ounces / 16)
- `convertPounds(double kilograms)` - Overloaded function that converts kilograms to pounds (kilograms × 2.21)
- `inputValidation()` - Validates user input ensuring it's a valid non-negative number

### Key Features

1. **Function Overloading**: The `convertPounds()` function is overloaded to handle both `int` (for ounces) and `double` (for kilograms) parameters. 
   The compiler selects the appropriate version based on the argument type.

2. **Input Validation**: The `inputValidation()` function:
   - Checks if input is a valid number (handles non-numeric input)
   - Ensures weight values are non-negative
   - Clears error states and input buffer when invalid input is detected
   - Loops until valid input is received

3. **Unit Conversion**: 
   - All weights are normalized to pounds internally
   - Conversions use the constants: `POUND_OUNCES = 16.0` and `KILO_POUNDS = 2.21`
   - When setting ounces, `std::floor()` converts the validated double to an integer before conversion

4. **Const Correctness**: All getter methods are marked `const` since they don't modify the object's state

### Program Flow
1. Creates a `Weight` object named `person`
2. Prompts user to enter weight in pounds, stores it, displays all three unit representations
3. Prompts user to enter weight in kilograms, converts and stores, displays all three unit representations
4. Prompts user to enter weight in ounces, converts and stores, displays all three unit representations



