Consider a text file named scores.txt that contains player scores for a game. A
possible sample is shown here where Ronaldo’s best score is 10400, Didier’s best
score is 9800, etc.
Ronaldo
10400
Didier
9800
Pele
12300
Kaka
8400
Cristiano
8000
Write a function named getHighScore that takes a string reference parameter and
an integer reference parameter. The function should scan through the file and set
the reference parameters to the name of the player with the highest score and the
corresponding score.

---

# Highest Score — README

## File location
The program reads `./4_Programming_set_4/4.16_Highest_Score/Utilities/Scores.txt`.

## Public functions (signatures)
- `bool getHighScore(std::string& fullName, int& highScore)`  
- `bool openFile(const std::string& path, std::ifstream& inputStream)`  
- `void showHighScore(const std::string& fullName, int highScore)`

## Program logic
1. `main` calls `getHighScore` with two references: `fullName` and `highScore`.  
2. `getHighScore` opens the scores file via `openFile`. If opening fails it returns `false`.  
3. It loops reading a name using `std::getline`. For each name it attempts to read the next line as an `int` using `input >> score`.  
4. If the score read fails (non\-integer or missing), the stream fail state is cleared and the remainder of that score line is skipped; the loop continues to the next name.  
5. If a score is read successfully, the trailing newline is consumed so the next `getline` reads the following name.  
6. The function tracks the largest score found and the corresponding player name. If none found, `highScore` is set to `-1` and `fullName` is cleared. `getHighScore` returns `true` on successful file processing (even if no valid records were found).  
7. `main` prints an error and exits if `getHighScore` returns `false`; otherwise it calls `showHighScore` to print the result. `showHighScore` prints `No players` when `highScore == -1`.

## Error handling
- File open failure: `getHighScore` returns `false`. `main` reports the error and exits.  
- Malformed score lines: skipped (stream cleared and line ignored). Program continues scanning remaining records.

## Behavior notes and assumptions
- Names may contain spaces and are read with `std::getline`.  
- Scores must be valid integers on a separate line. Non\-integer score lines are ignored.  
- If no valid name/score pair is found, output reports no players.  
- The program does not modify the input file.