#include <iostream>
using namespace std;

int main ( ) {
    float weight_kg;
    constexpr float MET_6_MPH = 10.0;
    constexpr float SPEED_AT_MET_10 = 6.0;
    float MET_current;
    constexpr float CALORIES_PER_MIN_FACTOR = 0.0175;
    constexpr int TIME_WORKOUT = 15;
    constexpr int FIRST_INTERVAL = 3;
    int current_time = 0;
    int speed_mph = 4;
    float total_calories = 0.0;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);

    cout << "Enter your weight (in kilograms):";
    cin >> weight_kg;

    current_time += FIRST_INTERVAL;

    if constexpr (TIME_WORKOUT > 0) {

        MET_current = (static_cast<float>(speed_mph) / SPEED_AT_MET_10) * MET_6_MPH;
        total_calories += CALORIES_PER_MIN_FACTOR * MET_current * weight_kg * FIRST_INTERVAL;
        speed_mph += 2;
    }

    int interval = 0;

    while (current_time < TIME_WORKOUT) {
        constexpr int NEXT_INTERVAL = 4;
        interval = min(NEXT_INTERVAL, TIME_WORKOUT - current_time);
        MET_current = (static_cast<float>(speed_mph) / SPEED_AT_MET_10) * MET_6_MPH;
        total_calories += CALORIES_PER_MIN_FACTOR * MET_current * weight_kg * static_cast<float>(interval);
        speed_mph += 2;
        current_time += interval;
    }

    cout << "Total calories burned: " << total_calories << " calories.\n";

    return 0;

}
