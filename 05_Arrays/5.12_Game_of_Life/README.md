The mathematician John Horton Conway invented the “Game of Life.” Though
not a “game” in any traditional sense, it provides interesting behavior that is
specified with only a few rules. This project asks you to write a program that allows
you to specify an initial configuration. The program follows the rules of Life (listed
shortly) to show the continuing behavior of the configuration.
LIFE is an organism that lives in a discrete, two-dimensional world. While this
world is actually unlimited, we do not have that luxury, so we restrict the array to
80 characters wide by 22 character positions high. If you have access to a larger
screen, by all means use it.
This world is an array with each cell capable of holding one LIFE cell. Generations
mark the passing of time. Each generation brings births and deaths to the LIFE
community. The births and deaths follow this set of rules:
1. We define each cell to have eight neighbor cells. The neighbors of a cell are the
   cells directly above, below, to the right, to the left, diagonally above to the right
   and left, and diagonally below, to the right and left.
2. If an occupied cell has zero or one neighbor, it dies of loneliness. If an occupied
   cell has more than three neighbors, it dies of overcrowding.
3. If an empty cell has exactly three occupied neighbor cells, there is a birth of a
   new cell to replace the empty cell.
4. Births and deaths are instantaneous and occur at the changes of generation.
   A cell dying for whatever reason may help cause birth, but a newborn cell cannot
   resurrect a cell that is dying, nor will a cell’s death prevent the death of another, say,
   by reducing the local population.

Examples: 

| Initial Configuration | Generation 1 | Generation 2 | Generation 3 |
|----------------------:|:-------------|:-------------|:-------------|
|                       | *            |              | *            |
|                   *** | *            | ***          | *            |
|                       | *            |              | *            |

and so on.  

Notes: Some configurations grow from relatively small starting configurations.
Others move across the region. It is recommended that for text output you use
a rectangular char array with 80 columns and 22 rows to store the LIFE world’s
successive generations. Use an * to indicate a living cell and use a blank to indicate
an empty (or dead) cell. If you have a screen with more rows than that, by all means
make use of the whole screen.
Suggestions: Look for stable configurations. That is, look for communities that repeat
patterns continually. The number of configurations in the repetition is called
the period. There are configurations that are fixed, that is, that continue without
change. A possible project is to find such configurations.
Hints: Define a void function named generation that takes the array we call
world, an 80-column by 22-row array of type char, which contains the initial
configuration. The function scans the array and modifies the cells, marking the
cells with births and deaths in accord with the rules listed previously. This involves
examining each cell in turn and either killing the cell, letting it live, or, if the cell
is empty, deciding whether a cell should be born. There should be a function
display that accepts the array world and displays the array on the screen. Some
sort of time delay is appropriate between calls to generation and display. To
do this, your program should generate and display the next generation when you
press Return. You are at liberty to automate this, but automation is not necessary
for the program.

---

# Illustrative example (Glider Gun)
<p align="center">
  <img src="./Figures/GliderGunDark.gif" alt="Glider Gun" width="48%" />
</p>


# Illustrative example (Spaceship crashes into Pulsar)
<p align="center">
  <img src="./Figures/SpaceshipPulsarDark.gif" alt="Spaceship into Pulsar" width="48%" />
</p>


# Implementation notes

## Functions (purpose, key behavior)

- `int main()`
    - Purpose: program entry point — creates the world grid, initializes it, runs the simulation loop.
    - Key steps: clear `world`, call `startGrid(...)` to place an initial pattern, 
      `display(...)`, then loop calling `generation(...)` and `display(...)` while `busyCells > 0`.
    - Note: `busyCells` is used to track how many cells are alive each generation (set by `startGrid` and updated by `generation`).

- `void startGrid(char grid[][COL], const int nRows, int& busyPosition, const Pattern p = Pattern::GliderGun)`
    - Purpose: dispatcher that sets an initial pattern into `grid`.
    - Behavior: calls `PulsarWithShip::apply(...)` or `GliderGun::apply(...)` depending on `p`.
    - Notes: Keeps a backward-compatible default of `Pattern::GliderGun`. 
      Pattern `apply` methods clear the grid, reset `busyPosition`, and place live-cell offsets via `setCell`.

- `void setCell(char grid[][COL], const int nRows, const int row, const int col, int& busyPosition)`
    - Purpose: safely set a single cell to alive (`FILL`) and update the alive counter.
    - Behavior: checks `inBounds(row, nRows)` and `inBounds(col, COL)`; 
      if the cell was previously empty it sets it to `FILL` and increments `busyPosition`.
    - Notes: centralizes bounds checks so pattern placement and other code do not duplicate that logic.

- `void display(const char grid[][COL], const int nRows)`
    - Purpose: write the current grid to `stdout` and pause briefly for animation.
    - Behavior: loops rows and columns printing characters; 
      calls `std::this_thread::sleep_for(std::chrono::milliseconds(50))`.
    - Notes: We ought to use `nRows` when printing wen `ROW` and `nRows` differ.

- `void generation(char grid[][COL], const int nRows, int& busyPosition)`
    - Purpose: compute the next generation of the world following Conway’s rules.
    - Behavior:
        - Allocates a local `nextGenGrid[ROW][COL]` and initializes it to `EMPTY`.
        - Uses `countNeighbors(...)` for each cell and applies the rules to fill `nextGenGrid`.
        - Copies `nextGenGrid` back into `grid` using `std::memcpy(grid, nextGenGrid, sizeof nextGenGrid)`.
        - Updates `busyPosition` to the number of cells born in this generation (`newBorn`).
    - Important caveat: `sizeof nextGenGrid` copies the full `ROW * COL` bytes. 
    - If `nRows` can differ from `ROW`, we should use `std::memcpy(grid, nextGenGrid, nRows * COL * sizeof(char))` or `std::copy_n`.

- `int countNeighbors(const int row, const int col, const char grid[][COL], const int nRows)`
    - Purpose: return number of live neighbors around `(row, col)`.
    - Behavior: iterates the 3×3 neighborhood, uses `inBounds` to skip outside indices, ignores the center cell, counts `grid[r][c] == FILL`.

- `bool inBounds(const int idxCell, const int limit)`
    - Purpose: simple index range check (`0 <= idxCell < limit`).
    - Usage: used before any grid access to avoid out-of-range indexing.

## Pattern structs 

- `struct GliderGun` and `struct PulsarWithShip`
    - Purpose: encapsulate initial patterns as self-contained units.
    - Interface: each exposes a static `apply(char grid[][COL], const int nRows, int& busyPosition)` function.
    - Behavior of `apply`:
        - Clears the grid (`std::fill_n(&grid[0][0], ROW * COL, EMPTY)`).
        - Sets `busyPosition = 0`.
        - Iterates a list of relative offsets and calls `setCell(...)` for each live-cell coordinate.
    - Benefits of using `struct`s:
        - Separation of concerns: pattern placement logic is grouped and isolated from simulation logic.
        - Easy extension: add new patterns by authoring another struct with an `apply` method.
        - Readability: named types make intent clear (`GliderGun::apply(...)` is self-documenting).
        - Reuse: patterns can be reused across multiple simulations or tests without modifying `startGrid`.

## Lambdas vs separate functions

- Lambdas are used in `generation` function as helpers:
- A lambda is an inline, unnamed function object that can capture local variables from the surrounding scope.
- The lambdas in `generation` function are:
```cpp
auto alive = [](char organism) { 
   return organism == FILL; 
};
```
```cpp
auto isBorn = [&](char& cell) { 
   cell = FILL; ++newBorn; 
};
```  
The `&` capture allows `isBorn` to update the local `newBorn` counter without passing it explicitly.
This allows me to update the number of total `organisms` living in the grid, hence ending the 
loop or repeat it indefinitely on the basis of such living cells.

### Separate functions alternative
The alternative is to define regular functions in file scope.
Functions signature:
```cpp
bool alive(char organism);
void die(char& organism);
void isBorn(char& organism, int& countAlive);
```
Functions definition:
```cpp
bool alive(const char organism) {
   return (organism == FILL);
}
void die(char& organism) {
   organism = EMPTY;
}
void isBorn(char& organism, int& countAlive) {
   organism = FILL;
   ++countCountAlive;
}
```

### Comparison

- Lambdas (used in `generation`)
   - Pros:
      - Local scope: helpers are defined next to the algorithm that uses them (better locality).
      - Can capture local variables (e.g., `newBorn`) directly; no extra parameters needed (better readability).
      - Avoid polluting global/function-scope namespace.
   - Cons:
      - Small, one-off helpers — not ideal if reuse or unit testing is needed (not a big deal here).
      - Slightly less discoverable if overused inline (can be misleading).

- Separate functions
   - Pros:
      - Reusable and easier to test independently.
      - Clear function signatures and potentially more readable if logic is non-trivial.
   - Cons:
      - Cannot capture local variables — we must pass references or make state global.

### Notes
- I decided to try lambdas in `generation` because they are short, closely tied to the algorithm, 
  and need to update the new organisms, `newBorn`. If the helper logic grows or is reused elsewhere, 
  we should refactor into separate functions with explicit parameters (or into a small helper class).
- When copying the computed grid, we should use `std::copy_n` for element-wise clarity 
  or `std::memcpy` with an explicit byte count: `nRows * COL * sizeof(char)` if nRows differ between old 
  and new Grid. This is not the case, however.



