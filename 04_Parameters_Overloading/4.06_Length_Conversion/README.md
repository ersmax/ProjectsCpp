# Length Conversion Program

(You should do the previous two programming projects before doing this one.)
Write a program that combines the functions in the previous two programming
projects. The program asks the user if he or she wants to convert from feet and
inches to meters and centimeters or from meters and centimeters to feet and inches.
The program then performs the desired conversion. Have the user respond by typing
the integer 1 for one type of conversion and 2 for the other conversion. The
program reads the user’s answer and then executes an if-else statement. Each
branch of the if-else statement will be a function call. The two functions called
in the if-else statement will have function definitions that are very similar to
the programs for the previous two programming projects. Thus, they will be fairly
complicated function definitions that call other functions. Include a loop that lets
the user repeat this computation for new input values until the user says he or she
wants to end the program.

---

## Overview
- Small interactive C++ program that converts lengths between feet\+inches and meters\+centimeters.
- Source file: `4_programming_set_4/4.06_Length_Conversion/6_Length_Conversion.cpp`.

Build and run
```bash
g++ -std=c++17 -O2 -o length_converter 4_programming_set_4/4.06_Length_Conversion/6_Length_Conversion.cpp
.\length_converter    # on Windows (PowerShell or CMD)
```

## What the program does
- Presents a menu:
    - `1` convert from feet\+inches -> meters\+centimeters
    - `2` convert from meters\+centimeters -> feet\+inches
    - `0` exit
- Reads validated user input, performs conversion, prints the result, and repeats until exit.

## Key constants and formulas
- `METERS_FEET = 0.3048` (meters per foot)
- `INCHES_FEET = 12`
- `METERS_INCH = METERS_FEET / INCHES_FEET` (meters per inch)
- `CM_METER = 100` (centimeters per meter)
- Conversion logic:
    - feet\+inches -> meters\+centimeters:
        - total meters = feet * METERS_FEET + inches * METERS_INCH
        - total centimeters = round(total meters * 100)
        - split into meters = totalCentimeters / 100, centimeters = totalCentimeters % 100
    - meters\+centimeters -> feet\+inches:
        - total centimeters = meters * 100 + centimeters
        - total inches = round(totalCentimeters / (METERS_INCH * 100))
        - split into feet = totalInches / 12, inches = totalInches % 12

## Input validation and error handling
- The program validates input ranges:
    - Feet: 5–7, Inches: 0–11 (for the feet\+inches branch)
    - Meters: 0–2, Centimeters: 0–99 (for the meters\+centimeters branch)
- Uses `cin` checks and `cin.clear()`/`cin.ignore()` to recover from invalid input.
- `assert` statements check pre/postconditions in `main` (can be disabled with `NDEBUG`).

## Design and implementation notes
- Menu selection is read robustly (invalid tokens are rejected and the input line consumed).
- Conversion uses integer normalization to avoid representing e.g. `100 cm` as both `1 m` and `100 cm`.
- Rounding policy: the code rounds to the nearest centimeter and to the nearest inch (both conversions). Truncation (floor) could be used instead if avoiding overestimation is required.
- Use of `round` can produce edge cases; converting by first computing total smallest units (cm or inches) and then splitting ensures normalized output.

## Function reference (brief)
- `makeChoice(int& choice)` — shows menu and reads a validated choice (0..2).
- `getData(FeetInches&)` — prompts for feet and inches, validates ranges.
- `getData(MetersCentimeters&)` — prompts for meters and centimeters, validates ranges.
- `convertData(const FeetInches&, MetersCentimeters&)` — does feet->metric conversion (round to cm).
- `convertData(const MetersCentimeters&, FeetInches&)` — does metric->imperial conversion (round to inches).
- `showData(FeetInches, MetersCentimeters)` — prints the equivalence.

## Example interaction
- User selects `1`, enters `5 10` → program prints equivalent meters and centimeters (rounded).
- User selects `2`, enters `1 80` → program prints equivalent feet and inches (rounded).
