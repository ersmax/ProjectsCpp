In cryptarithmetic puzzles, mathematical equations are written using letters. Each
letter can be a digit from 0 to 9, but no two letters can be the same. Here is a
sample problem:
SEND + MORE = MONEY
A solution to the puzzle is S = 9, R = 8, O = 0, M = 1, Y = 2, E = 5, N = 6, D = 7.
Write a program that finds solutions to the following cryptarithmetic puzzle:
TOO + TOO + TOO + TOO = GOOD
The simplest technique is to use a nested loop for each unique letter (in this case T,
O, G, D). The loops would systematically assign the digits from 0–9 to each letter.
For example, it might first try T = 0, O = 0, G = 0, D = 0, then T = 0, O = 0, G = 0,
D = 1, then T = 0, O = 0, G = 0, D = 2, etc. up to T = 9, O = 9, G = 9, D = 9.
In the loop body, test that each variable is unique and that the equation is satisfied.
Output the values for the letters that satisfy the equation.

=================================================================================

Documentation:
This program solves the cryptarithmetic puzzle:
`TOO + TOO + TOO + TOO = GOOD`.
Each letter represents a unique digit from 0 to 9.
The program uses four nested loops to systematically assign digits
to the letters T, O, G, and D.
For each combination, it checks that all digits are unique and that the equation is satisfied.
If a valid solution is found, it prints the digit assignments.

Logic:
- Using four nested loops to assign digits 0–9 to the letters T, O, G, and D.
- Each assignment ensures all digits are unique by skipping repeated values.
- For each valid assignment, it calculates the numeric values of `TOO` and `GOOD`.
- It checks if four times `TOO` equals `GOOD`.
- If the equation holds, it prints the solution and counts it.
- The program outputs all valid digit assignments that solve the puzzle.

There is an if statement to ensure that all letters are assigned unique digits
after each for loop. This is done by checking that no two letters have the same digit.

This is also done to avoid checking different letters in the inner loop that have the same digit.
This would cause unnecessary calculations and slow down the program (quadratic time complexity).
=================================================================================