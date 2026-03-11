One problem with dynamic arrays is that once the array is created using the new
operator the size cannot be changed. For example, you might want to add or delete
entries from the array similar to the behavior of a vector. This project asks you
to create a class called DynamicStringArray that includes member functions that
allow it to emulate the behavior of a vector of strings.
The class should have the following:
• A private member variable called dynamicArray that references a dynamic array
of type string.
• A private member variable called size that holds the number of entries in the
array.
• A default constructor that sets the dynamic array to nullptr and sets size
to 0.
• A function that returns size.
• A function named addEntry that takes a string as input. The function should
create a new dynamic array one element larger than dynamicArray, copy all
elements from dynamicArray into the new array, add the new string onto the
end of the new array, increment size, delete the old dynamicArray, and then
set dynamicArray to the new array.
• A function named deleteEntry that takes a string as input. The function
should search dynamicArray for the string. If not found, it returns false. If
found, it creates a new dynamic array one element smaller than dynamicArray.
It should copy all elements except the input string into the new array, delete
dynamicArray, decrement size, and return true.
• A function named getEntry that takes an integer as input and returns the
string at that index in dynamicArray. It should return nullptr if the index is
out of dynamicArray’s bounds.
• A copy constructor that makes a copy of the input object’s dynamic array.
• Overload the assignment operator so that the dynamic array is properly copied
to the target object.
• A destructor that frees up the memory allocated to the dynamic array.
Embed your class in a suitable test program.

---

## Implementation Logic

### Data Layout

The class owns a single contiguous heap allocation pointed to by `dynamicArray` (`std::string*`). 
All strings live side-by-side in that one block. `size` tracks how many elements are valid.

```
size = 3
dynamicArray ──→ [ "hello" | "beautiful" | "world" ]
                   [0]         [1]           [2]
```

### Memory Ownership Rule

Every public operation that changes the array follows the same three-step pattern:
1. Allocate a **new** array of the required size via a private helper.
2. `delete[]` the **old** array.
3. Point `dynamicArray` to the new array and update `size`.

This keeps ownership unambiguous: exactly one allocation exists at any time.

---

### Member-by-Member Logic

#### Default Constructor
Sets `dynamicArray = nullptr` and `size = 0`. No heap allocation occurs until `addEntry` is called.

#### `addEntry(newEntry)`
Delegates to `helperEntry`, which allocates `size + 1` elements, copies all existing strings, and appends `newEntry` at the end. The old array is deleted and `size` is incremented.

```
Before: [ "hello" | "world" ]   size = 2
After:  [ "hello" | "world" | "beautiful" ]   size = 3
```

#### `deleteEntry(entry)`
1. `searchEntry` scans `dynamicArray` linearly and returns the index, or `-1` if not found.
2. `helperDelete` allocates `size - 1` elements and copies every element except the one at the found index.  
   Special case: if `size == 1`, returns `nullptr` directly instead of allocating an empty array.
3. The old array is deleted, `dynamicArray` is set to the new one, and `size` is decremented.

```
Before: [ "hello" | "beautiful" | "world" ]   size = 3
Delete "beautiful":
After:  [ "hello" | "world" ]   size = 2
```

#### `getEntry(idx)`
Returns a `ConstStringPtr` (`const std::string*`) — a read-only, non-owning pointer to the element at `idx`. 
Returns `nullptr` if `idx` is out of bounds. The caller must **not** call `delete` on the returned pointer; the array owns its memory.

#### `operator[](idx)`
Same element access as `getEntry` but returns `const std::string&` and throws `std::out_of_range` instead of returning `nullptr`. 
Intended for use when the index is known to be valid.

#### Copy Constructor
Allocates a fresh array of the same `size` and deep-copies every element. The two objects are fully independent after construction.

#### `operator=(rhs)`
- Self-assignment guard: returns immediately if `this == &rhs`.
- If sizes differ: deletes the current array and allocates a new one of `rhs.size` (or sets `nullptr` if `rhs.size == 0`).
- Copies all elements from `rhs`.

#### Destructor
Calls `delete[] dynamicArray`. Safe to call even when `dynamicArray == nullptr` because `delete[]` on `nullptr` is a no-op.

#### `operator<<`
Prints elements in `{e0, e1, ..., eN}` format. Prints `{}` for an empty array.

---

### Key Design Decisions

| Decision | Reason |
|---|---|
| `ConstStringPtr` (`const std::string*`) for `getEntry` | Prevents the caller from modifying internal strings through the returned pointer |
| `nullptr` instead of `new std::string[0]` when empty | Keeps `dynamicArray == nullptr` ↔ `size == 0` consistent with the default constructor |
| Private helpers `helperEntry` / `helperDelete` | Isolate allocation logic; keep public methods concise |
| `searchEntry` is private | Internal utility only; not part of the public contract |

