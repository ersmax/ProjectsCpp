#include <iostream>
using namespace std;

int main ( ) {
    float amtEducationChild, amtFinancing;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Enter the amount required for one child's education:";
    cin >> amtEducationChild;
    cout << "Enter the amount you wish to sponsor:";
    cin >> amtFinancing;

    int numKids;
    float remaingAmt = amtFinancing;

    do {
        numKids = static_cast<int>(amtFinancing/amtEducationChild);
        remaingAmt -= static_cast<float>(numKids) * amtEducationChild;
    } while (amtFinancing >= amtEducationChild);

    cout << "Remaining amt: " << remaingAmt << endl
         << "Additional amt to sponsor: " << amtEducationChild - amtFinancing << endl
         << "Kids educated: " << numKids << endl;

    return 0;
}
