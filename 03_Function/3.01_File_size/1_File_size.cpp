#include <iostream>
using namespace std;

const int KB_PER_MB = 8000;

double sizeMegabytes(double duration, double bitRate);
// Precondition: duration is in minutes (including seconds),
//               bitRate is in kilobits per second
// Postcondition: returns the file size in megabytes


int main( ) {
    // Precondition: None
    // Postcondition: Prompts the user for the bit rate and duration of a video clip
    //                and outputs the file size in megabytes
    double fileSize, duration, bitRate;

    cout << "Enter the bit rate in kilobits:";
    cin >> bitRate;
    cout << "Enter the duration in minutes of the video:";
    cin >> duration;

    fileSize = sizeMegabytes(duration, bitRate);

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "The file size is: " << fileSize << endl;

    return 0;
}

double sizeMegabytes(double duration, double bitRate) {
    return ((60 * duration * bitRate) / KB_PER_MB);
}