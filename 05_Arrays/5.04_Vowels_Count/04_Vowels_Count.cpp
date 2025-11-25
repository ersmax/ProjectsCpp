#include <iostream>
#include <string>
#include <span>
#include <iomanip>

constexpr int SIZE = 50;
constexpr int N_VOWELS = 5;
constexpr char VOWELS[] = {'a', 'e', 'i', 'o', 'u'};

void fillUpText(char text[], int size, int& lettersUsed);
//   Precondition: size is the declared size of the array `text`
//   Postcondition: lettersUsed is the n of values stored in `text`.
// text[0] through text[lettersUsed - 1] have been filled with
// letters read from the keyboard.

void countVowels(const char text[], int size, int lettersUsed,
                int vowels[], int sizeVowels);
//   Precondition: size is the declared size of the array `text`
// Also, lettersUsed is <= size.
//   Postcondition: vowels[0] through vowels[sizeVowels - 1] contain
// the counts of each vowel found in `text`.

bool foundLetter(char letter, int& idxVowel);
//   Precondition: letter is a character to be checked if it is a vowel
//   Postcondition: If letter is a vowel, return true and set idxVowel
// to the index of the vowel in VOWELS array. Otherwise, return false.

void smartPrint(const int vowelsCount[], int size);
//   Precondition: size is the declared size of the array `vowelsCount`
//   Postcondition: Print the vowel counts in a formatted table.

int main( ) {
    char text[SIZE];
    int lettersUsed;
    int vowelsCount[N_VOWELS] = {};

    fillUpText(text, SIZE, lettersUsed);
    countVowels(text, SIZE, lettersUsed, vowelsCount, N_VOWELS);
    smartPrint(vowelsCount, N_VOWELS);

    std::cout << "\n";
    return 0;
}

void fillUpText(char text[], const int size, int& lettersUsed) {
    int idx = 0;
    std::string line;
    std::cout << "Enter letters up to " << size
              << " characters (or `exit` to go out)\n";
    while (idx < size && std::getline(std::cin, line)) {
        if (line == "exit") break;
        for (const char ch : line) {
            // if (std::isalpha(ch)) text[idx++] = ch; // consider only letters
            text[idx++] = ch;       // consider all characters
            if (idx >= size) break;
        }

        if (idx < size)
            std::cout << "Enter more letters (or `exit` to end)\n";
    }
    lettersUsed = idx;
}

void countVowels(const char text[], const int size, const int lettersUsed,
                int vowels[], int sizeVowels) {
    for (int idx = 0; idx < lettersUsed; ++idx) {
        int vowelLetter;
        char lowerCh = static_cast<char>(std::tolower(text[idx]));
        if (foundLetter(lowerCh, vowelLetter))  
            vowels[vowelLetter] += 1;
    }
}

bool foundLetter(const char letter, int& idxVowel) {
    for (size_t idx = 0; idx < std::size(VOWELS); ++idx)
        if (letter == VOWELS[idx]) {
            idxVowel = static_cast<int>(idx);
            return true;
        }
    return false;
}

void smartPrint(const int vowelsCount[], const int size) {
    std::cout << std::setw(8) << "Vowel"
              << std::setw(8) << "Count\n";

    for (int idx = 0; idx < size; ++idx)
        std::cout << std::setw(8) << VOWELS[idx]
                  << std::setw(8) << vowelsCount[idx]
                  << "\n";
}
