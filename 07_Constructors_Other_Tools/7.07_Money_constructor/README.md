Do Programming Project 6.8, the definition of a Money class, 
except create a default constructor that sets the monetary amount to 0 dollars and 0 cents, and create
a second constructor with input parameters for the amount of the dollars and cents
variables. Modify your test code to invoke the constructors.

---

## Code Logic

### Money Class
The `Money` class represents a monetary amount with two private integer member variables:
- `dollars`: stores the dollar amount
- `cents`: stores the cent amount

**Constructors:**
1. **Default constructor**: `Money()` - Initializes both dollars and cents to 0
2. **Single parameter constructor**: `Money(const int dollars)` - Sets dollars and initializes cents to 0
3. **Two parameter constructor**: `Money(const int dollars, const int cents)` - Sets both dollars and cents

**Member Functions:**
- `setDollars(int money)`: Validates and sets the dollar amount. Throws `std::invalid_argument` if the value is negative.
- `setCents(int money)`: Validates and sets the cent amount. Throws `std::invalid_argument` if the value is negative.
- `getDollars()`: Returns the current dollar amount.
- `getCents()`: Returns the current cent amount.
- `convertMoney()`: Converts the monetary amount to a double by combining dollars and cents (handles cents >= 100 by calculating quotient and remainder).

### Main Program Flow
1. Prompts the user to enter dollar and cent amounts
2. Uses `inputValidation()` to ensure valid non-negative integer input
3. Creates a `Money` object using the two-parameter constructor wrapped in a try-catch block
4. If valid, displays the equivalent monetary amount as a double using `convertMoney()`
5. If invalid (negative values), catches the exception and displays an error message

### Input Validation
The `inputValidation()` function:
- Validates that input is a valid integer
- Ensures the value is non-negative (>= 0)
- Clears and ignores invalid input, prompting the user to re-enter
- Returns the validated integer value

### Exception Handling
The program uses exception handling to manage invalid monetary values:
- Constructors call setter methods that throw `std::invalid_argument` for negative values
- The main function catches these exceptions and displays appropriate error messages
- This prevents the creation of `Money` objects with invalid negative amounts


