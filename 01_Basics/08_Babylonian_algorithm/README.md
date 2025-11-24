The Babylonian algorithm to compute the square root of a positive number n is as
follows:
1. Make a guess at the answer (you can pick n/2 as your initial guess).
2. Compute r = n / guess.
3. Set guess = (guess + r) / 2.
4. Go back to step 2 for as many iterations as necessary. The more steps 2 and 3
   are repeated, the closer guess will become to the square root of n.

Write a program that inputs a double for n, iterates through the Babylonian
algorithm five times, and outputs the answer as a double to two decimal places.
Your answer will be most accurate for small values of n.

==================================================================

This program implements the Babylonian algorithm to approximate
the square root of a positive number:

- Input Handling: Prompts the user to enter a positive number (`n`).
- Initial Guess: Sets the initial guess to `n / 2.0`, a common starting point for the algorithm.
- Iteration: Uses a `for` loop to repeat the Babylonian steps five times (as specified by `ITERATIONS`).
- Algorithm Steps:
  In each iteration, computes `r = n / guess` and updates `guess = (guess + r) / 2.0`.
- Early Convergence: If `guess` equals `sqrt(n)`, the loop breaks early, indicating convergence.
- Output Formatting: Sets output to fixed-point notation with two decimal places for clarity.
- Result Display**: Outputs the approximate square root.

Choice Rationale:
- The `for` loop is chosen for a fixed number of iterations, matching the problem requirements.
- The `if` statement inside the loop allows for early exit if the result converges before five iterations.
- Output formatting ensures the result is user-friendly and precise to two decimal places.

==================================================================