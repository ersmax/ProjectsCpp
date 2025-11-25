#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main ( ) {
    int digitCount[9] = {0};
    int totalCount = 0;
    fstream inputStream;

    inputStream.open("02_Flow_of_Control/2.12_Benfords_Law/Utilities/2_12_Benfords_Law.txt");
    if (!inputStream.is_open()) {
        cerr << "No file available.\n";
        return -1;
    }

    string strNum;
    while (inputStream >> strNum) {
        if (!strNum.empty() && isdigit(strNum[0])) {
            // ASCII code 48 (0), ASCII code 49 (1), ...
            int leadingDigit  = strNum[0] - '0';
            if (leadingDigit >= 1 && leadingDigit  <= 9) {
                digitCount[leadingDigit-1] += 1;
                totalCount++;
            }
        }
    }
    inputStream.close();

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);

    cout << "Leading Digit Distribution:\n";
    for (int idx = 0; idx < 9; ++idx) {
        double percentage = static_cast<double>(digitCount[idx]) / totalCount * 100.0;
        cout << (idx+1)
             << ": "
             << percentage
             << "%\n";
    }

    return 0;
}