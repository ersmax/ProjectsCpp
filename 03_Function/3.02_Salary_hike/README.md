Write a program to gauge the rate of an employee’s raise from the previous year.
The program asks for their annual salary in this year and the previous year. It estimates
the hike percentage as the difference in their salary from the previous year
divided by the previous year’s salary. Your program should allow the user to repeat
this calculation as often as the user wishes. Define a function to compute the hike
percentage for an employee. The hike rate should be a value of type double giving
the rate as a percentage, for example 5.3 for 5.3%.

==================================================================================


- The logic is split into functions:
  - `raise` computes the hike percentage, isolating calculation logic for reuse and testing.
  - `displayHike` handles output formatting and error messages, keeping main logic clean.

- Input validation checks for negative salaries and zero prior salary, ensuring robust error handling.
- Output formatting uses `ios::fixed` and `ios::showpoint` for consistent decimal display,
  improving readability.
- The main loop allows repeated calculations

==================================================================================