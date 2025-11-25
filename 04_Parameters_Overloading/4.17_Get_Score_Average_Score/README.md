Given the scores.txt file described in Programming Project 4.16, write two
additional functions. The first function should be named getPlayerScore and
take a string parameter as input that is a player’s name, and it should return the
player’s high score stored in the file. If the player’s name is not in the file, then
the function should return 0. The second function should output whether a
player’s high score is above average, exactly equal to the average, or below average,
where the average is computed from all of the scores in the file. You should
design the function appropriately (i.e., determine the function name, parameters,
and return values).

---
# Get Score / Average Comparison

Small C++ program that reads player names and high scores from a text file, 
reports the highest scorer, and compares a queried player's score to the average of all scores.

## Input file format (`Scores.txt`)
The file contains zero or more entries. Each entry is two lines:
- first line: player name (string)
- second line: integer score

## Program behavior
- Reads all entries into an `std::unordered_map<std::string,int>` mapping names to scores.
- Computes and displays the name and value of the highest score (or "No players" when none).
- Prompts the user to enter a player's name and outputs whether that player's score is above, 
  equal to, or below the average score computed from all players.

## Important function contracts
- `bool populateMap(std::string& nameHighScore, int& highScore, int& totalScore, std::unordered_map<std::string,int>& scores);`
  - Reads the file, fills `scores`, sets `totalScore`, `highScore`, and `nameHighScore`. Returns `false` if file can't be opened.
- `int getPlayerScore(const std::unordered_map<std::string,int>& scores, const std::string& namePlayer);`
  - Returns the player's score if found; returns `0` when the player is not present (per specification).
- `void comparePlayer(const std::unordered_map<std::string,int>& scores, int totalScore, const std::string& name, int score);`
  - If the player is not present, prints a "Comparison not possible" message. Otherwise prints one of:
    - `<name> scored above the average (<average>)`
    - `<name> scored equal to the average (<average>)`
    - `<name> scored below the average (<average>)`

## Notes and implementation details
- The program ignores empty name lines (at the start) and handles malformed score lines 
- I use `std::getline(std::cin >> std::ws, name)` to read the query name so leading whitespace/newline does not cause an empty read.
- Average is computed as `static_cast<double>(totalScore) / scores.size()` and printed as a floating value.
- Code contains an internal consistency `assert` that recomputes the total from the map to verify `totalScore`.

## Implementation
- One could perform a single `scores.find(name)` in `main` and passing the existence/score to `comparePlayer` to avoid redundant map lookups.

Sample session
--------------
When run with the example `Scores.txt` above, program output may look like:
```
Charlie scored 130
Enter a player's name: Bob
Bob scored below the average (115)
```



