#include <iostream>
using namespace std;

int main ( ) {
    int total_seconds;

    cout << "Enter the total number of seconds:";
    cin >> total_seconds;

    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;
    cout << total_seconds << " seconds is equivalent to "
         << hours << " hours, "
         << minutes << " minutes, and "
         << seconds << " seconds.\n";

    return 0;
}
