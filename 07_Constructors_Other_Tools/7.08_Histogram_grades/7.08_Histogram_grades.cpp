/* 5.07
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
*/

/*
Write a program that outputs a histogram of grades for an assignment given to
a class of students. The program should input each student’s grade as an integer
and store the grade in a vector. Grades should be entered until the user enters −1
for a grade. The program should then scan through the vector and compute the
histogram. In computing the histogram, the minimum value of a grade is 0, but
your program should determine the maximum value entered by the user. Output
the histogram to the console. See Programming Project 5.7 for information on how
to compute a histogram.
*/

#include <iostream>
#include <vector>

void input(std::vector<int>& grades);

void mergeSort(std::vector<int>& numbers, int start, int end);
void sort(std::vector<int>& numbers, int start, int mid, int end);


int main( )
{
	std::vector<int> grades;
	input(grades);
	mergeSort(grades, 0, grades.size() - 1);
	for (int grade : grades)
		std::cout << grade << ' ';
	std::cout << '\n';
	return 0;
}

void input(std::vector<int>& grades)
{
	int number;
	while(true)
	{
		std::cout << "Enter a number of grades (-1 to exit)\n";
		if (!(std::cin >> number))
		{
			std::cout << "Not a valid number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (number == -1)
			break;
		if (number < 0)
			continue;
		grades.push_back(number);
	}
}

void mergeSort(std::vector<int>& numbers, const int start, const int end)
{
	if (start >= end) return;
	const int mid = start + (end - start) / 2;
	mergeSort(numbers, start, mid);
	mergeSort(numbers, mid + 1, end);
	sort(numbers, start, mid, end);
}


void sort(std::vector<int>& numbers, const int start, const int mid, const int end)
{
	std::vector<int> supporting;
	int p1 = start;
	int p2 = mid + 1;
	while (p1 <= mid && p2 <= end)
	{
		if (numbers[p1] <= numbers[p2])
		{
			supporting.push_back(numbers[p1]);
			p1++;
		}
		else
		{
			supporting.push_back(numbers[p2]);
			p2++;
		}
	}
	while (p1 <= mid)
	{
		supporting.push_back(numbers[p1]);
		p1++;
	}
	while (p2 <= end)
	{
		supporting.push_back(numbers[p2]);
		p2++;
	}
	for (int idx = 0; idx < supporting.size(); idx++)
		numbers[start + idx] = supporting[idx];
}