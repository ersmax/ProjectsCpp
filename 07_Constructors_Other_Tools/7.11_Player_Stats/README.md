Do Programming Project 5.19, but this time use a class named Player to store a
player’s name and score.Be sure to include a constructor with this class that sets
the name and score.Then use a vector of the Player class to store the ten players.

---

## Program Logic (7.11_Player_Stats.cpp)

This program implements a player roster management system using modern C++ features:

### Core Components:
1. **Player Class** - Encapsulates player data (name and score) with:
   - Three constructors: default (using delegation), name-only, and name+score
   - Constructor delegation: `Player() : Player("no name", 0) {}`
   - Public getters: `getName()` and `getScore()`
   - Private setters: `setName()` and `setScore()`
   - Private member variables for data hiding

2. **std::vector<Player>** - Dynamic container for storing up to MAX_PLAYERS (10) players
   - Uses `reserve()` to pre-allocate capacity
   - Allows efficient insertion and deletion with `push_back()` and `erase()`

3. **Menu-driven Interface**:
   - Add player (with validation)
   - Display all players in formatted table
   - Search player by name
   - Delete player by name
   - Exit program

### Key Implementation Details:
- Input validation for both name (trims whitespace, rejects empty) and score (>= 0)
- Uses iterators for vector traversal and deletion
- Range-based for loops with const references for efficiency
- Returns -1 as sentinel value in `findPlayer()` to signal "not found"

---

## Evolution: Differences Between 5.19, 6.13, and 7.11

### **5.19_Players_Stats.cpp** (Arrays)
**Data Structure:**
- Two parallel arrays: `std::string names[MAX]` and `int scores[MAX]`
- Fixed size array (MAX = 10)
- Manual index management with `size` variable

**Memory Management:**
- Static allocation (all 10 slots allocated upfront)
- Manual shifting of elements when deleting: copy elements left to fill gaps

**Access Pattern:**
- Index-based access: `names[idx]` and `scores[idx]`
- Must keep arrays synchronized manually

**Key Operations:**
```cpp
// Deletion requires manual shifting
for (int idx = playerRanked; idx < size - 1; ++idx) {
    names[idx] = names[idx + 1];
    scores[idx] = scores[idx + 1];
}
--size;
```

---

### **6.13_Player_Stats_Class.cpp** (Class + Array)
**Data Structure:**
- Player class with public setters/getters
- Array of Player objects: `Player players[MAX]`
- Still uses fixed-size array

**Improvements over 5.19:**
- **Encapsulation**: Related data (name + score) bundled together
- **Type safety**: Single Player object instead of parallel arrays
- **No synchronization issues**: Name and score always paired

**Limitations:**
- Still using arrays (fixed size)
- Public setters allow unrestricted modification
- No constructors (requires manual setup with setters)

**Key Operations:**
```cpp
// Adding player requires separate setter calls
players[size].setName(namePlayer);
players[size].setScore(scorePlayer);
size++;
```

---

### **7.11_Player_Stats.cpp** (Class + Vector + Constructors)
**Data Structure:**
- Enhanced Player class with:
  - **Constructors** for object initialization
  - **Constructor delegation** for code reuse
  - **Private setters** (better encapsulation)
- `std::vector<Player>` for dynamic storage

**Improvements over 6.13:**

1. **Constructors**:
   - Objects initialized correctly at creation time
   - Constructor delegation reduces code duplication
   - No need for manual setter calls after creation

2. **std::vector Benefits**:
   - Dynamic sizing (grows as needed, shrinks when elements removed)
   - Built-in `erase()` method (no manual shifting)
   - Iterator support for safe deletion
   - `reserve()` for performance optimization

3. **Better Encapsulation**:
   - Private setters prevent external modification
   - Immutable after construction (no public setters)

4. **Modern C++ Features**:
   - Range-based for loops: `for (const Player& player : rooster)`
   - Auto type deduction: `auto iterator = rooster.begin()`
   - `constexpr` for compile-time constants

**Key Operations:**
```cpp
// Adding: construct and push in one step
const Player aPlayer(name, score);
rooster.push_back(aPlayer);

// Deletion: vector handles the shifting
rooster.erase(iterator);  // Automatic reallocation
```

---

## Summary Comparison

| Feature | 5.19 (Arrays) | 6.13 (Class+Array) | 7.11 (Class+Vector) |
|---------|---------------|--------------------|--------------------|
| Data Organization | Parallel arrays | Array of objects | Vector of objects |
| Memory | Fixed (static) | Fixed (static) | Dynamic |
| Encapsulation | None | Basic | Strong |
| Constructors | N/A | No | Yes (3 constructors) |
| Initialization | Manual | Setters | Constructor |
| Deletion | Manual shifting | Manual shifting | `vector::erase()` |
| Mutability | Full access | Public setters | Private setters only |
| Modern C++ | Basic | Intermediate | Advanced |
| Code Complexity | High (manual sync) | Medium | Low (STL handles it) |

**Progression**: Raw arrays → Object-oriented design → Modern C++ with STL containers and proper encapsulation
