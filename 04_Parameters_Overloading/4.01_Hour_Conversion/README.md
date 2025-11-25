# 4.01 Hour Conversion

Write a program that converts from 24-hour notation to 12-hour notation. For
example, it should convert 14:25 to 2:25 P.M. The input is given as two integers.
There should be at least three functions: one for input, one to do the conversion,
and one for output. Record the A.M./P.M. information as a value of type char,
'A' for A.M. and 'P' for P.M. Thus, the function for doing the conversions will
have a call-by-reference formal parameter of type char to record whether it is A.M.
or P.M. (The function will have other parameters as well.) Include a loop that lets
the user repeat this computation for new input values again and again until the user
says he or she wants to end the program.

---

## Overview
This program converts a time given in 24-hour notation (hour and minute integers) 
to 12-hour notation with an A.M./P.M. indicator. Example: `14 25` -> `2:25 P.M.`. 
The implementation separates concerns into three functions: 
input, conversion, and output, and loops to allow repeated conversions until the user opts out.

## Requirements
- C++ compiler supporting C++11 or later.
- Tested in CLion on Windows (developer environment). The code is standard and portable to other platforms and IDEs.

## Build and Run (Windows / CLion)
1. Open the project in CLion.
2. Configure the toolchain if required (MSVC, MinGW, or WSL).
3. Build and run the target from CLion (Run | Run).
4. Alternatively, compile on the command line:
   - With g++: `g++ -std=c++11 -O2 -Wall -Wextra 1_Hour_Conversion.cpp -o hour_conv`
   - Run: `.\hour_conv`

## Program Behavior and Usage
- The program prompts: `Enter the hour (0-23) and minute (0-59):`
- Enter two integers separated by space or newline. Example input: `14 25`
- If the read fails (non-integer input), the program prints `Invalid input. Enter two whole values.` 
  and re-prompts.
- If a numeric range is outside `[0..23]` for hour or `[0..59]` for minute, the program prints `Invalid range.` and re-prompts.
- After a successful conversion the program displays the time in `h:mm A.M./P.M.` format, then asks `Repeat? (y/Y):`.
- Type `y` or `Y` to repeat, any other character to exit.

Example session:
```
Enter the hour (0-23) and minute (0-59): 14 25
Time: 2:25 P.M.
Repeat? (y/Y): n
```

## Functions and Contracts
- `void getInput(int& hour, int& minute);`
  - Precondition: `hour` and `minute` variables declared.
  - Postcondition: sets `hour` and `minute` to valid integers (hour in `0..23`, minute in `0..59`).
  - Behavior: repeatedly prompts until valid numeric and range-correct values are read. 
    It clears stream state and discards the rest of the input line on failure or after a successful read.

- `void timeConversion(int& hour, char& amPm);`
  - Precondition: `hour` is in `0..23`, `amPm` is declared.
  - Postcondition: converts `hour` to 12-hour format (range `1..12`) and sets `amPm` to `'A'` (A.M.) or `'P'` (P.M.).
  - Conversion rules:
    - `0` -> `12 A.M.` (midnight)
    - `12` -> `12 P.M.` (noon)
    - `1..11` -> same hour, A.M.
    - `13..23` -> subtract 12, P.M.

- `void showTime(int hour, int minute, char amPm);`
  - Precondition: `hour` in `1..12`, `minute` in `0..59`, `amPm` is `'A'` or `'P'` (or `'\0'` if unknown).
  - Postcondition: prints the time in `h:mm A.M./P.M.` format.
  - Notes: Current implementation zero-pads minutes and (optionally) hour when `hour < 10`.

## Input Handling and Stream Safety
- The program uses `std::cin >>` for numeric extraction and checks the result. On failure, it calls `cin.clear()` to reset error flags.
- It uses `cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')` to discard the rest of the current input line:
  - This prevents leftover tokens (e.g. `12 30 junk`) from affecting subsequent reads.
  - It also avoids mixing formatted input (`operator>>`) and `std::getline` issues.
  - Behavior: `ignore` discards up to the next newline or until the count reaches `max()`. If EOF is reached, it stops and sets stream state accordingly.

## Assertions and Debugging
- The program uses `assert` to check pre/postconditions in `main`:
  - After `getInput`, asserts `0 <= hour < 24` and `0 <= minute < 60`.
  - After `timeConversion`, asserts `1 <= hour <= 12`, `0 <= minute < 60`, and `amPm` is `'A'` or `'P'`.
- To compile without assertions, define `NDEBUG` (e.g., by uncommenting `#define NDEBUG` or passing `-DNDEBUG`).
- Assertions help catch logic errors during development; they are not a substitute for runtime validation.

## Formatting and Output Notes
- Current `showTime` implementation zero-pads minutes and (optionally) hour when less than 10. Typical 12-hour displays do not zero-pad the hour (e.g., `2:25 P.M.` not `02:25 P.M.`).
- To match common examples, do not zero-pad the hour; keep zero-padding for minutes (use `std::setw` and `std::setfill` if preferred).

## Error Conditions and Edge Cases
- If input stream reaches EOF unexpectedly, the program will stop prompting and may exit.
- Non-numeric input is handled by clearing the stream and discarding the remainder of the line, then re-prompting.
- Inputs like `12 00` and `0 00` are handled specially to produce correct `12:00 P.M.` and `12:00 A.M.` results.

## Suggested Improvements
- Remove leading zero for hour in `showTime` to match usual 12-hour formatting.
- Use `<iomanip>` and `std::setw(2)`/`std::setfill('0')` for minute padding.
- Add unit tests for `timeConversion` to verify edge cases (0, 12, 23, etc.).
- Separate parsing and interactive UI to allow automated testing (e.g., provide a pure conversion function and a thin CLI wrapper).

## License and Attribution
- Adapt and extend as needed for learning and testing purposes.

