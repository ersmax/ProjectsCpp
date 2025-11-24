Scientists estimate that consuming roughly 10 grams of caffeine at once is a lethal
overdose. Write a program that inputs the number of milligrams of caffeine in
a drink and outputs how many of those drinks it would take to kill a person. A
12-ounce can of cola has approximately 34 mg of caffeine, while a 16-ounce cup
of coffee has approximately 160 mg of caffeine.

====================================================================================

This program calculates how many drinks containing a user-specified amount of caffeine
would be required to reach a lethal dose (estimated at 10,000 mg).

Key Features:
- Input: Prompts the user to enter the caffeine content (in mg) per drink.
- Calculation: Divides the lethal dose by the caffeine per drink to estimate the number of drinks.
  If the division is not exact, it adds one more drink to ensure the lethal dose is reached or exceeded.
- Output: Displays the approximate number of drinks needed for a lethal dose.

Process Overview:
1. Ask the user for caffeine content per drink.
2. Compute the minimum number of drinks to reach 10,000 mg.
3. Output the result in a clear sentence.

Important notes:
If the variable caffeine_mg were to be declared as an int,
we would need to use the modulo operator (%) to check if there is a remainder when dividing
lethal_dose_mg by caffeine_mg.
If there is a remainder, we would need to add 1 to the result of the division to ensure
we round up to the next whole number of drinks.

However, since caffeine_mg is declared as a float, we can simply use the if statement to check
if the division lethal_dose_mg / caffeine_mg is not an integer (i.e., if there is a remainder).
As an alternative, we could use the ceil function from the cmath library to round up the result
of the division to the next whole number.
If there is a remainder, we add 1 to the result of the division to round up to
the next whole number of drinks.
====================================================================================