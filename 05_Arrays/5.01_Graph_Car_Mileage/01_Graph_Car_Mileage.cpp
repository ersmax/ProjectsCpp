#include <iostream>
#include <iterator>
#include <limits>
#include <iomanip>
#include <string>
#include <cmath>

constexpr int TESTS = 10;
constexpr int KMH = 10;
constexpr double SCALE_FACTOR = 10.0;

void fillEntry(double mileage[], std::size_t size);
//   Precondition: size is the declared size of the array mileage
//   Postcondition: mileage[0] through mileage[size - 1] have been filled with
// nonnegative doubles read from the keyboard (values between 0 and 50)

void showTable(const double avgKm[],std::size_t sizeAvg,
               const double mileage[], std::size_t size);
//   Precondition: avgKm[0] through avgKm[sizeAvg - 1] have values
//   Postcondition: display a table comparing avgKm and mileage

void showGraph(const double avgKm[], std::size_t sizeAvg,
               const double mileage[], std::size_t size);
//   Precondition: avgKm[0] through avgKm[sizeAvg - 1] have values
//   Postcondition: display a graph comparing avgKm and mileage

void scale(const double numbers[], std::size_t size, double numbersScaled[]);
//   Precondition: numbers[0] through numbers[size - 1] have nonnegative values
//   Postcondition: numbersScaled[index] has been scaled to the number of tens
// (rounded to an integer) that were originally in numbers[index], for all
// index such that 0 <= index <= (size-1).

void printAsterisk(int number);
//   Postcondition: Prints `number` asterisks to the screen.

int main( ) {
    int choice;
    bool runningVisualization = true;
    double avgKm[TESTS] = {40,39,36,34,33,31,29,26,25,24};
    double testDrive[TESTS];
    fillEntry(testDrive, std::size(testDrive));

    while (runningVisualization) {
        std::cout << "Table (1), Graph (2) or Exit (0)?\n";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // discard rest of the line
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                showTable(avgKm, std::size(avgKm), testDrive, std::size(testDrive));
                break;
            case 2:
                showGraph(avgKm, std::size(avgKm), testDrive, std::size(testDrive));
                break;
            case 0:
                std::cout << "Exiting...\n";
                runningVisualization = false;
                break;
            default:
                std::cout << "Unknown option.\n";
                break;
        }
    }
    std::cout << "\n";
    return 0;
}

void fillEntry(double mileage[], std::size_t size) {
    double next;
    for (std::size_t idx = 0; idx < size; ++idx) {
        std::cout << "Mileage (Km/l) for "
                  << (idx + 1) * KMH << " km/h:\n";
        while (true) {
            if (!(std::cin >> next )) {
                std::cout << "Not a number. Retry\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            // discard rest of the input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if ((next > 0) && (next <= 50)) {
                mileage[idx] = next;
                break;
            }
            std::cout << "Mileage should be between 0-50\n";
        }
    }
}

void showTable(const double avgKm[], const std::size_t sizeAvg,
               const double mileage[], const std::size_t size) {

    std::cout << std::fixed << std::showpoint << std::setprecision(1);
    std::cout  << std::setw(10) << "Speed"
               << std::setw(8) << "Avg km/l"
               << std::setw(8) << "Test km/l"
               << std::setw(8) << "Diff"
               << std::setw(8) << "+/-"
               << "\n" ;

    for (std::size_t idx = 0; idx < size; ++idx) {
        std::string result;
        double diff = mileage[idx] - avgKm[idx];
        if (diff > 0) result = "above";
        else if (diff < 0) result = "below";
        else result = "equal";

        std::cout  << std::setw(5) << (idx + 1)* KMH << std::setw(5) << "km/h"
                   << std::setw(8) << avgKm[idx]
                   << std::setw(8) << mileage[idx]
                   << std::setw(8) << diff
                   << std::setw(8) << result
                   << "\n";
    }
}

void showGraph(const double avgKm[], std::size_t sizeAvg,
               const double mileage[], std::size_t size) {

    double avgScaled[TESTS];
    double mileageScaled[TESTS];
    scale(avgKm, sizeAvg, avgScaled);
    scale(mileage, size, mileageScaled);
    std::cout << "Mileage in km/l (in tens of units)\n";

    for (std::size_t idx = 0; idx < size; ++idx) {
        std::cout << "Speed: " << (idx + 1) * KMH << " km/h\n"
                  << std::setw(10) << "Average:";
        printAsterisk(static_cast<int>(avgScaled[idx]));
        std::cout << "\n";
        std::cout << std::setw(10) << "Actual:";
        printAsterisk(static_cast<int>(mileageScaled[idx]));
        std::cout << "\n";
    }
}

void scale(const double numbers[], std::size_t size, double numbersScaled[]) {
    for (std::size_t idx = 0; idx < size; ++idx)
        numbersScaled[idx] = std::floor((numbers[idx] / SCALE_FACTOR) + 0.5);
}

void printAsterisk(int number) {
    for (int count = 1; count <= number; ++count)
        std::cout  << "*";
}
