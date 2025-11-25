#include <iostream>
#include <cmath>
using namespace std;

double raise(double currentSalary, double priorSalary);
// Precondition: priorSalary is not zero
// Postcondition: returns the hike percentage

void futureRaise(double currentSalary, double salaryHike, int years);
// Precondition: years is a positive integer
// Postcondition: Displays the estimated salary for each year

double totalFutureRaise(double currentSalary, double salaryHike, int years);
// Precondition: years is a positive integer
// Postcondition: returns the total of future salaries,
//                given current salary, hike rate, and years to predict

void displayFutureRaise(int numberYears, double totalFutureRaise);
// Precondition: numberYears is a positive integer
// Postcondition: Displays the total of future salaries with the annuity

int main( ) {
    char answer;
    double currentYearSalary,
           lastYearSalary,
           salaryHike = -1,
           futureSalaries;
    int period;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    do {
        cout << "Enter current and last year salary "
             << "(separated by space):";
        cin >> currentYearSalary >> lastYearSalary;

        if (currentYearSalary <= 0 || lastYearSalary <= 0)
            cerr << "Error: Salaries cannot be negative.\n";
        else {
            salaryHike = raise(currentYearSalary, lastYearSalary);
            cout << "The salary hike is: " << salaryHike * 100 << "%.\n";

            while (true) {
                cout << "Enter the years you wish to predict the salary hike:";
                cin >> period;
                if (period > 0) break;
                cerr << "Error: Period must be a positive integer.\n"
                     << "Do you want to try again? (y/Y):";
                char cont;
                cin >> cont;
                if (cont != 'y' && cont != 'Y') return 0;
            }

            futureRaise(currentYearSalary, salaryHike, period);
            futureSalaries = totalFutureRaise(currentYearSalary, salaryHike, period);
            displayFutureRaise(period, futureSalaries);
        }

        cout << "Repeat? (y/Y):";
        cin >> answer;
    } while (answer == 'y' || answer == 'Y');

    return 0;
}

double raise(double currentSalary, double priorSalary) {
    return ((currentSalary - priorSalary) / priorSalary);
}

void futureRaise(double currentSalary, double salaryHike, int years) {
    double futureSalary = currentSalary;

    cout << "\nYear\tEstimated Salary\n";
    cout << "-------------------------\n";
    for (int idx = 1; idx <= years; ++idx) {
        futureSalary *= (1 + salaryHike);
        cout << idx << "\t" << futureSalary << endl;
    }
}

double totalFutureRaise(double currentSalary, double salaryHike, int years) {
    return (currentSalary * (1 + salaryHike) * (pow(1+salaryHike, years) - 1) / salaryHike) ;
}

void displayFutureRaise(int numberYears, double totalFutureRaise) {
    cout << "-------------------------\n";
    cout << "The sum of future salaries today for the next "
         << numberYears << " years is: "
         << totalFutureRaise << endl << endl;
}
