/*
A government research lab has concluded that an artificial sweetener commonly
used in diet soda will cause death in laboratory mice. A friend of yours is desperate
to lose weight but cannot give up soda. Your friend wants to know how much diet
soda it is possible to drink without dying as a result. Write a program to supply
the answer. The input to the program is the amount of artificial sweetener needed
to kill a mouse, the weight of the mouse, and the weight of the dieter. To ensure
the safety of your friend, be sure the program requests the weight at which the
dieter will stop dieting, rather than the dieter’s current weight. Assume that diet
soda contains one-tenth of 1% artificial sweetener. Use a variable declaration with
the modifier const to give a name to this fraction. You may want to express the
percentage as the double value 0.001.
*/
#include <iostream>
using namespace std;

int main ( ) {
    const double ARTIFICIAL_SWEETENER_PERC = 0.001; // 0.1% as a decimal
    double sweetener_to_kill_mouse;
    double mouse_weight;
    double dieter_target_weight;

    cout << "Enter the amount of artificial sweetener needed "
            "to kill a mouse (in grams):";
    cin >> sweetener_to_kill_mouse;
    cout << "Enter the weight of the mouse (in kg):";
    cin >> mouse_weight;
    cout << "Enter the target weight of the dieter (in kg):";
    cin >> dieter_target_weight;

    mouse_weight *= 1000;
    dieter_target_weight *= 1000;

    double sweetener_per_kg = sweetener_to_kill_mouse / mouse_weight;
    double total_sweetener_to_kill_dieter =
        sweetener_per_kg * dieter_target_weight;
    double max_diet_soda =
        total_sweetener_to_kill_dieter / ARTIFICIAL_SWEETENER_PERC;

    max_diet_soda = max_diet_soda/1000; // convert to grams
    cout << "The maximum amount of diet soda the dieter can safely drink is: "
         << max_diet_soda << " kilograms.\n";

    return 0;
}