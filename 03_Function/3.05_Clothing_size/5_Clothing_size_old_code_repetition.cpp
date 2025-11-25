#include <iostream>
using namespace std;

const float HAT_CONSTANT = 2.9f,
            JACKET_CONSTANT = 288.0f,
            JACKET_OFFSET = 0.125f,
            WAIST_CONSTANT = 5.7f,
            WAIST_OFFSET = 0.1f;

float hatSize(int weight, int heightFeet, int heightInches);
// Precondition: weight, heightFeet, and heightInches are positive integers
// Postcondition: returns the hat size in inches

float jacketSize(int weight, int heightFeet, int heightInches, int age);
// Precondition: weight, heightFeet, heightInches, and age are positive integers
// Postcondition: returns the jacket size in inches

float waistSize(int weight, int age);
// Precondition: weight and age are positive integers
// Postcondition: returns the waist size in inches

bool errorHandlingHeight(int heightFeet, int heightInches);
// Precondition: heightFeet and heightInches are integers
// Postcondition: returns true if height is within a reasonable range
//                (5 feet to 8 feet, and 0 to 11 inches); false otherwise

bool errorHandlingWeight(int weight);
// Precondition: weight is an integer
// Postcondition: returns true if weight is within a reasonable range
//                (80 to 400 pounds); false otherwise

bool errorHandlingAge(int age);
// Precondition: age is an integer
// Postcondition: returns true if age is within a reasonable range
//                (0 to 120 years); false otherwise

int main( ) {
    // Postcondition: Prompts user for height, weight, and age,
    //                then displays the hat, jacket, and waist sizes.
    int heightFeet, heightInches, age, weight;
    float sizeHat, sizeJacket, sizeWaist;
    char answer = 'y';

    do {
        cout << "Enter the height in feet and in inches\n"
                "separated by a space:";
        cin >> heightFeet >> heightInches;

        if (!errorHandlingHeight(heightFeet, heightInches)) {
            cerr << "Incorrect height. Retry (y/Y)?";
            cin >> answer;
            if (answer != 'y' && answer != 'Y')
                return -1;
        } else {
            break;
        }
    } while (answer == 'y' || answer == 'Y');

    do {
        cout << "Enter the weight (in pounds):";
        cin >> weight;

        if (!errorHandlingWeight(weight)) {
            cerr << "Incorrect weight. Retry (y/Y)?";
            cin >> answer;
            if (answer != 'y' && answer != 'Y')
                return -1;
        } else {
            break;
        }
    } while (answer == 'y' || answer == 'Y');

    do {
        cout << "Enter the age:";
        cin >> age;
        if (!errorHandlingAge(age)) {
            cerr << "Incorrect age. Retry (y/Y)?";
            cin >> answer;
            if (answer != 'y' && answer != 'Y')
                return -1;
        } else {
            break;
        }
    } while (answer == 'y' || answer == 'Y');

    sizeHat = hatSize(weight, heightFeet, heightInches);
    sizeJacket = jacketSize(weight, heightFeet, heightInches, age);
    sizeWaist = waistSize(weight, age);

    cout << "Hat size: " << sizeHat << endl
         << "Jacket size: " << sizeJacket << endl
         << "Waist size: " << sizeWaist << endl;

    return 0;
}

bool errorHandlingHeight(int heightFeet, int heightInches) {
    if (heightFeet < 5 || heightFeet > 8 || heightInches < 0 || heightInches > 11)
        return false;
    return true;
}

bool errorHandlingWeight(int weight) {
    if (weight < 80 || weight > 400)
        return false;
    return true;
}

bool errorHandlingAge(int age) {
    if (age < 0 || age > 120)
        return false;
    return true;
}

float hatSize(int weight, int heightFeet, int heightInches) {
    float height;

    height = heightFeet * 12.0f + heightInches;
    return ((weight / height) * HAT_CONSTANT);
}

float jacketSize(int weight, int heightFeet, int heightInches, int age) {
    int height;
    float size;

    height = heightFeet * 12 + heightInches;
    size = (height * weight) / JACKET_CONSTANT;
    if (age > 30)
        size += ((age - 30) / 10.0f) * JACKET_OFFSET;

    return size;
}

float waistSize(int weight, int age) {
    float size;

    size = weight / WAIST_CONSTANT;
    if (age > 28)
        size += ((age - 28) / 2.0f) * WAIST_OFFSET;

    return size;
}
