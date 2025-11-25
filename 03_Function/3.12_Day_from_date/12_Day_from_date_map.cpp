#include <algorithm>    // for transform
#include <iostream>     // for cin, cout, cerr
#include <string>       // for string class
#include <cctype>       // for toupper
#include <map>          // for map
using namespace std;

const map<string, int> monthMap = {
    {"JANUARY", 0}, {"JANUARY_LEAP", 6},
    {"FEBRUARY", 3}, {"FEBRUARY_LEAP", 2},
    {"MARCH", 3},
    {"APRIL", 6},
    {"MAY", 1},
    {"JUNE", 4},
    {"JULY", 6},
    {"AUGUST", 2},
    {"SEPTEMBER", 5},
    {"OCTOBER", 0},
    {"NOVEMBER", 3},
    {"DECEMBER", 5}
};

const string days[] = { "Sunday", "Monday",
                        "Tuesday", "Wednesday",
                        "Thursday", "Friday",
                        "Saturday" };

bool isLeapYear(int year);
// Precondition: year is a positive integer
// Postcondition: returns true if year is a leap year, false otherwise

int getCenturyValue(int year);
// Precondition: year is a positive integer
// Postcondition: returns the century value for the given year

int getYearValue(int year);
// Precondition: year is a positive integer
// Postcondition: returns the year value for the given century (e.g. 2025 -> 25)

int getMonthValue(const string& monthRaw, int year);
// Precondition: month is a String (e.g., January), year is a positive integer
// Postcondition: returns the month value for the given month and year,
// accounting for leap years, by using the map provided as global constant.

int main( ) {
    // Postcondition: Prompts user for a date (e.g., July 4 2008)
    // and displays the corresponding day of the week.
    int dayOfMonth, year, monthValue, yearValue, centuryValue;
    int dayOfWeek;
    string month;

    cout << "Enter date (Month Day Year, for example: July 4 2008):";
    cin >> month >> dayOfMonth >> year;

    monthValue = getMonthValue(month, year);
    yearValue = getYearValue(year);
    centuryValue = getCenturyValue(year);

    dayOfWeek = (dayOfMonth + monthValue+ yearValue + centuryValue) % 7;
    cout << days[dayOfWeek] << ", "
         << month << " "
         << dayOfMonth << ", "
         << year << endl;
    return 0;
}

bool isLeapYear(int year) {
    return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

int getCenturyValue(int year) {
    int century = year / 100;
    int remainder = century % 4;
    return ((3 - remainder) * 2);
}

int getYearValue(int year) {
    int yearCentury = year % 100;
    return (yearCentury + yearCentury / 4);
}

int getMonthValue(const string& monthRaw, int year) {
    string month = monthRaw;

    transform(monthRaw.begin(), monthRaw.end(), month.begin(), ::toupper);

    if (isLeapYear(year) && (month == "JANUARY" || month == "FEBRUARY"))
        month += "_LEAP";

    auto iteratorMapMonth = monthMap.find(month);
    if (iteratorMapMonth != monthMap.end())
        return iteratorMapMonth -> second;

    return -1;
}
