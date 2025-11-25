Write a program that finds and prints all of the prime numbers between 3 and 100.
A prime number is a number that can only be divided by one and itself (i.e., 3, 5,
7, 11, 13, 17, . . .).
One way to solve this problem is to use a doubly-nested loop. The outer loop can
iterate from 3 to 100, while the inner loop checks to see whether the counter
value for the outer loop is prime. One way to decide whether the number n is
prime is to loop from 2 to n − 1; if any of these numbers evenly divides n, then
n cannot be prime. If none of the values from 2 to n − 1 evenly divide n, then
n must be prime. (Note that there are several easy ways to make this algorithm
more efficient.)

================================================================================

This program prints all prime numbers between 3 and 100.
A prime number is a number greater than 1 that is only divisible by 1 and itself.
The program uses a nested loop:
- The outer loop iterates through each number from 3 to 100.
- For each number, the inner loop checks divisibility by all integers
  from 2 up to the square root of the number.
- If no divisors are found, the number is prime and printed.

Why check until sqrt(n)?
If a number `n` has a divisor greater than its square root,
the paired divisor must be less than or equal to the square root.
If no divisors are found up to `sqrt(n)`, `n` is prime.
This reduces the number of checks and improves efficiency.

Program Explanation:
- Start with `n = 3` and increment up to 100.
- For each `n`, check if any integer `m` from 2 to `sqrt(n)` divides `n` evenly.
- If none do, print `n` as a prime number.
- The program uses `std::cout` for output and `std::sqrt` for efficient checking.
- The result is a list of all prime numbers between 3 and 100.
=================================================================================