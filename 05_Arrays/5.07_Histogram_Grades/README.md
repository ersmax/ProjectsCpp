Generate a text-based histogram for a quiz given to a class of students. The quiz is
graded on a scale from 0 to 5. Write a program that allows the user to enter grades
for each student. As the grades are being entered, the program should count, using
an array, the number of 0s, the number of 1s, the number of 2s, the number of
3s, the number of 4s, and the number of 5s. The program should be capable of
handling an arbitrary number of student grades.
You can do this by making an array of size 6, where each array element is initialized
to zero. Whenever a zero is entered, increment the value in the array at index 0.
Whenever a one is entered, increment the value in the array at index 1, and so on,
up to index 5 of the array.
Output the histogram count at the end. For example, if the input grades are 3, 0,
1, 3, 3, 5, 5, 4, 5, 4, then the program should output
1 grade(s) of 0
1 grade(s) of 1
0 grade(s) of 2
3 grade(s) of 3
2 grade(s) of 4
3 grade(s) of 5

---

# Histogram Grades

This program gathers quiz grades (0–5) from the user, counts how many of each grade were entered, and prints a text histogram.

## Key design points and code-level comments

- Constants
  - `CLASS_SIZE` — maximum number of students (array capacity).
  - `N_GRADES` — number of possible grades (6, indexes `0`..`5`).

- `main`
  - Declares `grades[CLASS_SIZE]` to store individual grades.
  - Declares and zero-initializes `countGrades[N_GRADES] = {}` to accumulate counts.
  - Calls `registerGrades(...)` to read input and fill arrays.
  - Calls `showGrades(...)` to print the histogram.

- `registerGrades(int grades[], int classSize, int& nStudents, int countGrades[], int nGrades)`
  - Repeatedly prompts the user for a token (string).
  - Uses a sentinel token `end` to stop early.
  - Reads input as `std::string` to validate the whole token before converting.
  - After a successful parse and validation, stores the grade in `grades` and increments `countGrades[grade]`.
  - Ensures the loop stops when `student` reaches `classSize`.
  - Sets `nStudents` to the number of accepted grades.
  - Uses `std::cin.clear()` and `std::cin.ignore(...)` to recover from input errors and discard the rest of the line.

- `validGrade(const std::string& result, int& grade)`
  - Parses the string using `std::stoi(result, &positionFirstChar)` and checks `positionFirstChar == result.size()` so inputs like `3abc` are rejected.
  - Catches exceptions as `const` references (`const std::invalid_argument&`, `const std::out_of_range&`) to avoid slicing and extra copies.
  - Returns `true` only when parsing succeeds and `grade` is in the range `0..5`. Prints user-facing messages on failure (invalid token, out of range, or leftover characters).

- `showGrades(int countGrades[], int nGrades)`
  - Iterates `grade` from `0` to `nGrades - 1` and prints `countGrades[grade]` and the grade value.
  - Produces the histogram output required by the exercise.

## Behavior notes and rationale
- Reading input as a `std::string` and validating with `std::stoi` plus position checking prevents partially numeric inputs from being accepted.
- Zero-initializing `countGrades` (`{}`) prevents garbage counts.
- Catching exceptions by `const` reference is the recommended practice to preserve type information and avoid unnecessary copies.
- The program enforces a maximum of `CLASS_SIZE` entries and uses `end` to allow early termination.
