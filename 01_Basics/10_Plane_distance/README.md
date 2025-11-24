Write a program that reads the speed of an airplane in miles per hour and the travel
time in hours. The program should display the distance traveled by the airplane in
that time in miles, and its speed in meters per second. Use the equation
Speed in m/s = (Speed in MPH/3600) X 1609.344

==================================================================================

This program calculates the distance traveled by an airplane and its speed in meters per second,
given its speed in miles per hour and travel time in hours.

Code Choices Explained:
- Formatting Output: Sets output to fixed-point notation with two decimal places for clarity
- Variable Types: Uses `float` for all calculations to avoid type conversion warnings.
- Distance Calculation: Multiplies speed in MPH by time in hours to get distance in miles.
- Speed Conversion: Converts speed from miles per hour to meters per second using the formula:
  `Speed in m/s = (Speed in MPH / 3600) * 1609.344`
  The constants `3600.0f` and `1609.344f` are used as floats to match the variable types.
- Output: Displays both the distance in miles and the converted speed in meters per second.

Process Overview:
1. Prompt user for speed (MPH) and time (hours).
2. Calculate distance in miles.
3. Convert speed to meters per second.
4. Display results with formatted output.