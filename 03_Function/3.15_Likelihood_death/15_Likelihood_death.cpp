#include <iostream>     // for cin, cout, cerr
#include <string>       // for string class
#include <fstream>      // for file stream
#include <sstream>      // for istringstream
#include <vector>       // for vector container
#include <cstdlib>      // for rand & srand
#include <ctime>        // for time
#include <filesystem>   // for current_path
#include <windows.h>    // for Windows filesystem
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
namespace fs = std::filesystem;


const string PATH = "03_Function/3.15_Likelihood_death/Utilities/likelihood_death_2025.txt";
// File path to life death probability data.
// Path may change, according to the settings of `working directory` under Run menu in CLion.

const int MAX_AGE = 120;

string commaRemoval(const string& word);
// Precondition: word is a string that may contain commas
// Postcondition: Remove commas from word and return the result.
// This is required to use stoi and stod functions, as they
// do not handle commas in numbers.

bool readFile(const string& path, vector<double>& male, vector<double>& female);
// Precondition: path is a valid file path
// Postcondition: Reads the file and fills male and female vectors
// with death probabilities for each age.
// Returns true on success, false on failure.

int simulate(int age, char gender, vector<double>& male, vector<double>& female);
// Precondition: age is a non-negative integer or not greater than MAX_AGE
// Postcondition: Simulates the death age for a person of given age and gender

int main( ) {
    // Postcondition: Prompts user for age and gender,
    //                simulates the expected age of death,
    //                and displays the result.

    // seed the C library pseudorandom generator
    //      time(nullptr) returns system time
    //      cast result to uns int required by srand
    srand(static_cast<unsigned int>(time(nullptr)));
    int age;
    char gender;
    vector<double> male, female;

    cout << "Curret working directory: "
         << fs::current_path() << endl;

    if (!readFile(PATH, male, female)) return -1;

    cout << "Enter age:";
    cin >> age;
    cout << "Enter gender (M/F):";
    cin >> gender;

    age = simulate(age, gender, male, female);
    cout << "The expected age for this person is: "
         << age << endl;

    return 0;
}


string commaRemoval(const string &word) {
    string out;
    out.reserve(word.size());   // pre-allocate space for performance
    for (char ch : word)
        if (ch != ',')
            out.push_back(ch);  // push_back won't reallocate
    return out;                 //    until capacity exceeded (performance)
}

bool readFile(const string &path, vector<double> &male, vector<double> &female) {
    string line, text;
    ifstream inputStream;
    int age;
    double maleDeathProbability, femaleDeathProbability;

    inputStream.open(path);

    if (!inputStream) {
        cerr << "Error: unable to open file: `"
             << path  << "`\n";
        return false;
    }

    if (!getline(inputStream, line)) return false;  // skip header

    while (getline(inputStream, line)) {            // read rows

        if (line.empty()) continue;

        vector<string> lineFields;      // `container` of fields
        istringstream iss(line);        // create string stream to parse line

        while (iss >> text)
            lineFields.push_back(text);

        if (lineFields.size() < 5)      // at least 5 fields, or discard line
            continue;                   //    (women death prob is 5th field)

        try {
            age = stoi(lineFields[0]);  // field age
        } catch (...) {
            continue;
        }

        try {
            maleDeathProbability = stod(lineFields[1]); // field likelihood death men
        } catch (...) {
            maleDeathProbability = 0.0;
        }

        try {
            femaleDeathProbability = stod(lineFields[4]); // field likelihood death women
        } catch (...) {
            femaleDeathProbability = 0.0;
        }

        if (age < 0)
            continue;

        if (age >= static_cast<int>(male.size()) ) {
            male.resize(age + 1, 0.0);
            female.resize(age + 1, 0.0);
        }

        male[age] = maleDeathProbability;
        female[age] = femaleDeathProbability;
    }

    inputStream.close();

    return true;
}

int simulate(int age, char gender, vector<double>& male, vector<double>& female) {
    double deathReference;
    bool isMale = (gender == 'M' || gender == 'm');
    if (age < 0) age = 0;
    if (age > MAX_AGE) age  = MAX_AGE;

    do {
        deathReference = isMale ? male[age] : female[age];
        // [0,1) random number
        double randomGenerator = static_cast<double>(rand( ))
                                / (static_cast<double>(RAND_MAX) + 1.0);

        if (randomGenerator <= deathReference) return age;

    } while (age < MAX_AGE);

    return MAX_AGE;
}
