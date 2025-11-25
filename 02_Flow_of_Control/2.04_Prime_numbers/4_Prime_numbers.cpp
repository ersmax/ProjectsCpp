#include <iostream>
#include <cmath>
using namespace std;

int main ( ) {
    int n = 3;

    cout << "List of prime numbers (3-100):\n";
    while (n <= 100) {
        int m = 2;
        bool isPrime = true;

        while (m <= sqrt(n)) {
            if (n % m == 0) {
                isPrime = false;
                break;
            }
            m++;
        }
        if (isPrime)
            cout << n << " ";
        n++;
    }
    cout << endl;
    return 0;
}