#include <iostream>
#include <random>
#include <string>
#include <limits>
#include <algorithm>

constexpr int NUMBERS = 3;
constexpr int DIGITS = 10;
constexpr int PIN = 5;
constexpr int GIVEN_PIN = 12345;

void createSequence(int sequence[], int size);
void shuffleSequence(int sequence[], int size);
void enterPin(int pin[], int nDigits);
void showSystem(const int sequence[], int size);
bool checkPin(const int pin[], int nDigitsPin, const int sequence[], int nDigits);

int main( ) {
    int sequence[DIGITS];
    int pin[PIN];

    createSequence(sequence, DIGITS);
    shuffleSequence(sequence, DIGITS);
    showSystem(sequence, DIGITS);
    enterPin(pin, PIN);
    if (checkPin(pin, PIN, sequence, DIGITS))
        std::cout << "Correct PIN\n";
    else
        std::cout << "Wrong PIN\n";

    std::cout << "\n";
    return 0;
}

void createSequence(int sequence[], const int size) {
    for (int idx = 0; idx < size; ++idx)
        sequence[idx] = ((idx + (NUMBERS - 1)) % NUMBERS) + 1;
}

void shuffleSequence(int sequence[], const int size) {
    static std::random_device rd;
    static std::mt19937 engine(rd());
    // Fisher-Yates randomization
    for (int idx = size - 1; idx > 0; --idx) {
        std::uniform_int_distribution<int>dist(0, idx);
        const int temp = dist(engine);
        std::swap(sequence[idx], sequence[temp]);
    }
}

void enterPin(int pin[], const int nDigits) {
    std::string number;
    std::cout << "Enter the PIN sequence:\n";
    while (true) {
        if (!(std::cin >> number)) {
            std::cout << "Wrong input. Retry\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // check bounds
        bool isValid = true;
        for (const char c : number)
            if (c < '1' || c > ('0' + NUMBERS)) {
                isValid = false;
                break;
            }
        // check length
        if (number.size() != nDigits) {
            std::cout << "PIN must be " << nDigits << " digits\n";
            continue;
        }
        if (!isValid) {
            std::cout << "Wrong sequence\n";
            continue;
        }
        // add to array
        for (int idx = 0; idx < nDigits; ++idx)
            pin[idx] = number[idx] - '0';
        break;
    }
}

void showSystem(const int sequence[], int size) {
    std::cout << "PIN: ";
    for (int idx = 0; idx < size; ++idx)
        std::cout << idx << " ";
    std::cout << "\nNUM: ";
    for (int idx = 0; idx < size; ++idx)
        std::cout << sequence[idx] << " ";
    std::cout << "\n";
}

bool checkPin(const int pin[], const int nDigitsPin,
              const int sequence[], const int nDigits) {

    int givenPin[PIN];
    int temp = GIVEN_PIN;
    for (int idx = PIN - 1; idx >= 0; --idx) {
        givenPin[idx] = temp % DIGITS;
        temp /= DIGITS;
    }
    for (int digit = 0; digit < nDigitsPin; ++digit) {
        int actualPinDigit = givenPin[digit];
        if (sequence[actualPinDigit] != pin[digit]) return false;
    }
    return true;
}
