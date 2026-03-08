#include <iostream>
#include <iomanip>

typedef int *IntPtr;

void addGrades(IntPtr& grades, int& capacity, int& nGrades);
//   Precondition: grades is a dynamic array of integers, 
// capacity is the size of the array, and nGrades is the number of grades currently stored in the array.
//   Postcondition: the user is prompted to enter grades, which are stored in the dynamic array grades.
// nGrades is updated to reflect the number of grades entered, and capacity is updated if the array needs to be resized.
// The rule of resizing is twice the size of the current array.

int inputValidation();
//   Postcondition: the user is prompted to enter an integer, which is returned by the function.

void mergeSort(const IntPtr& number, int start, int end);
//   Precondition: number is a dynamic array of integers, 
// and start and end are the indices of the first and last elements of the array, respectively.
//   Postcondition: the dynamic array number is sorted in ascending order from index start to end using the merge sort algorithm.

void sort(const IntPtr& number, int start, int mid, int end);
//   Precondition: number is a dynamic array of integers, 
// and start, mid, and end are the indices of the first, middle, and last elements of the array, respectively.
//   Postcondition: the dynamic array number is sorted in ascending order from index start to end, 
// given that the left half of the array, from index start to mid, 
// and the right half of the array, from index mid + 1 to end, are already sorted respectively.

int countDifferent(const IntPtr& number, int size);
//   Precondition: number is a dynamic array of integers, and size is the number of elements in the array.
//   Postcondition: the number of different integers in the array is returned by the function.

IntPtr countFrequencies(IntPtr& number, int& size, int differentNumbers);
//   Precondition: number is a dynamic array of integers, size is the number of elements in the array,
// differentNumbers is the number of different integers in the array, and the array is sorted in ascending order.
//   Postcondition: a new dynamic array is returned by the function, which contains the frequency of each different integer in the original array.
// Moreover, the original array number is modified to contain only the different integers, 
// and size is updated to reflect the number of different integers in the array.

void printHistogram(const IntPtr& number, const IntPtr& frequencies, int size);
//   Precondition: number is a dynamic array of integers, frequencies is a dynamic array of integers, 
// and size is the number of elements in both arrays.
//   Postcondition: the histogram is printed to the console, where each line contains the frequency of a grade and the grade itself.

int main( )
{
	int nGrades = 0;
	int capacity = 10;
	IntPtr grades = new int[capacity];
	addGrades(grades, capacity, nGrades);
	mergeSort(grades, 0, nGrades - 1);

	// after countFrequencies executes, nGrades = differentGrades
	const int differentGrades = countDifferent(grades, nGrades);
	const IntPtr frequencies = countFrequencies(grades, nGrades, differentGrades);

	printHistogram(grades, frequencies, nGrades);
	delete [] grades;
	delete [] frequencies;

	std::cout << '\n';
	return 0;
}

IntPtr countFrequencies(IntPtr& number, int& size, const int differentNumbers)
{
	if (size == 0)	return new int[0];
	
	const IntPtr newGrades = new int[differentNumbers];
	const IntPtr frequencies = new int[differentNumbers];

	int uniqueIdx = 0;
	newGrades[uniqueIdx] = number[0];
	frequencies[uniqueIdx] = 1;

	for (int idx = 1; idx < size; idx++)
	{
		if (number[idx] == newGrades[uniqueIdx])
			frequencies[uniqueIdx]++;
		else
		{
			uniqueIdx++;
			newGrades[uniqueIdx] = number[idx];
			frequencies[uniqueIdx] = 1;
		}
	}
	size = uniqueIdx + 1;
	delete [] number;
	number = newGrades;
	return frequencies;
}

void mergeSort(const IntPtr& number, const int start, const int end)
{
	if (end - start <= 0) return;
	const int mid = start + (end - start) / 2;
	mergeSort(number, start, mid);
	mergeSort(number, mid + 1, end);
	sort(number, start, mid, end);
}

void sort(const IntPtr& number, const int start, const int mid, const int end)
{
	const IntPtr temp = new int[end - start + 1];
	int idxTemp = 0;
	int p1 = start;
	int p2 = mid + 1;
	while (p1 <= mid && p2 <= end)
	{
		if (number[p1] <= number[p2])
		{
			temp[idxTemp++] = number[p1];
			p1++;
		} else {
			temp[idxTemp++] = number[p2];
			p2++;
		}
	}
	while (p1 <= mid)
	{
		temp[idxTemp++] = number[p1];
		p1++;
	}
	while (p2 <= end)
	{
		temp[idxTemp++] = number[p2];
		p2++;
	}
	
	for (int idx = 0; idx < end - start + 1; idx++)
		number[start + idx] = temp[idx];
	
	delete [] temp;
}

void addGrades(IntPtr& grades, int& capacity, int& nGrades)
{
	std::cout << "Enter grades (-1 to finish)\n";
	while (true)
	{
		if (nGrades == capacity)
		{
			const IntPtr newGrades = new int[capacity * 2];
			for (int idx = 0; idx < capacity; idx++)
				newGrades[idx] = grades[idx];
			delete [] grades;
			grades = newGrades;
			capacity *= 2;
		}
		const int grade = inputValidation();
		if (grade == -1)	break;
		if (grade >= 0)
			grades[nGrades++] = grade;
	}
}

int countDifferent(const IntPtr& number, const int size)
{
	if (size == 0)	return 0;
	
	int counter = 1;
	for (int idx = 1; idx < size; idx++)
		if (number[idx] != number[idx-1])
			counter++;

	return counter;
}

void printHistogram(const IntPtr& number, const IntPtr& frequencies, const int size)
{
	for (int idx = 0; idx < size; idx++)
		std::cout << std::setw(3) << frequencies[idx] << " grade(s) of " << number[idx] << '\n';
}

int inputValidation()
{
	int number;
	while (true)
	{
		if (!(std::cin >> number))
		{
			std::cerr << "Not a valid number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		return number;
	}
}
