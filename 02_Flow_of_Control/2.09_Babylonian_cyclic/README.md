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
=============================================================================================

Algorithm
1. Initial Guess: Start with `n / 2.0` as the initial guess.
2. Iterative Steps:
   - Compute `r = n / guess`.
   - Update `guess = (guess + r) / 2`.
3. Stopping Condition:
   Stop when the absolute difference between the current guess
   and the previous guess is less than 1% of the previous guess.

Steps
1. Input: Read a positive number `n` from the user.
2. Output Formatting: Set the output to display two decimal places.
3. Loop:
   - Update the guess using the Babylonian algorithm.
   - Check the stopping condition.
4. Output: Print the approximate square root of `n`.

==============================================================================================