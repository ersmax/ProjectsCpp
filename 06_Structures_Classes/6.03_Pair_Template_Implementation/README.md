The type Point is a fairly simple data type, but under another name (the template
class pair) this data type is defined and used in the C++ Standard Template Library,
although you need not know anything about the Standard Template Library
to do this exercise. Write a definition of a class named Point that might be used to
store and manipulate the location of a point in the plane. You will need to declare
and implement the following member functions:
a. A member function set that sets the private data after an object of this class is
created.
b. A member function to move the point by an amount along the vertical and
horizontal directions specified by the first and second arguments.
c. A member function to rotate the point by 90 degrees clockwise around the
origin.
d. Two const inspector functions to retrieve the current coordinates of the point.
Document these functions with appropriate comments. Embed your class in a test
program that requests data for several points from the user, creates the points, then
exercises the member functions.

---

## 6.03_Pair_Template_Implementation.cpp — Code walkthrough

- `class Point`
  - `setCoordinates(double, double)`: stores X and Y values.
  - `getX() const`, `getY() const`: return the current coordinates.
  - `moveCoordinates(double dx, double dy)`: adds offsets to the stored coordinates.
  - `rotatePoint()`: rotates the point 90 degrees clockwise about the origin. Implementation swaps `x` and `y` and negates the new `y` (i.e. `swap(x,y); y = -y;`).

- Helper functions
  - `inputData()`: reads a double from `std::cin`. The project version handles invalid tokens by clearing the stream and discarding the input line before retrying; consider returning `std::optional<double>` for EOF-aware behavior.
  - `askCoordinates(Point points[], std::size_t maxSize, std::size_t &size)`: interactively asks the user for X and Y values and appends `Point` objects into the provided array until the user answers "no" or the array reaches capacity. It updates `size` with the number of stored points.
  - `showCoordinates(const Point points[], std::size_t size)`: prints all stored points (1..size) using the `getX`/`getY` inspectors.
  - `rotate(Point points[], std::size_t size)` and `move(Point points[], std::size_t size, double dx, double dy)`: utility loops that apply `rotatePoint()` and `moveCoordinates()` to the first `size` elements.

- `main()` flow
  1. Declare a fixed-size array of `Point` objects and a `size` counter.
  2. Call `askCoordinates` to fill the array and update `size`.
  3. Print the entered points via `showCoordinates`.
  4. Rotate and print again.
  5. Move all points and print the final coordinates.


## Implementation for a number of points
To test the `Point` class and its member functions, an array of `Point` objects is created,
and the functions `rotate` and `move` call the respective member functions on each `Point` in the array.
