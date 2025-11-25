// define NDEBUG        // uncomment this line to disable assertions
#include <iostream>     // for cin, c-out
#include <string>       // for string
#include <limits>       // for numeric_limits, stream-size
#include <cassert>

constexpr int MINUTES_PER_DAY= 24 * 60;

void enterDate(std::string& startingDate, std::string& endingDate);
// Precondition: startingDate and endingDate are declared
// Postcondition: defines the values of startingDate and endingDate

bool validDate(const std::string& date);
// Precondition: date is a string
// Postcondition: returns true if date is valid military time in "HHMM" format

int differenceMinute(const std::string& startingDate, const std::string& endingDate);
// Precondition: startingDate and endingDate are valid military times in "HHMM" format
// Postcondition: returns the difference in minutes between startingDate and endingDate

int differenceMin(const std::string& startingDate, const std::string& endingDate);
// Precondition: startingDate and endingDate are valid military times in "HHMM" format
// Postcondition: returns the difference in minutes between startingDate and endingDate

int hourDate(const std::string& date);
// Precondition: date is a valid military time in "HHMM" format
// Postcondition: returns the hour part of the date

int minuteDate(const std::string& date);
// Precondition: date is a valid military time in "HHMM" format
// Postcondition: returns the minute part of the date

int main( ) {
    std::string startingDate, endingDate;
    enterDate(startingDate, endingDate);

    assert(startingDate.size() == 4 && endingDate.size() == 4);
    const int difference = differenceMinute(startingDate, endingDate);
    const int differenceAlternativeWay = differenceMin(startingDate, endingDate);
    if (difference == differenceAlternativeWay)
        std::cout << difference;
    std::cout << "\n";
    return 0;
}

void enterDate(std::string& startingDate, std::string& endingDate) {
    while (true) {
        std::cout << "Enter valid starting date (e.g. 1200 for 12:00)\n";
        if (!(std::cin >> startingDate)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // ignore next input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (startingDate == "-1") std::exit(-1);
        if (!validDate(startingDate)) {
            std::cout << "Invalid starting time. Try again.\n";
            continue;
        }
        break;
    }
    while (true) {
        std::cout << "Enter valid ending date";
        if (!(std::cin >> endingDate)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // ignore next input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (endingDate == "-1") std::exit(-1);
        if (!validDate(endingDate)) {
            std::cout << "Invalid starting time. Try again.\n";
            continue;
        }
        break;
    }
}

bool validDate(const std::string& date) {
    if (date.size() != 4)  // right length
        return false;
    for (const char c : date) // a number
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;

    const int value = std::stoi(date);
    const int hours = value / 100;
    const int minutes = value % 100;

    return (hours >= 0 && hours <= 23 &&
            minutes >= 0 && minutes <= 59);
}


int hourDate(const std::string& date) {
    const int time = std::stoi(date);
    return (time / 100);
}

int minuteDate(const std::string& date) {
    const int time = std::stoi(date);
    return (time % 100);
}

int differenceMinute(const std::string& startingDate, const std::string& endingDate) {
    const int startHour = hourDate(startingDate);
    const int endHour = hourDate(endingDate);
    const int startMinute = minuteDate(startingDate);
    const int endMinute = minuteDate(endingDate);

    int hourDiff = endHour - startHour;
    int minuteDiff = endMinute - startMinute;

    if (minuteDiff < 0) {
        minuteDiff += 60;
        --hourDiff;
    }
    if (hourDiff < 0)
        hourDiff += 24;

    return (hourDiff * 60 + minuteDiff);
}

int differenceMin(const std::string& startingDate, const std::string& endingDate) {
    const int startHour = hourDate(startingDate);
    const int endHour = hourDate(endingDate);
    const int startMinute = minuteDate(startingDate);
    const int endMinute = minuteDate(endingDate);

    const int startingMinute = startHour * 60 + startMinute;
    const int endingMinute = endHour * 60 + endMinute;

    int difference = endingMinute - startingMinute;
    if (difference < 0)
        difference += MINUTES_PER_DAY ;  // that is, a day passed.
    return difference;
}
