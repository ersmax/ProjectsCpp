Programming Project 6.12 asked you to write a BoxOfProduce class that stored
three bundles of fruits or vegetables (stored in an array of strings of size 3) to ship
to a customer. Rewrite this class to use a vector instead of an array
and add appropriate constructors, mutators, and accessors. The class should have a function
to add additional fruits or vegetables to the box so there could be more than three
bundles in one box. The output function should output all items in the box.
Overload the + operator to return a new BoxOfProduce object that combines
the vector contents of both operand BoxOfProduce objects. Test your functions
and + operator from the main function. You do not have to implement the rest
of Programming Project 6.12 for this Programming Project, only the changes to
the BoxOfProduce class.

---

## Program Logic

This program simulates a Community Supported Agriculture (CSA) produce box delivery system, 
building on the logic of 6.12_Mystery_Box.cpp but with enhanced features and modern C++ practices.

### Workflow Overview

1. **File Reading**: Reads a list of available produce items from a text file (`Produce.txt`) into a vector.
2. **Random Selection**: Randomly selects three items from the available produce to fill a box.
3. **Display**: Shows the available produce list and current box contents.
4. **User Interaction**: Allows users to substitute or add items in the box.
5. **Loop**: Continues until the user is satisfied with their selection.
6. **Box Combination**: Demonstrates combining two boxes using operator overloading.
7. **Final Output**: Displays the final box contents for delivery.

### Class Structure

#### `FruitsVegetables` Class
- Represents a single produce item.
- Stores the name of the produce.
- Overloads the output stream operator for easy display.

#### `BoxOfProduce` Class
- Stores an arbitrary number of produce items using a `std::vector` (not a fixed-size array).
- Provides methods to add new items, access items by index, and get the current size.
- Overloads the `+` operator to combine the contents of two boxes into a new box.
- Overloads the output stream operator to display all items in the box.

### Helper Functions

- **processFile**: Reads produce names from a file into a vector.
- **randomSelection**: Randomly selects three items from the produce list to fill a box.
- **showList**: Displays the available produce items.
- **handleChange**: Allows the user to change or add items in the box.
- **changeItem/addItem**: Support changing or adding a specific item in the box.
- **inputValidation/itemValidation**: Robust input validation for user interaction.

### Operator Overloading

- The `+` operator is overloaded for `BoxOfProduce`, allowing two boxes to be combined into a new box containing all items from both.

---

## Key Differences from 6.12_Mystery_Box.cpp

| Feature                        | 6.12_Mystery_Box.cpp                                   | 8.09_Box_Produce.cpp                                      |
|--------------------------------|-------------------------------------------------------|-----------------------------------------------------------|
| **Data Structure**              | Fixed-size array (`FruitsVegetables box[3]`)          | Dynamic vector (`std::vector<FruitsVegetables> aBox`)     |
| **Box Size**                    | Always exactly 3 items                                | Can have more than 3 items (user can add more)            |
| **Adding Items**                | Only substitution allowed                             | Can substitute or add new items to the box                |
| **Operator Overloading**        | No operator overloading                               | Overloads `+` to combine two boxes                        |
| **Output**                      | Custom `output()` method                              | Overloaded `operator<<` for easy streaming                |
| **Random Selection**            | Fills box with 3 random items                         | Same, but uses vector and modern C++                      |
| **Encapsulation**               | Uses array and manual bounds checking                 | Uses vector and standard C++ idioms                       |
| **Extensibility**               | Limited to 3 items                                    | Easily extensible to any number of items                  |
| **Modern C++ Features**         | C++ basics                                            | Uses C++23, vectors, operator overloading, etc.           |

---

## Design Improvements in 8.09_Box_Produce.cpp

- **Flexibility**: The use of `std::vector` allows the box to grow beyond three items.
- **Operator Overloading**: The `+` operator makes it easy to combine boxes
- **Cleaner Output**: Overloading `operator<<` for both `FruitsVegetables` and `BoxOfProduce` simplifies display logic.
- **User Experience**: Users can now add as well as substitute items, making the program more interactive.

## Returning by const Value
```cpp
const BoxOfProduce BoxOfProduce::operator +(const BoxOfProduce& secondBox) const
{
	std::vector<FruitsVegetables> newBox = aBox;
	newBox.insert(newBox.end(), secondBox.aBox.begin(), secondBox.aBox.end());
	return BoxOfProduce(newBox);
	//for (const FruitsVegetables& item : secondBox.aBox)
	//	newBox.push_back(item);
}
```
This function return a constant value so as not to allow the calling object to modify the returned object. 
The function is also marked as const to prevent modification of the calling object. 
The function creates a new vector that combines the contents of both boxes and returns a new `BoxOfProduce` object initialized with this combined vector.


