#include <iostream>
using namespace std;

int main ( ) {
    float initial_deposit, monthly_interest_rate, fixed_withdrawal;
    cout << "Enter the initial deposit amount:";
    cin >> initial_deposit;
    cout << "Enter the monthly interest rate:";
    cin >> monthly_interest_rate;
    cout << "Enter the fixed amount to be withdrawn every month:";
    cin >> fixed_withdrawal;

    // Check boundary condition
    if ((initial_deposit - fixed_withdrawal) * monthly_interest_rate
        >= fixed_withdrawal) {
        cout << "The interest earned every month is greater\n"
                "than or equal to the withdrawal amount.\n"
                "The amount can be utilized indefinitely.\n";
    } else {
        int months = 0;
        double balance = initial_deposit;

        while (balance - fixed_withdrawal > 0) {
            balance -= fixed_withdrawal;
            balance += balance * monthly_interest_rate;
            months++;
        }

        cout << "The amount can be used for " << months << " months.\n";
    }

    return 0;
}