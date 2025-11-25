Write a function named convertToLowestTerms that inputs two integer parameters
by reference named numerator and denominator. The function should treat
these variables as a fraction and reduce them to lowest terms. For example, if
numerator is 20 and denominator is 60, then the function should change the
variables to 1 and 3, respectively. This will require finding the greatest common
divisor for the numerator and denominator then dividing both variables by that
number. If the denominator is zero, the function should return false, otherwise the
function should return true. Write a test program that uses convertToLowestTerms
to reduce and output several fractions.

---

# Analysis of GCD Calculation Methods and Sign Handling

## 1. Prime-factorization approach (`vector<int>` of prime factors)
- `findFactors(number)`:
    - Works on `abs(number)`.
    - Uses trial division starting at 2; whenever `divisor` divides `number` it pushes `divisor` into the vector, 
      and divides `number` by `divisor`. This produces prime factors with multiplicity in ascending order (e.g. 60 -> [2,2,3,5]).
    - Returns an empty vector for `0` or `1`.
- `findPrimeFactorizationGCD(numer, denom, gcd)`:
    - Builds two sorted lists of prime factors.
    - Uses two-pointer merge logic to multiply common primes into `gcd`. If both lists contain the same prime, that prime is a common factor and is multiplied into `gcd`. This yields the product of all common prime factors (the GCD).
    - This method correctly handles multiplicities (e.g. common [2,2] yields factor 4).
- Notes / limitations:
    - Trial division is simple but slow for large numbers.
    - Returning empty for `1` or `0` requires careful handling in the caller.
    - The code tackles the case when both numbers are negative (gcd negative), or one is negative (gcd positive)
      by using the standard library absolute value function `std::abs()`.


## 2. Euclidean GCD (the common and well-known remainder algorithm)
- Core idea:
    - gcd(a,b) = gcd(b, a mod b). Repeatedly replace (a,b) with (b, a % b) until the remainder is 0. The nonzero value then is the gcd.
- Step\-by\-step for the example `1071` and `462` (showing quotients and remainders):
    - 1071 = `462` * 2 + 147  -> remainder 147
    - `462`  = `147` * 3 + 21   -> remainder 21
    - `147`  = `21`  * 7 + 0    -> remainder 0
    - Stop: gcd = `21`
    - The quotients encountered are 2, 3, 7; the final nonzero divisor is `21` when remainder = 0.
- Implementation notes:
    - The code tackles the case when both numbers are negative (gcd negative), or one is negative (gcd positive)
      by using the standard library absolute value function `std::abs()`.

## Notes
- By definition gcd is non\-negative.
- Hence, `std::abs(number)` is always used before computations