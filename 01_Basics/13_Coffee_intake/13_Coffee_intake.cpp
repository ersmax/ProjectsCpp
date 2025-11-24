#include <iostream>
using namespace std;

int main( ) {
    constexpr int LETHAL_DOSE_MG = 10000;
    float caffeine_mg;

    cout << "Enter the amount of caffeine in milligrams (mg) per drink:";
    cin >> caffeine_mg;

    int drinks_to_lethal_dose = static_cast<int>(LETHAL_DOSE_MG/ caffeine_mg);

    // if caffeing_mg were declared as int, use modulo % instead
    if (static_cast<float>(drinks_to_lethal_dose) * caffeine_mg < LETHAL_DOSE_MG)
        drinks_to_lethal_dose++;

    cout << "It would take approximately " << drinks_to_lethal_dose
         << " drink(s) to reach a lethal dose of caffeine.\n";

    return 0;
}