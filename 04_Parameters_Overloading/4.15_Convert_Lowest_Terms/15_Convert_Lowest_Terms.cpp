#include <iostream>
#include <vector>
#include <limits>

void enterData(int& numerator, int& denominator);
// Precondition: numerator and denominator are declared
// Postcondition: defines the values of numerator and denominator

bool convertToLowestTerms(int& numerator, int& denominator);
// Precondition: denominator is not 0
// Postcondition: reduces numerator and denominator to the lowest terms

std::vector<int> findFactors(int number);
// Postcondition: returns a vector with the prime factors of number

void findPrimeFactorizationGCD(const int& numerator, const int& denominator, int& gcd);
// Postcondition: finds the GCD of numerator and denominator using prime factorization

int findEuclideanGCD(int numerator, int denominator);
// Postcondition: finds the GCD of numerator and denominator using the Euclidean algorithm

void showResults(const int& numerator, const int& denominator);
// Precondition: numerator and denominator are defined

int main( ) {
    int numerator, denominator;
    enterData(numerator, denominator);
    if (!convertToLowestTerms(numerator, denominator)) {
        std::cout << "Invalid input: denominator cannot be 0.\n";
        return -1;
    }

    showResults(numerator, denominator);
    std::cout << "\n";
    return 0;
}

void enterData(int& numerator, int& denominator) {
    while (true) {
        std::cout << "Enter numerator and denominator:";
        if (!(std::cin >> numerator >> denominator)) {
            std::cout << "Wrong numbers.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // ignore remaining input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
}

void showResults(const int& numerator, const int& denominator) {
    std::cout << numerator << "/" << denominator;
}

bool convertToLowestTerms(int& numerator, int& denominator) {
    if (denominator == 0)
        return false;
    if (numerator == 0) {
        denominator = 1;
        return true;
    }

    int gcd = 1;
    findPrimeFactorizationGCD(numerator, denominator, gcd);
    int euclideanGCD = findEuclideanGCD(numerator, denominator);
    std::cout << "Prime factorization GCD: " << gcd << "\n";
    std::cout << "Euclidean GCD: " << euclideanGCD << "\n";
    numerator /= gcd;
    denominator /= gcd;
    return true;
}

int findEuclideanGCD(int numerator, int denominator) {
    int gcd = 0;
    numerator = std::abs(numerator);
    denominator = std::abs(denominator);
    int remainder = numerator % denominator;
    while (remainder != 0) {
        numerator = denominator;
        denominator = remainder;
        remainder = numerator % denominator;
    }
    gcd = denominator;
    return gcd;
}


void findPrimeFactorizationGCD(const int& numerator, const int& denominator, int& gcd) {

    std::vector<int> factorsNumerator = findFactors(numerator);
    std::vector<int> factorsDenominator = findFactors(denominator);
    if (factorsNumerator.empty() || factorsDenominator.empty())
        return;

    size_t p1 = 0, p2 = 0;
    while (p1 < factorsNumerator.size() && p2 < factorsDenominator.size()) {
        if (factorsNumerator[p1] == factorsDenominator[p2]) {
            gcd *= factorsNumerator[p1];
            ++p1;
            ++p2;
        } else if (factorsNumerator[p1] < factorsDenominator[p2])
            ++p1;
        else
            ++p2;
    }
}


std::vector<int> findFactors(int number) {
    std::vector<int> factors = {};
    number = std::abs(number);
    if (number == 1 || number == 0)
        return factors;

    int divisor = 2;
    while (number > 1) {
        if (number % divisor == 0) {
            factors.push_back(divisor);
            number /= divisor;
            continue;
        }
        ++divisor;
    }
    return factors;
}
