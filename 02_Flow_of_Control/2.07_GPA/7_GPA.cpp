#include <iostream>
using namespace std;

enum Grades {F, E = 5, D, C, B, A, S = 10, invalid};

Grades charToGrade(char gradeChar) {
    switch (gradeChar) {
        case 'S':
        case 's': return S;
        case 'a':
        case 'A': return A;
        case 'b':
        case 'B': return B;
        case 'c':
        case 'C': return C;
        case 'd':
        case 'D': return D;
        case 'e':
        case 'E': return E;
        case 'f':
        case 'F': return F;
        default:
            cerr << "Invalid grade. "
                    "Please enter a valid grade.\n"
                    "(S, A, B, C, D, E, F): ";
            return invalid;
    }
}

int main ( ) {
    int subjects;
    int sum = 0;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "Insert the number of subjects:";
    cin >> subjects;

    int idx = 0;
    while (idx++ < subjects) {
        cout << "Add the grade of the " << idx << " subject:";
        char gradeChar;
        cin >> gradeChar;
        Grades grade = charToGrade(gradeChar);
        while (grade == invalid) {
            cin >> gradeChar;
            grade = charToGrade(gradeChar);
        }
        sum += grade;
    }
    float avg = static_cast<float>(sum)/static_cast<float>(subjects);
    cout << "GPA: " << avg << endl;
    return 0;
}