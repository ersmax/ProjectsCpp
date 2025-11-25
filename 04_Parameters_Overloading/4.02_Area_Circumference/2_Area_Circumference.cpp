// define NDEBUG        // uncomment this line todisable assertions
#include <iostream>     // for cin, cout, endl
#include <limits>       // for numeric_limits, streamsize
#include <cassert>      // for assert
#include <iomanip>      // for setprecision, fixed, showpoint
#include <cmath>        // for acos
using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::setprecision;
using std::fixed;
using std::showpoint;

const double PI = std::acos(-1.0);

void getData(double& radius);
// Precondition: radius is declared
// Postcondition: defines the value of radius

void areaCircumference(double radius, double& area, double& circumference);
// Precondition: radius is a positive number
// Postcondition: computes area and circumference of the circle

void showData(double area, double circumference);
// Precondition: area and circumference are computed and valid values
// Postcondition: displays the area and circumference


int main( ) {
    // Postcondition: Prompts user for radius,
    //                computes area and circumference,
    //                and displays the results.
    double area, circumference, radius;
    char answer;

    do {
        getData(radius);

        assert(radius>0);
        areaCircumference(radius, area, circumference);

        assert(area > 0 && circumference > 0);
        showData(area, circumference);

        cout << "Repeat? (y/Y)";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    } while (answer == 'y' || answer == 'Y');

    cout << "\n";
    return 0;
}

void getData(double& radius) {
    while (true) {
        cout << "Enter the radius (>0):";
        if (!(cin >> radius)) {
            cout << "Invalid value.\n";
            cin.clear(); // clear error flags, remove bad input
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        // discard extra tokens on same line (e.g 212.1 exit)
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "You entered: " << radius << endl;

        if (radius > 0)
            break;
        cout << "Wrong value.\n";
    }
}

void areaCircumference(double radius, double& area, double& circumference) {
    area = PI * radius * radius;
    circumference = 2.0 * PI * radius;
}

void showData(double area, double circumference) {
    cout << fixed << showpoint << setprecision(2);
    cout << "The area is " << area
         << " and circumference is " << circumference << endl;
}
