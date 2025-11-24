#include <iostream>
using namespace std;

int main ( ) {
    int height_feet;
    int height_inches;

    cout << "Enter your height (feet and inches separate by space):";
    cin >> height_feet >> height_inches;

    if (height_feet < 5 or height_feet > 7) {
        cout << "Height must be at least 5 feet or less than 8 feet.\n";
        return 1;
    }

    int ideal_weight = 110 + (height_inches * 5)
                           + ((height_feet - 5) * 12 * 5);

    cout << "Your ideal body weight is " << ideal_weight << " pounds.\n";

    return 0;
}