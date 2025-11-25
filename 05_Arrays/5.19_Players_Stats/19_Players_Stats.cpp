#include <iostream>     // for std::cout, std::cin
#include <limits>       // for std::numeric_limits
#include <iomanip>      // for std::setw
#include <string>       // for std::string
#include <cctype>       // for std::tolower, std::isspace

constexpr int MAX = 10;

void menu(char& choice);
//   Postcondition: displays the menu and sets choice to a valid option

bool handleChoice(char choice, std::string names[],
                  int scores[], int maxSize, int& size);
//   Precondition: choice is a valid menu option
//   Postcondition: handles the choice selected by the user.
// Returns false if the user chose to exit the program, true otherwise.

void addPlayer(std::string names[], int scores[], int maxSize, int& size);
//   Precondition: names and scores are arrays of size at least maxSize
//   Postcondition: adds a new player and score to names and scores arrays,
// if there is space available.

std::string enterName();
//   Postcondition: prompts the user to enter a name and returns it.

int enterScore();
//   Postcondition: prompts the user to enter a score and returns it.

void showPlayers(const std::string names[], const int scores[], int size);
//   Precondition: names and scores are arrays of size at least size
//   Postcondition: displays all player names and their scores.

void showStat(const std::string names[], const int scores[], int size);
//   Precondition: names and scores are arrays of size at least size
//   Postcondition: prompts the user to enter a player name and
// displays the corresponding score or a message if the player is not found.

void removePlayers(std::string names[], int scores[], int& size);
//   Precondition: names and scores are arrays of size at least size
//   Postcondition: prompts the user to enter a player name and
// removes the player from the list if found.

int findPlayer(const std::string& name, const std::string names[], int size);
//   Precondition: names is an array of size at least size
//   Postcondition: searches for name in names array.
// Returns the index of the player if found, -1 otherwise.

int main( ) {
    char choice;
    std::string names[MAX];
    int scores[MAX], size = 0;
    while (true) {
        menu(choice);
        if (!handleChoice(choice, names, scores, MAX, size)) break;
    }
    std::cout << "\n";
    return 0;
}

void menu(char& choice) {
    std::cout << "MENU\n"
              << "a. Add a new player and score\n"
              << "b. Print player names and their scores\n"
              << "c. Show the score by searching the player name\n"
              << "d. Remove a player by typing the name\n"
              << "0. Exit the program\n\n"
              << "Make a choice:\n";
    std::string line;
    while (true) {
        if (!std::getline(std::cin, line)) {    // EOF
            choice = '0';
            return;
        }
        std::size_t first = 0;
        while (first < line.size() && std::isspace(line[first]))    ++first;
        char letter = static_cast<char>(std::tolower(line[first]));
        if ((letter >= 'a' && letter <= 'd') || letter == '0') {
            choice = letter;
            return;
        }
        std::cout << "Not a valid choice. Retry\n";
    }
}

bool handleChoice(const char choice, std::string names[],
                  int scores[], const int maxSize, int& size) {
    switch (choice) {
        case 'a':
            addPlayer(names, scores, maxSize, size);
            break;
        case 'b':
            showPlayers(names, scores, size);
            break;
        case 'c':
            showStat(names, scores, size);
            break;
        case 'd':
            removePlayers(names, scores, size);
            break;
        case '0':
            return false;
        default:
            break;
    }
    return true;
}

void addPlayer(std::string names[], int scores[], const int maxSize, int& size) {
    if (size >= maxSize) {
        std::cout << "Roster is full\n";
        return;
    }
    names[size] = enterName();
    scores[size++] = enterScore();
}

void showPlayers(const std::string names[], const int scores[], const int size) {
    std::cout << std::setw(2) << "#"
              << std::setw(25) << "Player"
              << std::setw(10) << "Score\n";
    for (int idx = 0; idx < size; ++idx)
        std::cout << std::setw(2)    << idx + 1
                  << std::setw(25)   << names[idx]
                  << std::setw(10)   << scores[idx] << "\n";
    std::cout << std::string(37, '-') << "\n";
}

void showStat(const std::string names[], const int scores[], const int size) {
    if (size <= 0) {
        std::cout << "Rooster is empty\n";
        return;
    }
    const std::string player = enterName();
    const int playerRanked = findPlayer(player, names, size);
    if (playerRanked == -1)
        std::cout << "Player not found\n";
    else
        std::cout << names[playerRanked]    << "'s score: "
                  << scores[playerRanked]   << "\n";
}

void removePlayers(std::string names[], int scores[], int& size) {
    if (size <= 0) {
        std::cout << "Rooster is empty\n";
        return;
    }
    const std::string player = enterName();
    const int playerRanked = findPlayer(player, names, size);
    if (playerRanked == -1) {
        std::cout << "Player not found\n";
        return;
    }
    for (int idx = playerRanked; idx < size - 1; ++idx) {
        names[idx] = names[idx + 1];
        scores[idx] = scores[idx + 1];
    }
    --size;
}

int findPlayer(const std::string& name, const std::string names[], const int size) {
    bool found = false;
    int idx;
    for (idx = 0; idx < size; ++idx)
        if (names[idx] == name) {
            found = true;
            break;
        }
    if (found)  return idx;
    return -1;
}

std::string enterName() {
    while (true) {
        std::cout << "Enter a name:\n";
        std::string name;
        if (!std::getline(std::cin, name)) { // EOF
            std::cin.clear();
            continue;
        }
        // trim
        while (!name.empty() && std::isspace(name.front()))
            name.erase(name.begin());
        while (!name.empty() && std::isspace(name.back()))
            name.pop_back();    // name.erase(name.back() - 1);
        if (name.empty()) {
            std::cout << "Name cannot be empty\n";
            continue;
        }
        return name;
    }
}

int enterScore() {
    int score;
    while (true) {
        std::cout << "Enter score:\n";
        if (!(std::cin >> score)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wrong value\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (score < 0) {
            std::cout << "Score should be greater than 0.\n";
            continue;
        }
        return score;
    }
}
