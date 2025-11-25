Write a program like that of the previous exercise that converts from meters and
centimeters into feet and inches. Use functions for the subtasks.

---

# Meters and Centimeters → Feet and Inches

## Purpose
Convert a length given as meters and centimeters into feet and inches using small, 
well-tested functions. The program validates input and intentionally truncates 
(never rounds up) so a person is not "given" extra height.

## Design and coding choices
- Constants make units explicit:
  - `METERS_FEET` for meters-per-foot, `INCHES_FEET = 12`, `METERS_INCH = METERS_FEET / INCHES_FEET`, `CM_METER = 100.0`.
- Explicit unit conversions:
  - Centimeters are converted to meters using `centimeters / CM_METER` before converting to inches. This avoids a common factor-of-100 bug.
- Truncation policy:
  - The program truncates down to the nearest whole inch (uses `std::floor` on the total inches) rather than rounding. Rationale: avoid "gifting" height (1.829 m should not become 6 ft just because of rounding).
  - For non-negative inputs `static_cast<int>(x)` and `std::floor(x)` are equivalent, but `std::floor` makes the intent explicit and remains correct if negatives are ever introduced.
- Input validation & robustness:
  - `getData` enforces `meters` in \[0, 2\] and `centimeters` in \[0, 99\], rejects non-numeric input and discards trailing tokens.
  - `assert` checks ensure converted values remain in expected ranges.
- Small, single-responsibility functions:
  - `getData(int\& meters, int\& centimeters)` — reads and validates user input.
  - `lengthConversion(int meters, int centimeters, int\& feet, int\& inches)` — performs conversion and truncation.
  - `showData(int feet, int inches)` — prints the result.

## Usage (build / run)
- Build with your IDE (CLion/CMake) or compile directly:
  - Example (MinGW/g++ on Windows):
    ```bash
    g++ -std=c++17 -O2 -o meters_to_feet `4_programming_set_4/4.05_Meters_to_Feet_Inches/5_Meters_to_Feet_Inches.cpp`
    ```
  - Run:
    ```bash
    ./meters_to_feet
    ```
  - Follow prompts, e.g. enter `1 80` for 1 meter 80 centimeters.

## Example
Input:
```
Enter height in meters and cm (separated by a space)
(e.g. 1 80): 1 80
```
Output:
```
This is equivalent to 5 feet and 10 inches.
```
(1.80 m → 70.866 in → truncated to 70 in → 5 ft 10 in.)

## Edge cases and notes
- The program rejects values outside the expected ranges and non-numeric tokens.
- If you prefer rounding to nearest inch instead of truncation, replace `std::floor` with `std::lround` (and cast to `int`), but that changes the policy about "gifting" height.
- The conversion is implemented in terms of meters and the constant `METERS_INCH`; an alternative is to convert centimeters directly to inches using 2.54 cm/inch.

## Tests
- Try boundary values:
  - `0 0` → `0 ft 0 in`
  - `2 0` → the program accepts up to `2` meters
  - Non-numeric or out-of-range input is rejected with a prompt to re-enter
