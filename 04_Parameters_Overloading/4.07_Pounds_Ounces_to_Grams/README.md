# Pounds and Ounces to Grams Conversion Program

Write a program that will read a weight in pounds and ounces and will output
the equivalent weight in kilograms and grams. Use at least three functions: one
for input, one or more for calculating, and one for output. Include a loop that lets
the user repeat this computation for new input values until the user says he or she
wants to end the program. There are 2.2046 pounds in a kilogram, 1000 grams in
a kilogram, and 16 ounces in a pound.

---

## Overview
This program converts lengths between two systems:
- Feet and inches -> meters and centimeters
- Meters and centimeters -> feet and inches

It is menu-driven and repeats until the user chooses to exit. Input is validated and `assert` checks confirm results are within expected ranges during development.

## Key constants
- `METERS_FEET` — meters per foot (0.3048)
- `INCHES_FEET` — inches per foot (12)
- `METERS_INCH` — meters per inch (`METERS_FEET / INCHES_FEET`)
- `CM_METER` — centimeters per meter (100)

## Data structures
- `struct FeetInches` — holds `feet` and `inches`
- `struct MetersCentimeters` — holds `meters` and `centimeters`

## Main components
1. `makeChoice(int& choice)`  
   - Displays menu and reads user selection (0, 1, 2).  
   - Performs input validation and discards remainder of the input line.

2. `getData(FeetInches& feetInches)` and `getData(MetersCentimeters& metersCentimeters)`  
   - Read the two numbers for the chosen conversion direction.  
   - Validate ranges: feet 5–7 and inches 0–11 for one direction; meters 0–2 and centimeters 0–99 for the other.  
   - Re-prompt on invalid input.

3. `convertData(const FeetInches& src, MetersCentimeters& dst)`  
   - Converts feet+inches to total meters, rounds to nearest centimeter, then splits into meters and centimeters.

4. `convertData(const MetersCentimeters& src, FeetInches& dst)`  
   - Converts total centimeters to total inches (rounded), then splits into feet and inches.

5. `showData(FeetInches feetInches, MetersCentimeters metersCentimeters)`  
   - Prints a single-line, human-readable equivalence.

## Error handling and assertions
- User input is validated with loops; invalid streams are cleared and the rest of the line discarded using `cin.ignore(numeric_limits<streamsize>::max(), '\n')`.
- `assert` statements verify pre/postconditions during development (can be disabled by defining `NDEBUG`).

## Build and run (Windows)
- Compile with a C++17-capable compiler, e.g.:
  - `cl /EHsc /std:c++17 4_programming_set_4\4.06_Length_Conversion\6_Length_Conversion.cpp`
  - or use `g++ -std=c++17 -O2 -o length_convert 4_programming_set_4/4.06_Length_Conversion/6_Length_Conversion.cpp`
- Run the produced executable and follow on-screen prompts.

