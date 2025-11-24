#include <iostream>
using namespace std;

int main ( ) {
    float distance_km, time_min;
    constexpr float BASE_FARE = 2.0;
    constexpr float TIME_FARE_PER_MIN = 0.20;

    cout << "Enter the distance traveled (in kilometers):";
    cin >> distance_km;
    cout << "Enter the time taken (in minutes):";
    cin >> time_min;

    float fare = BASE_FARE * (distance_km > 0 ? min(distance_km, 2.0f) : 0);
    if (distance_km > 2) {
        constexpr float FARE_2_TO_8_KM = 0.50;
        fare += FARE_2_TO_8_KM * (min(distance_km, 8.0f) - 2);

        if (distance_km > 8) {
            constexpr float FARE_ABOVE_8_KM = 1.0;
            fare += FARE_ABOVE_8_KM * (distance_km - 8);
        }
    }
    fare += TIME_FARE_PER_MIN * (time_min > 0 ? time_min : 0);

    cout << "Total cab fare: $" << fare << endl;

    return 0;

}
