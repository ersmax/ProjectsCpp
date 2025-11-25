#include <iostream>     // for std::cout, std::cin
#include <limits>       // for std::numeric_limits
#include <string>       // for std::string

constexpr int CLASS_SIZE = 100;
constexpr int N_GRADES = 6;

void registerGrades(int grades[], int classSize, int& nStudents,
                    int countGrades[], int nGrades);
//   Precondition: classSize is the declared size of the array `grades`
//   Postcondition: nStudents is the number of grades entered (<= classSize).
// grades[0] through grades[nStudents - 1] have been filled with
// integers read from the keyboard in the range 0 to 5.
// countGrades[0] through countGrades[nGrades - 1] contain
// the count of each grade entered.

bool validGrade(const std::string& result, int& grade);
//   Precondition: result is the string entered by the user.
//   Postcondition: If result represents a valid integer grade in the range 0 to 5,
// then grade is set to that integer value and the function returns true.
// Otherwise, the function returns false. Also validates that the entire string
// is a valid integer.

void showGrades(int countGrades[], int nGrades);
//   Precondition: countGrades[0] through countGrades[nGrades - 1] have nonnegative values.
//   Postcondition: A text histogram is displayed showing the count of each grade
// from 0 to nGrades - 1.

int main( ) {
    int grades[CLASS_SIZE] = {};
    int countGrades[N_GRADES] = {};
    int nStudents = 0;

    registerGrades(grades, CLASS_SIZE, nStudents, countGrades, N_GRADES);
    showGrades(countGrades, N_GRADES);

    std::cout << "\n";
    return 0;
}

void registerGrades(int grades[], int classSize, int& nStudents,
                    int countGrades[], int nGrades) {

    int student = 0;
    std::string result;

    while(student < classSize) {
        std::cout << "Enter result (0-5) for student #" << student + 1
                  << " (or type `end` to terminate):\n";

        if (!(std::cin >> result)) {
            std::cout << "Invalid value. Retry.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // consume rest of the line
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (result == "end") break;

        int grade;
        if (validGrade(result, grade)) {
            grades[student++] = grade;
            ++countGrades[grade];
        }
    }
    nStudents = student;
}

bool validGrade(const std::string& result, int& grade) {
    try {
        std::size_t positionFirstChar = 0;
        grade = std::stoi(result, &positionFirstChar);
        if (positionFirstChar != result.size()) {
            std::cout << "Invalid grade. Retry\n";
            return false;
        }
    } catch (const std::invalid_argument&) {
        std::cout << "Not a number. Retry\n";
        return false;
    } catch (const std::out_of_range&) {
        std::cout << "Number out of range. Retry\n";
        return false;
    }
    return (grade >= 0 && grade <= 5);
}

void showGrades(int countGrades[], int nGrades) {
    for (int grade = 0; grade < nGrades; ++grade)
        std::cout << countGrades[grade] << " grade(s) of "
                  << grade << "\n";
}
