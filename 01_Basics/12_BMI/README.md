A simple rule to estimate your ideal body weight is to allow 110 pounds for the
first 5 feet of height and 5 pounds for each additional inch. Write a program with
a variable for the height of a person in feet and another variable for the additional
inches and input values for these variables from the keyboard. Assume the person
is at least 5 feet tall. For example, a person that is 6 feet and 3 inches tall would be
represented with a variable that stores the number 6 and another variable that stores
the number 3. Based on these values calculate and output the ideal body weight.

===================================================================================


This program estimates a person's ideal body weight based on their height in feet and inches.

Code Choices Explained:
- Input/Output: Uses `cin` and `cout` for user interaction, prompting for height in feet and inches.
- Input Validation: Checks that the height in feet is between 5 and 7 (inclusive),
  ensuring reasonable input.
- Variable Declaration: Uses `int` for all variables since height and weight are whole numbers.
- Calculation Logic:
  - Starts with 110 pounds for the first 5 feet.
  - Adds 5 pounds for each additional inch above 5 feet.
  - Calculates extra inches from feet above 5 using `((height_feet - 5) * 12 * 5)`.
- Output: Displays the calculated ideal body weight in pounds.

Process Overview:
1. Prompt user for height in feet and inches.
2. Validate input range.
3. Calculate ideal body weight using the given rule.
4. Output the result.

===============================================================================