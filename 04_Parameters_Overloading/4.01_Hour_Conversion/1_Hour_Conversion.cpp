// #define NDEBUG           // uncomment this line todisable assertions
#include <iostream>         // std::cin, std::cout, std::endl
#include <limits>           // std::numeric_limits, std::streamsize
#include <cassert>          // std::assert
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;

void getInput(int& hour, int& minute);
// Precondition: hour and minute are declared
// Postcondition: defines the values of hour and minute

void timeConversion(int& hour, char& amPm);
// Precondition: hour is in 0-23 range, amPm is declared
// Postcondition: converts hour to 12-hour format
//                and sets amPm to 'A' or 'P'

void showTime(int hour, int minute, char amPm);
// Precondition: hour is in 1-12 range, minute is in 0-59 range,
//               amPm is 'A' or 'P'
// Postcondition: displays the time in hh:mm A.M./P.M. format


int main( ) {
    // Postcondition: Prompts user for time in 24-hour format,
    //                converts it to 12-hour format, and displays it.
    char answer;
    int hour, minute;
    char amPm = '\0';   // NUL sentinel

    do {
        getInput(hour, minute);

        assert(0 <= hour && hour < 24 &&
               0 <= minute && minute < 60);
        timeConversion(hour, amPm);

        assert(1 <= hour && hour <= 12 &&
               0 <= minute && minute < 60 &&
               (amPm == 'A' || amPm == 'P'));
        showTime(hour, minute, amPm);

        cout << "Repeat? (y/Y):";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    } while (answer == 'y' || answer == 'Y');

    cout << endl;
    return 0;
}

void getInput(int& hour, int& minute) {
    while (true) {
        cout << "Enter the hour (0-23) and minute (0-59):";
        if (!(cin >> hour >> minute)) {
            cout << "Invalid input. Enter two whole values.\n";
            cin.clear();  // clear error flags, remove bad input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // discard extra tokens on same line
        // when reading time (avoid 12 30 exit_program)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (hour >= 0 && hour <= 23 &&
            minute >= 0 && minute <= 59)
            break;
        cout << "Invalid range.\n";
    }
}

void timeConversion(int &hour, char &amPm) {
    if (hour == 0) {            // midnight
        hour = 12;
        amPm = 'A';
    } else if (hour == 12) {    // noon
        amPm = 'P';
    } else if (hour > 12) {     // afternoon
        hour -= 12;
        amPm = 'P';
    } else                      // morning
        amPm = 'A';
}


void showTime(int hour, int minute, char amPm) {
    cout << "Time: " << (hour < 10 ? "0" : "") << hour
         << ":" << (minute < 10 ? "0" : "") << minute;
    if (amPm != '\0')
        cout << " " << amPm << ".M.";
    cout << '\n';
}
