Your Community Supported Agriculture (CSA) farm delivers a box of fresh fruits
and vegetables to your house once a week. For this Programming Project, define
the class BoxOfProduce that contains exactly three bundles of fruits or vegetables.
You can represent the fruits or vegetables as an array of type string. Add accessor
and mutator functions to get or set the fruits or vegetables stored in the array. Also
write an output function that displays the complete contents of the box on the
console.
Next, write a main function that creates a BoxOfProduce with three items
randomly selected from this list:
Broccoli
Tomato
Kiwi
Kale
Tomatillo
This list should be stored in a text file that is read in by your program. For now
you can assume that the list contains exactly five types of fruits or vegetables.
Do not worry if your program randomly selects duplicate produce for the three
items. Next, the main function should display the contents of the box and allow
the user to substitute any one of the five possible fruits or vegetables for any of the
fruits or vegetables selected for the box. After the user is done with substitutions
output the final contents of the box to be delivered.

---

# Overview

## Program Logic

This program simulates a CSA (Community Supported Agriculture) produce box delivery system with the following workflow:

1. **File Reading**: Reads a list of available produce items from `Produce.txt`
2. **Random Selection**: Randomly selects 3 items from the available produce to fill the box
3. **Display**: Shows the available produce list and current box contents
4. **User Interaction**: Allows users to substitute items in the box
5. **Loop**: Continues until the user is satisfied with their selection
6. **Final Output**: Displays the final box contents for delivery

## Class Structure

### `FruitsVegetables` Class
**Purpose**: Represents a single produce item (fruit or vegetable)

**Member Variables**:
- `std::string name` - Stores the name of the produce item

**Member Functions**:
- `void setName(const std::string& nameFruitVegetable)` - Sets the name of the produce item
- `std::string getName() const` - Returns the name of the produce item

**Design Rationale**: Encapsulates produce item data and provides a clean interface for accessing and modifying produce names. 
This class serves as the building block for both the produce inventory and box contents.

### `BoxOfProduce` Class
**Purpose**: Represents a box containing exactly 3 produce items

**Member Variables**:
- `FruitsVegetables box[ITEMS]` - Fixed-size array holding 3 produce items
- `int items` - Tracks the current number of items in the box (0-3)

**Member Functions**:
- `void addContent(int idx, const FruitsVegetables& produce)` - Adds a produce item at the specified index with bounds checking
- `bool changeContent(int idx, const FruitsVegetables& produce)` - Replaces a produce item at the specified index; returns true if successful
- `const FruitsVegetables& getItem(int idx) const` - Returns a reference to the produce item at the specified index
- `void output()` - Displays all items currently in the box (numbered list)
- `bool isValidIndex(int idx) const` - Validates if an index is within the valid range of items

**Design Rationale**: Manages the collection of produce items with encapsulation. 
The class ensures data integrity through bounds checking and provides a clear interface for manipulating box contents of class FuitsVegetables.

## Helper Functions

### File Processing Functions

- **`bool processFile(FruitsVegetables produceList[], int maxSize, int& sizeList)`**
  - Orchestrates the entire file reading process
  - Opens the file, parses content, closes the file
  - Returns false if file cannot be opened

- **`bool openFile(const std::string& pathFile, std::ifstream& inputStream)`**
  - Opens the specified file for reading
  - Returns false if file opening fails

- **`void closeFile(std::ifstream& inputStream)`**
  - Closes the input file stream

- **`void parseFile(std::ifstream& inputStream, FruitsVegetables produceList[], int maxSize, int& sizeList)`**
  - Reads produce names line-by-line from the file
  - Populates the produceList array
  - Skips empty lines
  - Updates sizeList with the number of items read

### Box Management Functions

- **`void randomSelection(const FruitsVegetables produceList[], int sizeList, BoxOfProduce& box)`**
  - Uses C++ random library (`std::random_device`, `std::mt19937`) for randomization
  - Selects 3 random items from the produce list
  - Fills the box with the randomly selected items
  - Allows duplicate selections as per requirements

- **`void showProduceList(const FruitsVegetables produceList[], int sizeList)`**
  - Displays all available produce items with numbered indices
  - Helps users see what options are available for substitution

- **`bool substitute(const FruitsVegetables produceList[], int sizeList, BoxOfProduce& box)`**
  - Manages the user interaction for item substitution
  - Prompts user if they want to make changes (y/n)
  - Returns false when user is done (to exit the loop)
  - Validates user input for both box position and desired produce item
  - Provides error messages for invalid selections

### Input Validation Functions

- **`char inputValidation()`**
  - Validates character input from the user
  - Handles stream errors and clears invalid input
  - Ensures robust input handling for y/n responses

- **`int itemValidation()`**
  - Validates integer input from the user
  - Handles stream errors and clears invalid input
  - Used for selecting box positions and produce items

## Main Function Flow

1. **Initialization**: Creates a `BoxOfProduce` object and an array to hold the produce list
2. **File Processing**: Calls `processFile()` to load available produce from file; exits if file read fails
3. **Random Fill**: Calls `randomSelection()` to populate the box with 3 random items
4. **Interactive Loop**:
   - Displays available produce list
   - Shows current box contents
   - Allows user to substitute items
   - Continues until user chooses to stop (enters 'n')
5. **Completion**: Outputs a newline for formatting and exits

## Design Decisions

- **Separation of Concerns**: `FruitsVegetables` handles individual items, `BoxOfProduce` manages the collection
- **Error Handling**: Input validation functions prevent crashes from invalid user input
- **File I/O Separation**: Dedicated functions for file operations make the code modular and testable
- **Constants**: `ITEMS`, `MAX`, `PATH`, and `SEPARATOR` are defined as constants for easy modification
- **Modern C++**: Uses C++23 features, modern random number generation, and const correctness throughout