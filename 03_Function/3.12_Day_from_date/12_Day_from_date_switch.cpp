#include <algorithm>    // for transform
#include <iostream>     // for cin, cout, cerr
#include <string>       // for string class
#include <cctype>       // for toupper
using namespace std;

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

int getMonthValue(int monthRaw, int year);
// Precondition: month is an integer between 1 and 12, year is a positive integer
// Postcondition: returns the month value for the given month and year,
// accounting for leap years

int convertMonth(const string& monthRaw);
// Precondition: monthRaw is a string representing the month name
// Postcondition: returns the integer value of the month (1-12), (1 = January, etc.)

int main( ) {
    // Postcondition: Prompts user for a date (e.g., July 4 2008)
    // and displays the corresponding day of the week.
    int dayOfMonth, year, monthValue, yearValue, centuryValue;
    int dayOfWeek;
    string month;

    cout << "Enter date (Month Day Year, for example: July 4 2008):";
    cin >> month >> dayOfMonth >> year;

    int monthInt = convertMonth(month);
    if (monthInt == -1) {
        cerr << "Error: Invalid month name.\n";
        return -1;
    }
    monthValue = getMonthValue(monthInt, year);
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

int getMonthValue(int month, int year) {
    switch (month) {
        // Month values based on the table provided by wikipedia.
        // Factor in leap years for Jan and Feb.
        case 1:  return isLeapYear(year) ? 6 : 0;
        case 2:  return isLeapYear(year) ? 2 : 3;
        case 3:  return 3;
        case 4:  return 6;
        case 5:  return 1;
        case 6:  return 4;
        case 7:  return 6;
        case 8:  return 2;
        case 9:  return 5;
        case 10: return 0;
        case 11: return 3;
        case 12: return 5;
        default: return -1; // Invalid month
    }
}

int convertMonth(const string& monthRaw) {
    static const string months[] = {
        "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
        "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
    };

    string month = monthRaw;
    transform(monthRaw.begin(), monthRaw.end(), month.begin(), ::toupper);

    for (int idx = 0; idx < 12; ++idx)
        if (month == months[idx])
            return (idx + 1);

    return -1; // Invalid month
}
