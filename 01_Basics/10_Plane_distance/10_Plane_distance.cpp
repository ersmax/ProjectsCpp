#include <iostream>
using namespace std;

int main ( ) {
    float speed_mph, time_hours;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Enter the speed of the airplane in miles per hour:";
    cin >> speed_mph;
    cout << "Enter the travel time in hours:";
    cin >> time_hours;

    float distance_miles = speed_mph * time_hours;
    float speed_mps = (speed_mph / 3600.0f) * 1609.344f;

    cout << "Distance traveled: " << distance_miles << " miles.\n"
         << "Speed in meters per second: " << speed_mps << " miles/second.\n";

    return 0;
}
