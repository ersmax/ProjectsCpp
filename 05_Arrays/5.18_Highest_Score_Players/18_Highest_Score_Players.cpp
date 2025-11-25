#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

constexpr int MAX = 1000;
constexpr int BEST = 3;
const std::string PATH = "./05_Arrays/5.18_Highest_Score_Players/Utilities/Scores.txt";

void copyData(std::string name[], int score[], int maxSize, int& nPlayers);
//   Precondition: name and score are arrays of size maxSize
//   Postcondition: fills name and score arrays with data from the file located at PATH.
// nPlayers is set to the number of players read from the file.

bool openFile(const std::string& pathFile, std::ifstream& inputStream);
//   Precondition: pathFile is a valid file path
//   Postcondition: opens the file located at pathFile for reading.

void closeFile(std::ifstream& inputStream);
//   Precondition: inputStream is an open file stream
//   Postcondition: closes the file stream.

void parseFile(std::ifstream& inputStream,
               std::string name[], int score[], int maxSize, int& nPlayers);
//   Precondition: inputStream is an open file stream
//   Postcondition: reads names and scores from inputStream and fills
// name and score arrays up to maxSize. nPlayers is set to the number of players read.

void showBest(const std::string name[], const int score[], int size, int topPlayers);
//   Precondition: name and score are arrays of size at least size
//   Postcondition: displays on console the topPlayers players with highest scores.

void orderData(std::string name[], int score[], int size);
//   Precondition: name and score are arrays of size at least size
//   Postcondition: sorts name and score arrays in descending order of scores.

void merge(std::string name[], int score[], int size,
           std::string bufferName[], int bufferScore[],
           int start, int mid, int end);
//   Precondition: name and score are arrays of size at least size. bufferName and bufferScore are
// temporary arrays of size at least size. They avoid memory churn (allocation/deallocation during recursion).
//   Postcondition: merges two sorted subarrays of name and score defined by
// [start..mid] and [mid+1..end] into a single sorted subarray in descending order of scores.

void mergeSort(std::string name[], int score[], int size,
               std::string bufferName[], int bufferScore[], int start, int end);
//   Precondition: name and score are arrays of size at least size. bufferName and bufferScore are
// temporary arrays of size at least size. They avoid memory churn (allocation/deallocation during recursion).
//   Postcondition: sorts name and score arrays in descending order of scores
// using the merge sort algorithm on the subarray defined by [start..end].

int main( ) {
    std::string name[MAX];
    int score[MAX];
    int nPlayers = 0;
    copyData(name, score, MAX, nPlayers);
    orderData(name, score, nPlayers);
    showBest(name, score, nPlayers, BEST);

    std::cout << "\n";
    return 0;
}

void copyData(std::string name[], int score[], const int maxSize, int& nPlayers) {
    std::ifstream inputStream;
    if (!openFile(PATH, inputStream)) {
        std::cerr << "Cannot open file\n";
        return;
    }
    parseFile(inputStream, name, score, maxSize, nPlayers);
    closeFile(inputStream);
}

bool openFile(const std::string& pathFile, std::ifstream& inputStream) {
    inputStream.open(pathFile);
    if (!inputStream)
        return false;
    return true;
}

void closeFile(std::ifstream& inputStream) {
    inputStream.close();
}

void parseFile(std::ifstream& inputStream,
               std::string name[], int score[], const int maxSize, int& nPlayers) {
    nPlayers = 0;
    std::string nameLine, scoreLine;
    while (nPlayers < maxSize && std::getline(inputStream, nameLine)) {
        if (nameLine.empty())   continue;
        if (!std::getline(inputStream, scoreLine))  break;  // expect score in next line

        std::istringstream iss(scoreLine);
        int points;
        while (iss >> points) {
            name[nPlayers] = nameLine;
            score[nPlayers++] = points;
        }
    }
}

void orderData(std::string name[], int score[], const int size) {
    if (size <= 1) return;
    std::string tempName[MAX];
    int tempScore[MAX];
    mergeSort(name, score, size, tempName, tempScore, 0, size - 1);
}

void mergeSort(std::string name[], int score[], const int size,
               std::string bufferName[], int bufferScore[], int start, int end) {
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSort(name, score, size, bufferName, bufferScore, start, mid);
    mergeSort(name, score, size, bufferName, bufferScore, mid + 1, end);
    merge(name, score, size, bufferName, bufferScore, start, mid, end);
}

void merge(std::string name[], int score[], const int size,
           std::string bufferName[], int bufferScore[],
           const int start, const int mid, const int end) {

    int p1 = start, p2 = mid + 1, idxScore = start;
    while ((p1 <= mid) && (p2 <= end)) {
        if (score[p1] >= score[p2]) {
            bufferScore[idxScore] = score[p1];
            bufferName[idxScore] = name[p1];
            ++p1;
        } else {
            bufferScore[idxScore] = score[p2];
            bufferName[idxScore] = name[p2];
            ++p2;
        }
        ++idxScore;
    }
    // Merge wrap-up
    while (p1 <= mid) {
        bufferScore[idxScore] = score[p1];
        bufferName[idxScore] = name[p1];
        ++p1;
        ++idxScore;
    }
    while (p2 <= end) {
        bufferScore[idxScore] = score[p2];
        bufferName[idxScore] = name[p2];
        ++p2;
        ++idxScore;
    }
    for (int idx = start; idx <= end; ++idx) {
        score[idx] = bufferScore[idx];
        name[idx] = bufferName[idx];
    }
}

void showBest(const std::string name[], const int score[],
              const int size, const int topPlayers) {
    for (int idx = 0; idx < size; ++idx) {
        const bool highlight = (idx < topPlayers);
        if (highlight) std::cout << "*** ";
        else           std::cout << "    ";
        std::cout << "Player #" << std::setw(2) << idx + 1
                  << ": " << std::setw(12) << name[idx]
                  << ", score: " << std::setw(6) << score[idx];
        if (highlight) std::cout << " ***";
        std::cout << "\n";
    }
}
