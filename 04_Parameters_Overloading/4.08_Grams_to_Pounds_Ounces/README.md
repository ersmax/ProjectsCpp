Write a program like that of the previous exercise that converts from kilograms and
grams into pounds and ounces. Use functions for the subtasks.

---

# Overview  
The program converts a weight given as kilograms and grams into pounds and ounces and repeats on user request.

## Key constants (in code)
    - `POUNDS_KILO` — pounds per kilogram.
    - `OUNCES_POUND` — ounces per pound (16).
    - `OUNCES_KILO` — derived ounces per kilogram.
    - `GRAMS_KILO` — grams per kilogram (1000).

## Program structure
1. `main()`
        - Repeats: call `getData`, assert inputs non\-negative, call `convertData`, call `showData`, prompt to repeat.
2. `getData(int& kilograms, double& grams)`
        - Prompts user, reads `kilograms` and `grams`.
        - Validates input stream, clears bad input, ignores the rest of the line.
        - Rejects negative values and loops until valid non\-negative input.
3. `convertData(int kilograms, double grams, int& pounds, double& ounces)`
        - Computes total pounds as `(kilograms + grams / GRAMS_KILO) * POUNDS_KILO`.
        - Sets `pounds` = integer part (`floor`) of total pounds.
        - Sets `ounces` = fractional part \* `OUNCES_POUND` (keeps fractional ounces).
        - Commented alternative shows how to produce integer ounces with rounding and handle a 16\-ounce rollover to increase pounds.
4. `showData(int kilograms, double grams, int pounds, double ounces)`
        - Prints input and result using fixed formatting and two decimal places.
        - Chooses singular/plural labels for `kilo`/`kilos` and `gram`/`grams` based on values.

## Notes / potential improvements
- The program does not normalize `grams >= 1000` into extra kilograms; that can be added in `convertData`.
- It is possible to treat `ounces` as integer instead of double, at the expense of less precision.
  Replace `convertData` with this code, and change type of parameter `double& ounces` in the remaining code.

```
void convertData(int kilograms, double grams, int& pounds, double& ounces) {
    double totalPounds = (kilograms + grams / GRAMS_KILO ) * POUNDS_KILO;
    pounds = static_cast<int>(floor(totalPounds));
    double leftOunces = ((totalPounds - pounds) * OUNCES_POUND);
    ounces = static_cast<int>(round(leftOunces));
    if (ounces == OUNCES_POUND) {
        ++pounds;
        ounces = 0; 
    }
}
```