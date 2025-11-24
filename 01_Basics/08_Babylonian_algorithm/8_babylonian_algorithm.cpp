#include <complex>
#include <iostream>
using namespace std;

int main ( ) {
    double n;
    double r = 0.0;
    constexpr int ITERATIONS = 5;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Enter a positive number to find its square root:";
    cin >> n;

    double guess = n / 2.0; // Initial guess

    for (int idx = 0; idx < ITERATIONS; ++idx) {
        r = n / guess;
        guess = (guess + r) / 2.0;
        if (guess == sqrt(n)) {
            cout << "Converged after " << (idx + 1) << " iterations.\n";
            break;
        }
    }

    cout << "The approximate square root of " << n << " is " << guess << endl;

    return 0;
}
