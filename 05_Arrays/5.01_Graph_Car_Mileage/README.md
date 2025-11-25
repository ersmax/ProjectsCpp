Write a program that reads in the average mileage in kilometers per liter of a car
at 10 different speeds ranging from 10 kilometers per hour to 100 kilometers per
hour, and then reads in the actual mileage obtained for a test drive at each of the 10
speeds. The program then prints out a nicely formatted table showing the mileage
obtained during the 10 test drives and whether it was above or below the average
mileage at that speed, and by how much it varied. The average mileage should be
given for the 10 different speeds in 10 kmph steps. To obtain the mileage during
the test drives, the program repeatedly asks the user to enter the mileage for each
speed. The output should correctly label each speed.
After you have completed the previous program, produce an enhanced version
that also outputs a graph showing the average and actual mileage of the car at each
speed. The graph should be similar to the one shown in Playground repository, Display 5.0.4, 
except that there should be two bars for each speed and they should be labeled as average and
actual mileage at each speed.

---

## Illustrative example

<p align="center">
  <img src="./Figures/mileageTable.PNG" alt="Car mileage Table" width="48%" />
  <img src="./Figures/mileageGraph.PNG" alt="Car mileage Graph" width="48%" />
</p>

## Overview
This program compares a car's average mileage (km/l) at 10 speeds (10, 20, ..., 100 km/h) 
with actual mileage values entered by the user. It prints a formatted table and an ASCII graph 
with two bars per speed (average and actual). The program is menu-driven: show a table, show a graph, or exit.

## Global constants
- `constexpr int TESTS = 10`  
  Number of speed samples (10 speeds).
- `constexpr int KMH = 10`  
  Speed step in km/h (used to label speeds as `(index+1) * KMH`).
- `constexpr double SCALE_FACTOR = 10.0`  
  Used when scaling mileage into "tens" for the graph.

## Main flow (`main`)
- Initializes `avgKm[TESTS]` with the provided average mileages.
- Declares `testDrive[TESTS]` and fills it by calling `fillEntry`.
- Presents a looped menu prompting: `Table (1), Graph (2) or Exit (0)?`
  - Validates numeric input; clears and ignores bad input.
  - `case 1`: calls `showTable(...)`.
  - `case 2`: calls `showGraph(...)`.
  - `case 0`: sets the running flag false to exit the loop.
  - `default`: prints `Unknown option.`

Notes:
- Input is read into an `int choice`. The loop uses a `bool runningVisualization` flag 
  so the program can cleanly continue or exit after loop cleanup.
- After reading `choice`, the rest of the input line is discarded to avoid leftover tokens.

## Input helper (`fillEntry`)
Signature: `void fillEntry(double mileage[], std::size_t size)`

Behavior:
- Iterates `size` times and prompts the user for mileage at each speed label `(idx + 1) * KMH`.
- Validates user input:
  - Requires a numeric value.
  - Accepts only values `> 0` and `<= 50`.
  - On invalid input, clears `std::cin` and ignores the rest of the line, then retries.
- Stores each validated value into `mileage[idx]`.

## Table output (`showTable`)
Signature: `void showTable(const double avgKm[], std::size_t sizeAvg, const double mileage[], std::size_t size)`

Behavior:
- Prints a header with columns: Speed, Avg km/l, Test km/l, Diff, +/-.
- For each index:
  - Computes `diff = mileage[idx] - avgKm[idx]`.
  - Sets a textual result: `"above"`, `"below"`, or `"equal"`.
  - Prints a formatted row showing speed label, average, test value, difference, and the textual result.
- Uses `std::fixed`, `std::showpoint`, and `std::setprecision(1)` for numeric formatting and `std::setw` for alignment.

## Graph output (`showGraph`)
Signature: `void showGraph(const double avgKm[], std::size_t sizeAvg, const double mileage[], std::size_t size)`

Behavior:
- Allocates fixed-size local arrays `avgScaled[TESTS]` and `mileageScaled[TESTS]` (no VLAs).
- Calls `scale(...)` to convert both arrays to scaled integer-like counts (number of asterisks).
- For each speed:
  - Prints `Speed: N km/h`.
  - Prints `Average:` followed by `printAsterisk(...)` for the scaled average.
  - Prints `Actual:` followed by `printAsterisk(...)` for the scaled actual.
- The graph shows mileage in "tens of units"; e.g., a mileage of 34 km/l scaled by `SCALE_FACTOR=10` gives ~3 asterisks.

## Scaling helper (`scale`)
Signature: `void scale(const double numbers[], std::size_t size, double numbersScaled[])`

Behavior:
- For each element `numbers[idx]`, computes a rounded number of tens:
  - Uses `std::floor((numbers[idx] / SCALE_FACTOR) + 0.5)` for rounding to nearest integer.
- Writes the result into `numbersScaled[idx]`.
- (Recommended) clamp negative results to `0` if negative inputs are possible.

## Asterisk printer (`printAsterisk`)
Signature: `void printAsterisk(int number)`

Behavior:
- Prints `number` asterisks (`*`) to `std::cout` to form the bar for the ASCII graph.
- Uses a simple loop to write characters; `number` should be nonnegative.

## Implementation notes and portability
- All array sizes and loop counters use `std::size_t` where appropriate to avoid signed/unsigned issues.
- Local arrays in `showGraph` use the compile-time constant `TESTS` to avoid variable-length arrays (VLAs) which are non-standard in C++.
- Input validation is done defensively: `std::cin.clear()` and `std::cin.ignore(...)` are used to recover from invalid reads.
- `scale` rounds to the nearest integer and can be adjusted to clamp values (e.g., minimum 0).
- `printAsterisk` expects a safe cast to `int` when a scaled double is used; cast and clamp before calling to avoid negative or extremely large counts.

## Example usage
1. Run program.
2. Enter 10 numeric mileages when prompted (each between 0 and 50).
3. At the menu: enter `1` to view table, `2` to view graph, `0` to exit.

## Quick checklist for maintainers
- Ensure `TESTS` matches the number of average values in `avgKm`.
- Keep `KMH` consistent if speed step changes.
- If supporting larger mileages or different scaling, adjust `SCALE_FACTOR` and rounding/clamping logic.


