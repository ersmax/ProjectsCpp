#include <iostream>     // for std::cout, std::cerr
#include <fstream>      // for std::fstream
#include <sstream>      // for std::istringstream
#include <string>       // for std::string
#include <cmath>        // for std::abs
#include <iomanip>      // for std::setprecision, std::fixed, std::showpoint, std::setw

constexpr int DIGITS = 10;
const std::string PATH = "./05_Arrays/5.17_Benford_Law_Arrays/Utilities/benford.txt";

void readData(const std::string& path, int& totNumbers, int count[], int size);
//   Precondition: path is a valid file path
//   Postcondition: reads the file and fills count array with the frequency
// of leading digits (0 through size - 1). totNumbers is set to the total
// of numbers read.

bool openFile(const std::string& path, std::fstream& inputStream);
//   Precondition: path is a valid file path
//   Postcondition: opens the file located at path for reading.

void closeFile(const std::string& path, std::fstream& inputStream);
//   Precondition: path is a valid file path
//   Postcondition: closes the file located at path.

void checkNumber(int number, int& totNumbers, int count[], int size);
//   Precondition: number is an integer
//   Postcondition: updates totNumbers and count array according to the leading digit
// of number.

void checkBenfordLaw(int totalNumbers, const int count[], int size);
//   Precondition: totalNumbers is the total of numbers read,
//   Postcondition: displays on console the percentage of each leading digit
// (0 through size - 1) found in the data.

int main( ) {
    int count[DIGITS] = {0};
    int totalNumbers = 0;
    readData(PATH, totalNumbers, count, DIGITS);
    checkBenfordLaw(totalNumbers, count, DIGITS);
    std::cout << "\n";
    return 0;
}

void readData(const std::string& path, int& totNumbers,
              int count[], const int size) {
    std::fstream inputStream;
    if (!openFile(path, inputStream)) {
        std::cerr << "Cannot open file\n";
        return;
    }
    std::string line;

    while(std::getline(inputStream, line)) {
        if (line.empty())   continue;
        std::istringstream iss(line);

        int number;
        while (iss >> number)
            checkNumber(number, totNumbers, count, size);
    }
    closeFile(path, inputStream);
}

void checkNumber(int number, int& totNumbers, int count[], const int size) {
    // widen to avoid overflow on negation
    long long n = number;
    n = std::abs(number);
    ++totNumbers;
    const std::string s = std::to_string(n);
    int leadingDigit = s[0] - '0';
    if (leadingDigit >= 0 && leadingDigit < size)
        ++count[leadingDigit];
    // alternatively (no memory allocation):
    // while (number >= 10) number /= 10;
    // if (number >= 0 && number < size)
    //    ++count[number];
}

bool openFile(const std::string& path, std::fstream& inputStream) {
    inputStream.open(path);
    if (!inputStream)
        return false;
    return true;
}

void closeFile(const std::string& path, std::fstream& inputStream) {
    inputStream.close();
}

void checkBenfordLaw(const int totalNumbers, const int count[], const int size) {
    if (totalNumbers == 0) {
        std::cout << "No numbers read.\n";
        return;
    }
    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    for (int idx = 0; idx < size; ++idx) {
        const double ratio = static_cast<double>(count[idx]) / totalNumbers;
        const double percent = ratio * 100.0;
        std::cout << "#" << idx << ": " << std::setw(5) << percent << "%\n";
    }
}