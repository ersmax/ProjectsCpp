#include <iostream>
using namespace std;

int main( ) {
    double amount_needed;
    double annual_interest_rate;
    int duration_months;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Enter the amount you need to receive:";
    cin >> amount_needed;
    cout << "Enter the annual interest rate (as a percentage, e.g., 15 for 15%):";
    cin >> annual_interest_rate;
    cout << "Enter the duration of the loan in months:";
    cin >> duration_months;

    double duration_years = duration_months/12.0;
    annual_interest_rate /= 100.0;

    double nominal_value = amount_needed / (1 - (annual_interest_rate * duration_years));
    double monthly_payment = nominal_value / (duration_months);

    cout << "The required face value of the loan is: $" << nominal_value << endl;
    cout << "The monthly payment will be: $" << monthly_payment << endl;

    return 0;
}
