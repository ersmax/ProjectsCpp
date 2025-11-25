#include <iostream>
using namespace std;

int main ( ) {
    double n;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Give a number n:";
    cin >> n;

    double guess = n/2.0;
    double prevGuess;

    do {
        prevGuess = guess;
        const double r = n / guess;
        guess = (guess + r) / 2;
    } while ( abs(prevGuess - guess) > 0.01 * prevGuess );

    cout << "The square root of " << n
         << " is approximately " << guess << endl;
    return 0;
}