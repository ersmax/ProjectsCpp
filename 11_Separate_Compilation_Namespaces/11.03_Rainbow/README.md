
Programming Project 7.1
 Define a class called RainbowColor that is an abstract data type for a color in the visible
spectrum of light. Your class will have a member variable of type int to represent
a color. Include all the following member functions: a constructor to set the color
using the first letter in the name of the color as an argument, a constructor to set the
color using an integer as an argument, a default constructor, an input function that
reads the color as an integer, an input function that outputs the color as an integer,
an output function that outputs the name of the color, and a member function that
returns the next color in the spectrum as a value of type RainbowColor. Embed your
class definition in a test program.


/*
Extend Programming Project 7.1 from Chapter 7 in which you implemented a RainbowColor
class by placing the class definition and implementation in a namespace,
then providing access to the names in the namespace. Test your code. To provide
access to names in namespaces, you may use local using declarations, such as
using std::cout;
or use local using directives such as
using namespace std;
inside a block, or qualify names using the names of namespaces, such as std::cout.
You may not use global namespace directives such as the following which are not
in a block and apply to the entire file:
using namespace std;
*/

---

## Implementation Overview

This project is split into three translation units:

### `11.03_Rainbow.h` - Interface

- Declares two internal lookup tables in an unnamed namespace:
  - `COLOR_CODE`: `std::vector<int>` holding the numeric codes for the 7 rainbow colors, in spectrum order.
  - `COLOR`: `std::vector<std::string>` holding the corresponding color names (`"Purple"`, `"Violet"`, ..., `"Red"`).
- Declares namespace `myNamespace` containing class `RainbowColor`:
  - Stores the current color as an `int` code (`color`).
  - Constructors:
    - Default: initializes to the first color in `COLOR_CODE`.
    - `RainbowColor(int colorCode)`: constructs from a numeric color code.
    - `RainbowColor(char colorName)`: constructs from the first letter of a color name.
  - Member functions:
    - `int getColorCode() const`: returns the stored color code.
    - `const std::string& getColorName() const`: returns the matching color name; if the code is invalid, returns a shared "Not a valid color name" string.
    - `const RainbowColor nextColor() const`: returns a new `RainbowColor` representing the next color in the spectrum (wraps from last back to first).
  - Friend:
    - `operator>>(std::istream&, RainbowColor&)`: reads a color interactively from a stream.

### `11.03_Rainbow.cpp` - Implementation

- Implements `RainbowColor` and several helper functions in an unnamed namespace.

#### Helper functions (unnamed namespace)

- `bool validateColor(const std::string& colorName)`: returns `true` if `colorName` exactly matches one of the entries in `COLOR`.
- `bool validateColor(int color)`: returns `true` if `color` matches one of the values in `COLOR_CODE`.
- `bool setColorName(const std::string& colorName, int& theColor)`: if `colorName` is valid, finds the matching entry in `COLOR` (by first character) and sets `theColor` to the corresponding value from `COLOR_CODE`.
- `bool setColorCode(int colorCode, int& theColor)`: if `colorCode` is valid, assigns it to `theColor`.
- `std::string nameInput(std::istream& inputStream)`: repeatedly prompts and reads a color name from `inputStream` until a valid string extraction occurs.
- `int colorInput(std::istream& inputStream)`: repeatedly prompts and reads a color code from `inputStream` until a valid integer extraction occurs.
- `bool setColorName(std::istream& inputStream, int& theColor)`: interactive front-end that asks the user whether they want to enter a name (`'n'`) or a numeric code (`'c'`), uses `nameInput`/`colorInput` plus `setColorName`/`setColorCode`, and sets `theColor` on success.

#### `myNamespace::RainbowColor` implementation

- Default constructor: initializes `color` to `COLOR_CODE[0]` (first spectrum color).
- `RainbowColor(char colorName)`:
  - Uses `validateColor(colorName)` (via helper taking `std::string`) to ensure the letter corresponds to a known color.
  - Scans `COLOR` and, when the first character matches `colorName`, sets `color` to the matching entry in `COLOR_CODE`.
  - Throws `std::invalid_argument` if no matching color exists.
- `RainbowColor(int colorCode)`:
  - Calls `validateColor(colorCode)`; if valid, stores it in `color`, otherwise throws `std::invalid_argument`.
- `int getColorCode() const`: trivially returns `color`.
- `const std::string& getColorName() const`:
  - Searches `COLOR_CODE` for `color` and returns the corresponding entry from `COLOR`.
  - If no match is found, returns a static `std::string` with the text `"Not a valid color name"`.
- `const RainbowColor nextColor() const`:
  - Finds the index of `color` in `COLOR_CODE`.
  - If it is the last index, returns a `RainbowColor` initialized with `COLOR_CODE[0]` (wrap-around).
  - Otherwise returns a `RainbowColor` initialized with the next entry in `COLOR_CODE`.
- `std::istream& operator>>(std::istream& inputStream, RainbowColor& myColor)`:
  - Calls `setColorName(inputStream, myColor.color)` in a loop until a valid color is entered.
  - Returns the input stream to allow chaining.

### `11.03_Rainbow_app.cpp`

- Contains `main` and a small helper for displaying the available colors.
- `showColors()`:
  - Prints a header row `Color` / `Code` using `std::setw` for alignment.
  - Iterates over `COLOR` and `COLOR_CODE` in parallel, printing each color and its numeric code.
  - Prints a separator line of dashes.
- `main()`:
  - Calls `showColors()` to display the menu of colors and codes.
  - Brings `myNamespace::RainbowColor` into scope with `using`.
  - Creates two `RainbowColor` objects, `aColor` and `anotherColor`, using the default constructor.
  - Prompts the user to enter each color; extraction uses `operator>>`, which handles name/code input and validation.
  - Outputs for each entered color:
    - The color name via `getColorName()`.
    - The next color in the spectrum via `nextColor().getColorName()`.
