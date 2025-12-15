Do Programming Project 6.8, except remove the two private integer variables and
use a single variable of type double to store the monetary value in their place. The
rest of the functions should have the same headers. For several functions, this will
require code to convert from an integer format to appropriately modify the double.
For example, if the monetary amount stored in the double is 4.55 (representing
$4.55) and if the function to set the dollar amount is invoked with the value 13,
then the double should be changed to 13.55. While this will take some work, the
code in your test program from Programming Project 6.8 should still work without
requiring any changes. This is the benefit of encapsulating the member variables.

---

# Key Improvement: Encapsulation and Internal Representation Change

This program demonstrates **encapsulation** by maintaining the same public interface 
as Project 6.08 while completely changing the internal data representation. 
The external behavior remains identical, showcasing the benefit of separating interface from implementation.

### Internal Representation

**Version 6.08 (Previous):**
- Two separate `int` member variables: `dollars` and `cents`
- Storage: `dollars = 4`, `cents = 55` represents $4.55

**Version 6.09 (Current):**
- Single `double` member variable: `amount`
- Storage: `amount = 4.55` represents $4.55
- More compact and mathematically natural representation

### Core Logic Changes

#### 1. `setDollars()` - Preserving Cents When Updating Dollars

```cpp
void Money::setDollars()
{
    const int input = inputValidation();
    const double remainingCents = amount - static_cast<int>(amount);
    amount = input + remainingCents;
}
```

**Logic:**
- Extract the fractional part (cents) from the current `amount` using `amount - static_cast<int>(amount)`
- Example: If `amount = 4.55`, then `remainingCents = 4.55 - 4 = 0.55`
- Set new amount to `input + remainingCents` (e.g., `13 + 0.55 = 13.55`)
- **Key insight:** The cents are preserved when updating only the dollar portion

#### 2. `setCents()` - Normalizing Cents to Dollars + Remainder

```cpp
void Money::setCents()
{
    const int cents = inputValidation();
    const int dollars = std::floor(amount) + cents / 100;
    const int remainingCents = cents % 100;
    amount = dollars + (static_cast<double>(remainingCents) / 100.0);
}
```

**Logic:**
- Extract current dollar amount using `std::floor(amount)`
- Handle cents ≥ 100 by converting to additional dollars: `cents / 100` (integer division)
- Calculate leftover cents: `cents % 100`
- Reconstruct `amount` with updated dollars and normalized cents
- **Example:** If `amount = 4.55` and user enters `150` cents:
  - `dollars = 4 + 150/100 = 4 + 1 = 5`
  - `remainingCents = 150 % 100 = 50`
  - `amount = 5 + 0.50 = 5.50`

#### 3. `getDollars()` and `getCents()` - Extracting Integer Components

```cpp
int Money::getDollars() const
{
    return std::floor(amount);
}

int Money::getCents() const
{
    const double cents = (amount - std::floor(amount)) * 100.0;
    return static_cast<int>(cents);
}
```

**Logic:**
- `getDollars()`: Extract whole-dollar portion using `std::floor()`
- `getCents()`: Extract fractional part, multiply by 100, and cast to `int`
- **Example:** If `amount = 4.55`:
  - `getDollars()` returns `4`
  - Fractional part: `4.55 - 4.0 = 0.55`
  - `getCents()` returns `static_cast<int>(0.55 * 100.0) = 55`

#### 4. `convertMoney()` - Reconstructing Double from Components

```cpp
double Money::convertMoney() const
{
    return (getDollars() + static_cast<double>(getCents()) / 100.0);
}
```

**Logic:**
- Get integer dollars and cents via accessors
- Convert cents to fractional dollars: `getCents() / 100.0`
- Add together to reconstruct the monetary value
- **Note:** Could be simplified to `return amount;` 
  since `amount` already stores the correct value, 
- but current implementation demonstrates proper type conversion and tests the accessor methods

### Main Function Enhancement

**Version 6.08:**
- Tests with only one `Money` object

**Version 6.09:**
- Creates an **array of 2 `Money` objects**: `Money aTransaction[2];`
- Uses a loop to test both objects
- Satisfies the requirement to "test all of your functions with at least two different Money objects"
- Demonstrates that arrays of class objects work with different API 

### Benefits of This Approach

1. **Encapsulation:** The Abstract Programming Interface (`setDollars()`, `setCents()`, `convertMoney()`) remains unchanged despite the internal representation shift
2. **Backward Compatibility:** Code that used the 6.08 version would work with 6.09 without modification
3. **Memory Efficiency:** One `double` (8 bytes) vs. two `int`s (8 bytes total) - similar memory but simpler conceptually
4. **Mathematical Clarity:** Using a `double` is more natural for monetary values
5. **Flexibility:** Easier to extend with operations like addition, subtraction, multiplication

### Potential Improvements (Future Considerations)

- **Floating-point precision:** For production financial software, consider using integer cents (e.g., store 455 for $4.55) or a fixed-point library to avoid floating-point rounding errors
- **Const correctness:** Mark `getDollars()` and `getCents()` as `const` (already done in version 6.09)
- **Simplify `convertMoney()`:** Could return `amount` directly instead of reconstructing via accessors
- **Add constructors:** Allow initialization with dollars and cents in the constructor
- **Overload operators:** Add `+`, `-`, `*`, `/`, comparison operators for more natural usage