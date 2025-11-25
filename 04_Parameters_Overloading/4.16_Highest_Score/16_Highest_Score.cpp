#include <iostream>
#include <fstream>
#include <string>
#include <limits>

const std::string SCORES_PATH = "./04_Parameters_Overloading/4.16_Highest_Score/Utilities/Scores.txt";

bool getHighScore(std::string& fullName, int& highScore);
// Precondition: fullName and highScore are declared
// Postcondition: sets fullName to the name of the player with the highest score
//                and highScore to the corresponding score

bool openFile(const std::string& path, std::ifstream& inputStream);
// Precondition: path is the file path and inputStream is declared
// Postcondition: opens the file located at path and associates it with inputStream

void showHighScore(const std::string& fullName, int highScore);
// Postcondition: displays the name of the player with the highest score and the score

int main( ) {
    std::string nameHighScore;
    int highScore;
    if (!getHighScore(nameHighScore, highScore)) {;
        std::cout << "Error reading high score\n";
        return -1;
    }
    showHighScore(nameHighScore, highScore);
    std::cout << "\n";
    return 0;
}

bool getHighScore(std::string& fullName, int& highScore) {
    std::ifstream input;
    if (!openFile(SCORES_PATH, input))
        return false;

    std::string nameCurrentPlayer;
    int score;
    bool foundPlayer = false;
    highScore = std::numeric_limits<int>::min();

    while (std::getline(input, nameCurrentPlayer)) {
        // read score in next line for each name
        if (!(input >> score)) {
            // malformed score, clear the input stream in input file stream
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input in the same line of score
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (!foundPlayer || score > highScore) {
            foundPlayer = true;
            highScore = score;
            fullName = nameCurrentPlayer;
        }
    }
    input.close();

    if (!foundPlayer) {
        fullName.clear();
        highScore = -1;
    }
    return true;
}

bool openFile(const std::string& path, std::ifstream& inputStream) {
    inputStream.open(path);
    return (inputStream.is_open());
}

void showHighScore(const std::string& fullName, int highScore) {
    if (highScore == -1)
        std::cout << "No players";
    else
        std::cout <<fullName << " scored " << highScore;
}

