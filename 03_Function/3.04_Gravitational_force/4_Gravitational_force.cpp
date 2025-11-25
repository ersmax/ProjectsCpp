#include <iostream>
#include <cmath>
using namespace std;

const double G = 6.673e-8;

double gravitationalForce(double massBody1, double massBody2, double distance);
// Precondition: massBody1, massBody2, and distance are positive numbers
// Postcondition: returns the gravitational force between the two bodies

int main( ) {
    // Precondition: None
    // Postcondition: Prompts user for masses and distance, then displays
    //                the gravitational force between the two bodies.
    char answer;
    double mass1, mass2, distance, force;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(10);

    do {
        cout << "Enter the masses of two bodies (in grams)\n "
                "and the distance (in cm) separated by space:";
        cin >> mass1 >> mass2 >> distance;

        if (mass1 < 0 || mass2 < 0 || distance < 0)
            cerr << "Error: Masses and distance must be positive numbers.\n";
        else {
            force = gravitationalForce(mass1, mass2, distance);
            cout << "The gravitational force between the two bodies is: "
                 << force << " dynes.\n";
        }

        cout << "Repeat? (y/Y): ";
        cin >> answer;
    } while (answer == 'y' || answer == 'Y');

    return 0;
}

double gravitationalForce(double massBody1, double massBody2, double distance) {
    return ((G * massBody1 * massBody2) / pow(distance, 2));
}
