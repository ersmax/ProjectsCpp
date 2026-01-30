You operate several hot dog stands distributed throughout town. Define a class
named HotDogStand that has a member variable for the hot dog stand’s ID number 
and a member variable for how many hot dogs the stand sold that day. Create
a constructor that allows a user of the class to initialize both values.
Also create a function named JustSold that increments the number of hot dogs
the stand has sold by one. This function will be invoked each time the stand sells a
hot dog so that you can track the total number of hot dogs sold by the stand. Add
another function that returns the number of hot dogs sold.
Finally, add a static variable that tracks the total number of hot dogs sold by all
hot dog stands and a static function that returns the value in this variable. Write
a main function to test your class with at least three hot dog stands that each sell a
variety of hot dogs.

---

## Code Logic Explanation

### Class Design: `HotDogStand`

**Member Variables:**
- `standID` (string): Unique identifier for each hot dog stand
- `soldStand` (int): Number of hot dogs sold by this specific stand
- `totalSold` (static int): Tracks total hot dogs sold across ALL stands
- `nextID` (static int): Auto-increment counter starting at 1010 for generating unique IDs

### Constructors

1. **Default Constructor:** `HotDogStand()`
   - Auto-generates an ID in format "A1010", "A1011", "A1012", etc.
   - Initializes `soldStand` to 0
   - Uses static `nextID` counter that increments with each new stand

2. **Single Parameter Constructor:** `HotDogStand(const std::string& id)`
   - Allows custom ID assignment
   - Validates ID through `setId()` - rejects IDs starting with 'A' followed by digits 1-9
   - Initializes `soldStand` to 0

3. **Two Parameter Constructor:** `HotDogStand(const std::string& id, const int soldItems)`
   - Sets both custom ID and initial sold count
   - Validates ID and soldItems through helper methods
   - Adds initial `soldItems` to both `soldStand` and global `totalSold`

### Key Methods

**`justSold()`**
- Increments this stand's count (`soldStand++`)
- Increments global total (`totalSold++`)
- Called each time a hot dog is sold

**`getSoldStand()`**
- Returns number of hot dogs sold by this specific stand

**`getTotalSold()` (static)**
- Returns total hot dogs sold across all stands

### Validation Logic

**`setId(const std::string& id)`**
- **Reserves IDs** starting with 'A' followed by digits '1'-'9' for auto-generation
- Throws `std::invalid_argument` if reserved ID is used
- Allows: "A0", "B10", "C15", etc.
- Rejects: "A1", "A10", "A1010" (conflicts with auto-generated IDs)

**`setSoldItems(int soldItems)`**
- Validates that initial sold count is non-negative
- Throws `std::invalid_argument` if negative
- Updates both local and global counters

### Main Function Flow

1. **Creates three stands inside try block:**
   - `aStand`: Auto-generated ID ("A1010")
   - `anotherStand`: Custom ID "B10" with 10 initial sales
   - `aThirdStand`: Custom ID "A0" (allowed since '0' < '1')

2. **Simulates sales:**
   - `aStand` sells 2 hot dogs
   - `anotherStand` sells 1 hot dog
   - `aThirdStand` sells 1 hot dog

3. **Reports results:**
   - Individual stand sales
   - Total sales across all stands (14 hot dogs: 10 initial + 4 new)

### Exception Handling

- All object creation and operations are wrapped in `try-catch`
- If constructor throws during object creation (invalid ID or negative soldItems):
  - Object is NOT created
  - Execution jumps to catch block
  - Error message is displayed
  - Remaining code in try block is skipped

**Example:** If `aThirdStand("A10")` was used instead of `"A0"`:
- Constructor would throw exception (reserved ID)
- `aThirdStand` would never exist
- Subsequent operations on `aThirdStand` would cause compilation errors (variable out of scope)

### Static Variable Behavior

- `totalSold` persists across all instances - shared by entire class
- When any stand sells a hot dog, global total is updated
- Initial sales from constructor also counted in global total
- Accessible without creating an object: `HotDogStand::getTotalSold()`

In addition, nextID keeps track of IDs assigned automatically, and it is increased
each time that a Constructor with no IDs is called, that is `HotDogStand()`.

