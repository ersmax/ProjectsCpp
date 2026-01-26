# Rectangle Class

Define a class called Rectangle that has two member variables of type double to
represent the width and height of a rectangle. Include these member functions:
a constructor to construct the Rectangle class using width and height as arguments, 
a default constructor that initializes both width and height to 5, and a
member function each to set width and height. Also include a member function
that computes the area of the rectangle, and output functions to display the width,
height, and area of the rectangle.

---

## Implementation Documentation

### Class Overview

The `Rectangle` class represents a geometric rectangle with validation to ensure dimensions are non-negative. It provides constructors, getters, setters, area calculation, and display functionality.

### Design Decisions

1. **Member initialization**: Constructor uses `: height(0.0), width(0.0)` to ensure members have defined values even if setter throws
2. **No stored area**: Area is calculated on-demand via `getArea()` to always reflect current dimensions
3. **Exception propagation**: Constructors don't catch exceptions, allowing caller to decide error handling policy
4. **Const correctness**: All getters and display functions are marked `const`

### Member Variables

- `double height` - Height of the rectangle (must be non-negative)
- `double width` - Width of the rectangle (must be non-negative)

### Constructors

#### Default Constructor

The default constructor initializes the `Rectangle` object with a width and height of 5. This ensures that every rectangle has a predetermined size upon creation, preventing the creation of rectangles with uninitialized or zero dimensions.

```cpp
Rectangle() : width(5), height(5) {}
```
- Initializes both dimensions to 5.0
- Always succeeds (no validation needed)
- Ensures every rectangle has valid dimensions upon creation

#### Parameterized Constructor

The parameterized constructor allows for the creation of a `Rectangle` object with specified width and height. It includes validation to ensure that both dimensions are non-negative.

```cpp
Rectangle(double w, double h) {
    setWidth(w);
    setHeight(h);
}
```

**Logic:**
1. Initializes members to 0.0 for safety
2. Uses setter functions to validate and assign values
3. **Exception behavior**: If validation fails, throws exception and object is NOT created
4. Ensures RAII principle - object either fully valid or doesn't exist

### Member Functions

#### Setters (with Validation)
- `void setWidth(double widthLength)` - Sets width if non-negative, throws `std::invalid_argument` otherwise
- `void setHeight(double heightLength)` - Sets height if non-negative, throws `std::invalid_argument` otherwise

**Precondition:** Values must be non-negative (>= 0)

#### Getters
- `double getHeight() const` - Returns current height
- `double getWidth() const` - Returns current width
- `double getArea() const` - Computes and returns area (height × width)

**Design decision:** Area is computed on-demand rather than stored to avoid stale data when dimensions change.

#### Display Functions
- `void displaySides() const` - Outputs height and width to console
- `void displayArea() const` - Outputs calculated area to console

### Validation Logic
```cpp
static bool validate(const double length) { return (length >= 0); }
```
- Private static helper function
- Returns `true` if value is non-negative
- Used by both setters to enforce invariant

**Postcondition:** Returns true if length is non-negative

### Exception Handling Pattern

The implementation follows C++ best practices:
- **Constructors**: Let exceptions propagate (don't catch internally)
- **Caller responsibility**: Wrap construction in try-catch if needed
- **RAII guarantee**: Object construction either succeeds completely or fails completely

**Why not catch exceptions in the constructor?**
- If exception is caught in constructor, constructor completes and object IS created
- This creates an object in an invalid state with uninitialized members
- Undefined behavior results when using the object
- By letting exceptions propagate, the object is never created if construction fails

```cpp
try { 
    Rectangle r(10, 2);                         // If this succeeds, object is valid 
} catch (const stdinvalid_argument& e) { 
    stdcout << "Error: " << e.what() << '\n';   // Object was never created - no invalid state possible 
}
```



