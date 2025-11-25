#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int idealBMI(const string& firstName, const string& lastName, int feet, int inch) {
    if (feet < 5 || feet >= 8) {
        cerr << firstName << " " << lastName << ": "
             << "Error. Height should be "
                "at least 5 or less than 8 inches.\n";
        return -1; // Return an error value
    }
    return 110 * 5 + (feet - 5) * 5 + (inch * 5);
}

int main ( ) {
    string firstName, lastName;
    int feet, inches;
    fstream inputStream;

    inputStream.open("02_Flow_of_Control/2.11_Ideal_BMI/Utilities/2_11_Ideal_BMI.txt");

    if (!inputStream.is_open()) {
        cout << "Failed to open file." << endl;
        return -1;
    }

    while (inputStream >> firstName
          >> lastName >> feet >> inches) {

        int BMI = idealBMI(firstName, lastName, feet, inches);

        if (BMI == -1)
            continue;

        cout << firstName  << " " << lastName
             << ", your ideal BMI is: "
             << BMI << endl;
    }

    inputStream.close();
    return 0;
}