Do Programming Project 5.18 except use only one array as a parameter instead
of two arrays. The single array should be of type Player where Player is a class
that you create. The Player class should have a member variable of type string
to store the player’s name and a member variable of type int to score the player’s
score. Encapsulate these variables appropriately. Upon return from your function
the array entry at index 0 should be set to the name and score of the player with the
best score, the entry at index 1 should be set to the name and score of the player
with the second best score, etc.

---

## Implementation logic

This implementation uses a `Player` class and a single `Player[]` array to
load, sort and display high scores. 

- `class Player` — encapsulates `name` (`std::string`) and `score` (`int`) with
  public setters (`setName`, `setScore`) and getters (`getName`, `getScore`).

- `main` — allocates `Player players[MAX]`, calls `processFile` to load data,
  `orderData` to sort the array in descending score order, then `showBest` to
  print the top `BEST` players.

- `processFile` — opens the scores file at `PATH`, calls `parseFile` to fill the
  `players` array, and closes the file. Returns `false` if the file cannot be
  opened.

- `parseFile` — reads the file two lines at a time (name then score line). The
  score line may contain one or more integers; each integer is recorded as a
  separate `Player` entry with the preceding name. `nPlayers` is incremented
  for each recorded score and bounded by `maxSize`.

- `orderData` — allocates a temporary `Player buffer[MAX]` and invokes
  `mergeSort` to sort the `players` array in descending order using merge sort.

- `mergeSort` / `merge` — standard merge sort operating on `Player` objects.
  Function signatures use `Player players[]` and `Player buffer[]`, which decay
  to pointers to the first element; therefore the `size` (or `start`/`end`)
  parameters are required to track array bounds. `merge` copies ranges into the
  buffer and then copies the merged sequence back into `players`.

- `showBest` — iterates the sorted array and prints each player's rank,
  `name` and `score`. The top `BEST` entries are highlighted.

## Implementation notes:
- Passing `Player players[]` to functions passes a pointer to the first element
  (no elementwise copy). That is why bounds information (`size`, `start`,
  `end`) is passed explicitly.
- Compared to the previous implementation in 5.18, this version used only one
  array of `Player` objects instead of two separate arrays for names and scores.
  This allows for better encapsulation of related data and simplifies function.

