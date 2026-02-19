Modify the definition of the class Money shown in Playground Display 8.0.5 so that the following
are added:
a. The operators <, <=, >, and >= have each been overloaded to apply to the type
Money. (Hint: See Self-Test Exercise 8.)
b. The following member function has been added to the class definition. (We
show the function declaration as it should appear in the class definition. The
definition of the function itself will include the qualifier Money::.)
const Money percent(int percentFigure) const;
//Returns a percentage of the money amount in the calling
//object. For example, if percentFigure is 10, then the value
//returned is 10% of the amount of money represented by the
//calling object.
For example, if purse is an object of type Money whose value represents the
amount $100.10, then the call
purse.percent(10);
returns 10% of $100.10; that is, it returns a value of type Money that represents
the amount $10.01.

---

## Implementation Logic

### Class Design
The `Money` class stores monetary amounts using two `int` members:
- `dollars`: the dollar part of the amount
- `cents`: the cents part of the amount

**Negative amounts** are represented with both dollars AND cents negative 
(e.g., -$4.50 = -4 dollars, -50 cents). This design simplifies comparison operations.

### Constructors
1. **Default constructor**: Initializes to $0.00
2. **Double constructor**: Converts a double to dollars and cents using helper methods
   - `dollarsPart()`: Extracts integer part (truncates towards zero)
   - `centsPart()`: Extracts fractional part and rounds to nearest cent
   - `round()`: Uses `std::floor(number + 0.5)` to round away from zero for both positive and negative numbers.
	  Then it applies the cast to int to get the final cents value. This ensures that -$4.50 correctly rounds to -4 dollars and -50 cents, 
	  while $4.50 rounds to 4 dollars and 50 cents.
3. **Two-int constructor**: Takes dollars and cents separately, validates they have consistent signs
4. **Single-int constructor**: Creates amount with only dollars (cents = 0)

### Comparison Operators (Part a)
All comparison operators use the same logic pattern:
- **First**, compare dollars
- **If dollars are equal**, compare cents
- Works correctly with negative amounts because both dollars and cents share the same sign

Examples:
- `operator<`: Returns true if (dollars < other.dollars) OR (dollars equal AND cents < other.cents)
- `operator<=`: Similar but allows cents equality
- `operator>`: Reversed logic from `<`
- `operator>=`: Reversed logic from `<=`

### Percent Function (Part b)
Calculates a percentage of the money amount:
1. Converts the Money object to a total decimal amount: `dollars + cents * 0.01`
2. Multiplies by the percentage factor: `0.01 * percentFigure`
3. Returns a new Money object using the double constructor

Example: `Money($100.10).percent(10)` = `0.1 * 100.10` = `$10.01`

### Arithmetic Operators
Addition and subtraction operators:
1. Convert both amounts to total cents (dollars * 100 + cents)
2. Perform the operation on total cents
3. Handle negative results using absolute values
4. Convert back to dollars and cents
5. Apply negative sign to both dollars and cents if result is negative

This avoids issues with integer division and modulo on negative numbers.
From the literature (Savitch, Absolute C++, 6th edition, p. 50):
When used with negative values of type int, the result of the operators / and % can
be different for different implementations of C++. Thus, you should use / and % with
int values only when you know that both values are nonnegative.

### Input/Output Operators
- **Output (`<<`)**: Formats as `$dollars.cents` or `-$dollars.cents`, always shows 2 decimal places
- **Input (`>>`)**: Expects format `$amount` (e.g., `$10.50`), validates dollar sign, uses double constructor

### Key Design Decisions
1. **Negative representation**: Both components negative ensures comparison operators work naturally
2. **Rounding**: Uses `std::floor(number + 0.5)` for proper "round half away from zero" behavior
3. **Friend functions**: Operators are friends to access private members directly for efficiency
4. **Const correctness**: Getters and percent function are const; operators return const Money to prevent misuse

---


