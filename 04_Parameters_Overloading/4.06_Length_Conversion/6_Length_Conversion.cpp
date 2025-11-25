// define NDEBUG        // uncomment this line todisable assertions
#include <iostream>     // for cin, cout, endl
#include <cassert>      // for assert
#include <cmath>        // for round
#include <limits>       // for numeric_limits, streamsize
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::floor;
using std::round;

constexpr double METERS_FEET = 0.3048;
constexpr int INCHES_FEET = 12;
constexpr double METERS_INCH = METERS_FEET / INCHES_FEET;
constexpr int CM_METER = 100.0;

struct FeetInches {
    int feet = 0;
    int inches = 0;
};

struct MetersCentimeters {
    int meters = 0;
    int centimeters = 0;
};

void makeChoice(int& choiceMenu);
// Precondition: choice is declared
// Postcondition: 1 if user wants to convert feet/inches to meters/centimeters
//                2 if user wants to convert meters/centimeters to feet/inches
//                0 to exit program

void getData(FeetInches& feetInches);
// Precondition: feetInches is declared
// Postcondition: defines the values of feet and inches

void getData(MetersCentimeters& metersCentimeters);
// Precondition: metersCentimeters is declared
// Postcondition: defines the values of meters and centimeters

void convertData(const FeetInches& feetInches, MetersCentimeters& metersCentimeters);
// Precondition: feetInches is in 5-7 feet and 0-11 inches range
// Postcondition: converts feet and inches to meters and centimeters

void convertData(const MetersCentimeters& metersCentimeters, FeetInches& feetInches);
// Precondition: metersCentimeters is in 0-2 meters and 0-99 centimeters range
// Postcondition: converts meters and centimeters to feet and inches

void showData(const FeetInches& feetInches, const MetersCentimeters& metersCentimeters);
// Precondition: feetInches is in 5-7 feet and 0-11 inches range
//               metersCentimeters is in 0-2 meters and 0-99 centimeters range
// Postcondition: displays the equivalent lengths

int main( ) {
    // Postcondition: Prompts user for conversion choice,
    //                performs the desired conversion,
    //                and displays the results.
    int choice;

    do {
        makeChoice(choice);
        switch (choice) {
            case 1: {
                FeetInches feetInches;
                MetersCentimeters metersCentimeters;
                getData(feetInches);

                assert(feetInches.feet >= 5 && feetInches.feet <= 7 &&
                       feetInches.inches >= 0 && feetInches.inches <= 11);
                convertData(feetInches, metersCentimeters);

                assert(metersCentimeters.meters >= 0 && metersCentimeters.meters <= 2 &&
                       metersCentimeters.centimeters >= 0 && metersCentimeters.centimeters <= 99);
                showData(feetInches, metersCentimeters);
                break;
            }
            case 2: {
                FeetInches feetInches;
                MetersCentimeters metersCentimeters;
                getData(metersCentimeters);

                assert(metersCentimeters.meters >= 0 && metersCentimeters.meters <= 2 &&
                       metersCentimeters.centimeters >= 0 && metersCentimeters.centimeters <= 99);
                convertData(metersCentimeters, feetInches);

                assert(feetInches.feet >= 5 && feetInches.feet <= 7 &&
                       feetInches.inches >= 0 && feetInches.inches <= 11);
                showData(feetInches, metersCentimeters);
                break;
            }
            case 0:
                cout << "Goodbye\n";
            default:
                break;
        }

    } while (choice == 1 || choice == 2);

    return 0;
}

void makeChoice(int& choiceMenu) {
    while (true) {
        cout << "Enter choice:\n"
         << "1. Convert feet inches to meters and cm\n"
         << "2. Convert meters and cm into feet inches\n"
         << "0. Exit\n"
         << "-----------------------------------------\n";
        if (!(cin >> choiceMenu)) {
            cout << "Wrong choice.\n\n";
            cin.clear();   // clear err flag and ignore line
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        // Read only choice, discard the remainder of line
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (choiceMenu >= 0 && choiceMenu <= 2)
            break;
        cout << "Wrong choice.\n\n";
    }
}

void getData(MetersCentimeters& metersCentimeters) {
    while (true) {
        cout << "Enter meters and centimeters: \n";
        if (!(cin >> metersCentimeters.meters
                     >> metersCentimeters.centimeters)) {
            cout << "Wrong Input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        // ignore the remainder of the input
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (metersCentimeters.meters >= 0 &&
            metersCentimeters.centimeters >= 0) {

            break;
        }
        cout << "Wrong Input.\n";
    }
}

void getData(FeetInches& feetInches) {
    while (true) {
        cout << "Enter feet and inches: \n";
        if (!(cin >> feetInches.feet
                     >> feetInches.inches)) {
            cout << "Wrong Input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
                     }
        // ignore the remainder of the input
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (feetInches.feet >= 0 &&
            feetInches.inches >= 0)
            break;

        cout << "Wrong Input.\n";
    }
}

void convertData(const FeetInches& feetInches, MetersCentimeters& metersCentimeters) {
    double totalMeters = METERS_FEET * feetInches.feet
                         + feetInches.inches * METERS_INCH;

    // round to nearest height
    int totalCentimeters = static_cast<int>(round(totalMeters * CM_METER));

    metersCentimeters.meters = totalCentimeters / CM_METER;
    metersCentimeters.centimeters = totalCentimeters % CM_METER;
}

void convertData(const MetersCentimeters& metersCentimeters, FeetInches& feetInches) {
    int totalCentimeters = metersCentimeters.meters * CM_METER
                           + metersCentimeters.centimeters;

    int totalInches = static_cast<int>(round(static_cast<double>(totalCentimeters)
                                                    / (METERS_INCH * CM_METER)));

    feetInches.feet = totalInches / INCHES_FEET;
    feetInches.inches = totalInches % INCHES_FEET;
}

void showData(const FeetInches& feetInches, const MetersCentimeters& metersCentimeters) {
    cout << feetInches.feet << " feet, " << feetInches.inches << "\" are equivalent to "
         << metersCentimeters.meters << " meters and " << metersCentimeters.centimeters << " cm.\n";
}
