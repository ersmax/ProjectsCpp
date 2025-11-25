#include <iostream>     // for std::cin, std::cout
#include <span>         // for std::span
#include <algorithm>    // for std::reverse
#include <string>       // for std::string
#include <cctype>       // for std::isdigit

constexpr int SIZE = 20;

void fillUpNumbers(int number[], int size, int& usedSize);
//   Precondition: size is the declared size of the array `number`
//   Postcondition: usedSize is the n of values stored in `number`.
// number[0] through number[usedSize - 1] have been filled with
// digits of a positive integer read from the keyboard.

void sumNumbers(const int number1[], int sizeNumber1,
                const int number2[], int sizeNumber2,
                int result[], int& sizeResult, int size);
//  Precondition: size is the declared size of the array `result`
//  Postcondition: The sum of the two integers stored in number1 and number2
//  is stored in `result`. sizeResult is the number of digits in the result.
//  If the sum exceeds the maximum number of digits (size), an overflow message
//  is displayed and result is set to all zeros.

int main( ) {
    int result[SIZE] = {};
    int number1[SIZE], number2[SIZE];
    int sizeNumber1 = 0, sizeNumber2 = 0, sizeResult = 0;
    fillUpNumbers(number1, SIZE, sizeNumber1);
    fillUpNumbers(number2, SIZE, sizeNumber2);
    sumNumbers(number1, sizeNumber1, number2, sizeNumber2, result, sizeResult, SIZE);

    std::reverse(result, result + sizeResult);
    for (const int digit : std::span(result, sizeResult))
        std::cout << digit;

    std::cout << "\n";
    return 0;
}

void fillUpNumbers(int number[], int size, int& usedSize) {
    std::string line;

    while (true) {
        std::cout << "Enter the number up to " << size
                  << "digits, or `exit` to terminate\n";
        std::getline(std::cin, line);
        if (line == "exit") return;

        // check correct number of digits
        if (line.size() > static_cast<size_t>(size)) {
            std::cout << "Too many digits. Retry\n";
            continue;
        }

        // check every letter is a digit
        bool invalidDigit = false;
        for (const char ch : line)
            if (!std::isdigit(static_cast<unsigned char>(ch))) {
                std::cout << "Not a valid number. Retry\n";
                invalidDigit = true;
                break;
            }
        if (invalidDigit) continue;

        break;
    }

    usedSize = static_cast<int>(line.size());

    // store least significant digit first
    for (int idx = 0; idx < usedSize; ++idx)
        number[idx] = line[usedSize - idx - 1] - '0';

    for (int idx = usedSize; idx < size; ++idx)
        number[idx] = 0;
}

void sumNumbers(const int number1[], const int sizeNumber1,
                const int number2[], const int sizeNumber2,
                int result[], int& sizeResult, const int size) {

    // check whether one number is empty
    if (sizeNumber1 == 0) {
        for (int idx = 0; idx < sizeNumber2; ++idx)
            result[idx] = number2[idx];
        for (int idx = sizeNumber2; idx < size; ++idx)
            result[idx] = 0;

        sizeResult = sizeNumber2;
        return;
    }
    if (sizeNumber2 == 0) {
        for (int idx = 0; idx < sizeNumber1; ++idx)
            result[idx] = number1[idx];
        for (int idx = sizeNumber1; idx < size; ++idx)
            result[idx] = 0;

        sizeResult = sizeNumber1;
        return;
    }

    // sum the two indexed variables for the same position
    int p1 = 0, p2 = 0, p3 = 0;
    int carry = 0;
    while ((p1 < sizeNumber1 || p2 < sizeNumber2) && (p3 < size)) {
        int a = (p1 < sizeNumber1) ? number1[p1++] : 0;
        int b = (p2 < sizeNumber2) ? number2[p2++] : 0;
        int sum = a + b + carry;

        result[p3++] = sum % 10;
        carry = sum / 10;
    }

    //
    while ((p1 < sizeNumber1) && (p3 <size)) {
        int sum = number1[p1++];
        sum += carry;
        result[p3++] = (sum > 9) ? sum % 10 : sum;
        carry = sum / 10;
    }
    while ((p2 < sizeNumber2) && (p3 <size)) {
        int sum = number2[p2++];
        sum += carry;
        result[p3++] = (sum > 9) ? sum % 10 : sum;
        carry = sum / 10;
    }

    // no room for carry means overflow
    if (carry && p3 >= size) {
        for (int idx = 0; idx < size; ++idx)    result[idx] = 0;
        std::cout << "integer overflow.\n";
        return;
    }

    if (carry)
        result[p3++] = carry;

    sizeResult = p3;
}


