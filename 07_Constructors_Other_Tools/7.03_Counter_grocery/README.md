# Class Design: Counter

My mother always took a little red counter to the grocery store. The counter was
used to keep tally of the amount of money she would have spent so far on that visit
to the store if she bought everything in the basket. The counter had a four-digit
display, increment buttons for each digit, and a reset button. An overflow indicator
came up red if more money was entered than the $99.99 it would register. (This
was a long time ago.)

Write and implement the member functions of a class Counter that simulates and
slightly generalizes the behavior of this grocery store counter. The constructor should
create a Counter object that can count up to the constructor’s argument. That is,
Counter(9999) should provide a counter that can count up to 9999. 
A newly constructed counter displays a reading of 0. The member function void reset( );
sets the counter’s number to 0. The member function void incr1( ); increments
the units digits by 1, void incr10( ); increments the tens digit by 1, and void
incr100( ); and void incr1000( ); increment the next two digits, respectively.
Accounting for any carrying when you increment should require no further action than
adding an appropriate number to the private data member. A member function bool
overflow( ); detects overflow. (Overflow is the result of incrementing the counter’s
private data member beyond the maximum entered at counter construction.)

Use this class to provide a simulation of my mother’s little red clicker. Even though
the display is an integer, in the simulation, the rightmost (lower order) two digits
are always thought of as cents and tens of cents, the next digit is dollars, and the
fourth digit is tens of dollars.

Provide keys for cents, dimes, dollars, and tens of dollars. Unfortunately, no choice of
keys seems particularly mnemonic. One choice is to use the keys asdfo: a for cents,
followed by a digit 1 to 9; s for dimes, followed by a digit 1 to 9; d for dollars, followed
by a digit 1 to 9; and f for tens of dollars, again followed by a digit 1 to 9. Each entry
(one of asdf followed by 1 to 9) is followed by pressing the Return key. Any overflow
is reported after each operation. Overflow can be requested by pressing the o key.

---

## Implementation Logic

The `Counter` class encapsulates the behavior of a digital tally counter with configurable limits.

#### Private Data Members
- `int limit`: Maximum value the counter can reach (default: 9999)
- `int current`: Current counter value (starts at 0)
- `bool overflowFlag`: Tracks whether overflow has occurred

#### Constructors
1. **Default Constructor**: `Counter()` - Creates a counter with default limit of 9999
2. **Parameterized Constructor**: `Counter(int userLimit)` - Creates a counter with custom limit (0-9999)
   - Uses `setLimit()` to validate and set the user-provided limit
   - Throws `std::invalid_argument` if limit is outside valid range

#### Public Member Functions

**`void incr(int number)`**
- Increments the counter by the specified number (0-9)
- Uses `assert()` to enforce precondition (number must be 0-9)
- Checks for overflow before incrementing
- If overflow would occur, sets current to limit and sets overflow flag

**`void decr(int number)`**
- Decrements the counter by the specified number (0-9)
- Handles underflow by setting current to 0 (can't go negative)
- Clears overflow flag when decrementing below the limit
- Short-circuits if number is 0

**`void reset()`**
- Resets counter to 0
- Clears the overflow flag

**`bool getOverflow() const`**
- Returns the state of the overflow flag

**`int getCurrent() const`**
- Returns the current counter value

#### Private Helper Functions

**`void setLimit(int userLimit)`**
- Validates that limit is between 0 and 9999
- Throws exception if validation fails

**`bool overflow(int addend)`**
- Checks if adding the addend would exceed the limit
- If overflow detected:
  - Sets current to limit
  - Sets overflow flag to true
  - Returns true
- Returns false if no overflow

**`bool underflow(int subtrahend) const`**
- Checks if subtracting would result in negative value
- Returns true if current - subtrahend < 0

### Program Flow

#### Main Function Logic
1. Creates two Counter objects:
   - `aCounter`: Default limit (9999)
   - `anotherCounter`: Custom limit (4999)
2. Enters do-while loop that continues until user enters 'y' to exit
3. For each iteration:
   - Displays menu
   - Shows Counter 1's current value
   - Gets user choice and processes operation on Counter 1
   - Shows Counter 1's new value
   - Repeats for Counter 2
   - Asks if user wants to exit

#### Menu System

**Key Mappings** (stored in `CHOICES` array):
- **Increment Operations** (a, s, d, f):
  - `a`: Increment by cents (×1)
  - `s`: Increment by dimes (×10)
  - `d`: Increment by dollars (×100)
  - `f`: Increment by tens of dollars (×1000)
  
- **Decrement Operations** (z, x, c, v):
  - `z`: Decrement by cents (×1)
  - `x`: Decrement by dimes (×10)
  - `c`: Decrement by dollars (×100)
  - `v`: Decrement by tens of dollars (×1000)
  
- **Status Check** (o):
  - `o`: Display overflow status

**`showMenu()`**
- Displays all available menu options with descriptions

**`makeChoice()`**
- Prompts user for menu choice
- Validates input against `CHOICES` array
- Handles invalid input with error recovery (clear + ignore)
- Returns 'e' to allow exit
- Loops until valid choice is entered

**`inputValidation()`**
- Prompts for numeric input between 0-9
- Handles non-numeric input gracefully
- Loops until valid number is entered

**`menuSubmission(char choice, Counter& myCounter)`**
- Uses switch statement to route choice to appropriate operation
- Calls `inputValidation()` to get the digit (0-9)
- Multiplies digit by appropriate power of 10:
  - Cents operations: digit × 1
  - Dimes operations: digit × 10
  - Dollars operations: digit × 100
  - Tens of dollars operations: digit × 1000
- For overflow check, displays appropriate message based on flag state

### Key Design Decisions

1. **Generalized Interface**: Instead of separate `incr1()`, `incr10()`, `incr100()`, `incr1000()` methods, uses single `incr(int)` method with multiplication in calling code
2. **Extended Functionality**: Adds decrement operations not in original specification
3. **Dual Counter Demo**: Main program operates two counters simultaneously to demonstrate independent state management
4. **Robust Input Validation**: Multiple layers of validation prevent invalid states
5. **Overflow Persistence**: Overflow flag remains set until counter is reset or decremented below limit
6. **Assertion Usage**: Debug-time precondition checking with `assert()` (can be disabled with `NDEBUG`)

### Error Handling

- **Constructor**: Throws exception for invalid limit
- **Input Validation**: Loops until valid input received (no exceptions thrown)
- **Overflow/Underflow**: Handled by clamping to valid range (limit or 0)
- **Assertions**: Runtime checks in debug mode for method preconditions