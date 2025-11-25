Enhance your program from the previous exercise by having it also print out the
estimated annual salary of the employee in one or two years from the time of the
calculation. The increase in annual salary is estimated as the hike rate times the
salary at the start of the year. Define a second function to determine the estimated
salary of the employee after a specified number of years, given the current salary of
the employee and the hike rate as arguments.

==============================================================================

- Purpose:
  Estimates future annual salaries and the total sum of future salaries for an employee,
  based on current and prior salary, using a constant hike rate.

- Functions:
  - `double raise(double currentSalary, double priorSalary)`
    Calculates the salary hike rate as a percentage increase from the prior salary.
    - Precondition: `priorSalary` is not zero.
    - Postcondition: Returns the hike rate as a decimal (e.g., 0.05 for 5%).

  - `void futureRaise(double currentSalary, double salaryHike, int years)`
    Prints the estimated salary for each year over a specified period, applying compound growth.

  - `double totalFutureRaise(double currentSalary, double salaryHike, int years)`
    Computes the sum of all future salaries over the given period,
    using the geometric progression formula (annuity)

  - `void displayFutureRaise(int numberYears, double totalFutureRaise)`
    Displays the total sum of future salaries for the specified number of years.

- Main Flow:
  - Prompts the user for current and last year salaries.
  - Validates input (salaries must be positive).
  - Calculates the hike rate.
  - Prompts for the number of years to predict.
  - Displays estimated future salaries and their total sum.
  - Allows repeated calculations.

- Formatting:
  Uses fixed-point notation with two decimal places for salary outputs.

- Error Handling:
  Prints an error message if input salaries are negative or zero.

=================================================================================