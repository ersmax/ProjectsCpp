// #define NDEBUG       // to disable assert statements
#include <array>        // for std::array
#include <iostream>     // for std::cin, std::cout
#include <string>       // for std::string
#include <limits>       // for std::numeric_limits
#include <cassert>      // for assert
#include <iomanip>      // for std::setw, std::setprecision, std::fixed, std::showpoint

constexpr int JUDGES = 3;
constexpr int PARAMETERS = 4;
const std::array<std::string, PARAMETERS> NAME_PARAMETERS = {
    "Technicality", "Expression", "Stage Utilization", "Energy level" };


void fillData(double score[][PARAMETERS], int nJudges);
//   Postcondition: The function reads scores from the user for each judge
// against all parameters. The scores are stored in the 2D array `score`

void computeJudgeAvg(const double score[][PARAMETERS], int nJudges,
                     double judgeAvg[], int numJudges);
//   Precondition: The function assumes that all scores in the array `score`
// are within the valid range of 1 to 10.
//   Postcondition: The function computes the average score given by each judge
// and stores the result in the array `judgeAvg`

void computeParameterAvg(const double score[][PARAMETERS], int nJudges,
                         double parameterAvg[], int nParameters);
//   Precondition: The function assumes that all scores in the array `score`
// are within the valid range of 1 to 10.
//   Postcondition: The function computes the average score for each parameter
// across all judges and stores the result in the array `parameterAvg`

double computeParticipantAvg(const double judgeAvg[], int nJudges);
//   Precondition: The function assumes that all averages in the array `judgeAvg`
// are within the valid range of 1 to 10.
//   Postcondition: The function computes and returns the overall average score
// for the participant based on the averages provided by each judge

void displayResults(const double score[][PARAMETERS], int nJudges,
                    const double judgeAvg[], int numJudges,
                    const double parameterAvg[], int numParameters,
                    double participantAvg);
//   Postcondition: The function displays the scores given by each judge,
// the average score for each judge, the average score for each parameter,
// and the overall average score for the participant

int main( ) {
    double score[JUDGES][PARAMETERS] = {};
    double judgeAvg[JUDGES] = {};
    double parameterAvg[PARAMETERS] = {};

    fillData(score, JUDGES);

    for (const double (&judge)[PARAMETERS] : score)
        for (const double singleScore : judge)
            assert((singleScore >= 1) && (singleScore <= 10));
    computeJudgeAvg(score, JUDGES, judgeAvg, JUDGES);
    computeParameterAvg(score, JUDGES, parameterAvg, PARAMETERS);
    double participantScore = computeParticipantAvg(judgeAvg, JUDGES);
    displayResults(score, JUDGES, judgeAvg, JUDGES, parameterAvg, PARAMETERS, participantScore);

    std::cout << "\n";
    return 0;
}

void fillData(double score[][PARAMETERS], const int nJudges) {
    double next;

    for (int judge = 0; judge < nJudges; ++judge) {

        for (int nParameter = 0; nParameter < PARAMETERS; ++nParameter) {
            std::cout << "Enter vote (1-10) for " << NAME_PARAMETERS[nParameter]
                      << " for judge " << judge + 1 << ":\n";

            while (true) {
                if (!(std::cin >> next)) {
                    std::cout << "Invalid value for " << NAME_PARAMETERS[nParameter]
                                  << ". Retry.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                // ignore remaining input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if ((next >= 1) && (next <= 10)) {
                    score[judge][nParameter] = next;
                    break;
                }
                std::cout << "Score for " << NAME_PARAMETERS[nParameter]
                           << " must be greater than (or equal) 1 and less than (or equal) 10\n";
            }
        }
    }
}

void computeJudgeAvg(const double score[][PARAMETERS], const int nJudges,
                    double judgeAvg[], const int numJudges) {

    for (int judge = 0; judge < numJudges; ++judge) {
        double sum = 0;
        for (int parameter = 0; parameter < PARAMETERS; ++parameter)
            sum += score[judge][parameter];

        const double avgJudge = sum / PARAMETERS;
        judgeAvg[judge] = avgJudge;
    }
}

void computeParameterAvg(const double score[][PARAMETERS], const int nJudges,
                         double parameterAvg[], const int nParameters) {

    for (int parameter = 0; parameter < nParameters; ++parameter) {
        double sum = 0;
        for (int judge = 0; judge < nJudges; ++judge)
            sum += score[judge][parameter];

        const double avgParameter = sum / nJudges;
        parameterAvg[parameter] = avgParameter;
    }
}

double computeParticipantAvg(const double judgeAvg[], const int nJudges) {
    double sum = 0;
    for (int judge = 0; judge < nJudges; ++judge)
        sum += judgeAvg[judge];
    return (sum / nJudges);
}

void displayResults(const double score[][PARAMETERS], int nJudges,
                    const double judgeAvg[], int numJudges,
                    const double parameterAvg[], int numParameters,
                    double participantAvg) {

    std::cout << std::fixed << std::showpoint << std::setprecision(1);

    std::cout << std::setw(8)   << "Judge"
              << std::setw(10)  << "Average"
              << std::setw(12)  << "Technical"
              << std::setw(12)  << "Expression"
              << std::setw(12)  << "Stage"
              << std::setw(12)  << "Energy" << "\n";

    for (int judge = 0; judge < nJudges; ++judge) {
        std::cout << std::setw(8)   << judge + 1
                  << std::setw(10)  << judgeAvg[judge];

        for (int parameter = 0; parameter < numParameters; ++parameter)
            std::cout << std::setw(12)  << score[judge][parameter];
        std::cout << "\n";
    }

    std::cout << std::setw(18)   << "Parameter avg =";
    for (int parameter = 0; parameter < numParameters; ++parameter)
        std::cout << std::setw(12) << parameterAvg[parameter];
    std::cout << "\n";

    std::cout << std::setw(18)   << "Participant avg = "
                                 << participantAvg << "\n";
}
