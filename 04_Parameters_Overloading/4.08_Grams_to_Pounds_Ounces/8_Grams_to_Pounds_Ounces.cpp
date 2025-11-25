// define NDEBUG        // uncomment this line todisable assertions
#include <cassert>      // for assert
#include <iostream>     // for cin, cout
#include <limits>       // for numeric_limits, streamsize
#include <cmath>        // for floor
#include <iomanip>      // for setprecision
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::floor;
using std::fixed;
using std::showpoint;
using std::setprecision;

constexpr double POUNDS_KILO = 2.2046;
constexpr int OUNCES_POUND = 16;
constexpr double OUNCES_KILO = POUNDS_KILO * OUNCES_POUND;
constexpr int GRAMS_KILO = 1000;

void getData(int& kilograms, double& grams);
// Precondition: kilograms and grams are declared
// Postcondition: defines the values of kilograms and grams

void convertData(int kilograms, double grams, int& pounds, double& ounces);
// Precondition: kilograms and grams are non-negative
// Postcondition: converts kilograms and grams to pounds and ounces

void showData(int kilograms, double grams, int pounds, double ounces);
// Precondition: kilograms and grams are non-negative
//               pounds is a non-negative integer
//               ounces is a non-negative double
// Postcondition: displays the equivalent weight in pounds and ounces

int main( ) {
    // Postcondition: Prompts user for weight in kilograms and grams,
    //                converts it to pounds and ounces,
    //                and displays it.
    char answer;
    int kilograms, pounds;
    double grams, ounces;

    do {
        getData(kilograms, grams);

        assert(kilograms >= 0 && grams >= 0);
        convertData(kilograms, grams, pounds, ounces);

        assert(kilograms >= 0 && grams >= 0 &&
               pounds >= 0 && ounces >= 0);
        showData(kilograms, grams, pounds, ounces);

        cout << "Repeat (y/Y)?:";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (answer == 'y' || answer == 'Y');

    return 0;
}

void getData(int& kilograms, double& grams) {
    while (true) {
        cout << "Enter kilo and grams separated by a space:";
        if (!(cin >> kilograms >> grams)) {
            cout << "Wrong values.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // read only kilo and grams, ignore the rest
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (kilograms >= 0 && grams >= 0)
            break;

        cout << "Weight cannot be negative.\n";
    }
}

void convertData(int kilograms, double grams, int& pounds, double& ounces) {
    double totalPounds = (kilograms + grams / GRAMS_KILO ) * POUNDS_KILO;
    pounds = static_cast<int>(floor(totalPounds));
    ounces = (totalPounds - pounds) * OUNCES_POUND;
}

void showData(int kilograms, double grams, int pounds, double ounces) {
    cout << fixed << showpoint << std::setprecision(2);
    const char* kiloLabel = (kilograms == 0 || kilograms == 1) ? "kilo" : "kilos";
    const char* gramsLabel = (grams == 0 || grams == 1) ? "gram" : "grams";
    cout << kilograms << " " << kiloLabel << " "
         << grams << " " << gramsLabel << " "
         << " are equivalent to "
         << pounds << " pounds and "
         << ounces << " ounces.\n" ;
}
