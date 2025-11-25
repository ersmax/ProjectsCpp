#include <iostream>
using namespace std;

double estimatedHeight(char gender, int motherHeight, int fatherHeight);
// Precondition: Gender is either M (male) or F (female).
// Postcondition: Return the esitmated height in inches

int main( ) {
    // Postcondition: Return the height of the child in foot and inches.
    char answer, gender;
    int feetFather, inchesFather, feetMother, inchesMother;
    int feetChild, inchesChild;

    do {
        // Input validation father
        while (true) {
            cout << "Enter the height on the father in feet and inches (separated by space):";
            cin >> feetFather >> inchesFather;
            if (feetFather < 5 || feetFather > 7 || inchesFather < 0 || inchesFather > 11)
                cerr << "Error: Feet must be between 5 and 7, inches between 0 and 11.\n";
            else
                break;
        }
        // Input validation mother
        while (true) {
            cout << "Enter the height on the mother in feet and inches (separated by space):";
            cin >> feetMother >> inchesMother;
            if (feetMother < 5 || feetMother > 7 || inchesMother < 0 || inchesMother > 11)
                cerr << "Error: Feet must be between 5 and 7, inches between 0 and 11.\n";
            else
                break;
        }
        // Input validation gender
        while (true) {
            cout << "Enter the gender of the child (M/F):";
            cin >> gender;
            if (gender != 'M' && gender != 'F')
                cerr << "Wrong gender value. Retry.\n";
            else
                break;
        }

        double result = estimatedHeight(gender,
                                        feetMother * 12 + inchesMother,
                                        feetFather * 12 + inchesFather);

        feetChild = static_cast<int>(result/12);
        inchesChild = static_cast<int>(result) % 12;

        cout << "Height of the child will be: "
             << feetChild << " feet and "
             << inchesChild << " inches.\n";
        cout << "Continue (y/Y)?";
        cin >> answer;
    } while (answer == 'y' && answer == 'Y');

    cout << endl;
    return 0;
}

double estimatedHeight(char gender, int motherHeight, int fatherHeight) {
    double hChild;

    if (gender == 'M')
        hChild = ((motherHeight * 13/12.0) + fatherHeight) / 2;
    else
        hChild = ((fatherHeight * 12/13.0) + motherHeight) / 2;

    return hChild;
}

