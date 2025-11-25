#include <iostream>
#include <cstdlib>  // rand & srand
#include <ctime>    // srand
#include <iomanip>  // setw formatter for output
#include <limits>   // input validation
#include <string>   // string class
using namespace std;

constexpr int GOAL = 100;

int humanTurn(int humanTotalScore);
// Precondition: humanTotalScore is a non-negative integer
// Postcondition: performs a human turn and returns the turn total

int computerTurn(int computerTotalScore);
// Precondition: computerTotalScore is a non-negative integer
// Postcondition: performs a computer turn and returns the turn total

void printDivider();
// Postcondition: prints a divider line

void printScores(int humanScore, int computerScore);
// Precondition: humanScore and computerScore are non-negative integers
// Postcondition: prints the current scores of human and computer

int main( ) {
    // Postcondition: Simulates a game of Pig between a human and the computer.

    // seeds the C library pseudorandom generator
    // time(nullptr) returns current time
    // cast the result to unsigned required by srand
    srand(static_cast<unsigned>(time(nullptr)));

    int humanScore = 0, computerScore = 0;
    string dummy;

    cout << "Press enter to start the game.\n";
    getline(cin, dummy);

    while (true) {
        cout << "\n";
        printDivider();
        cout << setw(30) << left << "Player turn" << "\n";
        printDivider();

        humanScore += humanTurn(humanScore);
        printScores(humanScore, computerScore);
        if (humanScore >= GOAL) {
            cout << "\n" << setw(30) << left
                 << "Result: " << "Congrats, you won!\n";
            break;
        }

        cout << "\n";
        printDivider();
        cout << setw(30) << left << "Computer turn" << "\n";
        printDivider();

        computerScore += computerTurn(computerScore);
        printScores(humanScore, computerScore);
        if (computerScore >= GOAL) {
            cout << "\n" << setw(30) << left << "Game over. Computer won.\n";
            break;
        }
    }

    return 0;
}

int humanTurn(int humanTotalScore) {
    int roll, turnPoints = 0;
    char answer;

    while (true) {
        roll = rand( ) % 6 + 1;
        cout << setw(25) << left << "Face on the dice:"
             << setw(4) << right << roll <<  "\n";

        // Trivial case
        if (roll == 1) {
            cout << setw(15) << left << "Turn result:"
                 << setw(15) << right << "Points lost" << endl;

            cout << setw(25) << left << "Turn total:"
                 << setw(5) << right << 0 << "\n";

            return 0;
        }

        turnPoints += roll;
        cout << setw(25) << left << "Turn points:"
             << setw(4) << right << turnPoints << "\n"
             << setw(25) << left << "Total if held:"
             << setw(4) << right << (humanTotalScore + turnPoints) << "\n";
        printDivider();

        if (humanTotalScore + turnPoints >= GOAL)
            cout << setw(25) << left << "Note:" << "Congratulations, you reached " << GOAL << " points\n";

        // Input validation
        while (true) {
            cout << "Roll again (r) or hold (h)?";
            // Extract the next non-whitespace character,
            // discards everything up to the next newline \n.
            // In case of errors, clean the stream.
            if (!(cin >> answer)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Input error. Please enter \"r\" or \"h\"\n.";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (answer == 'r' || answer == 'R')
                break;
            if (answer == 'h' || answer == 'H' )
                return turnPoints;
            cerr << "Invalid input. Please enter \"r\" or \"h\".\n";
        }
    // Outer loop: continue rolling
    }
}

int computerTurn(int computerTotalScore) {
    int turnPoint = 0, roll;

    do {
        roll = rand() % 6 + 1;
        cout << setw(25) << left << "Computer rolled:"
             << setw(5) << right << roll << "\n";

        if (roll == 1) {
            cout << setw(15) << left << "Turn result:"
                 << setw(15) << right << "PC lost turn" << endl;

            cout << setw(15) << left << "Turn points:"
                 << setw(15) << right << 0 << '\n';

            cout << setw(15) << left << "Tot. points:"
                 << setw(15) << right << computerTotalScore << '\n';
            return 0;
        }

        turnPoint += roll;
    } while (turnPoint < 20 && computerTotalScore + turnPoint < GOAL);

    cout << setw(25) << left << "Turn points by computer:"
         << setw(4) << right << turnPoint << endl;
    cout << setw(25) << left << "Tot. points by computer:"
         << setw(4) << right << (turnPoint + computerTotalScore) << endl;
    printDivider();

    return turnPoint;
}

void printDivider() {
    cout << string(30, '=') << "\n";
}

void printScores(int humanScore, int computerScore) {
    printDivider();
    cout << setw(18) << left << "Player"
         << setw(12) << right << "Score" << "\n";

    printDivider();
    cout << setw(18) << left << "Human"
         << setw(12) << right << humanScore << "\n";
    cout << setw(18) << left << "Computer"
         << setw(12) << right << computerScore << "\n";

    printDivider();
}




