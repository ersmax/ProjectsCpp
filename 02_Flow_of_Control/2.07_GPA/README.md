Write a program to calculate the grade point average (GPA) of a student by getting
their grades for all their subjects. Grades and their grade points are
Grade S 10 points
Grade A 9 points
Grade B 8 points
Grade C 7 points
Grade D 6 points
Grade E 5 points
Grade F 0 points
The program should input the number of subjects, followed by the grade obtained
in each subject. The program should calculate the average of the grade points and
print it.
===================================================================================

The program calculates the Grade Point Average (GPA) of a student
based on their grades for all subjects.

It uses an `enum` to represent grades and their corresponding grade points.
The program ensures valid input by repeatedly prompting the user until a valid grade is entered.


1. Enum Definition
enum Grades {F, E = 5, D, C, B, A, S = 10, invalid};
- `Grades` is an enumeration that maps letter grades to their respective grade points.
- `F` is assigned 0 points, `E` is explicitly assigned 5 points,
   and `S` is explicitly assigned 10 points.
   Other grades (`D`, `C`, `B`, `A`) are implicitly assigned consecutive values.
- `invalid` is used as a sentinel value to represent invalid grades.

2. Function: `charToGrade`
- Purpose:
  Converts a character input (`gradeChar`) into the corresponding `Grades` enum value.
- Logic:
  - Valid grades (`S`, `A`, `B`, `C`, `D`, `E`, `F`) are mapped to their respective enum values.
  - Invalid grades trigger an error message (`cerr`) and return the `invalid` sentinel value.
- Case-insensitivity: Both uppercase and lowercase letters are handled.

3. Main Function
- Purpose: Calculates the GPA based on user input.
- Formatting: Configures `cout` to display floating-point numbers with two decimal places.

5. Loop for Grade Input and Summation
- Grade Input:
  - Prompts the user to enter a grade for each subject.
  - Calls `charToGrade` to validate and convert the input.
  - If the input is invalid, the user is repeatedly prompted until a valid grade is entered.
- Grade Summation: Adds the grade points to `sum`.

6. GPA Calculation and Output
- GPA Calculation: Divides the total grade points (`sum`) by the number of subjects.
- Output: Displays the GPA with two decimal places.

Key Features
1. Validation: Ensures only valid grades are accepted.
2. Case-Insensitive Input: Handles both uppercase and lowercase grade letters.
3. Error Handling: Provides clear error messages for invalid input.
4. User-Friendly Output: Displays the GPA in a readable format.

Example Execution
Insert the number of subjects: 3
Add the grade of the 1 subject: A
Add the grade of the 2 subject: Z
Invalid grade. Please enter a valid grade.
(S, A, B, C, D, E, F): B
Add the grade of the 3 subject: C

Output:
GPA: 8.00