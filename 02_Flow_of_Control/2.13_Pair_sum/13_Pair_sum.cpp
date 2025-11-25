#include <iostream>
#include <fstream>
using namespace std;

int main ( ) {
    constexpr int SIZE = 10;
    int numbers[SIZE] = {0};
    int number;
    fstream inputStream;

    inputStream.open("02_Flow_of_Control/2.13_Pair_sum/Utilities/2_13_Pair_sum.txt");
    if (!inputStream.is_open()) {
        cout << "No file available.\n";
        return -1;
    }

    // int idx = 0;
    // while (inputStream >> number) {
    //     numbers[idx] = number;
    //     idx++;
    // }

    for (int idx = 0; idx < SIZE; idx++)
        inputStream >> numbers[idx];

    inputStream.close();

    cout << "Input a number:";
    cin >> number;

    int countSolution = 0;
    for (int idx1 = 0; idx1 < SIZE - 1; idx1++) {
        for (int idx2 = 1; idx2 < SIZE; idx2++) {
            if (numbers[idx1] + numbers[idx2] == number) {
                countSolution++;
                cout << "Solution number "
                     << countSolution
                     << ": "
                     << numbers[idx1]
                     << " + "
                     << numbers[idx2] << endl;
            }
        }
    }
    if (countSolution == 0)
        cout << "No pair found.\n";

    return 0;
}