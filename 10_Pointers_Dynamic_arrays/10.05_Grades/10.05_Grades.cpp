/*
5.7 (Grades)
Generate a text-based histogram for a quiz given to a class of students. The quiz is
graded on a scale from 0 to 5. Write a program that allows the user to enter grades
for each student. As the grades are being entered, the program should count, using
an array, the number of 0s, the number of 1s, the number of 2s, the number of
3s, the number of 4s, and the number of 5s. The program should be capable of
handling an arbitrary number of student grades.
You can do this by making an array of size 6, where each array element is initialized
to zero. Whenever a zero is entered, increment the value in the array at index 0.
Whenever a one is entered, increment the value in the array at index 1, and so on,
up to index 5 of the array.
Output the histogram count at the end. For example, if the input grades are 3, 0,
1, 3, 3, 5, 5, 4, 5, 4, then the program should output
1 grade(s) of 0
1 grade(s) of 1
0 grade(s) of 2
3 grade(s) of 3
2 grade(s) of 4
3 grade(s) of 5

7.8 (Histogram of Grades)
Write a program that outputs a histogram of grades for an assignment given to
a class of students. The program should input each student’s grade as an integer
and store the grade in a vector. Grades should be entered until the user enters −1
for a grade. The program should then scan through the vector and compute the
histogram. In computing the histogram, the minimum value of a grade is 0, but
your program should determine the maximum value entered by the user. Output
the histogram to the console. See Programming Project 5.7 for information on how
to compute a histogram.
Output the histogram count at the end. For example, if the input grades are 3, 0,
1, 3, 3, 5, 5, 4, 5, 4, then the program should output
1 grade(s) of 0
1 grade(s) of 1
0 grade(s) of 2
3 grade(s) of 3
2 grade(s) of 4
3 grade(s) of 5

10.05
This programming project is based on Programming Projects 7.8 and 5.7. Write
a program that outputs a histogram of grades for an assignment given to a class of
students. The program should input each student’s grade as an integer and store
the grade in a vector. Grades should be entered until the user enters -1 for a grade.
The program should then scan through the vector and compute the histogram. In
computing the histogram, the minimum value of a grade is 0, but your program
should determine the maximum value entered by the user. Use a dynamic array to
store the histogram. Output the histogram to the console.

*/

#include <iostream>
#include <iomanip>

typedef int *IntPtr;

void addGrades(IntPtr& grades, int& capacity, int& nGrades);
int inputValidation();
void mergeSort(const IntPtr& number, int start, int end);
void sort(const IntPtr& number, int start, int mid, int end);
int countDifferent(const IntPtr& number, int size);
IntPtr countFrequencies(IntPtr& number, int& size, int differentNumbers);
//   Postcondition: change number and count freq
void printHistogram(const IntPtr& number, const IntPtr& frequencies, int size);

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
