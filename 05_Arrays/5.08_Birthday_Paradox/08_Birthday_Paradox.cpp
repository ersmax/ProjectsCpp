#include <iostream>     // for std::cout
#include <random>       // for random number generation
#include <tuple>        // for std::tie

constexpr int MAX_PEOPLE = 50;
constexpr int MAX_TRIALS = 5000;

struct Birthday {
    int month;
    int day;
    bool operator == (const Birthday& other) const {
        return (std::tie(month, day) == std::tie(other.month, other.day));
    }
};

void askBirthday(Birthday people[], int nPeople);
//   Precondition: nPeople is the number of people in the room.
//   Postcondition: people[0] through people[nPeople - 1] have been
// assigned random birthdays.

void randomBirthday(Birthday& birthday);
//   Postcondition: birthday has been assigned a random month and day.

bool isSameBirthday(const Birthday people[], int nPeople);
//   Precondition: nPeople is the number of people in the room.
//   Postcondition: returns true if at least two people in the room
// share the same birthday; otherwise, returns false.

void showResults(const int sameBirthday[], int nPeople, int nTrials);
//   Precondition: sameBirthday[0] through sameBirthday[nPeople - 1] have been
// filled with the number of trials where at least two people shared birthday
// for room sizes 2 to nPeople.
//   Postcondition: shows on console the probability of two people sharing
// birthday for room sizes 2 to nPeople.

int main( ) {
    int trial = 0;
    int sameBirthday[MAX_PEOPLE - 1] = {};
    Birthday people[MAX_PEOPLE] = {};

    while (trial++ < MAX_TRIALS) {
        for (int peopleRoom = 2; peopleRoom <= MAX_PEOPLE; ++peopleRoom) {
            askBirthday(people, peopleRoom);
            if (isSameBirthday(people, peopleRoom))
                sameBirthday[peopleRoom - 2] += 1;
        }
    }

    showResults(sameBirthday, MAX_PEOPLE - 1, MAX_TRIALS);

    std::cout << "\n";
    return 0;
}

void askBirthday(Birthday people[], const int nPeople) {
    for (int idx = 0; idx < nPeople; ++idx)
        randomBirthday(people[idx]);
}

void randomBirthday(Birthday& birthday) {
    // use a single static seed the generator, so don't reseed every call
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> monthDistrib(1, 12);
    birthday.month = monthDistrib(rng);

    int maxDay = 31;
    if (birthday.month == 4 || birthday.month == 6 ||
        birthday.month == 9 || birthday.month == 11)
        maxDay = 30;
    else if (birthday.month == 2)
        maxDay = 28;

    std::uniform_int_distribution<int> dayDistrib(1, maxDay);
    birthday.day = dayDistrib(rng);
}

bool isSameBirthday(const Birthday people[], const int nPeople) {
    for (int p1 = 0; p1 < nPeople - 1; ++p1)
        for (int p2 = p1 + 1; p2 < nPeople; ++p2)
            if (people[p1] == people[p2]) return true;

    return false;
}

void showResults(const int sameBirthday[], const int nPeople, const int nTrials) {
    for (int idx = 0; idx < nPeople; ++idx) {
        std::cout << "For " << idx + 2 << " people, "
                  << "the probability of two birthdays is about "
                  << static_cast<double>(sameBirthday[idx]) / static_cast<double>(nTrials)
                  << "\n";
    }
}
