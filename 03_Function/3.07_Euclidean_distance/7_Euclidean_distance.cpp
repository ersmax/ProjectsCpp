#include <iostream>
#include <cmath>
using namespace std;

double euclideanDistance(int x1, int y1, int x2, int y2);
// Precondition: x1, y1, x2, and y2 are integers
// Postcondition: returns the Euclidean distance between the two points

int main( ) {
    // Postcondition: Prompts user for the coordinates of two points,
    //                then displays the Euclidean distance between them.
    int x1, x2, y1, y2;
    double distance;

    cout << "Enter the first point coordinates (x, y):\n"
         << "(separated by a space):";
    cin >> x1 >> y1;
    cout << "Enter the second point coordinates (x, y):\n"
         << "(separated by a space):";
    cin >> x2 >> y2;

    distance = euclideanDistance(x1, y1, x2, y2);

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "The Euclidean distance is: " << distance << endl;

    return 0;
}

double euclideanDistance(int x1, int y1, int x2, int y2) {
    double sumSquares = pow((x2 - x1), 2) + pow((y2 - y1), 2);

    return sqrt(sumSquares);
}
