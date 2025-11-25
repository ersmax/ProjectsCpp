#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

constexpr int PLANTS = 4;
constexpr int COL_WIDTH = 4;

void enterData(int production[], int numPlants);
//   Postcondition: fill production array with total production for each plant.

void getTotal(int& totPlant, int nPlant);
//   Precondition: nPlant is the plant number (1 to numPlants).
// Postcondition: totPlant is the total production for plant number nPlant.

void scale(const int numbers[], int scaledNumbers[], int numPlants);
//   Precondition: numbers[0] through numbers[numPlants-1] each has a nonnegative value.
//   Postcondition: scaledNumbers[index] has been scaled to the number of 1000s
// (rounded to an integer) that were originally in numbers[index], for all
// `index` such that 0 <= index <= (numPlants-1).

int findMax(const int scaleNumbers[], int numPlants);
//   Precondition: scaleNumbers[0] through scaleNumbers[numPlants-1]
// each has a nonnegative value.
//   Postcondition: returns the maximum value among scaleNumbers[0]
// through scaleNumbers[numPlants-1].

void showRawData(const int numbers[], int numPlants);
//   Postcondition: display the raw production data for each plant.

void showHistogram(const int scaleNumbers[], int numPlants);
//   Precondition: scaleNumbers[0] through scaleNumbers[numPlants-1]
// each has a nonnegative value.
//   Postcondition: display a vertical histogram for the scaled production data.

void printAsterisks(int number);
//   Postcondition: Prints `number` asterisks to the screen.

int main( ) {
    int production[PLANTS];
    int scaledProduction[PLANTS];

    enterData(production, PLANTS);
    scale(production, scaledProduction, PLANTS);
    showRawData(production, PLANTS);
    showHistogram(scaledProduction, PLANTS);

    std::cout << "\n";
    return 0;
}


void enterData(int production[], const int numPlants) {
    for (int idx = 0; idx < numPlants; ++idx) {
        std::cout << "Production for plant #"
                  << idx + 1 << ":\n";
        getTotal(production[idx], idx+1);
    }
}

void getTotal(int& totPlant, int nPlant) {
    totPlant = 0;
    std::string line;
    while (true) {
        std::cout << "Enter production of Plant " << nPlant
                  << " for each line separated by space or comma."
                     "(-1 to exit)\n";
        // EOF or input error
        if (!std::getline(std::cin, line)) {
            std::cout << "End of input\n";
            return;
        }
        // Replace any non-digit char with space, cast for portability
        for (char& c : line) {
            auto uc = static_cast<unsigned char>(c);
            if (!std::isdigit(uc) && c != '-' && !std::isspace(uc))
                c = ' ';
        }

        std::istringstream iss(line);
        bool terminate = false;
        int productionLine;
        while (iss >> productionLine) {
            if (productionLine == -1) {
                terminate = true;
                break;
            }
            if (productionLine < 0) continue;
            totPlant += productionLine;
        }

        std::cout << "Current total production Plant " << nPlant
                  << ": " << totPlant << "\n";
        if (terminate) break;
    }
}

void scale(const int numbers[], int scaledNumbers[], const int numPlants) {
    for (int idx = 0; idx < numPlants; ++idx)
        scaledNumbers[idx] = std::floor(numbers[idx] / 1000.0 + 0.5);
}

void showRawData(const int numbers[], const int numPlants) {
    std::cout << "Units produced per plant:\n\n";
    for (int plant = 0; plant < numPlants; ++plant)
        std::cout << "Plant #" << plant + 1 << ": " << numbers[plant] << "\n";
}


void showHistogram(const int scaleNumbers[], const int numPlants) {
    int maxProduction = findMax(scaleNumbers, numPlants);

    std::cout << "\nUnits produced (in thousands) per plant:\n";

    for (int row = maxProduction - 1; row >= 0; --row) {
        for (int plant = 0; plant < numPlants; ++plant) {
            if (scaleNumbers[plant] > row)
                printAsterisks(1);
            else
                printAsterisks(0);
        }
        std::cout << "\n";
    }
    for (int plant = 0; plant < numPlants; ++plant) {
        std::string label = std::string("#") + std::to_string(plant+1);
        std::cout << std::setw(COL_WIDTH) << label;
    }
}

int findMax(const int scaleNumbers[], const int numPlants) {
    int max = 0;
    for (int idx = 0; idx < numPlants; ++idx)
        max = (scaleNumbers[idx] > max) ? scaleNumbers[idx] : max;
    return max;
}

void printAsterisks(const int number) {
    if (number > 0)
        for (int count = 0; count < number; ++count)
            std::cout << std::setw(COL_WIDTH) << '*';
    else
        std::cout << std::setw(COL_WIDTH) << ' ';

}
