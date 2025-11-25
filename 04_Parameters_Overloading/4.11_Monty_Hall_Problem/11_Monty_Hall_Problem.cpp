#include <iostream>     // for cin, console out
#include <random>       // for random device, mt19937, uniform int distribution
#include <utility>      // for pair
#include <vector>       // for vector
#include <algorithm>    // for find
#include <iomanip>      // for show-point, setprecision
using std::cout;
using std::cin;
using std::vector;
using std::move;
using std::find;
using std::pair;
using std::showpoint;
using std::fixed;
using std::setprecision;
using std::uniform_int_distribution;

std::random_device rd;  // obtain a random number from hardware
std::mt19937 rng(rd()); // seed the generator

constexpr int DOORS = 5;        // Change here # of doors. Original: 3

constexpr int GAMES = 1;        // Change here # of games to simulate. Original: 10000

void showResults(const vector<pair<int, double> >& leftDoorsProbs, int selectedDoor);
// Precondition: leftDoorsProbs contains doors and their probabilities of winning
//               selectedDoor is the door currently selected by the contestant
// Postcondition: displays the doors left, their probabilities, and the selected door

void randomDoorPrice(int& winningDoor);
// Postcondition: randomly selects a door (1 to DOORS) to hide the prize

int initialPick(int& choiceDoor);
// Postcondition: randomly selects a door (1 to DOORS) as the contestant's initial choice
//                variable returns the selected door, but also define the first choice

void nextPick(const vector<pair<int, double> >& leftDoorsProbs, int& selectedDoor);
// Precondition: leftDoorsProbs contains doors and their probabilities of winning
//               selectedDoor is the door currently selected by the contestant
// Postcondition: updates selectedDoor to a new door based on the highest probability

void startGame(vector<pair<int, double>>& leftDoorsProbs);
// Postcondition: initializes leftDoorsProbs with all doors and equal probabilities

void removeLosingDoor(vector<pair<int, double> >& leftDoorsProbs,
                      int winningDoor,
                      int selectedDoor);
// Precondition: leftDoorsProbs contains doors and their probabilities of winning
//               winningDoor is the door hiding the prize
//               selectedDoor is the door currently selected by the contestant
// Postcondition: removes one losing door from leftDoorsProbs and redistributes
//                its probability among the remaining doors (excluding selectedDoor)

void showStatistics(const int& winsStaying, const int& winsSwitch);
// Precondition: winsStaying and winsSwitch are the counts of wins for each strategy
// Postcondition: displays the winning statistic for both strategies

int main( ) {
    int nGames = 0;
    int winningDoor, selectedDoor;
    int winsStaying = 0, winsSwitch = 0;

    /*  This is NOT thread safe
    // seed the C library pseudorandom generator
    // time(nullptr) returns current time
    // case the result to unsigned required by `srand`
    srand(static_cast<unsigned>(time(nullptr)));
    */

    cout << showpoint << fixed << setprecision(2);

    while (nGames < GAMES) {

        vector<pair<int, double>> leftDoorsProbs;

        startGame(leftDoorsProbs);
        randomDoorPrice(winningDoor);
        cout << "Winning door: " << winningDoor << "\n";

        const int initialChoice = initialPick(selectedDoor);

        showResults(leftDoorsProbs, selectedDoor);

        size_t doorsLeft = leftDoorsProbs.size();
        while (doorsLeft > 2) {
            removeLosingDoor(leftDoorsProbs, winningDoor, selectedDoor);
            --doorsLeft;
            nextPick(leftDoorsProbs, selectedDoor);
            showResults(leftDoorsProbs, selectedDoor);
        }
        if (initialChoice == winningDoor)
            ++winsStaying;
        if (selectedDoor == winningDoor)
            ++winsSwitch;
        ++nGames;
    }
    showStatistics(winsStaying, winsSwitch);

    return 0;

}

void showResults(const vector<pair<int, double> >& leftDoorsProbs,
                 const int selectedDoor) {


    for (auto pair : leftDoorsProbs) {
        cout << pair.first << ") " << (pair.second * 100.0) << "%";
        if (pair.first == selectedDoor)
            cout << " <-- selected";
        cout << "\t";
    }
    cout << "\n";
    cout << "Selected door: " << selectedDoor << "\n";
}

void showStatistics(const int& winsStaying, const int& winsSwitch) {
    const double ratioStay = static_cast<double>(winsStaying) / GAMES;
    const double ratioSwitch = static_cast<double>(winsSwitch) / GAMES;

    cout << "If you keep your initial choice by choosing randomly one of the "
         << DOORS << " doors, you win "
         << (ratioStay * 100) << "% of " << GAMES << " games.\n\n";

    cout << "If you switch to another of the "
         << DOORS << " doors and follow Bayes' Theorem, you win "
             << (ratioSwitch * 100) << "% of " << GAMES << " games.\n";
}


void startGame(vector<pair<int, double> >& leftDoorsProbs) {
    double probabilities = 1.0 / DOORS;
    leftDoorsProbs.reserve(DOORS);
    for (int idx = 1; idx <= DOORS; ++idx)
        // associate door and probabilities
        leftDoorsProbs.emplace_back(idx, probabilities);
}

void randomDoorPrice(int& winningDoor) {
    uniform_int_distribution<int> dist(1, DOORS);
    winningDoor = dist(rng);              // C++ standard compliant
    // winningDoor = rand( ) % DOORS + 1; // This is NOT thread safe
}

int initialPick(int& choiceDoor) {
    uniform_int_distribution<int> dist(1, DOORS);
    choiceDoor = dist(rng);              // C++ standard compliant
    return choiceDoor;
    // choiceDoor = rand( ) % DOORS + 1; // This is NOT thread safe
}

void nextPick(const vector<pair<int, double> >& leftDoorsProbs, int& selectedDoor) {
    // choose among candidates that have higher probability
    //  pick the door(s) with max probability and break ties randomly
    double selectedDoorProb = -1.0;

    for (const auto& door : leftDoorsProbs) {
        if (door.first == selectedDoor) {
            selectedDoorProb = door.second;
            break;
        }
    }
    // find max probability among remaining doors
    double maxProb = -1.0;
    for (const auto& door : leftDoorsProbs) {
       if (door.first == selectedDoor)
           continue;
       if (door.second > selectedDoorProb && door.second > maxProb)
           maxProb = door.second;
    }

    // if no other door has higher probability, keep the current selection
    if (maxProb < 0.0)
        return;

    // collect doors with max probability and break ties randomly
    vector<int> bestDoors;
    for (const auto& door : leftDoorsProbs) {
        if (door.second == maxProb)
            bestDoors.push_back(door.first);
    }
    // guarding against empty bestDoors
    if (bestDoors.empty())
        return;

    // pick randomly among best doors
    uniform_int_distribution<size_t> dist(0, bestDoors.size() - 1);
    selectedDoor = bestDoors[dist(rng)];        // C++ standard compliant
    /* This is NOT thread safe */
    // size_t pick = static_cast<size_t>(rand()) % bestDoors.size();
    // selectedDoor = bestDoors[pick];

}


void removeLosingDoor(vector<pair<int, double> >& leftDoorsProbs,
                      const int winningDoor,
                      const int selectedDoor) {

    if (leftDoorsProbs.size() <= 2)
        return;

    // build candidates in the original order
    vector<pair<int, double> > candidates;
    candidates.reserve(leftDoorsProbs.size());
    for (const auto& door : leftDoorsProbs)
        if (door.first != winningDoor && door.first != selectedDoor)
            candidates.push_back(door);

    if (candidates.empty())
        return;

    // pick losing door from candidates (excluding selected and winning doors)

    uniform_int_distribution<size_t> dist(0, candidates.size() - 1);    // C++ standard compliant
    size_t pickIndex = dist(rng);
    int losingDoorId = candidates[pickIndex].first;
    double losingProb = candidates[pickIndex].second;

    /* This is NOT safe thread */
    // size_t pickIndex = static_cast<size_t>(rand()) % candidates.size();;
    // int losingDoorId = candidates[pickIndex].first;
    // double losingProb = candidates[pickIndex].second;

    // compute probability to redistribute - 2:
    // one is for remove losing door, and one for the selected door
    double probsRedistributed = losingProb / static_cast<double>(leftDoorsProbs.size()  - 2);

    // redistribute the probability of losing door to other (non-selected) doors,
    //  including the winning door
    for (auto& door : leftDoorsProbs)
        if (door.first != losingDoorId && door.first != selectedDoor)
            door.second += probsRedistributed;

    // erase the losing door by finding its iterator
    for (auto iterator = leftDoorsProbs.begin();
            iterator != leftDoorsProbs.end();
            ++iterator)

        if (iterator -> first == losingDoorId) {
            leftDoorsProbs.erase(iterator);
            break;
        }
}
