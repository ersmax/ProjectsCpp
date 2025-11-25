Programming Project 2.9 asked you to implement the Babylonian Algorithm to
compute the square root of a number.
Put this algorithm into a function and test it by using it to calculate the square root
of several numbers. The function should return the square root as a double and
also process the number n as a double.
---
Project 2.9: Babylonian Cyclic Square Root
(This is an extension of an exercise from Chapter 1.) The Babylonian algorithm to
compute the square root of a positive number n is as follows:
1. Make a guess at the answer (you can pick n/2 as your initial guess).
2. Compute r = n / guess.
3. Set guess= (guess + r) / 2.
4. Go back to step 2 for as many iterations as necessary. The more steps 2 and 3
   are repeated, the closer guess will become to the square root of n.
   Write a program that inputs a double for n, iterates through the Babylonian algorithm
   until the guess is within 1% of the previous guess, and outputs the answer
   as a double to two decimal places. Your answer should be accurate even for large
   values of n.
---

# Babylonian Square Root

This program implements the Babylonian (Heron) algorithm to compute the square root 
of a positive double value and demonstrates input validation and simple error handling.


## Overview
- Reads a positive number from standard input, computes its square root using the Babylonian algorithm, 
  and prints the result to two decimal places.
- Input is repeatedly requested until the user enters a numeric value greater than 0. 
  The user may repeat the computation interactively.

Building (Windows / CLion / g++)
- In CLion: open the folder containing `14_Babylonian_square_root.cpp` and build/run using the IDE.
- From the command line with a GCC toolchain:
  ```bash
  g++ -std=c++17 -O2 -Wall -Wextra -o 14_Babylonian_square_root 14_Babylonian_square_root.cpp
  ```

Running
- Run the produced executable and follow prompts:
   - Example:
      - Enter a positive number: `25`
      - Output: `Square root is: 5.00`

Input validation
- The helper `inputNumber()` repeatedly prompts:
   - If extraction `cin >> n` fails (non-numeric text), the stream error flags 
     are cleared with `cin.clear()` and the remainder of the current line is discarded with:
     ```
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
     ```
     This discards characters up to and including the next newline so the next prompt starts with fresh input.
   - If a numeric value is read but `n <= 0.0`, the function asks again (the program enforces strictly positive input).

Error handling in `babylonianSquareRoot`
- Negative inputs:
   - If `number < 0.0`, the function returns `std::numeric_limits<double>::quiet_NaN()`.
   - A quiet NaN is a IEEE floating-point "not-a-number" value used 
     to indicate an invalid/unrepresentable result without raising a floating-point exception. 
     Clients can detect it with `std::isnan(result)`.
- Zero:
   - If `number == 0.0`, the function returns `0.0` immediately.
- Division by zero:
   - The iteration logic guards against `guess == 0.0` by resetting `guess` to `1.0` 
     before computing `r = number / guess`.
- Infinite loop prevention:
   - A `maxIterations` cap (10,000) prevents an infinite loop in degenerate cases; 
     the iteration loop exits when the change is within tolerance or the iteration cap is reached.

Algorithm and stopping criterion
- Initial guess: `guess = number / 2`.
- Iteration:
   1. `r = number / guess`
   2. `guess = (guess + r) / 2`
- Stopping condition: stop when the absolute change `|guess - prevGuess|` is less than `FACTOR * prevGuess`, 
  where `FACTOR = 0.01` (1%). This is a relative tolerance to make 
  the stopping criterion scale with the magnitude of the guess.
   - Implementation uses `fabs(guess - prevGuess) > FACTOR * prevGuess`.
   - Note: if `prevGuess` is small or zero, the code avoids division-by-zero by forcing `guess` 
     to a safe nonzero value before dividing.

Output formatting
- Uses:
  ```cpp
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  ```
  to always print results with two digits after the decimal point (e.g., `5.00`).

Design considerations & limitations
- The program enforces strictly positive input via `inputNumber()`. The `babylonianSquareRoot` function 
  also defensively handles `number <= 0.0` so it can be reused independently.
- Using `number / 2` as initial guess is simple and works well for many inputs; for very large 
  or very small inputs a scaled initial guess (e.g., `std::max(1.0, number/2.0)`) can improve robustness.
- The stopping criterion is relative (1%). If more precise results are required, reduce `FACTOR` 
  (for example to `1e-6`) and/or use a smaller absolute tolerance as needed.
- Returning NaN for negative inputs follows the exercise requirement to signal an invalid result; 
  client code should check `std::isnan()` if it needs to handle that case specially.

Testing
- Manual tests to try:
   - Typical: `25` → `5.00`
   - Non-perfect square: `2` → approximately `1.41`
   - Large values: `1e12`
   - Invalid input: type `abc` → the program re-prompts
   - Negative values (if calling `babylonianSquareRoot` directly) → function returns NaN
- Automated tests can call `babylonianSquareRoot` directly and assert:
   - `std::isnan(babylonianSquareRoot(-1.0))` is true
   - `babylonianSquareRoot(0.0) == 0.0`
   - `fabs(babylonianSquareRoot(25.0) - 5.0) < tolerance`

```