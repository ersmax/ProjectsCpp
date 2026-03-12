Do Programming Project 5.19 but this time use a class named Player to store a
player’s name and score. Be sure to include a constructor with this class that sets
the name and score. Then, use a dynamic array of the Player class to store the
players. Start with a dynamic array that stores no players. To add a player, create
a new dynamic array that is one larger than the current size, and copy the existing
and the new player into it. To remove a player, create a new dynamic array that is
one smaller than the current size, and copy all players into it except the player that
is to be removed.

---

## Logic

### Data Structures

- **`Player` class** — stores a player's `name` (`std::string`) and `score` (`int`).
  - Three constructors: default, name-only, and name+score.
  - `getName()` — public const getter, returns a const reference to `name`.
  - `setScore()` — private, validates that score is non-negative; throws `std::invalid_argument` otherwise.
  - `operator<<` / `operator>>` — friend overloads for formatted console I/O.

- **`PlayerPtr`** (`Player*`) — points to the start of the current dynamic array of players.
- **`ConstPlayerPtr`** (`const Player*`) — used when read-only access to a player is needed (e.g. lookup result).

---

### Dynamic Array Strategy

The program starts with no players (`rooster = nullptr`, `size = 0`).

**Add player** — allocates a new array one element larger, copies all existing players into it, appends the new player, increments `size`, returns the new array. The old array is then deleted and the pointer reassigned.

```
old array [P0, P1, ..., Pn-1]   →   new array [P0, P1, ..., Pn-1, Pnew]
```

**Remove player** — allocates a new array one element smaller, copies all players except the one to remove, decrements `size`, returns the new array. The old array is then deleted and the pointer reassigned.

```
old array [P0, P1, P2, P3]  (remove P1)   →   new array [P0, P2, P3]
```

Both operations follow the same safe pattern in `menu`:
```
newArray = operation(oldArray)
delete [] oldArray
pointer = newArray
```

---

### Key Functions

| Function | Description |
|---|---|
| `addPlayer` | Allocates `size+1` array, copies existing players, reads new player via `operator>>`, increments `size` |
| `removePlayer` | Gets name from user, finds index via `findIdxPlayer`, calls `helperDeleteByIdx`, decrements `size` |
| `helperDeleteByIdx` | Allocates `size-1` array, copies all players skipping `idxDeletePlayer` |
| `findIdxPlayer` | Linear search by name, returns index or `-1` if not found |
| `findPlayer` | Linear search by name, returns `ConstPlayerPtr` or `nullptr` if not found (used by `queryScore`) |
| `printRooster` | Iterates array and prints each player via `operator<<` |
| `queryScore` | Finds player by name and prints their score, or "Player not found" |
| `inputValidation` | Loops until a valid char `'a'`–`'e'` is entered via `cin` |
| `enterName` | Uses `std::getline` to read a full line (supports spaces); rejects empty input |
| `enterScore` | Uses `cin >>` to read a non-negative integer; rejects invalid or negative input |

---

### Memory Management

| Event | Action |
|---|---|
| Program start | `rooster = nullptr` — no allocation |
| Add player | `new Player[size+1]`, old array `delete[]`'d after pointer reassigned |
| Remove player | `new Player[size-1]`, old array `delete[]`'d after pointer reassigned |
| Remove last player | `new Player[0]` — valid in C++; `size` becomes 0 |
| `delete[] nullptr` | Valid no-op — safe on first add when `rooster` is still `nullptr` |
| Program exit | `delete [] rooster` in `main` frees final array |

---

### Input Handling

- **`enterName`** uses `std::getline` so multi-word names (e.g. `John Doe`) are captured in full. After `inputValidation` consumes its `'\n'` via `ignore`, the stream is clean for `getline`.
- **`enterScore`** uses `cin >>` followed by `ignore` to discard the trailing newline, leaving the stream clean for the next `getline` call.
- **`inputValidation`** uses `cin >>` + `ignore` and only accepts `'a'`–`'e'` (case-insensitive).

---

### Alternative implementations of deleting a player
`removePlayer` illustrates two different ways of deleting a player: by passing the index in the dynamic array or by passing a pointer to the indexed variable in the dynamic structure.
The difference betwen the two approaches can be seen in the relative function declarations:

```cpp
PlayerPtr helperDelete(const PlayerPtr& myRooster, const int size, const ConstPlayerPtr& idxDeletePlayer);
//   Postcondition: A new dynamic array of Player objects has been created that contains all the players in myRooster except for the player pointed to by idxDeletePlayer.

PlayerPtr helperDeleteByIdx(const PlayerPtr& myRooster, int size, int idxDeletePlayer);
//   Postcondition: A new dynamic array of Player objects has been created that contains all the players in myRooster except for the player at index idxDeletePlayer.
```

Thus:
- `helperDelete` takes a pointer to the player to delete, which requires an additional search to find the index of that player in the array.
- `helperDeleteByIdx` takes the index directly, which is more efficient since it avoids the extra search. This is the approach used in `removePlayer` for better performance.