#include <iostream>
#include <cstdlib>
using namespace std;

constexpr int FACES = 6;

int sum_two_dices();
// Precondition: None
// Postcondition: returns the sum of rolling two six-sided dice

bool outcome();
// Precondition: None
// Postcondition: returns true if the player wins, false if the player loses

int main( ) {
    // Postcondition: Simulates 10,000 games of craps,
    //                then displays the likelihood of winning.
    srand(time(0));
    int games = 10000;
    int wins = 0, losses = 0;
    double result;

    for (int idx = 0; idx < games; ++idx ) {
        if (outcome())
            wins++;
        else
            losses++;
    }

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    result = (wins/static_cast<double>(wins + losses)) * 100;
    cout << "The likelihood of winning is: " << result << "%.\n"
         << "Number of wins: " << wins << endl
         << "Number of losses: " << losses << endl;

    if (result < 0.50)
        cout << "The house is more likely to win the game.\n";
    else
        cout << "You are more likely to win the game than the house.\n";

    return 0;
}

int sum_two_dices() {
    return (rand( ) % FACES + 1) + (rand( ) % FACES + 1);
}

bool outcome() {
    int result = sum_two_dices();

    if (result == 7 || result == 11)
        return true;
    if (result == 2 || result == 3 || result == 12)
        return false;

    int new_point = result;
    while (true) {
        int roll = sum_two_dices();
        if (roll == new_point)
            return true;
        if (roll == 7)
            return false;
    }
}