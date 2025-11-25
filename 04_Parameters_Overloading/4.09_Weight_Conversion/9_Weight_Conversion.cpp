// define NDEBUG            // uncomment this line todisable assertions
#include <cassert>          // for assert
#include <iostream>         // for cin, cout
#include <limits>           // for numeric_limits, streamsize
#include <cmath>            // for floor
#include <iomanip>          // for setprecision
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::floor;
using std::fixed;
using std::showpoint;
using std::setprecision;

constexpr double POUNDS_KILO = 2.2046;
constexpr int OUNCES_POUND = 16;
constexpr double OUNCES_KILO = POUNDS_KILO * OUNCES_POUND;
constexpr int GRAMS_KILO = 1000;

struct PoundsOunces {
    int pounds = 0;
    double ounces = 0.0;
};

struct KilogramsGrams {
    int kilograms = 0;
    double grams = 0.0;
};

void makeChoice(int& choiceMenu);
// Precondition: choice is declared
// Postcondition: 1 if user wants to convert pounds/ounces to kilograms/grams

void getData(PoundsOunces& poundsOunces);
// Precondition: poundsOunces is declared
// Postcondition: defines the values of pounds and ounces

void getData(KilogramsGrams& kilogramsGrams);
// Precondition: kilogramsGrams is declared
// Postcondition: defines the values of kilograms and grams

void convertData(const PoundsOunces& poundsOunces, KilogramsGrams& kilogramsGrams);
// Precondition: poundsOunces is non-negative
// Postcondition: converts pounds and ounces to kilograms and grams

void convertData(const KilogramsGrams& kilogramsGrams, PoundsOunces& poundsOunces);
// Precondition: kilogramsGrams is non-negative
// Postcondition: converts kilograms and grams to pounds and ounces

void showData(const PoundsOunces& poundsOunces, const KilogramsGrams& kilogramsGrams);
// Precondition: poundsOunces is non-negative
//               kilogramsGrams is non-negative
// Postcondition: displays the equivalent weights

int main( ) {
    // Postcondition: Prompts user for conversion choice,
    //                performs the desired conversion,
    //                and displays the results.
    int choice;

    while (true) {
        makeChoice(choice);
        if (choice == 1) {          // Pound to Kilo
            PoundsOunces poundsOunces;
            KilogramsGrams kilogramsGrams;
            getData(poundsOunces);

            assert(poundsOunces.pounds >= 0 && poundsOunces.ounces >= 0);
            convertData(poundsOunces, kilogramsGrams);

            assert(kilogramsGrams.kilograms >= 0 && kilogramsGrams.grams >= 0);
            showData(poundsOunces, kilogramsGrams);
        }
        else if (choice == 2) {   // Kilo to pound
            PoundsOunces poundsOunces;
            KilogramsGrams kilogramsGrams;
            getData(kilogramsGrams);

            assert(kilogramsGrams.kilograms >= 0 && kilogramsGrams.grams >= 0);
            convertData(kilogramsGrams, poundsOunces);

            assert(poundsOunces.pounds >= 0 && poundsOunces.ounces >= 0);
            showData(poundsOunces, kilogramsGrams);
        } else
            break;
    }
    cout << '\n';
    return 0;
}

void makeChoice(int &choiceMenu) {
    while (true) {
        cout << "Menu:\n"
             << "1. Convert pounds & ounces to kilo and grams\n"
             << "2. Kilograms and grams to pounds and ounces\n"
             << "0. Exit\n"
             << "Choice:";
        if (!(cin >> choiceMenu)) {
            cout  << "Invalid choice.\n\n";
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        if (choiceMenu == 0 || choiceMenu == 1 || choiceMenu == 2)
            break;
        cout << "Invalid choice.\n\n";
    }
}

void getData(PoundsOunces& poundsOunces) {
    while (true) {
        cout << "Enter the weight in pounds and ounces (separated by a space):";
        if (!(cin >> poundsOunces.pounds >> poundsOunces.ounces)) {
            cout << "Wrong input\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // ignore input after pound and ounce
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (poundsOunces.pounds >= 0 && poundsOunces.ounces >= 0)
            break;

        cout << "Weight must be greater than or equal to 0.\n";
    }
}

void getData(KilogramsGrams& kilogramsGrams) {
    while (true) {
        cout << "Enter kilo and grams separated by a space:";
        if (!(cin >> kilogramsGrams.kilograms >> kilogramsGrams.grams )) {
            cout << "Wrong values.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // read only kilo and grams, ignore the rest
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (kilogramsGrams.kilograms >= 0 && kilogramsGrams.grams >= 0)
            break;

        cout << "Weight cannot be negative.\n";
    }
}

void convertData(const PoundsOunces& poundsOunces, KilogramsGrams& kilogramsGrams) {
    double totalOunce = poundsOunces.pounds * OUNCES_POUND + poundsOunces.ounces;
    double totalKilos = totalOunce / OUNCES_KILO;

    kilogramsGrams.kilograms = static_cast<int>(totalKilos);
    kilogramsGrams.grams = (totalKilos - kilogramsGrams.kilograms) * GRAMS_KILO;
}

void convertData(const KilogramsGrams& kilogramsGrams, PoundsOunces& poundsOunces) {
    double totalPounds = (kilogramsGrams.kilograms + kilogramsGrams.grams / GRAMS_KILO ) * POUNDS_KILO;
    poundsOunces.pounds = static_cast<int>(floor(totalPounds));
    poundsOunces.ounces = (totalPounds - poundsOunces.pounds) * OUNCES_POUND;
}

void showData(const PoundsOunces& poundsOunces, const KilogramsGrams& kilogramsGrams) {
    cout << fixed << showpoint << std::setprecision(2);
    const char* kiloLabel = (kilogramsGrams.kilograms == 0 || kilogramsGrams.kilograms == 1) ?
                            "kilo" : "kilos";
    const char* gramLabel = (round(kilogramsGrams.grams) == 0 || round(kilogramsGrams.grams) == 1) ?
                            "gram" : "grams";
    const char* poundLabel = (poundsOunces.pounds == 0 || poundsOunces.pounds == 1) ?
                            "pound" : "pounds";
    const char* ounceLabel = (round(poundsOunces.ounces) == 0 || round(poundsOunces.ounces) == 1) ?
                            "ounce" : "ounces";
    cout << kilogramsGrams.kilograms << " " << kiloLabel << " "
         << kilogramsGrams.grams << " " << gramLabel << " "
         << " are equivalent to "
         << poundsOunces.pounds << " " << poundLabel << " "
         << poundsOunces.ounces << " " << ounceLabel << ".\n\n";
}
