(You should do the previous two programming projects before doing this one.)
Write a program that combines the functions of the previous two programming
projects. The program asks the user if he or she wants to convert from pounds
and ounces to kilograms and grams or from kilograms and grams to pounds and
ounces. The program then performs the desired conversion. Have the user respond
by typing the integer 1 for one type of conversion and 2 for the other. The
program reads the user’s answer and then executes an if-else statement. Each
branch of the if-else statement will be a function call. The two functions called
in the if-else statement will have function definitions that are very similar to
the programs for the previous two programming projects. Thus, they will be fairly
complicated function definitions that call other functions in their function bodies.
Include a loop that lets the user repeat this computation for new input values until
the user says he or she wants to end the program.

---

# Overview
This is a menu-driven program that converts between pounds\+ounces and kilograms\+grams 
and lets the user repeat conversions until they exit.

## Key constants
- `POUNDS_KILO` — how many pounds in 1 kilogram.
- `OUNCES_POUND` — 16 ounces per pound.
- `OUNCES_KILO` — ounces in a kilogram (used to convert via a single base unit).
- `GRAMS_KILO` — 1000 grams per kilogram.

## Data types
- `PoundsOunces` — holds `int pounds` and `double ounces`.
- `KilogramsGrams` — holds `int kilograms` and `double grams`.

## Program flow (`main`)
- Loop: call `makeChoice` to get user menu selection.
- If choice `1`: read pounds\+ounces with `getData`, convert with `convertData(const PoundsOunces&, KilogramsGrams&)`, then print with `showData`.
- If choice `2`: read kilograms\+grams with `getData`, convert with `convertData(const KilogramsGrams&, PoundsOunces&)`, then print with `showData`.
- Choice `0` exits.

## Input helpers (`makeChoice`, `getData`)
- Validate numeric input, clear `cin` state on failure, and ignore the rest of the input line to avoid leftover characters.
- Ensure non\-negative values before accepting.

## Conversion functions and overload (`convertData`)
- Pounds→Kilograms: convert entire pounds+ounces into total ounces, convert to total kilograms, then split into whole kilograms and fractional grams.
- Kilograms→Pounds: compute total kilograms + grams fraction, convert to total pounds, split into integer pounds and ounces.
- Implementation detail: convert via a single base unit (ounces or kilos) so rounding is consistent.

## Output (`showData`)
- Uses `fixed`, `showpoint`, `setprecision(2)` for consistent two\-decimal formatting.
- Chooses singular/plural labels based on the numeric values.
- Note: the code compares doubles to `0` or `1` when selecting labels — direct `double ==` comparisons can be unreliable; use a small epsilon when necessary.

## Notes
- Overload ambiguity: 
  The input parameter are passed as const reference to avoid copying, while output parameters are non-const references.
  Ensure the function signatures match exactly to avoid ambiguity in overload resolution.
  For example `convertData(const PoundsOunces&, KilogramsGrams&)` and `convertData(const KilogramsGrams&, PoundsOunces&)`). 

## Improvements
- Floating\-point noise: guard very small fractional residues (e.g. `if (fabs(v) < 1e-9) v = 0.0;`) before comparisons or printing.
- Normalization: the program currently accepts ounces ≥ 16 or grams ≥ 1000 as input. 
  You may consider normalizing inputs/outputs so ounces < 16 and grams < 1000 for canonical representation (carry excess to the next larger unit).

---