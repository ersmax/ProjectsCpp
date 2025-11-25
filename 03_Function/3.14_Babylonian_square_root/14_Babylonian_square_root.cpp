#include <iostream> // for cin, cout, endl
#include <cmath>    // for fabs
#include <limits>   // for numeric_limits
using namespace std;

const double FACTOR = 0.01;

double inputNumber();
// Postcondition: prompts user for a positive number
//                and returns it as a double

double babylonianSquareRoot(double number);
// Precondition: number is a positive double
// Postcondition: returns the square root of number.
// Check for negative input and return quiet NaN in that case.

int main( ) {
    // Postcondition: Prompts user for a positive number,
    //                computes its square root using the
    //                Babylonian algorithm, and displays the result.
    double n, square;
    char answer;

    cout.setf(ios::fixed);      // use fixed-point notation (no exp)
    cout.setf(ios::showpoint);  // use decimal point & trailing 0s: 10.00
    cout.precision(2);

    while (true) {
        n = inputNumber();
        square = babylonianSquareRoot(n);

        cout << "Square root is: " << square << endl;
        cout << "Repeat (y/Y)?";
        cin >> answer;
        if (answer != 'y' && answer != 'Y')
            break;
    }

    cout << endl;
    return 0;
}

double inputNumber() {
    double n;

    while (true) {
        cout << "Enter a positive number:";
        if (cin >> n) {
            if (n > 0.0) break;
            cout << "Please enter a positive number.\n";
        } else {
            // Clear stream error flags and discard remaining
            // characters on current line up to and including '\n'
            cout << "Invalid input. Please enter a numeric value.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return n;
}

double babylonianSquareRoot(double number) {
    int maxIterations = 10000, iteration = 0;
    double guess = number / 2;
    double r;
    double prevGuess;

    if (number < 0.0)
        // Negative input: return a quiet NaN
        // to signal an invalid result
        return numeric_limits<double>::quiet_NaN();
    if (number == 0.0)
        return 0.0;

    do {
        if (guess == 0.0)
            guess = 1.0;    // avoid division by 0
        r = number / guess;
        prevGuess = guess;
        guess = (guess + r) / 2;
        ++iteration;
    } while ((fabs(guess - prevGuess) > FACTOR * prevGuess)
        &&   (iteration < maxIterations));

    return guess;
}
