#include <iostream>
using namespace std;

int main() {
    int total_coupons;
    int candy_bars = 0, gumballs = 0, remaining_coupons = 0;

    cout << "Enter the number of coupons you have: ";
    cin >> total_coupons;

    candy_bars = total_coupons / 10;
    remaining_coupons = total_coupons % 10;
    gumballs = remaining_coupons / 3;

    cout << "You can get " << candy_bars << " candy bar(s) and "
         << gumballs << " gumball(s).\n";

    return 0;
}