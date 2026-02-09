 First, complete Programming Project 6.12. Modify the main function with a loop
so that the user determines how many BoxOfProduce objects are created. Each box
should contain three bundles of fruits or vegetables selected randomly from this
list: tomatillo, broccoli, tomato, kiwi, and kale. Add a menu so the user can decide
when to stop creating boxes. The menu should allow the user to make substitutions
for the randomly selected items in a box.
You would like to throw in a free recipe flyer for salsa verde if the box contains
tomatillos. However, there are only 5 recipe flyers. Add a static member variable
to the BoxOfProduce class that counts the number of recipe flyers remaining and
initialize it to 5. Also add a member variable that indicates whether or not the box
contains a recipe flyer and modify the output function to also print “salsa verde
recipe” if the box contains a recipe flyer. Finally, add logic inside the class so that if
the box contains at least one order of tomatillos then it automatically gets a recipe
flyer until all of the recipe flyers are gone. Note that a box should only get one
recipe flyer even if there are multiple orders of tomatillos.
Test your class by creating boxes with tomatillos from your menu until all of the
flyers are gone.

---

## Program Logic

### Main Flow
1. **Initialization**: Load produce list from file (tomatillo, broccoli, tomato, kiwi, kale)
2. **User Input**: Ask user how many boxes to create
3. **Box Creation Loop**: For each box:
   - Create a `BoxOfProduce` object (constructor auto-increments box counter)
   - Fill with 3 randomly selected items via `randomSelection()`
   - Display box contents and available produce list
   - Allow user to substitute items until satisfied
   - Store completed box in vector
4. **Continue Loop**: After all boxes created, ask if user wants to add more boxes
5. **Termination**: Program ends when user declines to add more boxes

### Recipe Flyer Management (Automatic)
The class automatically manages recipe flyers using private helper methods:

- **On Item Addition** (`addContent()`):
  - When a tomatillo is added, if the box doesn't have a flyer and flyers remain, assign one

- **On Item Substitution** (`changeContent()`):
  - After substitution, check if box now contains tomatillos
  - If yes and no flyer assigned: give flyer (if available)
  - If box had flyer but no longer has tomatillos: remove flyer and return it to the pool

- **Flyer Constraints**:
  - Only 5 flyers total (static counter `tomatilloFlyer`)
  - One flyer per box maximum (tracked by `hasFlyer` member)
  - Flyers can be "recycled" during substitution if tomatillos are removed

---

## Key Differences from Project 6.12

### Structural Changes

1. **Constructor Added**:
   - **6.12**: No constructor
   - **7.10**: `BoxOfProduce()` constructor that increments static box counter

2. **Static Members**:
   - **6.12**: None
   - **7.10**: 
     - `nBox` - tracks total number of boxes created
     - `tomatilloFlyer` - counts recipe flyers remaining (initialized to 5)

3. **Instance Members**:
   - **6.12**: `box[]`, `items`
   - **7.10**: Added `hasFlyer` - boolean indicating if this box contains a recipe flyer

### Functional Changes

4. **Multiple Box Creation**:
   - **6.12**: Single box only (`BoxOfProduce aBox;` in main)
   - **7.10**: User determines quantity, stored in `std::vector<BoxOfProduce>`, with option to add more

5. **Recipe Flyer Feature** (New in 7.10):
   - New private methods:
     - `isTomatillo()` - checks if produce name is "tomatillo" (case-insensitive using `std::transform`)
                        (used when new item of type `FruitsVegetables` is added to the box)
     - `hasTomatillo()` - scans box for any tomatillos (used when user substitutes items)
     - `giveFlyer()` - assigns flyer, decrements counter
     - `removeFlyer()` - removes flyer, increments counter (flyer recycling)
   - Automatic flyer assignment logic integrated into `addContent()` and `changeContent()`

6. **Method Signature Changes**:
   - **`changeContent()`**:
     - **6.12**: Returns `bool` to indicate success/failure
     - **7.10**: Returns `void` (validation moved to caller via `isValidIndex()`)
   - **`output()`**:
     - **6.12**: only shows the items of type `FruitsVegetables` in the box
     - **7.10**: It also displays "salsa verde recipe" when `hasFlyer == true`

7. **Additional Helper Functions**:
   - **6.12**: None beyond core functionality
   - **7.10**: 
     - `fillBoxes()` - encapsulates the box creation and substitution loop
     - `addBoxes()` - prompts user to add more boxes after initial batch

8. **Input Validation Enhancement**:
   - **`itemValidation()`**:
     - **6.12**: Accepts any integer (including negatives after first check fails)
     - **7.10**: Explicitly checks `if (value < 0) continue;` to ensure positive values

### Subtle Implementation Details

9. **Flyer Assignment Timing**:
   - In `addContent()`: Checks the single item being added (`isTomatillo(produce)`) 
     before deciding to give a flyer (only gives flyer if the new item is a tomatillo and box doesn't already have one)
   - In `changeContent()`: Checks entire box after substitution (`hasTomatillo()`)
     The item could be a tomatillo being removed or added, but there could be other tomatillo in the box. 
     Hence, we check the whole box to determine flyer status.
   - This logic ensures correctness whether building a new box or modifying existing one

10. **Const Correctness**:
    - **7.10** adds `const` qualifiers to methods that don't modify state: `output()`, `hasTomatillo()`, `getItem()`, `isValidIndex()`

11. **Static Method Access**:
    - **7.10** adds public static getters: `getNumberBox()`, `getFlyersLeft()` for external access to static counters

---

