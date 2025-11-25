Write a program that will allow two users to play tic-tac-toe. The program should
ask for moves alternately from player X and player O. The program displays the
game positions as follows:

|  Positions  |   |   | 
|------------:|:--|:--|
|           1 | 2 | 3 | 
|           4 | 5 | 6 | 
|           7 | 8 | 9 |  

The players enter their moves by entering the position number they wish to mark.
After each move, the program displays the changed board. A sample board configuration
is as follows:

|  Current board |   |   | 
|---------------:|:--|:--|
|              X | X | O | 
|              4 | 5 | 6 | 
|              O | 8 | 9 |  


---

## Illustrative example
<p align="center">
  <img src="./Figures/TicTacToe.PNG" alt="Tic Tac Toe" width="48%" />
</p>

# Overview Tic-Tac-Toe Game

The program implements a two-player interactive tic‑tac‑toe game (3×3). 
Players enter moves by typing the position number (1..9). T
he program alternates turns, validates input, updates the board, records moves for each player, 
and prints the board after each input and at the end.

## Key constants

- `PLAYERS = 2` — number of players.
- `N_ROWS = 3`, `N_COLS = 3` — board dimensions.
- `MOVES = 5` — maximum moves recorded per player (for a 3×3 board each player can make up to 5 moves).

## Board representation

- The board is a 2D array: `int board[N_ROWS][N_COLS]`.
- At initialization the board stores position numbers `1..(N_ROWS*N_COLS)` so empty cells are shown by their position number.
- When a player marks a cell it is replaced by that player's numeric marker:
    - For `PlayerIndex::O` the stored value is `0`.
    - For `PlayerIndex::X` the stored value is `-1`.
- A cell is considered occupied when its stored value is < `1` (the code uses `board[row][col] < 1`).

This choice ensures no collision between position numbers (positive) and player markers (`0` and `-1`).

## `enum class PlayerIndex`

Declaration in the file:

- `enum class PlayerIndex { O = 0, X = -1 };`

### Notes:

- The enum values are chosen to match the integers stored in the board for each player. Converting an enum value to `int` via `static_cast<int>(player)` yields the board value for that player.
- Using an `enum class` scopes the names (`PlayerIndex::O`, `PlayerIndex::X`) and avoids accidental implicit conversions.

## Important index math

To convert a 1-based position `pos` to 0-based row/col:

```cpp
// pos is in 1..(N_ROWS*N_COLS)
int row = (pos - 1) / N_COLS;
int col = (pos - 1) % N_COLS;
```

This mapping is used when reading user input and when storing/retrieving cell values.

## Function-by-function

Each function is listed with its signature and concise description.

### `int boardValue(PlayerIndex player);`
- Returns the integer representation stored on the board for `player`.
- Implementation: `return static_cast<int>(player);`
- Purpose: centralizes conversion from enum to board value. Using a function clarifies intent and isolates the conversion.

### `char playerChar(PlayerIndex player);`
- Returns the character to print for a player on the board.
- Current implementation uses:
    - `PlayerIndex::O` → `'0'` (zero character) — this is how the code is written.
    - `PlayerIndex::X` → `'X'`
- Used by prompts and `showBoard` when a cell holds a player marker.

### `void togglePlayer(PlayerIndex& player);`
- Toggles the current player:
    - If `player == PlayerIndex::O` sets `player = PlayerIndex::X`
    - Else sets `player = PlayerIndex::O`
- Called after each turn to switch who moves next.

### `void initializeBoard(int board[][N_COLS], int nRows);`
- Fills the `board` with consecutive position numbers from `1` to `nRows * N_COLS`.
- These numbers are printed for empty cells.

### `void showBoard(const int board[][N_COLS], int nRows);`
- Prints the current board to `std::cout`.
- For each cell:
    - If `cell == boardValue(PlayerIndex::O)` prints `playerChar(PlayerIndex::O)`.
    - Else if `cell == boardValue(PlayerIndex::X)` prints `playerChar(PlayerIndex::X)`.
    - Else prints the position number stored in the cell.
- This function gives the user a clear view of which positions remain available.

### `void playTurn(int board[][N_COLS], int nRows, int movesPlayer[], int& nMoves, PlayerIndex playerNumber);`
- Orchestrates one player's turn:
    1. Calls `enterMove` to get a valid position (1..9) that is not occupied.
    2. Records the chosen position in `movesPlayer[nMoves++]`.
    3. Converts the position to `row` and `col` and writes `board[row][col] = boardValue(playerNumber)`.

### `int enterMove(const int board[][N_COLS], int nRows, PlayerIndex playerNumber);`
- Repeatedly prompts the player until a valid integer move is entered.
- Validations:
    - Input is numeric.
    - Position is within range `1..nRows*N_COLS`.
    - Cell is not already occupied (determined by `isCellBusy`).
- Consumes remaining input on each read to avoid leftover characters interfering with subsequent reads.
- Calls `showBoard` each loop to show current state before prompting.

### `bool isCellBusy(const int board[][N_COLS], int nRows, int position);`
- Converts `position` to `(row,col)` and returns `true` if the stored value indicates the cell is occupied.
- Current occupancy test: `return (board[row][col] < 1);` (both `0` and `-1` are treated as busy).

## `main` flow

1. Declare `board`, counters, and arrays to record moves:
    - `movesPlayerX[MOVES]`, `nMovesX` for player X.
    - `movesPlayerO[MOVES]`, `nMovesY` for player O (the code uses `nMovesY` as the O counter).
2. Randomly choose starting player:
    - `std::uniform_int_distribution<int> playerNumber(0, 1);`
    - `playerTurn = (playerNumber(rng) == 0) ? PlayerIndex::O : PlayerIndex::X;`
3. Initialize the board to position numbers.
4. Loop `while (placesLeft > 0)`:
    - Call `playTurn` for the current player.
    - Call `togglePlayer`.
    - Decrement `placesLeft`.
5. After loop, call `showBoard` and exit.

## Notes and reasoning highlights

- The choice to store positive position numbers for empty cells and non‑positive numbers for player marks avoids ambiguity when printing the board.
- The `enum class PlayerIndex` values are set so `static_cast<int>(player)` is exactly the stored board value; `boardValue` simply wraps this cast for clarity.
- Input handling in `enterMove` is defensive: it clears `std::cin` and discards remaining characters when a non-number is entered.
- Move recording arrays keep which positions each player has taken; these arrays are separate from the `board` and are incremented via their associated `nMoves` variables.

