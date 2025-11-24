/*
*One gallon is 3785.41 milliliters. Write a program that will read the volume
of a package of milk in milliliters, and output the volume in gallons, as well as the
number of packets needed to yield one gallon of milk.
*/

#include <iostream>
using namespace std;

int main( ) {
    constexpr double ML_PER_GALLON = 3785.41;
    double volume_ml;

    cout << "Enter the volume of the milk package in milliliters:";
    cin >> volume_ml;

    double volume_gallons = volume_ml / ML_PER_GALLON;

    cout << "Volume in gallons: " << volume_gallons << endl;
    int packets_needed = static_cast<int>(ML_PER_GALLON / volume_ml) +
                        (static_cast<int>(ML_PER_GALLON)
                            % static_cast<int>(volume_ml) != 0);

    cout << "Number of packets needed to yield one gallon: "
         << packets_needed << endl;

    return 0;
}