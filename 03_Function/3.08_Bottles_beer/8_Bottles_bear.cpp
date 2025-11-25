#include <iostream>
#include <string>
using namespace std;

string numberToWords(int number);
// Precondition: number is between 0 and 99
// Postcondition: returns the number in words

int main( ) {
    // Postcondition: Outputs all 99 stanzas
    //                of the "Ninety-Nine Bottles of Beer on the Wall" song.
    for (int idx = 99; idx > 0; --idx)
        cout << numberToWords(idx) << " bottle" << (idx > 1 ? "s" : "") << " of beer on the wall,\n"
             << numberToWords(idx) << " bottle" << (idx > 1 ? "s" : "") << " of beer,\n"
             << "Take one down, pass it around,\n"
             << numberToWords(idx - 1) << " bottle" << (idx -1 > 1 ? "s" : "") << " of beer on the wall.\n\n";

    return 0;
}

string numberToWords(int number) {
    const string belowTwenty[] = {"Zero", "One", "Two", "Three", "Four", "Five",
                                  "Six", "Seven", "Eight", "Nine", "Ten",
                                  "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
                                  "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const string tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty",
                           "Seventy", "Eighty", "Ninety"};

    if (number < 20)
        return belowTwenty[number];
    else {
        string result;
        int prefix, suffix;

        prefix = number / 10;
        suffix = number % 10;
        result = tens[prefix];
        result += (suffix != 0 ? "-" + belowTwenty[suffix] : "");

        return result;
    }
}
