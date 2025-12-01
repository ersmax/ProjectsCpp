Write a rating program for a software development firm with the following rating
policies.
a. Core competency – This parameter measures an employee’s involvement, innovation,
and passion toward their assigned tasks, and is graded on 10 points.
b. Performance evaluation – This parameter measures an employee’s performance
over the year, and is graded on 30 points.
c. Ideation – An employee is measured on their patent submissions, patents
awarded, technical papers presented, etc. and is graded on 10 points.
d. The performance evaluation accounts for 50% of an employee’s final rating,
core competency accounts for 30%, and ideation accounts for 20%.
The total points obtained by an employee are summed up and normalized. Employees
with points of 80 or more are rated a 1, those between 60 to 79 are rated a
2, those between 50 to 59 are rated a 3, and those less than 50 are rated a 4.
The program will read an employee’s points against the three criteria and output
the total points obtained on a scale of 100, and the final rating point. Define and
use a structure for the employee records.

---
# Overview
The program collects three component scores from the user:
- Core competency: 0–10
- Performance evaluation: 0–30
- Ideation: 0–10

Each component is weighted and combined to produce a total on a 0–100 scale:
- Performance: 50% (contributes up to 50 points)
- Core competency: 30% (contributes up to 30 points)
- Ideation: 20% (contributes up to 20 points)

## Normalization formula
Each raw score is converted to a fraction of its maximum, multiplied by its weight, and scaled to the 0..100 range. The code computes the total as:
Total =
- (performance / 30.0) * (0.50 * 100.0) +
- (coreCompetency / 10.0) * (0.30 * 100.0)
- (ideation / 10.0) * (0.20 * 100.0)

## Rating thresholds
- total >= 80.0 → rating 1
- 60.0 <= total < 80.0 → rating 2
- 50.0 <= total < 60.0 → rating 3
- total < 50.0 → rating 4

## Functions
1. setSkills(Skills& employee): Prompts the user for each component, validates ranges, and stores values in the Skills struct. Accepts -1 as a sentinel to exit.
2. inputData(): Reads and returns a double from standard input while handling invalid input. Callers rely on -1 to exit.
3. normalize(const Skills& employee): Calculates and returns the normalized total score (0..100) using the normalization formula.
4. rateEmployee(double total): Maps the normalized total to an integer rating (1..4) using the thresholds above.
5. printResults(double total, int rate): Prints the total score and the final rating (formatted for readability).

## Examples
- Max values: core=10, performance=30, ideation=10 → total = 100 → rating 1
- Zero values: core=0, performance=0, ideation=0 → total = 0 → rating 4
- Mixed example: core=7.5, perf=18, ideation=4 →
- perf contrib = (18/30)*50 = 30
- comp contrib = (7.5/10)*30 = 22.5
- idea contrib = (4/10)*20 = 8
- total = 60.5 → rating 2.

