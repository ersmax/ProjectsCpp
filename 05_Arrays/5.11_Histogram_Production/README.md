Write a program that accepts input like the program in Display 5.4 (repository Playgroud 5_0_4)
and that outputs a bar graph like the one in that program, except that your program will
output the bars vertically rather than horizontally. A two-dimensional array may
be useful.

---

## Illustrative example
<p align="center">
  <img src="./Figures/Histogram.PNG" alt="Histogram" width="48%" />
</p>


## Purpose
This program collects production numbers for a fixed number of plants, 
scales the totals into thousands (rounded), prints the raw totals, 
and displays a vertical bar chart (histogram) of the scaled data.

## High-level flow
- `main`:
  - Calls `enterData` to read production values for each plant.
  - Calls `scale` to convert totals to thousands (rounded).
  - Calls `showRawData` to print totals per plant.
  - Calls `showHistogram` to print a vertical histogram of the scaled totals.

## Function summaries

- `enterData(int production[], int numPlants)`
  - Prompts the user per plant and accumulates totals using `getTotal`.
  - Fills `production[0..numPlants-1]`.

- `getTotal(int& totPlant, int nPlant)`
  - Reads lines of numbers (space- or comma-separated). Non-digit separators are normalized.
  - Adds positive numbers to `totPlant`. `-1` ends input for that plant.
  - Shows a running total after each input line.

- `scale(const int numbers[], int scaledNumbers[], int numPlants)`
  - Converts each entry to thousands using `std::floor(numbers[i] / 1000.0 + 0.5)` to round to nearest thousand.
  - Result is stored in `scaledNumbers`.

- `findMax(const int scaleNumbers[], int numPlants)`
  - Returns the maximum scaled value among the `numPlants` entries.
  - Important: always pass `numPlants` (the actual array length) when calling this function.

- `printAsterisks(int number)`
  - Intended to print the presence/absence of a bar unit for a single column.
  - Correct behavior for a vertical, fixed-column-width histogram:
    - Print exactly one column (one field) per call, either a `'*'` or a blank, using `std::setw(COL_WIDTH)`.
    - Do not loop to print multiple `setw` columns for a single `number`, because that breaks alignment.

- `showRawData(const int numbers[], int numPlants)`
  - Prints each plant's raw (unscaled) production.

- `showHistogram(const int scaleNumbers[], int numPlants)`
  - Steps:
    1. Call `findMax(scaleNumbers, numPlants)` to determine chart height.
    2. For each row from `max - 1` down to `0`, iterate plants and call `printAsterisks` once per plant to produce a single fixed-width column.
    3. Print the bottom labels: plant index and the `#` marker aligned with the same column width.
  - Alignment details:
    - Use a single `COL_WIDTH` constant across all formatted output (`std::setw(COL_WIDTH)`).
    - Each plant produces exactly one formatted column per row; this guarantees vertical alignment of bars and labels.

## Formatting details
- I print a single label per plant using the same width. 
  Example label: `"#1"` formatted with `std::setw(COL_WIDTH)` — this prints the `#` and the plant number together in the same bottom line and aligned with the columns above.
- We want the `#` character and the plant index on the *same* printed field (e.g. `#1`);
- This is done with the label string `std::string("#") + std::to_string(plant+1)` and print it with `std::setw(COL_WIDTH)`.

## Example of desired output layout
(With `COL_WIDTH = 4` and 4 plants, scaled values = [3,1,4,2])

Row 3:            *      
Row 2:    *       *   
Row 1:    *       *   *
Row 0:    *   *   *   *
Labels:  #1  #2  #3  #4

Each `*` or blank occupies exactly `COL_WIDTH` columns; labels use the same width.


