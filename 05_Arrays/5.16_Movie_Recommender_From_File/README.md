Do Programming Project 5.14 except instead of only four reviewers, allow for up to
1000 reviewers and store the reviews in a text file. While your program should support
up to 1000 reviewers, the actual number of reviewers stored in the file could
vary from 1 to 1000. The only movies that are reviewed are numbered from 100 to
105 as in Programming Project 5.14. You are welcome to design the format used
to store the reviews in the text file. After the reviews are read from the text file the
program should input three movies and make predictions for the remaining two
movies as in Programming Project 5.14.

---

# Illustrative Example
<p align="center">
  <img src="./Figures/MovieRating.PNG" alt="Movie Rating From File" width="48%" />
</p>


# Overview
This program builds an implementation of the movie recommender system from Programming Project 5.14,
but extends it to support up to 1000 reviewers loaded from a text file (and potentially much more).
The big benefit is that it reuses the same algorithms while allowing for a variable number of reviewers
loaded at runtime from an external data source.

## Short summary of the program behavior
This program `16_Movie_Reccomender_From_File` extends `14_Movie_Recomendation` by moving data to a file,
introducing `openFile`/`copyData` to load reviews,
and switching from a compile-time reviewer count to a runtime `people` count,
while keeping arrays sized to `MAX_REVIEWERS` for capacity.
Error checks were added to avoid processing uninitialized rows.

## Changes from `14_Movie_Recomendation` to `16_Movie_Reccomender_From_File`
1. Data source
    1. `14` used a built-in `source` array and `fillReviews`.
    2. `16` reads reviews from a file (path stored in `PATH` \- `./5_programming_set_5/5.16_Movie_Recommender_From_File/Utilities/ratings.txt`) 
        and removes the hardcoded `source`.
    3. `16` introduced `openFile`, `closeFile`, and `copyData` to handle file I/O and parsing, while `fillReviews` was removed.

2. Reviewer count and sizing
    1. `14` used a fixed runtime constant `MAX_REVIEWERS = 4` in the function parameters.
    2. `16` increases capacity to `MAX_REVIEWERS = 1000` but introduces a runtime count variable `people` 
       (passed as `reviewers` to functions) that represents the actual number of loaded reviewers. 
       All algorithms operate on `people` (the actual rows used) rather than assuming all `MAX_REVIEWERS` are valid.
    3. Functions that previously iterated up to `MAX_REVIEWERS` inside `predictScore`  
       (e.g., `computeDistance`, `findMostSimilar`, `computeRatingFromSimilar`, `showSimilar`) 
       and `showReviews`, now accept a `reviewers` parameter and use that value.

3. New I/O helpers
    1. Added `bool openFile(const std::string& path, std::fstream& inputStream)` and `void closeFile(const std::string& path, std::fstream& inputStream)` 
       to centralize file open/close logic.
    2. Added `void copyData(const std::string& path, int reviews[][MOVIES], int& people)` 
       to parse the ratings file and populate `reviews` and `people`.

4. `copyData` behavior and parsing
    1. Uses `std::getline` to skip a header line and to read each record line.
    2. Parses each line with `std::istringstream`, expecting `1` user id field + `MOVIES` integer ratings (whitespace-separated).
    3. Validates that each line provides all fields; skips incomplete lines.
    4. Copies ratings into `reviews[user][0..MOVIES-1]` and increments `user` once per valid record.
    5. Guards against exceeding `MAX_REVIEWERS` and sets `people = user` at the end.
    6. If file open fails, `copyData` writes `people = 0` and returns.

5. Robustness and error handling
    1. `main` checks `people == 0` after `copyData` and exits early if no data loaded.
    2. `predictScore` checks `reviewers <= 0` and returns early to avoid calling `std::min_element` on an empty range.
    3. `copyData` prevents buffer overflow by stopping when `user >= MAX_REVIEWERS`.

6. Indexing and mapping
    1. Movie codes still range from `FIRST` (100) to `LAST` (105); code-to-index mapping (`code - FIRST`) is preserved in distance/compute functions.
    2. `copyData` reads a user id field but stores only the ratings in the zero-based `reviews` matrix; the user id is not used as an array index.

7. Initialization of arrays
    1. Initialization of arrays (e.g., `distance[MAX_REVIEWERS] = {0.0}`) is retained for predictable behavior.

8. Input format assumptions (VERY important)
    1. File must contain a header line followed by rows with: `user_id rating100 rating101 ... rating105` separated by whitespace.
    2. If the file uses commas or another layout, the parser will skip/ignore those lines.
       We may need to update `copyData` to handle the different delimiter if necessary.
       If that is the case, please have a look at my other examples that parse CSV files, for instance
       [Likelihood of Death](/3_programming_set_3/3.15_Likelihood_death).

