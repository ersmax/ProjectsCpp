#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <cassert>
using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::pair;
using std::numeric_limits;
using std::streamsize;
using std::endl;
using std::swap;

constexpr int ITEMS = 4;

void addVoucherValue(double& voucherValue);
// Precondition: voucherValue is declared
// Postcondition: defines the value of voucherValue

void addItem(vector<pair<string, double>>& items);
// Precondition: items is declared
// Postcondition: adds an item (name, price) to items vector

void sortItem(vector<pair<string, double>>& items);
// Precondition: items vector is filled with items and has predefined size
// Postcondition: sorts items vector in descending order by price

void showItem(const vector<pair<string, double>>& items);
// Precondition: items vector is filled with items
// Postcondition: displays the items and their prices

void useVoucher(vector<pair<string, double>>&items,
                double& voucherValue, double& total);
// Precondition: items vector is filled with items
// Postcondition: deducts item prices from voucherValue
//                until voucherValue is less than the cheapest item
//                updates total with the sum of prices of items redeemed

void showTotalBalance(double voucherValue, double total);
// Precondition: voucherValue is greater than or equal to 0
// Postcondition: displays the total value of items redeemed
//                and the voucher balance left

int main( ) {
    vector<pair<string, double>> items;
    double voucherValue, total = 0;

    addVoucherValue(voucherValue);
    for (int idx = 0; idx < ITEMS; idx++)
        addItem(items);

    assert(items.size() == ITEMS);
    sortItem(items);

    showItem(items);
    useVoucher(items, voucherValue, total);
    cout << "Items redeemed:\n";
    showItem(items);

    assert(voucherValue >= 0);
    showTotalBalance(voucherValue, total);

    return 0;
}


void addVoucherValue(double& voucherValue) {
    while (true) {
        cout << "Enter the value of voucher:";
        while (!(cin >> voucherValue)) {
            cout << "Invalid Input. Enter a number:";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // discard extra tokens
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (voucherValue >= 0)
            break;
        cout << "Invalid amount. ";
    }
    cout << "Voucher value: " << voucherValue << endl;
}

void addItem(vector<pair<string, double> >& items) {
    string name;
    double price;

    while (true) {
        cout << "Enter the name and price of item:";
        while (!(cin >> name >> price)) {
            cout << "Invalid input. Enter valid name and price:";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        // discard extra tokens
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        if (price >= 0) {
            items.emplace_back(name, price);
            break;
        }
        cout << "Invalid price.\n";
    }
    cout << "Item " << items.back().first << " added"
         << " (p: " << items.back().second << ")\n";
}

void sortItem(vector<pair<string, double> >& items) {
    for (size_t i = 0; i < items.size(); i++) {
        size_t idxMaxValue = i;

        for (size_t j = i + 1; j < items.size(); j++)
            if (items[idxMaxValue].second < items[j].second)
                idxMaxValue = j;

        if (idxMaxValue != i)
            swap(items[i], items[idxMaxValue]);
    }
}

void showItem(const vector<pair<string, double>>& items) {
    for (const pair<string, double>& item : items)
        cout << item.first << " price: " << item.second << endl;
}

void useVoucher(vector<pair<string, double> >& items,
                double& voucherValue, double& total) {
    total = 0;

    // use iterator to change the items vector
    for (auto iterator = items.begin(); iterator != items.end();)
        if (voucherValue >= iterator->second) {
            total += iterator->second;
            voucherValue -= iterator->second;
            ++iterator;
        } else
            iterator = items.erase(iterator);
}

void showTotalBalance(const double voucherValue, const double total) {
    cout << "Total value items redeemed: " << total << endl;
    cout << "Voucher value left (not reedeemed): " << voucherValue << endl;
}
