// define NDEBUG        // uncomment this line todisable assertions
#include <cassert>      // for assert
#include <iomanip>      // for setprecision
#include <iostream>     // for cin, cout
#include <limits>       // for numeric_limits, streamsize
using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;
using std::fixed;
using std::setprecision;


constexpr double POUNDS_KILO = 2.2046;
constexpr int OUNCES_POUND = 16;
constexpr double OUNCES_KILO = POUNDS_KILO * OUNCES_POUND;
constexpr int GRAMS_KILO = 1000;

void getData(int& pound, int& ounce);
// Precondition: pound and ounce are declared
// Postcondition: defines the values of pound and ounce

void transformData(int pound, int ounce, int& kilo, double& grams);
// Precondition: pound and ounce are non-negative integers
// Postcondition: converts pound and ounce to kilo and grams

void showData(int pound, int ounce, int kilograms, double grams);
// Precondition: pound and ounce are non-negative integers
//               kilo is a non-negative integer
//               grams is a non-negative double
// Postcondition: displays the equivalent weight in kilos and grams

int main( ) {
    char answer;
    int pound, ounce, kilo;
    double grams;

    do {
        getData(pound, ounce);

        assert(pound >= 0 && ounce >= 0);
        transformData(pound, ounce, kilo, grams);

        assert(pound >= 0 && ounce >= 0
               && kilo >= 0 && grams >= 0);
        showData(pound, ounce, kilo, grams);

        cout << "Continue (y/Y)?: ";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (answer == 'y' || answer == 'Y');
}

void getData(int& pound, int& ounce) {
    while (true) {
        cout << "Enter the weight in pounds and ounces (separated by a space):";
        if (!(cin >> pound >> ounce)) {
            cout << "Wrong input\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore input after pound and ounce
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pound >= 0 && ounce >= 0)
            break;

        cout << "Weight must be greater than or equal to 0.\n";
    }
}

void transformData(int pound, int ounce, int& kilo, double& grams) {
    int totalOunce = pound * OUNCES_POUND + ounce;
    double totalKilos = totalOunce / OUNCES_KILO;
    double totalGrams = totalKilos * GRAMS_KILO;

    kilo = static_cast<int>(totalGrams / GRAMS_KILO);
    grams = totalGrams - static_cast<double>(kilo * GRAMS_KILO);
}

void showData(int pound, int ounce, int kilograms, double grams) {
    cout << fixed << std::setprecision(0);
    const char* poundLabel = (pound == 1) ? "pound" : "pounds";
    const char* ounceLabel = (ounce == 1) ? "ounce" : "ounces";

    cout << pound << " " << poundLabel << " "
         << ounce << " " << ounceLabel << " "
         << " are equivalent to "
         << kilograms << " kilos and "
         << grams << " grams.\n" ;
}
