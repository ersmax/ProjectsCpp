#include <iostream>
#include <limits>       // for std::numeric_limits
#include <span>         // for std::span
#include <string>       // for std::string
#include <utility>      // for std::swap
#include <cctype>       // for std::isalpha

constexpr int SIZE = 10;

void fillArray(char letters[], std::size_t size, int& numberUsed);
//   Precondition: size is the declared size of the array `letters`
//   Postcondition: numberUsed is the n of values stored in `letters`.
// letters[0] through letters[numberUsed - 1] have been filled with
// letters read from the keyboard.

void removeDuplicates(char letters[], std::size_t size, int& numberUsed);
//   Precondition: numberUsed is <= declared size of `letters`
// Also, letters[0] through letters[numberUsed - 1] have values.
//   Postcondition: all duplicate letters have been removed from
// the array `letters`. numberUsed is updated to reflect the new
// number of unique letters in the array.

int main( ) {
    int numberUsed = 0;
    char letters[SIZE];
    fillArray(letters, std::size(letters), numberUsed);
    removeDuplicates(letters, std::size(letters), numberUsed);

    for (const char element : std::span(letters, numberUsed))
        std::cout << element << " ";

    std::cout << "\n";
    return 0;
}

void fillArray(char letters[], const std::size_t size, int& numberUsed) {
    std::size_t idx = 0;
    std::string next;
    std::cout << "Enter up to " << size << " letters (-1 to end).\n";

    while (idx < size) {
        if (!(std::cin >> next)) {
            std::cout << "Not a letter\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (next == "-1")
            break;
        if (next.size() != 1 || !std::isalpha(static_cast<unsigned char>(next[0])) ) {
            std::cout << "Please insert a letter or -1 to exit\n";
            continue;
        }

        letters[idx++] = next[0];
    }
    numberUsed = idx;
}

void removeDuplicates(char letters[], const std::size_t size, int& numberUsed) {
    if (numberUsed == 0) return;

    for (int p1 = 0; p1 < numberUsed; ++p1) {
        int p2 = p1 + 1;
        int p3 = p1 + 1;

        while (p3 < numberUsed) {
            if (letters[p1] != letters[p3]) {
                if (p1 != p2)
                    std::swap(letters[p2], letters[p3]);
                ++p2;
                ++p3;
            } else
                ++p3;
        }
        numberUsed = p2;  // trunk the `subpart` of repeated chars e.g. a b c `a` `a` `a`
    }
}
