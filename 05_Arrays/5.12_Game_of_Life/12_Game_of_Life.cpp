#include <iostream>  // for std::cout
#include <algorithm> // for std::fill_n
#include <string>    // for std::string
#include <cstring>   // for std::memcpy
#include <thread>    // for std::this_thread::sleep_for
#include <chrono>    // for std::chrono::milliseconds

void generation();

constexpr int ROW = 22;
constexpr int COL = 80;
constexpr char FILL = '*';
constexpr char EMPTY = ' ';

enum class Pattern {GliderGun, PulsarWithShip};


void startGrid(char grid[][COL], int nRows, int& busyPosition, Pattern p = Pattern::PulsarWithShip);
//   Precondition: nRows is the number of rows in grid.
// grid is an array of size nRows x COL.
//   Postcondition: grid[0][0] through grid[nRows-1][COL-1] have been filled
// with an initial configuration of LIFE cells.

void setCell(char grid[][COL], int nRows,
             int row, int col, int& busyPosition);
//   Precondition: row and col are the position in grid to set to FILL.
//   Postcondition: If row and col are within bounds of grid,
// grid[row][col] is set to FILL and busyPosition is incremented.

void generation(char grid[][COL], int nRows, int& busyPosition);
//   Precondition: nRows is the number of rows in grid.
// grid is an array of size nRows x COL. busyPosition is the number of
// occupied cells in grid.
//   Postcondition: grid[0][0] through grid[nRows-1][COL-1] have been
// updated to the next generation according to the rules of LIFE.

int countNeighbors(int row, int col, const char grid[][COL], int nRows);
//   Precondition: row and col are the position in grid to count neighbors for.
// grid is an array of size nRows x COL. nRows is the number of rows in grid.
//   Postcondition: returns the number of occupied neighbor cells around the grid

bool inBounds(int idxCell, int limit);
//   Precondition: idxCell is the index to check. limit is the upper bound (exclusive).
//   Postcondition: returns true if idxCell is within bounds [0, limit-1], else false.

void display(const char grid[][COL], int nRows);
//   Precondition: nRows is the number of rows in grid.
// grid is an array of size nRows x COL.
//   Postcondition: the contents of grid[0][0] through grid[nRows-1][COL-1]
// have been displayed on the console.

struct PulsarWithShip {
   //    Place a pulsar with a small ship in the grid that crashes into it.
   static void apply(char grid[][COL], const int nRows, int& busyPosition) {
      std::fill_n(&grid[0][0], ROW * COL, EMPTY);
      busyPosition = 0;
         // Place a pulsar around 2/3 of the col width and centered
      const int centerRow = nRows / 2;
      constexpr int startingCol = 2 * (COL / 3);

      constexpr int colLarge[] = {-6, -1, 1, 6};
      constexpr int rowLarge[] = {-4, -3, -2, 2, 3, 4};

      constexpr int colSmall[] = {-4, -3, -2, 2, 3, 4};
      constexpr int rowSmall[] = {-6, -1, 1, 6};

      for (const int col : colLarge)
         for (const int row : rowLarge)
            setCell(grid, nRows, centerRow + row, startingCol + col, busyPosition);

      for (const int col : colSmall)
         for (const int row : rowSmall)
            setCell(grid, nRows, centerRow + row, startingCol + col, busyPosition);

         // place a small ship at the starting column and middle row
      constexpr int offsets[][2] = {
         {-1, 0}, {+1, 0}, {+2, 1},
         {-2, 2}, {+2, 2}, {-2, 3}, {+2, 3},
         {+2, 4}, {-1, 5}, {+2, 5}, { 0, 6},
         {+1, 6}, {+2, 6}
      };

      constexpr int startRow = 5;
      constexpr int startCol = 15;
      for (const auto& offset : offsets)
         setCell(grid, nRows, startRow + offset[0], startCol + offset[1], busyPosition);
   }
};

struct GliderGun {
   //    Place Gosper glider gun at the start.
   static void apply(char grid[][COL], const int nRows, int& busyPosition) {
      std::fill_n(&grid[0][0], ROW * COL, EMPTY);
      busyPosition = 0;
      constexpr int originRow = 5;
      constexpr int originCol = 2;

      constexpr int gunOffsets[][2] = {
         {5,1},{5,2},{6,1},{6,2},
         {5,11},{6,11},{7,11},
         {4,12},{8,12},
         {3,13},{9,13},
         {3,14},{9,14},
         {6,15},
         {4,16},{8,16},
         {5,17},{6,17},{7,17},
         {6,18},
         {3,21},{4,21},{5,21},
         {3,22},{4,22},{5,22},
         {2,23},{6,23},
         {1,25},{2,25},
         {6,25},{7,25},
         {3,35},{4,35},{3,36},{4,36}
      };

      for (const auto& offset : gunOffsets)
         setCell(grid, nRows, originRow + offset[0], originCol + offset[1], busyPosition);
   }
};

int main( ) {
   char world[ROW][COL];
   std::fill_n(&world[0][0], ROW * COL, EMPTY);

   int busyCells = 0;
   startGrid(world, ROW, busyCells);
   display(world, ROW);

   while (busyCells > 0) {
      generation(world, ROW, busyCells);
      display(world, ROW);
   }
   std::cout << "\n";
   return 0;
}

void startGrid(char grid[][COL], const int nRows, int& busyPosition, const Pattern p) {
   switch (p) {
      case Pattern::PulsarWithShip:
         PulsarWithShip::apply(grid, nRows, busyPosition);
         break;
      case Pattern::GliderGun:
         GliderGun::apply(grid, nRows, busyPosition);
         break;
   }
}

void setCell(char grid[][COL], const int nRows,
             const int row, const int col,
             int& busyPosition) {

   if (!inBounds(row, nRows) || !inBounds(col, COL))
      return;
   if (grid[row][col] != FILL) {
      grid[row][col] = FILL;
      ++busyPosition;
   }
}

void display(const char grid[][COL], const int nRows) {
   for (int row = 0; row < nRows; ++row) {
      for (int col = 0; col < COL; ++col)
         std::cout << grid[row][col];
      std::cout << "\n";
   }
   // std::cout << std::string(COL, '-') << "\n";
   std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void generation(char grid[][COL], const int nRows, int& busyPosition) {
   // Births and deaths occur at the changes of generation.
   char nextGenGrid[ROW][COL];
   std::fill_n(&nextGenGrid[0][0], ROW * COL, EMPTY);

   int newBorn = 0;
   auto alive = [](const char organism) {
      return (organism == FILL);
   };
   auto isBorn = [&](char& cell) {
      cell = FILL;
      ++newBorn;
   };
   auto die = [&](char& cell) {
      cell = EMPTY;
   };

   for (int row = 0; row < nRows; ++row) {
      for (int col = 0; col < COL; ++col) {
         switch (countNeighbors(row, col, grid, nRows)) {
            case 0:
            case 1:
               die(nextGenGrid[row][col]);
               break;
            case 2:
               if (alive(grid[row][col]))
                  isBorn(nextGenGrid[row][col]);
               else
                  die(nextGenGrid[row][col]);
               break;
            case 3:
               isBorn(nextGenGrid[row][col]);
               break;
            default:
               die(nextGenGrid[row][col]);
               break;
         }
      }
   }
   std::memcpy(grid, nextGenGrid, sizeof nextGenGrid);
   busyPosition = newBorn;
}

int countNeighbors(const int row, const int col, const char grid[][COL], const int nRows) {
   int neighbors = 0;
   for (int r = row - 1; r <= row + 1; ++r) {
      if (!inBounds(r, nRows))      continue;

      for (int c = col - 1; c <= col + 1; ++c) {
         if (!inBounds(c, COL))     continue;
         if (r == row && c == col)  continue;   // itself
         if (grid[r][c] == FILL)    ++neighbors;
      }
   }
   return neighbors;
}

bool inBounds(const int idxCell, const int limit) {
   return ((idxCell >= 0) && (idxCell < limit));
}
