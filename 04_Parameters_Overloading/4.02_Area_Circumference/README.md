# Area and Circumference

The area of a circle can be calculated using the formula
A = pr 2
where r is the radius of the circle, and p is the ratio of the circle’s circumference to
its diameter. The circumference can be calculated using the formula
C = pd
where d is the diameter of the circle, whose value is twice that of the radius. Write
a void function that takes the radius of the circle, and two reference parameters
to compute the area and the circumference. Use a value of 3.14159 for p.

---

## Overview
Small CLI program that computes the area and circumference of a circle from a user-supplied radius. 
The implementation separates concerns into input, computation, and output functions.

## Requirements
- C++ compiler with C++11 or later.
- Tested in CLion on Windows; works with MSVC, MinGW, or GCC.
- Uses `<cmath>` for PI via `std::acos(-1.0)`. If using C++20, `std::numbers::pi` is an alternative.

## Build and Run
From CLion: open the project and run the target.

From command line (example with g++):
```
g++ -std=c++11 -O2 -Wall -Wextra 2_Area_Circumference.cpp -o area_calc
.\area_calc
```

## Program Behavior
- Prompts: `Enter the radius (>0):`
- Accepts a floating-point radius > 0.
- On non-numeric input or invalid range, re-prompts after clearing the stream.
- Computes:
  - Area = PI * r * r
  - Circumference = 2 * PI * r
  - PI is taken from `std::acos(-1.0)` (accurate constant).
- Displays results formatted to two decimal places.
- After output asks: `Repeat? (y/Y)` — `y` or `Y` repeats; any other key exits.

Example session:
```
Enter the radius (>0): 5
You entered: 5
The area is 78.54 and circumference is 31.42
Repeat? (y/Y) n
```

## Function Contracts

- `void getData(double& radius);`
  - Precondition: `radius` declared.
  - Postcondition: sets `radius` to a positive `double` read from input.
  - Behavior: loops until a numeric value `> 0` is provided; clears stream and discards remainder of line on errors.

- `void areaCircumference(double radius, double& area, double& circumference);`
  - Precondition: `radius > 0`.
  - Postcondition: `area` and `circumference` set to computed values.
  - Uses `const double PI = std::acos(-1.0);`

- `void showData(double area, double circumference);`
  - Precondition: `area` and `circumference` computed.
  - Postcondition: prints values with fixed format and two decimal places.

## Input Handling & Safety
- Uses `std::cin >>` for numeric input, checks result.
- On failure calls `cin.clear()` and `cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')` 
  to remove bad input.
- Also ignores extra tokens on the same line after successful extraction 
  to avoid leftover input affecting subsequent prompts.

## Assertions & Debugging
- `assert(radius > 0)` and `assert(area > 0 && circumference > 0)` are used to validate internal assumptions.
- To remove assertions in a release build, define `NDEBUG` (e.g., pass `-DNDEBUG` to the compiler).

## Formatting Notes
- Output uses `std::fixed` and `std::setprecision(2)` for consistent presentation.
- `showpoint` is optional; remove if trailing zeros are undesirable.

## Edge Cases and Notes
- Zero or negative radius is rejected by `getData`.
- EOF on stdin will cause input to fail and the program to exit the input loop.
- Use `std::acos(-1.0)` rather than `cos(-1.0)` to obtain PI; `cos(-1.0)` does not yield PI.

## Suggested Improvements
- Provide a pure computation API (no I/O) to enable unit testing.
- Replace magic constant usage with `std::numbers::pi` in C++20.
- Add unit tests for `areaCircumference` covering small, large, and boundary inputs.
- Improve UI by accepting command-line arguments for non-interactive use.

## License
Example educational code; adapt as needed for learning and testing.
