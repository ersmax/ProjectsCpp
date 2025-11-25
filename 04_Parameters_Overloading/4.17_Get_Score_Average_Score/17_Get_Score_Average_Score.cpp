// define NDEBUG
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <limits>
#include <cassert>

const std::string FILE_PATH = "./04_Parameters_Overloading/4.16_Highest_Score/Utilities/Scores.txt";

bool populateMap(std::string& nameHighScore, int& highScore, int& totalScore,
                 std::unordered_map<std::string, int>& scores);
// Postcondition: populates the map with player names and scores from the file
//                also sets nameHighScore and highScore to the player with the highest score
//                Additionally, sets totalScore to the sum of all scores

bool openFile(std::ifstream& inputStream, const std::string& path);
// Precondition: path is the file path and inputStream is declared
// Postcondition: opens the file located at path and associates it with inputStream

void showHighScore(const std::string& nameHighScore, int highScore);
// Postcondition: displays the name of the player with the highest score and the score

int getPlayerScore(const std::unordered_map<std::string, int>& scores,
                    const std::string& namePlayer);
// Precondition: scores is a map with player names and scores
// Postcondition: returns the score of the player with name namePlayer
//               if the player is not found, returns -1

void comparePlayer(const std::unordered_map<std::string, int>& scores,
                   int totalScore, const std::string& name, int score);
// Precondition: scores is a map with player names and scores
//               totalScore is the sum of all scores
//               name is the name of the player to compare
//               score is the score of the player to compare
// Postcondition: compares the player's score to the average score and displays the result

int main( ) {
    int totalScore = 0, highScore;
    std::string nameHighScore, name;
    std::unordered_map<std::string, int> scores;
    if (!populateMap(nameHighScore, highScore, totalScore, scores)) {
        std::cerr << "Cannot open file.\n";
        return -1;
    }
    showHighScore(nameHighScore, highScore);

    std::cout << "Enter a player's name:";
    std::getline(std::cin >> std::ws, name);

    int score = getPlayerScore(scores, name);
    comparePlayer(scores, totalScore, name, score);

    std::cout << "\n";
    return 0;
}

bool populateMap(std::string& nameHighScore, int& highScore, int& totalScore,
                std::unordered_map<std::string, int>& scores) {

    std::ifstream inputStream;
    if (!openFile(inputStream, FILE_PATH))
        return false;

    std::string namePlayer;
    int scorePlayer;
    bool foundPlayer = false;
    highScore = std::numeric_limits<int>::min();

    while (std::getline(inputStream, namePlayer)) {
        if (namePlayer.empty())
            continue;
        if (!(inputStream >> scorePlayer)) {
            // malformed input
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // in case of successful read, ignore characters after score
        inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (!foundPlayer || scorePlayer > highScore) {
            foundPlayer = true;
            highScore = scorePlayer;
            nameHighScore = namePlayer;
        }

        // add score to total
        totalScore += scorePlayer;

        // update the Statistics
        scores[namePlayer] = scorePlayer;
    }

    inputStream.close();

    if (!foundPlayer) {
        nameHighScore.clear();
        highScore = -1;
    }

    return true;
}


bool openFile(std::ifstream& inputStream, const std::string& path) {
    inputStream.open(path);
    return inputStream.is_open();
}

void showHighScore(const std::string& nameHighScore, int highScore) {
    if (highScore == -1)
        std::cout << "No players\n";
    else
        std::cout << nameHighScore << " scored " << highScore << "\n";
}

int getPlayerScore(const std::unordered_map<std::string, int>& scores,
                    const std::string& namePlayer) {

    auto iterator = scores.find(namePlayer);
    if (iterator == scores.end())
        return -1;

    return iterator->second;
}

void comparePlayer(const std::unordered_map<std::string, int>& scores,
                   const int totalScore, const std::string& name,
                   const int score) {

    if (scores.find(name) == scores.end()) {
        std::cout << "Comparison not possible\n";
        return;
    }
    double average = static_cast<double>(totalScore) / scores.size();

    double totalCheck = 0;
    for (const auto& player : scores)
        totalCheck += player.second;

    double averageCheck = static_cast<double>(totalCheck) / scores.size();
    assert(averageCheck == average);

    std::cout << name << " scored ";
    if (score > average)        std::cout << " above ";
    else if (score == average)  std::cout << " as equal as ";
    else                        std::cout << " below ";
    std::cout << " the average (" << average << ")\n";
}
