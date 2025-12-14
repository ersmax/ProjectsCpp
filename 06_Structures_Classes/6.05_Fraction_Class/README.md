Define a class for a type called Fraction. This class is used to represent a ratio
of two integers. Include mutator functions that allow the user to set the numerator
and the denominator. Also include a member function that returns the value
of the numerator divided by the denominator as a double. Include an additional
member function that outputs the value of the fraction reduced to lowest terms.
For example, instead of outputting 20/60 the function should output 1/3. This will
require finding the greatest common divisor for the numerator and denominator,
and then dividing both by that number. Embed your class in a test program.

---


# Logic 

- `Fraction` class
  - private members: `numerator`, `denominator` (both `int`).
  - public mutators: `setNumerator()` and `setDenominator()` read values from the user using `inputValidation()`.
  - public accessors: `getNumerator()` and `getDenominator()` return the stored values (marked `const`).
  - `reduce()` prints the fraction reduced to lowest terms by dividing numerator and denominator by the gcd.
  - `divide()` returns the floating-point result of `numerator / denominator` (implemented with `static_cast<double>` to avoid integer division).
  - `findGcd()` computes the greatest common divisor using the binary GCD (Stein) algorithm.

- helper functions
  - `inputValidation()` repeatedly reads from `std::cin` until a valid integer is entered; 
  - it clears the stream and discards the rest of the input line on invalid input.
  - `isEven(int)` returns whether a number is even (uses `% 2`).

- binary GCD (Stein) algorithm used in `findGcd()`
  - remove all common factors of 2 from both numbers, counting how many (stored in `idx`).
  - repeatedly remove factors of 2 from each number and replace the larger by its difference with the smaller until one becomes zero.
  - the result is `(1 << idx) * remaining_nonzero`, which equals `2^idx * gcd_of_odd_parts`.

- notes and caveats
  - The implementation in the repository currently does not normalize or reject negative inputs; `findGcd()` expects nonnegative integers. Passing negative values may yield incorrect results.
  - As an alternative to the custom binary GCD, `std::gcd(std::abs(a), std::abs(b))` (from `<numeric>`) is simpler and handles edge cases when available.

# Resources
- [HS-Based Error Correction Algorithm for Noisy Binary GCD Side](https://link.springer.com/chapter/10.1007/978-3-031-33488-7_3)
- [Binary GCD Algorithm](https://iq.opengenus.org/binary-gcd-algorithm/)

# Pseudocode GCD Stein Algorithm:
```cpp
Input: a, b such that 0 < b < a
Output:	gcd(a, b)
begin

idx = 0; u = a; v = b;
while isEven(u) && isEven(v):
  u /= 2; v /= 2; i++;

while u != 0:
  while isEven(u):
	u /= 2;
  while isEven(v):
	v /= 2;
  if u >= v:
	u = (u - v);
  else:
	v = (v - u);

return (v * (2^idx));	
```