Write a program that manages a list of up to ten players and their high scores in the
computer’s memory (not on disk as in Programming Project 18). Use two arrays
to manage the list. One array should store the player’s name, and the other array
should store the player’s high score. Use the index of the arrays to correlate the
names with the scores. In the next chapter you will learn a different way to organize
related data by putting them into a struct or class. Do not use a struct or class for
this program. Your program should support the following features:
a. Add a new player and score (up to ten players).
b. Print all player names and their scores to the screen.
c. Allow the user to enter a player name and output that player’s score or a message
if the player name has not been entered.
d. Allow the user to enter a player name and remove the player from the list.
Create a menu system that allows the user to select which option to invoke.

---

# Overview

This program manages up to ten players and their high scores using two parallel arrays: 
one for player names and one for scores. 
The arrays are correlated by index (same index = same player). 
The program uses a text menu to let the user add, list, query, and remove players. 
Input is validated and trimmed; EOF is handled gracefully.

## Illustrative example
<p align="center">
  <img src="./Figures/Players.PNG" alt="Players" width="48%" />
</p>


## High-level flow
- `main` creates the arrays and enters a loop that shows the menu and handles the chosen action until the user exits.

## Function summaries and logic

- `menu(char& choice)`
  - Displays the menu.
  - Reads a full line with `std::getline`.
  - Skips leading whitespace to find the first meaningful character.
  - Converts that character to lowercase (using `std::tolower` with `static_cast<unsigned char>`).
  - Validates the choice is one of `a`, `b`, `c`, `d`, or `0`.
  - On EOF sets `choice` to `'0'` (exit).

- `handleChoice(char choice, std::string names[], int scores[], int maxSize, int& size)`
  - Dispatches the selected option using a `switch`.
  - Calls the appropriate function for each menu item.
  - Returns `false` when the user chose to exit (`'0'`), otherwise `true`.

- `addPlayer(std::string names[], int scores[], int maxSize, int& size)`
  - If the roster is full (`size >= maxSize`) prints a message and returns.
  - Calls `enterName()` to obtain a validated, trimmed name.
  - Calls `enterScore()` to obtain a validated non\-negative score.
  - Stores the name and score at index `size` and increments `size`.

- `enterName()`
  - Prompts repeatedly until a non\-empty name is entered.
  - Reads a full line with `std::getline`. On EOF clears state and retries.
  - Trims leading and trailing whitespace using `std::isspace` (with `static_cast<unsigned char>`).
  - Rejects empty names (after trimming) and prompts again.
  - Returns the validated trimmed name.

- `enterScore()`
  - Prompts repeatedly until a valid non\-negative integer is entered.
  - Uses `operator>>` to read an `int`. On failure clears the stream and ignores the rest of the line.
  - Rejects negative scores and prompts again.
  - Returns the validated score.

- `showPlayers(const std::string names[], const int scores[], int size)`
  - Prints a header row and then each player line with index (`#`), name, and score.
  - Uses `std::setw` for alignment and `std::string(37, '-')` to print a separator.

- `showStat(const std::string names[], const int scores[], int size)`
  - If the roster is empty prints a message and returns.
  - Prompts for a name using `enterName()`.
  - Uses `findPlayer` to locate the name; prints the score if found or "Player not found" otherwise.

- `removePlayers(std::string names[], int scores[], int& size)`
  - If the roster is empty prints a message and returns.
  - Prompts for a name using `enterName()`.
  - Uses `findPlayer` to get the index. If found, shifts all subsequent elements left to overwrite the removed entry and decrements `size`.

- `findPlayer(const std::string& name, const std::string names[], int size)`
  - Performs a linear search over the `names` array.
  - Returns the index of the matching name or `-1` if not found.

##  Alternative input validation
An alternative to input validation in `showMenu` could be:
However, this implementation works for simple input but has weaknesses: 
it reads a single token with operator>> (so multi-character input can be mishandled), 
doesn't accept uppercase, and doesn't handle EOF cleanly. 
The version that uses std::getline, trims leading whitespace, converts to lowercase, 
handles EOF by returning '0', and improve the logic of  showMenu(char& choice).

```cpp
void showMenu(char& choice) {
    std::cout << "a. Add a new player and score\n"
              << "b. Print player names and their scores\n"
              << "c. Show the score by searching the player name\n"
              << "d. Remove a player by typing the name\n"
              << "0. Exit the program\n\n"
              << "Make a choice:\n";

    char letter;
    while (true) {
        if (!(std::cin >> letter)) {
            std::cout << "Error in the choice\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
        if ((letter >= 'a' && letter <= 'd') || letter == '0') {
            choice = letter;
            break;
        }
        std::cout << "Not a valid choice.\n";
    }
}
```