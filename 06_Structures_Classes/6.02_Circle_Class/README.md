Define a class for a type called Circle. An object of type Circle is used to display
the area, diameter, and circumference of a circle based on the radius of that object.
Include a mutator function that sets the radius to a value given as an argument.
Include member function to calculate the area, diameter, and circumference of the
circle. Also include a member function that returns the radius of the circle. Embed
your class definition in a test program.

---

# Overview
The `Circle` class models a simple geometric circle. 
It stores a radius and caches computed values for diameter, area, and circumference. 
The class provides a mutator to set the radius, an accessor to obtain the radius, and helper functions to compute and display results.

### Member variables
- `double radius` — the circle's radius. Defaults to `0`.
- `double diameter` — cached diameter value (`radius * 2`).
- `double area` — cached area value (`pi * radius^2`).
- `double circumference` — cached circumference value (`pi * diameter`).

Cached values are updated by the private `compute()` function when results are requested.

### Public API
- `void setRadius(double circleRadius)`  
  - Precondition: `circleRadius` is a numeric value.  
  - Behavior: If `circleRadius` is negative, the function prints an error message `"Radius cannot be negative\n"` and leaves the stored radius unchanged. If non-negative, it updates the `radius` member.  
  - Return: `void`. Consider returning `bool` or throwing `std::invalid_argument` for alternate error-handling behavior.

- `double getRadius() const`  
  - Behavior: Returns the current `radius` value. This function is `const`.

- `void showResults()`  
  - Behavior: Calls the private `compute()` method to update cached values, then prints the `diameter`, `area`, and `circumference` each on its own line. Since it updates cached members, `showResults()` is not `const` in the current implementation.

### Private helpers
- `void compute()`  
  - Behavior: Updates `diameter`, `area`, and `circumference` using the current `radius`. The implementation uses `std::numbers::pi` from `<numbers>` (requires C++20 or later).  
  - Formulas used:
    - `diameter = radius * 2`
    - `area = std::numbers::pi * radius * radius`
    - `circumference = std::numbers::pi * diameter`

### Example usage (from `main`)
The provided `main()` demonstrates basic usage:

- Construct a `Circle` instance: `Circle circle1;`  
- Set the radius: `circle1.setRadius(25.0);`  
- Read the radius: `circle1.getRadius();`  
- Print computed results: `circle1.showResults();`

---

### Implementation notes 
- The source is written for C++23 due to `std::numbers::pi`, which requires the `<numbers>` header and a C++20 or later standard.

