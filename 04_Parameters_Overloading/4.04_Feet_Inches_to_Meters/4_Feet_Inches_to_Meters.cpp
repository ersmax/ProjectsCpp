// define NDEBUG        // uncomment this line todisable assertions
#include <iostream>     // for cin, cout, endl
#include <limits>       // for numeric_limits, streamsize
#include <cassert>      // for assert
#include <cmath>        // for round
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::ios;
using std::round;

constexpr double FOOT = 0.3048;
constexpr double METER = 100.0;

void getLength(double& feet, double& inches);
// Precondition: feet and inches are declared
// Postcondition: defines the values of feet and inches

void lengthConversion(double feet, double inches, int& meters, int& cm);
// Precondition: feet is in 5-7 range, inches is in 0-11 range
// Postcondition: converts feet and inches to meters and centimeters

void showLength(int feetMeter, int inchesCentimeter);
// Precondition: feetMeter is in 1-2 range, inchesCentimeter is in 0-99 range
// Postcondition: displays the length in meters and centimeters

int main( ) {
    // Postcondition: Prompts user for length in feet and inches,
    //                converts it to meters and centimeters,
    //                and displays it.
    double lengthFt, lengthIn;
    int meters, centimeters;
    char answer = 'n';

    do {

        getLength(lengthFt, lengthIn);

        assert(lengthFt >= 5 && lengthFt < 8 &&
               lengthIn >= 0 && lengthIn < 12);
        lengthConversion(lengthFt, lengthIn, meters, centimeters);

        assert(meters >= 1 && meters < 3 &&
               centimeters >= 0 && centimeters < 100);
        showLength(meters, centimeters);

        cout << "Repeat (y/Y)?";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    } while (answer == 'y' || answer == 'Y');

    cout << endl;
    return 0;
}

void getLength(double& feet, double& inches) {

    while (true) {
        cout << "Enter the height of an adult (feet: 5-7; inches: 0-11)\n"
             << "format: feet inches (e.g. 5 10)...:";
        if (!(cin >> feet >> inches)) {
            cout << "Wrong input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        // discard extra token on the same line
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if (feet < 5 || feet > 7 ||
            inches < 0 || inches > 11)
            cout << "Invalid range\n";
        else
            break;
    }
}

void lengthConversion(double feet, double inches, int& meters, int& cm) {
    double cent;
    double totalMeters = feet * FOOT + (inches * (FOOT / 12.0) );

    meters = static_cast<int>(totalMeters);
    cent = (totalMeters - meters) * METER;
    cm = static_cast<int>(round(cent + 1e-9));  // prevent rounding issues

    if (cm >= 100) {
        cm -= 100;
        ++meters;
    }
}

void showLength(int feetMeter, int inchesCentimeter) {
    cout << "This is equivalent to " << feetMeter << " meters, "
         << inchesCentimeter << " cm.\n";
}

