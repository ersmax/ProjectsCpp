// #define NDEBUG          // for assert
#include <iostream>     // for std::cout, std::cin
#include <limits>       // for std::numeric_limits
#include <cmath>        // for std::sqrt, std::pow
#include <span>         // for std::span
#include <string>       // for std::string, std::stod
#include <cstddef>      // for std::size_t
#include <cassert>      // for assert

constexpr int SIZE = 10;

void fillArray(double numbers[], std::size_t size, int& numberUsed);
//   Precondition: size is the declared size of the array `numbers`
//   Postcondition: numberUsed is the n of values stored in `numbers`.
// scores[0] through scores[numberUsed - 1] have been filled with
// double values.

double computeStandardDev(const double numbers[], std::size_t size, int numberUsed);
//   Precondition: numberUsed is <= declared size of `numbers`
// Also, numbers[0] through numbers[numberUsed - 1] have values.
//   Postcondition: return the standard deviation of the first `numberUsed` elements in `numbers`.

int main( ) {
    double numbers[SIZE];
    int numberUsed = 0;

    fillArray(numbers, std::size(numbers), numberUsed);

    assert(numberUsed <= static_cast<int>(std::size(numbers)));
    double standardDev = computeStandardDev(numbers, std::size(numbers), numberUsed);

    for (const double& element : std::span(numbers, numberUsed))
        std::cout  << element << " ";

    std::cout << "\n";
    std::cout << "Their standard deviation is " << standardDev;

    std::cout << "\n";
    return 0;
}

void fillArray(double numbers[], const std::size_t size, int& numberUsed) {
    std::size_t idx = 0;
    std::string next;
    std::cout << "Enter up to " << size << " numbers (or `exit` to end).\n";

    while (idx < size) {
        if (!(std::cin >> next)) {
            std::cout << "Not a number\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (next == "exit")
            break;

        try {
            size_t idxFirstCharacter;       // write index of first invalid character (not a number)
            double number = std::stod(next, &idxFirstCharacter);
            if (idxFirstCharacter != next.size()) {
                std::cout << "Not a valid number at idx " << idx
                          << ". Retry (or `exit` to end).\n";
                continue;
            }
            numbers[idx++] = number;

        } catch (const std::exception&) {
            std::cout << "Invalid number: " << next << "\n";
        }

    }
    numberUsed = idx;
}

double computeStandardDev(const double numbers[], const std::size_t size, const int numberUsed) {
    if (numberUsed <= 0) return 0.0;

    double sum = 0.0;
    for (int idx = 0; idx < numberUsed; ++idx)
        sum += numbers[idx];

    double average = sum / numberUsed;

    double sumSquared = 0;
    for (int idx = 0; idx < numberUsed; ++idx) {
        double deviation = numbers[idx] - average;
        sumSquared += std::pow(deviation, 2);
    }

    return (std::sqrt(sumSquared/numberUsed));
}
