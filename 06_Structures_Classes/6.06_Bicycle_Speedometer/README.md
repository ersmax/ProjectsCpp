Define a class called BicycleSpeedometer that will track distance traveled by,
travel time of, and the average speed of the rider. The class should have member
variables for distance traveled (in miles), and the time taken (in minutes). Include
mutator functions to set distance, and time. Include a member function to compute
the average speed (in miles per hour).
Use your class with a test program that creates the class, reads input values for all
the required member variables and outputs the average speed of the rider.

---

## Logic 

- The program defines a class `BicycleSpeedometer` that encapsulates the data and
  behavior needed to compute a rider's average speed.
- Private members:
  - `distance` (double) — stores distance traveled in miles, default-initialized to 0.
  - `time` (int) — stores travel time in minutes, default-initialized to 0.
- Public mutators:
  - `setDistance()` prompts the user and assigns a validated positive `double` to
    `distance` using the static helper `inputValidation()`.
  - `setTime()` prompts the user and assigns a validated value (converted to `int`)
    to `time` using `inputValidation()`.
- Accessors:
  - `getDistance()` returns the stored `distance`.
  - `getTime()` returns the stored `time`.
- Calculation helpers:
  - `inputValidation()` reads user input, rejects non-numeric input and non-positive
    values, and returns a validated positive `double`.
  - `minuteToHour()` converts the stored minutes to hours (`time / 60.0`).
  - `avgSpeed()` computes average speed in miles per hour as `distance / minuteToHour()`
    and is marked `const` because it does not modify object state.
- `main()` flow:
  1. Create a `BicycleSpeedometer` instance.
  2. Prompt and read `distance` and `time` via `setDistance()` and `setTime()`.
  3. Print the average speed computed by `avgSpeed()` with fixed formatting.

Notes:
- Input validation prevents zero or negative values so the division in
  `avgSpeed()` does not divide by zero (provided `time` is set to a positive value).
- The program formats output using `std::fixed` and `std::setprecision(1)`.

