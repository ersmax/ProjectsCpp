Create a class called Television that has member variables
displayType – A string that stores the television’s display type
dimension – A variable of type double that stores the dimension
of the television in inches.
connectivitySupport – A dynamic array of strings that stores the different
connectivity modes supported by the television
The class should have mutator and accessor functions to set and get the above
member variables. Include a constructor that takes arguments of type string,
double, and an array of strings to assign the three member variables. Also include
a copy constructor.
Embed your class in a test program that reads the input from the user to set displayType,
dimension, and connectivitySupport values by default for a television.
Your program should then read in input for the number of televisions. Your
program should create as many Television objects as required using the copy
constructor, and ask the user if customization is required for any television. If so,
use the mutator methods to set the values accordingly.

---

## Program Logic

### `Television` class
- **Purpose:** Models a single TV set and owns its dynamic list of supported connectivity ports.
- **Data members:**
  - `displayType` – `std::string` holding the model / display type name.
  - `dimension` – `double` storing the screen size in inches.
  - `connectivitySupport` – `StringPtr` (pointer to dynamic `std::string` array) that stores supported ports.
  - `sizeConnectivity` – `int` holding how many ports are currently stored in `connectivitySupport`.
- **Constructors:**
  - Default constructor: initializes an "empty" TV with default dimension 22.0 and no ports (`connectivitySupport == nullptr`, `sizeConnectivity == 0`).
  - `Television(const std::string& name)`: sets `displayType` and uses a default dimension of 22.0 with a single default port `"HDMI"`.
  - `Television(const std::string& name, double inches)`: sets `displayType` and validates `dimension` via `setDimension(inches)`, still defaulting to one `"HDMI"` port.
  - `Television(const std::string& name, double inches, const ConstStringPtr connections, int size)`: fully custom constructor. It validates the dimension, sets `sizeConnectivity`, allocates a dynamic array of `size` strings, and copies each connection name into `connectivitySupport`. This matches the assignment requirement for a constructor taking a string, a double, and an array of strings.
- **`setDimension(double inches)`:** small helper enforcing that dimension is at least 1.0 inch. Throws `std::invalid_argument` if the value is invalid.
- **Destructor (`~Television`):** releases the dynamically allocated `connectivitySupport` array using `delete[]`, avoiding memory leaks.
- **Copy constructor:** builds a *deep copy* of another `Television`. It copies the simple members (`displayType`, `dimension`, `sizeConnectivity`) and, if `sizeConnectivity > 0`, allocates a new string array and copies each port string. If `sizeConnectivity == 0`, it sets `connectivitySupport` to `nullptr`.
- **Copy assignment operator (`Television::operator=`):** allows one existing `Television` to be assigned from another.
  - First guards against self-assignment (`if (this == &secondTv) return *this;`).
  - Copies `displayType` and `dimension`.
  - Deletes the old `connectivitySupport` array on the left-hand side to prevent leaks.
  - Copies `sizeConnectivity`, then either sets `connectivitySupport` to `nullptr` (if zero) or allocates a new array and copies each port string. This also implements a full deep copy.

### Stream operators
- **`operator>>(std::istream&, Television&)`:**
  - Interactively reads all data for a `Television` from the given input stream.
  - Uses `enterName` to read a non-empty model name, and `enterNumber` to read a valid dimension in inches.
  - Calls `enterPorts` to dynamically build a validated list of connectivity ports.
  - Assigns `displayType` and `dimension` to the `Television`.
  - Deletes any existing `connectivitySupport` array of the target object, then attaches the new array returned by `enterPorts` and updates `sizeConnectivity`.
  - Returns the input stream so extraction can be chained.

- **`operator<<(std::ostream&, const Television&)`:**
  - Prints a formatted summary of a `Television`.
  - Outputs `displayType`, `dimension`, and then iterates over `connectivitySupport` to show each port separated by commas.
  - Returns the `ostream` so insertion can be chained.

### Global typedefs and constants
- `StringPtr`, `ConstStringPtr` – simplify passing dynamic string arrays around.
- `TvPtr`, `ConstTvPtr` – pointer aliases for arrays of `Television`.
- `MENU` – single constant string that stores the user menu text.
- `PORTS` / `N_PORTS` – fixed list of valid port names and its size.

### Top-level control: `main` and `menu`
- **`int main()`**
  - Initializes `tvList` as `nullptr` and `size` as 0; together they represent a resizable dynamic array of `Television` objects.
  - Repeatedly calls `menu(tvList, size)` in a loop. The menu performs the selected operation and returns `true` to continue or `false` to exit.
  - After the loop ends (user chooses option `f`), `main` deletes the dynamic `tvList` array and returns.

- **`bool menu(TvPtr& tvList, int& size)`**
  - Prints the `MENU` string.
  - Reads a validated choice using `inputValidation`.
  - Dispatches based on the chosen option:
    - `a`: Add a single new TV (`addTelevisions` with `multipleTvs == false`).
    - `b`: Define one "standard" TV and add multiple copies using the copy constructor.
    - `c`: Print all current TVs (`showTelevision`).
    - `d`: Change characteristics of a TV (`changeCharacteristics` with `deleteFlag == false`).
    - `e`: Remove a TV by ID (`changeCharacteristics` with `deleteFlag == true`).
    - `f`: Return `false` to signal program termination.
  - Returns `true` as long as the user has not chosen to exit.

### Functions related to list manipulation
- **`void addTelevisions(TvPtr& tvList, int& size, bool multipleTvs)`**
  - If `multipleTvs` is true, asks the user how many TVs to add; otherwise it defaults to 1.
  - Allocates a new dynamic array `temp` of size `size + numberTvs`.
  - Copies existing TVs from `tvList` into `temp` using the copy assignment operator (deep copies).
  - Reads one `Television` from the user (`newTelevision`) using `operator>>`.
  - For each new position, constructs a copy (`Television copyTv(newTelevision)`) and assigns it into `temp`.
  - Updates `size` and replaces the old array by deleting `tvList` and making `tvList = temp`.

- **`void showTelevision(const TvPtr& tvList, int size)`**
  - Iterates from 0 to `size - 1`.
  - For each index, prints a 1-based ID (`idx + 1`) and then the TV using `operator<<`.

- **`void changeCharacteristics(TvPtr& tvList, int& size, bool deleteFlag)`**
  - If the list is not empty, calls `showId` to print all available IDs.
  - Uses `selectId` to get a valid 0-based index from the user.
  - If `deleteFlag` is `true`, calls `deleteTv` to remove that TV from the list.
  - Otherwise, calls `changeTelevision` to modify that TV in place.

- **`void deleteTv(TvPtr& tvList, int& size, int idDelete)`**
  - If `size == 1`, deletes the single TV array, sets `tvList` to `nullptr`, sets `size` to 0, and reports that the list is now empty.
  - Otherwise, allocates a new array of size `size - 1`.
  - Copies all TVs except the one at `idDelete` into the new array, maintaining order.
  - Decrements `size`, deletes the old `tvList` array, and points `tvList` to the new array.

- **`void changeTelevision(const TvPtr& tvList, int size, int id)`**
  - Prints the 1-based ID and current details of the selected TV.
  - Creates a temporary `Television newTelevision` and reads new values via `operator>>`.
  - Assigns `tvList[id] = newTelevision;` which triggers the copy assignment operator to safely replace the internal state.

- **`void showId(const ConstTvPtr& tvList, int size)`**
  - Prints the list of available TV IDs in a compact comma-separated format.
  - IDs are 1-based to be more intuitive for the user.

- **`int selectId(const ConstTvPtr& tvList, int size)`**
  - If `size == 0`, returns `-1` to signal an empty list.
  - Otherwise, reads a number from the user using `enterNumber`.
  - Converts the user’s 1-based input into 0-based index and validates the range.
  - Re-prompts until a value in `[0, size)` is entered.
  - Returns the valid 0-based index.

### Functions related to input and validation
- **`std::string enterName(std::istream& inputStream, const std::string& prompt)`**
  - Repeatedly prints the prompt and tries to read a full line into `name`.
  - If stream input fails, it clears the error flags, discards the rest of the line, and re-prompts.
  - Rejects empty strings and forces the user to enter at least one character.
  - Returns a valid, non-empty name.

- **`double enterNumber(std::istream& inputStream, const std::string& prompt)`**
  - Repeatedly prints the prompt and tries to read a `double`.
  - If extraction fails (e.g., user types letters), clears the stream, discards the invalid input, and re-prompts.
  - Ignores remaining characters on the line after a successful read.
  - Validates the number to be at least `1.0`; otherwise, prints a message and re-prompts.
  - Returns the validated number.

- **`char enterInput()`**
  - Reads a single character from `std::cin`.
  - On failure, clears error flags, discards the bad input, and re-prompts.
  - Consumes the rest of the line (so further reads start fresh).
  - Returns the lowercase version of the character.

- **`char inputValidation()`**
  - Uses `enterInput()` to get a character.
  - Checks that the character is between `'a'` and `'f'` (the valid menu choices).
  - If invalid, prints an error message and re-prompts until a valid option is chosen.
  - Returns the valid lowercase character.

### Port-handling helpers
- **`StringPtr enterPorts(std::istream& inputStream, int& sizeNewPorts)`**
  - Initializes `sizeNewPorts` to 0 and `newPorts` to `nullptr`.
  - In a loop, prints the list of valid ports (`printPorts`), then asks for a port name using `enterName`.
  - Uses `isDuplicate` to prevent the same port being added twice.
  - Uses `addPort` to validate the port against `PORTS` and grow the dynamic array by one element.
  - Stops if the user chooses not to add more ports (answer not `'y'`) or if `sizeNewPorts` reaches `N_PORTS`.
  - Returns the dynamic array of entered ports; the caller takes ownership and is responsible for deleting it.

- **`bool addPort(StringPtr& newPorts, int& size, const std::string& port)`**
  - Allocates a new array `temp` one element larger than the current `size`.
  - Copies existing entries from `newPorts` into `temp`.
  - Checks whether the requested `port` is one of the allowed values in `PORTS`.
  - If it is valid, writes it into the last index of `temp`, increments `size`, deletes the old `newPorts` array, and points `newPorts` to `temp`, returning `true`.
  - If not valid, deletes `temp` and returns `false`, leaving `newPorts` and `size` unmodified.

- **`bool isDuplicate(const ConstStringPtr& newPorts, int size, const std::string& port)`**
  - Iterates through the existing `newPorts` entries.
  - If `port` is already present, prints a message and returns `true`.
  - Otherwise returns `false`.

- **`void printPorts()`**
  - Prints all allowed port names from the global `PORTS` array in a human-friendly comma-separated format.

---

In summary, the program demonstrates:
- Correct use of dynamic memory with the Rule of Three.
- A resizable array of objects managed via raw pointers.
- Careful input validation and user-friendly prompts.
- Clear separation of responsibilities between the class representing one TV and the free functions that manage collections of TVs and user interaction.
