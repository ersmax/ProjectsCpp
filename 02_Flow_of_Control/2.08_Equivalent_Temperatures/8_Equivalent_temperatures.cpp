/*
Write a program that finds the temperature, as an integer, that is the same in both
Celsius and Fahrenheit. The formula to convert from Celsius to Fahrenheit is as
follows:
Fahrenheit = (9/5)*Celsius + 32
Your program should create two integer variables for the temperature in Celsius
and Fahrenheit. Initialize the temperature to 100 degrees Celsius. In a loop, decrement
the Celsius value and compute the corresponding temperature in Fahrenheit
until the two values are the same.
*/

#include <iostream>
using namespace std;

int main ( ) {
    int tempCelsius = 100, tempFahr;

    do {
        tempFahr = 9.0/5 * tempCelsius + 32;
        if (tempCelsius == tempFahr)
            break;
        tempCelsius--;
    } while (tempCelsius != tempFahr);

    cout << "We have the same temperature at "
         << tempCelsius << " C\n";
    return 0;
}