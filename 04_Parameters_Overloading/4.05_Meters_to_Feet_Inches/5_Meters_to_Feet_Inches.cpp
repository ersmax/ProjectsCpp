// #define NDEBUG       // uncomment this line todisable assertions
#include <iostream>     // for cin, cout, endl
#include <limits>       // for numeric_limits, streamsize
#include <cassert>      // for assert
#include <cmath>        // for floor
using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;
using std::floor;


constexpr double METERS_FEET = 0.3048;
constexpr int INCHES_FEET = 12;
constexpr double METERS_INCH = METERS_FEET / INCHES_FEET;
constexpr double CM_METER = 100.0;

void getData(int& meters, int& centimeters);
// Precondition: meters and centimeters are declared
// Postcondition: defines the values of meters and centimeters

void lengthConversion(int meters, int centimeters,
                      int& feet, int& inches);
// Precondition: meters is in 0-2 range, centimeters is in 0-99 range
// Postcondition: converts meters and centimeters to feet and inches

void showData(int feet, int inches);
// Precondition: feet is in 0-7 range, inches is in 0-11 range
// Postcondition: displays the length in feet and inches

int main( ) {
    // Postcondition: Prompts user for length in meters and centimeters,
    //                converts it to feet and inches,
    int meters, centimeters, feet, inches;
    char answer;

    do {
        getData(meters, centimeters);

        assert(meters >= 0 && centimeters >= 0);
        lengthConversion(meters, centimeters, feet, inches);

        assert(feet >= 0 && feet < 8 &&
               inches >= 0 && inches < 12);
        showData(feet, inches);

        // ignore following characters
        cout << "Repeat? (y/Y)";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (answer == 'y' || answer == 'Y');

    cout << '\n';
    return 0;
}

void getData(int& meters, int& centimeters) {
    while (true) {
        cout << "Enter height in meters and cm (separated by a space)\n"
                "(e.g. 1 80):";
        if (!(cin >> meters >> centimeters)) {
            cout << "Enter numbers.\n";
            cin.clear();  // clear error flags, remove input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // discard extra tokens (e.g. 1 80 exit)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (meters >= 0 && meters <= 2  &&
            centimeters >= 0 && centimeters <= 99)
            break;

        cout << "Invalid numbers range.";
    }
}

void lengthConversion(int meters, int centimeters,
                      int& feet, int& inches) {

    // note: height truncation to avoid gifting height
    double totMeters = meters + centimeters / CM_METER ;
    int totInches = static_cast<int>(floor(totMeters / METERS_INCH));

    feet = totInches / INCHES_FEET;
    inches = totInches % INCHES_FEET;
}

void showData(int feet, int inches) {
    cout << "This is equivalent to " << feet
         << " feet and " << inches << " inches.\n";
}
