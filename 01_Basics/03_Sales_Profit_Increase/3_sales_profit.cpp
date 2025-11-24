/*
An electronics company sees a 13% increase in sales from the previous year, making
27% more profit than the previous work. Write a program that takes the company’s
previous year’s sales and profit in millions as input and outputs the increase in sales
and profit in millions from the previous year. Use a variable declaration with the
modifier const to express the sales and profit increase.
*/
#include <iostream>
using namespace std;

int main( ) {
    float previous_sales, previous_profit;
    const float SALES_INCREASE_PERC = 0.13;  // 13%
    const float PROFIT_INCREASE_PERC = 0.27; // 27%

    cout << "Enter the previous year's sales (in millions $):";
    cin >> previous_sales;
    cout << "Enter the previous year's profit (in millions $):";
    cin >> previous_profit;

    cout << "Increase in sales: "
         << previous_sales * SALES_INCREASE_PERC << " million $\n"
         << "Increase in profit: "
         << previous_profit * PROFIT_INCREASE_PERC << " million $\n";

    return 0;
}