Define a class named PrimeNumber that stores a prime number. 
The default constructor should set the prime number to 1. Add another constructor that allows
the caller to set the prime number. Also, add a function to get the prime number.
Finally, overload the prefix and postfix ++ and −− operators so they return a PrimeNumber object that is the next largest prime number (for ++) and the next smallest
prime number (for −−). For example, if the object’s prime number is set to 13, then
invoking ++ should return a PrimeNumber object whose prime number is set to 17.
Create an appropriate test program for the class.

---

## Implementation Overview

### Class Design: PrimeNumber

The `PrimeNumber` class encapsulates a single prime number with the following features:

**Data Members:**
- `int prime`: Stores the prime number value

**Constructors:**
- `PrimeNumber()`: Default constructor that initializes the prime to 1 
- `PrimeNumber(int number)`: Parameterized constructor that sets the prime using `setPrime()`

**Public Methods:**
- `int getPrime() const`: Returns the stored prime number
- `PrimeNumber& operator++()`: Prefix increment - modifies the object to the next prime and returns a reference to itself
- `PrimeNumber operator++(int)`: Postfix increment - saves the current value, modifies to next prime, returns the old value
- `PrimeNumber& operator--()`: Prefix decrement - modifies the object to the previous prime and returns a reference to itself
- `PrimeNumber operator--(int)`: Postfix decrement - saves the current value, modifies to previous prime, returns the old value

**Friend Functions:**
- `operator>>`: Validates that input is prime before accepting it; marks stream as failed if not prime
- `operator<<`: Outputs the prime number value

**Private Methods:**
- `void setPrime(int)`: Sets prime to the given number if it's prime, otherwise finds the closest prime

---

## Prime Number Detection: Iterative vs. Recursive

### Iterative Implementation: `isPrime(int number)`

```cpp
bool isPrime(const int number)
{
    if (number <= 2)
        return (number == 2);
    if (number % 2 == 0)    return false;

    // Check divisibility by all odd numbers up to sqrt(number)
    const int limit = static_cast<int>(std::sqrt(number));
    for (int next = 3; next <= limit; next += 2)
        if (number % next == 0)        
            return false;

    return true;
}
```

**How it works:**
1. **Edge cases**: Numbers ≤ 2 return true only if equal to 2
2. **Even numbers**: All even numbers (except 2) are not prime
3. **Trial division**: Check divisibility by all odd numbers from 3 to √n
4. **Optimization**: Only check up to √n because if n has a divisor larger than √n, it must also have a corresponding divisor smaller than √n

**Characteristics:**
- **Efficient** - single function call overhead
- **No stack concerns** - uses constant stack space
- **Time Complexity**: O(√n)
- **Space Complexity**: O(1) - constant space

---

### Recursive Implementation: `isPrimeRecursive(int number, int divisor = 3)`

```cpp
bool isPrimeRecursive(const int number, const int divisor)
{
    if (number <= 3)        
        return (number == 2 || number == 3);
    if (number % 2 == 0)        // even number
        return false;
    if (number % divisor == 0)  // multiple
        return false;

    // Check divisibility by all odd numbers up to sqrt(number)
    if (divisor * divisor > number)
        return true;
    else
        return isPrimeRecursive(number, divisor + 2);
}
```

**How it works:**
1. **Base cases**: 
   - Numbers ≤ 3: only 2 and 3 are prime
   - Even numbers: return false immediately
2. **Divisibility check**: If current divisor divides the number, it's not prime
3. **Termination condition**: If divisor² > number, we've checked all necessary divisors
4. **Recursive case**: Check next odd divisor (divisor + 2)

**Characteristics:**
- **Function call overhead** - one function call per divisor checked
- **Stack usage** - uses stack space proportional to number of recursive calls
- **Time Complexity**: O(√n) - same as iterative
- **Space Complexity**: O(√n) - due to call stack

---

### Call Stack Analysis

**For iterative version:**
```
main() → isPrime(97)
[Single function call, loop executes internally]
```
- Stack depth: **1 frame**
- Memory usage: Constant

**For recursive version (checking if 97 is prime):**
```
main() → isPrimeRecursive(97, 3)
         → isPrimeRecursive(97, 5)
            → isPrimeRecursive(97, 7)
               → isPrimeRecursive(97, 9)
                  → isPrimeRecursive(97, 11)
                     [returns true when 11² = 121 > 97]
```
- Stack depth: **~√n / 2 frames** (checks odd divisors from 3 to √n)
- For n = 97: ~5 stack frames
- For n = 10,000: ~50 stack frames
- For n = 1,000,000: ~500 stack frames

**Stack Overflow Risk:**
- **Iterative**: **Safe** - no risk regardless of input size
- **Recursive**: **Generally safe** for reasonable prime numbers
  - Maximum depth ≈ √n / 2
  - For n = 1,000,000: ~500 calls (safe)
  - For n = 1,000,000,000: ~15,811 calls (relatively safe on modern systems)
  - Stack overflow is **unlikely** for practical use cases

**Conclusion:**
**The iterative version is superior** due to simplicity, efficiency, and zero stack concerns. 
The recursive version is done for educational purposes to demonstrate recursion techniques, but offers no practical advantage for prime checking.

---

## Helper Functions

### `findNextPrime(int number)`
Finds the smallest prime greater than the given number.

**Algorithm:**
1. Handle special cases (n < 2 → return 2; n = 2 → return 3)
2. Start from the next odd number after `number`
3. Check each odd candidate with `isPrime()`
4. Return the first prime found

**Optimization**: Skips all even numbers (except 2)

---

### `findPreviousPrime(int number)`
Finds the largest prime smaller than the given number.

**Algorithm:**
1. If n ≤ 3, return 2 (smallest prime)
2. Start from the previous odd number before `number`
3. Check each odd candidate with `isPrime()` going backwards
4. Return the first prime found

**Edge case**: Returns 2 when no larger previous prime exists

---

### `findCloserPrime(int number)`
Determines which prime (previous or next) is closest to the given number.

**Algorithm:**
1. Find both `previous` and `next` primes
2. Calculate absolute differences from `number`
3. Return the prime with smaller difference
4. If tied, prefer the previous prime (≤ comparison)

**Side effect**: Prints diagnostic information showing both candidates and the chosen closest prime

---

### `numberValidation()`
Provides robust input validation with error recovery.

**Algorithm:**
1. Read integer from `std::cin`
2. If read fails:
   - Print error message
   - Clear error flags
   - Ignore invalid input
   - Loop to retry
3. Clear remaining input buffer
4. Return valid number as `PrimeNumber` object

**Note**: Uses `std::numeric_limits` to clear entire input line

---

## Operator Overloading Design Decisions

### Prefix vs. Postfix Semantics

**Prefix operators (`++obj`, `--obj`):**
- Modify the object **first**
- Return reference to **modified** object
- Return type: `PrimeNumber&`
- Allow chaining: `++(++obj)` is valid
- More efficient (no copy needed)

**Postfix operators (`obj++`, `obj--`):**
- Save **old** value
- Modify the object
- Return **old** value as a **const** temporary
- Return type: `const PrimeNumber`
- Prevent nonsense: `(obj++)++` is prevented by const
- Less efficient (requires copy)

### Why `const` Return for Postfix?

Returning `const PrimeNumber` from postfix operators prevents chaining like `(a++)++`, 
which would increment a temporary object (meaningless operation). 
This follows Scott Meyers' recommendation in "Effective C++" for safer code.

Alternative: Standard library uses non-const returns to match built-in types, 
but const is considered better practice for user-defined types.

---

## Test Program Analysis

The test program demonstrates:
1. **Input validation** via `numberValidation()`
2. **Prefix decrement**: `--aPrime` modifies and returns reference
3. **Postfix decrement**: `aPrimeCopy--` returns old value, then modifies
4. **Prefix increment**: `++aPrimeCopy2` modifies and returns reference
5. **Postfix increment**: `aPrimeCopy3++` returns old value, then modifies

**Example output for input 13:**
```
Enter a number:
13
The prime number is: 13
--13: 11          [prefix: shows new value]
13--: 13          [postfix: shows old value]
++11: 13          [prefix: shows new value]
13++: 13          [postfix: shows old value]
```

The prefix operators show the **new** value, 
while postfix operators show the **old** value, demonstrating the fundamental difference between them.
