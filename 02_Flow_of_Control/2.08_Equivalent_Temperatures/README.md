Write a program that finds the temperature, as an integer, that is the same in both
Celsius and Fahrenheit. The formula to convert from Celsius to Fahrenheit is as
follows:
Fahrenheit = (9/5)*Celsius + 32
Your program should create two integer variables for the temperature in Celsius
and Fahrenheit. Initialize the temperature to 100 degrees Celsius. In a loop, decrement
the Celsius value and compute the corresponding temperature in Fahrenheit
until the two values are the same.

============================================================================================

Purpose
The program finds the temperature (as an integer) where Celsius and Fahrenheit scales are equal.

Logic
The formula for converting Celsius to Fahrenheit is:
Fahrenheit = (9/5) * Celsius + 32
The program starts at 100°C and decrements the Celsius value until it matches the Fahrenheit value.

Steps
1. Initialize Variables:
   - `tempCelsius` starts at 100.
   - `tempFahr` stores the Fahrenheit equivalent.

2. Loop:
   - Convert Celsius to Fahrenheit using the formula.
   - Check if Celsius equals Fahrenheit.
   - If not, decrement Celsius and repeat.
