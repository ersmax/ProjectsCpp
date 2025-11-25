A common memory matching game played by young children is to start with a
deck of cards that contains identical pairs. For example, given six cards in the deck,
two might be labeled “1”, two might be labeled “2”, and two might be labeled “3”.
The cards are shuffled and placed facedown on the table. The player then selects
two cards that are facedown, turns them faceup, and if they match they are left
faceup. If the two cards do not match, they are returned to their original position
facedown. The game continues in this fashion until all cards are faceup.
Write a program that plays the memory matching game. Use 16 cards that are
laid out in a 4 * 4 square and are labeled with pairs of numbers from 1 to 8. Your
program should allow the player to specify the cards through a coordinate system.
For example, in the following layout:

| cards | 1 | 2 | 3 | 4 |
|---:|:--:|:--:|:--:|:--:|
| 1 | 8 | * | * | * |
| 2 | * | * | * | * |
| 3 | * | 8 | * | * |
| 4 | * | * | * | * |

all of the cards are facedown except for the pair of 8’s, which has been located at
coordinates (1,1) and (2,3). To hide the cards that have been temporarily placed
faceup, output a large number of newlines that force the old board off the screen.
Hint: Use a 2D array for the arrangement of cards and another 2D array that indicates
whether a card is faceup or facedown. Write a function that “shuffles” the
cards in the array by repeatedly selecting two cards at random and swapping them.

---

# Illustrative example
<p align="center">
  <img src="./Figures/CardgameDark.gif" alt="Cardgame" width="48%" />
</p>

# Memory Matching Game - Implementation

This program implements a simple console memory/matching game using a `4 \* 4` grid of numbered card pairs. 
The player picks two coordinates per turn; matching pairs stay faceup until all cards are matched.

## Key constants
- `ROWS`, `COLS` — board dimensions (`4` each).
- `CARDS` — total card count (`ROWS * COLS`).
- `SAME` — pair grouping helper (`2`).
- `COORDINATES` — number of coordinates to pick (`2`).
- `UNFOLD`, `FOLD` — characters used to show facedown / faceup states.

## Program flow (`main`)
1. Allocate `board[ROWS][COLS]` (int values) and `upDown[ROWS][COLS]` (face state).
2. Call `createBoard` to initialize paired values and set all cards to `UNFOLD`.
3. Call `shuffleCards` to randomly permute card positions.
4. Show the current board with `showBoard`.
5. Loop while `chooseCards` returns true and there are unmatched cards:
   - Call `unfold` to reveal the chosen pair, handle matching logic and update `remainingCards`.
   - Redraw board with `showBoard`.
6. Print final result ("You won!" or "Game over").

## Function summaries

- `void createBoard(int cards[][COLS], char upDown[][COLS], int nRows)`
  - Initializes `cards` with pairs of numbers (1..`CARDS/2`) laid out row-major.
  - Sets every element of `upDown` to `UNFOLD` (facedown).
  - Logic detail: increments `cardValue` so every two adjacent slots become a pair.

- `void shuffleCards(int cards[][COLS], int nRows)`
  - Performs an in-place Fisher–Yates shuffle over the flattened `nRows * COLS` indices.
  - Maps a flat index `i` to 2D coordinates as `row = i / COLS`, `col = i % COLS`.
  - Uses a single `mt19937` RNG seeded with `random_device` and `uniform_int_distribution`.

- `void showBoard(const int cards[][COLS], const char upDown[][COLS], int nRows)`
  - Prints a column header, a separator line, then each row number and row contents.
  - For each cell: prints `UNFOLD` if card is facedown, otherwise prints the numeric value.
  - Useful for both normal view and debugging (commented debug dump of true values exists).

- `bool chooseCards(const int nRows, const int nCols, int card1[], int card2[], int dimensions)`
  - Prompts the user `dimensions` times (2) for "row column".
  - Accepts `exit` or EOF to terminate early and returns `false` in that case.
  - Validates numeric input, range (`1..nRows`, `1..nCols`), and prevents selecting the same card twice.
  - On success fills `card1`/`card2` (0-based indices) and returns `true`.

- `void unfold(const int cards[][COLS], char upDown[][COLS], int nRows, const int card1[], const int card2[], int dimensions, int& remainingCards)`
  - Marks the chosen two coordinates as `FOLD` (faceup).
  - If values match: decrements `remainingCards` by 2, prints a match message, and leaves them faceup.
  - If values do not match: shows the board, prompts the user to press Enter, then restores only those cards that were previously `UNFOLD` (so previously-found matches remain `FOLD`).
  - Calls `clearConsole()` after hiding the temporary reveal to push the old board off-screen.

- `void clearConsole()`
  - Current implementation prints multiple newlines (8) to push previous output off the visible console.
  - Note: this is a simple fallback; some IDE run windows (e.g. CLion) or large terminals may require more newlines or a platform-specific clear. A robust option would use platform APIs (Win32 or ANSI sequences) or increase the newline count.

# Note on randomization: Why the Fisher-Yates shuffle?

In short, Fisher Yates shuffle algorithm ensures that each possible permutation  of the array is equally likely, 
because the random selection is done from the unshuffled portion of the array only. Those elements that have
already been placed in their final position are not considered for swapping again. 

Advantages:
- Uniform distribution: Fisher-Yates generates each possible permutation with equal probability when paired with a proper RNG. 
  This avoids subtle biases introduced by naive shuffling methods.
- In-place and O(n): The algorithm runs in linear time and shuffles the array without extra memory, which is simple and efficient for small boards like the 4 \* 4 grid.
- Correct use of RNG: This implementation uses a single `std::mt19937` seeded from `std::random_device` and `std::uniform_int_distribution` for each step, avoiding modulo bias and reseeding issues.
- 2D mapping: The board is flattened conceptually; Fisher-Yates operates on flat indices and maps them to row/column with `row = idx / COLS` and `col = idx % COLS`, keeping the code simple and generic for other sizes.
