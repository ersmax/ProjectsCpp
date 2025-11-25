#include <iostream>
#include <cmath>
using namespace std;

int main ( ) {
    int numberOfStories;
    float basePriceFirstFloor;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Enter the number of stories in the building: ";
    cin >> numberOfStories;
    cout << "Enter the base price of apartments on the first floor: ";
    cin >> basePriceFirstFloor;


    cout << "\nFloor\tBase Price\tAmenities\tTaxes\t\tTotal Price\n";
    cout << "---------------------------------------------------------------\n";

    for (int floor = 1; floor <= numberOfStories; ++floor) {
        constexpr float TAX_RATE = 0.20,
                        AMENITY_RATE = 0.05;
        double basePrice = basePriceFirstFloor * pow(1.02, floor - 1);
        double amenities = basePrice * AMENITY_RATE;
        double taxes = (basePrice + amenities) * TAX_RATE;
        double totalPrice = basePrice + amenities + taxes;

        cout << floor << "\t"
             << basePrice << "\t"
             << amenities << "\t"
             << taxes << "\t"
             << totalPrice << endl;
    }

    return 0;
}