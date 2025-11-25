# Length Conversion 

Write a program that will read in a length in feet and inches and output the equivalent
length in meters and centimeters. Use at least three functions: one for input,
one or more for calculating, and one for output. Include a loop that lets the user
repeat this computation for new input values until the user says he or she wants to
end the program. There are 0.3048 meters in a foot, 100 centimeters in a meter,
and 12 inches in a foot.

---

## Purpose
- Convert a length given in feet and inches to meters and centimeters, 
  allowing repeated conversions until the user quits.

## High level structure
- Functions are separated by responsibility:
    - `getLength` — input and validation loop.
    - `lengthConversion` — numeric conversion from feet\+inches to meters\+centimeters.
    - `showLength` — formatted output.
- `main` orchestrates the flow and provides the repeat loop.

## Input handling
- Uses `cin >> feet >> inches` for natural two-value input.
- On input failure the stream is cleared and the rest of the line is discarded via `cin.ignore(numeric_limits<streamsize>::max(), '\n')` to remove leftover tokens and the newline so the next read is clean.
- After successful extraction the same `cin.ignore(...)` is used to discard extra tokens on the same line (protects against inputs like `5 10 junk`).
- A validation loop in `getLength` re-prompts until values are within the required ranges.

## Range checks and assertions
- Runtime validation is performed in `getLength`.
- `main` contains `assert` statements to express pre/postconditions for developer checks. Note: `assert` is active unless `NDEBUG` is defined; define `NDEBUG` to disable asserts in release builds.

## Constants and readability
- Physical constants are declared with `constexpr` (e.g. `FOOT`, `METER`) to avoid magic numbers and to make intent clear.

## Conversion details and numeric robustness
- Total length in meters is computed as feet \* `FOOT` + inches \* (`FOOT` / 12.0).
- Integer meters are obtained with `static_cast<int>(totalMeters)`.
- Centimeters are computed from the fractional meter part, multiplied by `METER`, and rounded with `round`.
- A small epsilon (`1e-9`) is added before rounding to mitigate floating point boundary errors.
- If rounding produces 100 cm, the code carries the extra centimeter into meters and reduces cm by 100.

## Example formula
```cpp
double totalMeters = feet * FOOT + (inches * (FOOT / 12.0));
int meters = static_cast<int>(totalMeters);
int cm = static_cast<int>(round((totalMeters - meters) * METER + 1e-9));
if (cm >= 100) { cm -= 100; ++meters; }
```

## Notes for maintenance
- Keep numeric constants as `constexpr` for clarity.
- Keep the `cin.ignore(...)` calls to avoid leftover input affecting later reads.
- Use `round` with a small epsilon to avoid off-by-one centimeter errors due to floating point imprecision.
- Remove extraneous `cout << '\n';` at program end — program exit flushes streams automatically.