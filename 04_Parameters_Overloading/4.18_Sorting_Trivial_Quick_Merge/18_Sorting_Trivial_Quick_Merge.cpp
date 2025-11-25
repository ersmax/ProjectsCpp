#include <iostream>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 rng(rd());

void trivialSort(int& a, int& b, int& c);
// Precondition: a, b, and c are integers
// Postcondition: sorts a, b, and c in ascending order

std::vector<int> quickSort(const std::vector<int>& numbers);
// Precondition: numbers is a vector of integers
// Postcondition: returns a new vector with the elements of numbers sorted in ascending order

void quickSortReference(std::vector<int>& numbers);
// Precondition: numbers is a vector of integers
// Postcondition: sorts numbers in ascending order in place

void quickSortInPlace(std::vector<int>& numbers, int low, int high);
// Precondition: numbers is a vector of integers
//               low and high are valid indices in numbers
// Postcondition: Helper function that sorts numbers in place using quicksort algorithm
//                (Choose pivot randomly, Hoare's partitioning scheme)

int main( ) {
    int a = 30, b = 10, c = 20;
    trivialSort(a, b, c);

    std::vector<int> numbers = {30, 10, -90, 3, 1, 89, 29, 7, -43, 28};
    std::cout  << "Quicksort (by copy): ";
    for (int element : quickSort(numbers))
        std::cout << element << " ";
    std::cout << "\n";
    std::cout << "Quicksort (by reference): ";
    quickSortReference(numbers);

    std::cout << "\n";
    return 0;
}

void trivialSort(int& a, int& b, int& c) {
    std::cout << "Trivial sort: ";
    if (a > b) std::swap(a, b);
    if (a > c) std::swap(a, c);
    if (b > c) std::swap(b, c);
    std::cout << a << " " << b << " " << c << "\n";
}

std::vector<int> quickSort(const std::vector<int>& numbers) {
    if (numbers.size() <= 1) return numbers;

    std::uniform_int_distribution<size_t> dist(0, numbers.size() - 1);
    size_t pivotIdx = dist(rng);
    int pivotValue = numbers[pivotIdx];

    std::vector<int> smaller, equal, larger;
    for (const int& element : numbers) {
        if (element > pivotValue)        larger.push_back(element);
        else if (element == pivotValue)  equal.push_back(element);
        else                             smaller.push_back(element);
    }
    std::vector<int> result = quickSort(smaller);
    result.insert(result.end(), equal.begin(), equal.end());
    std::vector<int> sortedLarge = quickSort(larger);
    result.insert(result.end(), sortedLarge.begin(), sortedLarge.end());
    return result;
}

void quickSortReference(std::vector<int>& numbers) {
    if (numbers.size() <= 1) return;
    quickSortInPlace(numbers, 0, static_cast<int>(numbers.size()) - 1);
    for (int number : numbers)
        std::cout << number << " ";
}

void quickSortInPlace(std::vector<int>& numbers, int low, int high) {
    // Hoare's algorithm
    if (low >= high) return;

    std::uniform_int_distribution<int> dist(low, high);
    size_t pivotIdx = dist(rng);
    int pivot = numbers[pivotIdx];

    int p1 = low;
    int p2 = high;

    while (p1 < p2) {
        while (numbers[p1] < pivot)
            ++p1;
        while (numbers[p2] > pivot)
            --p2;
        std::swap(numbers[p1], numbers[p2]);
    }
    quickSortInPlace(numbers, low, p2);
    quickSortInPlace(numbers, p2 + 1, high);
}
