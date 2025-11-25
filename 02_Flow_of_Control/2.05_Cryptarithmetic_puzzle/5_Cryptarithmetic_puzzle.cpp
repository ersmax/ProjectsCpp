#include <iostream>
using namespace std;

int main ( ) {

    int countSolution = 0;
    // T
    for (int idxT = 0; idxT <= 9; idxT++) {
        // O
        for (int idxO = 0; idxO <= 9; idxO++) {
            if (idxO == idxT) continue;
            // G
            for (int idxG = 0; idxG <= 9; idxG++) {
                if (idxG == idxT || idxG == idxO) continue;
                // D
                for (int idxD = 0; idxD <= 9; idxD++) {
                    if (idxD == idxT || idxD == idxO || idxD == idxG) continue;

                    // Check if 4 * TOO == GOOD
                    int TOO = 100*idxT + 10*idxO + 1*idxO;
                    int GOOD = 1000*idxG + 100*idxO + 10*idxO + 1*idxD;

                    if ( 4 * TOO == GOOD ) {

                        countSolution++;
                        cout << countSolution << " solution found:\t";
                        cout << "T = " << idxT << ", "
                             << "O = " << idxO << ", "
                             << "G = " << idxG << ", "
                             << "D = " << idxD << endl;
                    }

                }
            }
        }
    }
    return 0;
}