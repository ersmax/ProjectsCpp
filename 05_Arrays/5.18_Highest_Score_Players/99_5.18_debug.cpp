// This program is similar to 18_Highest_Score, with additional debug prints

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

constexpr int MAX = 1000;
constexpr int BEST = 3;
const std::string PATH = "./05_Arrays/5.18_Highest_Score_Players/Utilities/Ranking.txt";

void copyData(std::string name[], int score[], int maxSize, int& nPlayers);
bool openFile(const std::string& pathFile, std::ifstream& inputStream);
void closeFile(std::ifstream& inputStream);
void parseFile(std::ifstream& inputStream,
               std::string name[], int score[], int maxSize, int& nPlayers);
void showBest(const std::string name[], const int score[], int size, int topPlayers);
void orderData(std::string name[], int score[], int size);
void mergeSort(std::string name[], int score[], int size,
               std::string bufferName[], int bufferScore[],
               int start, int end, int depth);
void merge(std::string name[], int score[], int size,
           std::string bufferName[], int bufferScore[],
           int start, int end, int depth);

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
    if (size <= 1)  return;
    std::string bufferName[MAX];
    int bufferScore[MAX];
    mergeSort(name, score, size, bufferName, bufferScore, 0, size - 1, 0);
}

void mergeSort(std::string name[], int score[], const int size,
               std::string bufferName[], int bufferScore[],
               const int start, const int end, const int depth) {

    std::cout << depth << ": ";
    for (int idx = start; idx <= end; ++idx)
        std::cout << score[idx] << " ";
    std::cout << "\n";
    if (start >= end) return;  // edge case: no elements, start > end
    const int mid = start + (end - start) / 2;
    mergeSort(name, score, size, bufferName, bufferScore, start, mid, depth + 1);
    mergeSort(name, score, size, bufferName, bufferScore, mid + 1, end, depth + 1);
    merge(name, score, size, bufferName, bufferScore, start, end, depth);
}

void merge(std::string name[], int score[], const int size,
           std::string bufferName[], int bufferScore[],
           const int start, const int end, int depth) {
    const int mid = start + (end - start) / 2;
    int p1 = start;
    int p2 =  mid + 1;
    ++depth;
    int idxScore = start;
    std::cout << "Depth: " << depth  <<  "\n";
    while ((p1 <= mid) && (p2 <= end)) {
        if (score[p1] >= score[p2]) {
            bufferScore[idxScore] = score[p1];
            bufferName[idxScore] = name[p1];
            ++p1;
        }
        else {
            bufferScore[idxScore] = score[p2];
            bufferName[idxScore] = name[p2];
            ++p2;
        }
        ++idxScore;
    }
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
    std::cout << "Merging: ";
    for (int idx = start; idx <= end; ++idx)
        std::cout << score[idx] << " ";
    std::cout << "\n";
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
