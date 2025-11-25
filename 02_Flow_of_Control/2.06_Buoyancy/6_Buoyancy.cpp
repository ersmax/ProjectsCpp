#include <iostream>
#include <cmath>
using namespace std;

int main ( ) {
    float weight, radius;
    constexpr float g = 62.4;       // lb/ft3
    constexpr float PI = 3.14159265358979323846;

    cout << PI;

    cout << "Enter the weight (in pounds) of the sphere: ";
    cin >> weight;
    cout << "Enter the radius (in feet) of the sphere: ";
    cin >> radius;

    auto volume = static_cast<float>((4.0 / 3.0) * PI * pow(radius,3));
    float buoyantForce = volume * g; // buoyant force
    if (buoyantForce >= weight)
        cout << "The sphere will float in water.\n";
    else
        cout << "The sphere will sink in water.\n";
    return 0;
}