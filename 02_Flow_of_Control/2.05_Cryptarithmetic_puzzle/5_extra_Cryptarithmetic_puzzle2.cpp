/*
Here is an
extra problem:
SEND + MORE = MONEY
A solution to the puzzle is S = 9, R = 8, O = 0, M = 1, Y = 2, E = 5, N = 6, D = 7.
Output the values for the letters that satisfy the equation.
*/
#include <iostream>
using namespace std;

int main ( ) {
    int countSolution = 0;
    // D
    for (int idxD = 0; idxD <= 9; idxD++) {
        // E
        for (int idxE = 0; idxE <= 9; idxE++) {
            if (idxE == idxD) continue;
            // M
            for (int idxM = 1; idxM <= 9; idxM++) {
                if (idxM == idxD || idxM == idxE) continue;
                // N
                for (int idxN = 0; idxN <= 9; idxN++) {
                    if (idxN == idxD || idxN == idxE || idxN == idxM) continue;
                    // O
                    for (int idxO = 0; idxO <= 9; idxO++) {
                        if (idxO == idxD || idxO == idxE || idxO == idxM || idxO == idxN) continue;
                        // R
                        for (int idxR = 0; idxR <= 9; idxR++) {
                            if (idxR == idxD || idxR == idxE || idxR == idxM || idxR == idxN || idxR == idxO) continue;
                            // S
                            for (int idxS = 1; idxS <= 9; idxS++) {
                                if (idxS == idxD || idxS == idxE || idxS == idxM || idxS == idxN || idxS == idxO || idxS == idxR) continue;
                                // Y
                                for (int idxY = 0; idxY <= 9; idxY++) {
                                    if (idxY == idxD || idxY == idxE || idxY == idxM || idxY == idxN || idxY == idxO || idxY == idxR || idxY == idxS) continue;

                                    int SEND = 1000 * idxS + 100 * idxE + 10 * idxN + 1 * idxD;
                                    int MORE = 1000 * idxM + 100 * idxO + 10 * idxR + 1 * idxE;
                                    int MONEY = 10000 * idxM + 1000 * idxO + 100 * idxN + 10 * idxE + 1 *idxY;

                                    if (SEND + MORE == MONEY) {
                                        countSolution++;
                                        cout << "Solution " << countSolution << ": ";
                                        cout << "S=" << idxS << ", E=" << idxE << ", N=" << idxN
                                             << ", D=" << idxD << ", M=" << idxM << ", O=" << idxO
                                             << ", R=" << idxR << ", Y=" << idxY << endl;

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

