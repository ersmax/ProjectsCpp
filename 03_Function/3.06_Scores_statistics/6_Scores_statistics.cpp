#include <iostream>
#include <cmath>
using namespace std;

double averageScore(double score1, double score2, double score3, double score4);
// Precondition: score1, score2, score3, and score4 are numbers
// Postcondition: returns the average of the four scores

double standardDeviation(double score1, double score2, double score3, double score4);
// Precondition: score1, score2, score3, and score4 are numbers
// Postcondition: returns the standard deviation of the four scores

void showStatistics(double averageScores, double sdScores);
// Precondition: averageScores and sdScores are computed and valid values
// Postcondition: Displays the average and standard deviation of the scores

int main( ) {
    // Postcondition: Prompts user for four scores, then displays
    //                the average and standard deviation of the scores.
    double score1, score2, score3, score4,
           averageScores, sdScores;
    char answer;

    do {
        cout << "Enter the four scores\n "
                "separated by a space:";
        cin >> score1 >> score2 >> score3 >> score4;

        averageScores = averageScore(score1, score2, score3, score4);
        sdScores = standardDeviation(score1, score2, score3, score4);
        showStatistics(averageScores, sdScores);

        cout << "Repeat (y/Y)?";
        cin >> answer;

    } while (answer == 'y' || answer == 'Y');

    return 0;
}

double averageScore(double score1, double score2, double score3, double score4) {
    return (score1 + score2 + score3 + score4) / 4.0;
}

double standardDeviation(double score1, double score2, double score3, double score4) {
    double average, sumSquaredDeviations = 0;

    average = averageScore(score1, score2, score3, score4);
    sumSquaredDeviations = pow((score1 - average),2)
                           + pow((score2 - average),2)
                           + pow((score3 - average), 2)
                           + pow((score4 - average), 2);

    return (sqrt(sumSquaredDeviations / 4.0));
}

void showStatistics(double averageScores, double sdScores) {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "The average of scores is:"
         << averageScores << endl
         << "The standard deviation is: "
         << sdScores << endl;
}


