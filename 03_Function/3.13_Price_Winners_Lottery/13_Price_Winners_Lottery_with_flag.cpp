#include <iostream>     // for cin, cout, cerr
#include <ctime>        // for time
#include <cstdlib>      // for rand & srand
using namespace std;

const int PARTICIPANTS = 25;
const int PRICES = 4;

void lotteryExtraction(int participants[], int winners[], bool choosen[], int poolSize, int nPrices);
// Precondition: participants[] is an array of integers representing the participants
//               poolSize is the number of participants in the pool
//               choosen[] is a boolean array to track chosen participants
//               nPrices is the number of prices to be assigned
// Postcondition: fills winners[] with the randomly selected winners' numbers
// Take advantage of Independence of events probability rule,
// use a boolean array to track chosen participants.
// This means that after selecting a winner, that participant cannot be selected again.

void settingParticipants(int participants[], int pool);
// Precondition: participants[] is an array of integers representing the participants
//               pool is the number of participants in the pool
// Postcondition: fills participants[] with participant numbers from 1 to tot participants.

void showWinners(int winners[], int prices);
// Precondition: winners[] is an array of integers representing the winners
//               prices is the number of prices to be assigned
// Postcondition: displays the number of the participants who won the prices.

int main( ) {
    int participants[PARTICIPANTS];
    int winners[PRICES];
    bool choosen[PARTICIPANTS] = {false};
    int pool = PARTICIPANTS;
    int prices = PRICES;

    // seeds the C library pseudorandom generator
    //      time(nullptr) returns current time
    //      cast result to unsigned required by srand
    srand((static_cast<unsigned int>(time(nullptr))));

    settingParticipants(participants, pool);
    lotteryExtraction(participants, winners, choosen, pool, prices);
    showWinners(winners, prices);

    return 0;
}

void settingParticipants(int participants[], int pool) {
    for (int idx = 0; idx < pool; ++idx)
        participants[idx] = idx + 1;
}


void lotteryExtraction(int participants[], int winners[], bool choosen[],
                       int poolSize, int nPrices) {
    int numberWinner;
    int idx = 0;

    // change logic to use a boolean array
    while (idx < nPrices) {
        numberWinner = rand( ) % poolSize;
        if (!choosen[numberWinner]) {
            choosen[numberWinner] = true;
            winners[idx++] = participants[numberWinner];
        }
    }
}

void showWinners(int winners[], int prices) {
    for (int idx = 0; idx < prices; ++idx)
        cout << "Price " << idx + 1
             << " winner is Participant n. " << winners[idx] << endl;
}
