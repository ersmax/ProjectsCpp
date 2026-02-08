#include <iostream>
#include <vector>

void input(std::vector<int>& grades);
//   Postcondition: the vector grades contains the grades entered by the user, 
// and -1 is used to end the input.

void mergeSort(std::vector<int>& numbers, int start, int end);
//   Postcondition: the vector numbers is sorted in ascending order.
// This is a recursive implementation of merge sort, which is a divide and conquer algorithm.

void sort(std::vector<int>& numbers, int start, int mid, int end);
//   Postcondition: the vector numbers is sorted in ascending order from index start to end.
// There is a comparison between the left half of the array, start to mid, 
// and the right half of the array, mid + 1 to end.
// The sorted result is stored in a supporting vector, which is then copied back to numbers.

void count(const std::vector<int>& numbers, std::vector<int>& uniqueNumbers, 
		   std::vector<int>& frequencies);
//   Precondition: the vector numbers is ordered by ascending order
//   Postcondition: uniqueNumbers contains the unique numbers in numbers, and frequencies
// contains the frequency of each unique number in numbers. The size of uniqueNumbers
// and frequencies are the same, and the frequency of uniqueNumbers[idx] is frequencies[idx].

void print(const std::vector<int>& uniqueNumbers, const std::vector<int>& frequencies);
//   Postcondition: the histogram is printed to the console, where each line contains the frequency

void count2(std::vector<int>& numbers, std::vector<int>& frequencies);
//   Precondition: the vector numbers is ordered by ascending order
//   Postcondition: the vector numbers contains only unique numbers in the original vector, and frequencies
// contains the frequency of each unique number in the original vector.
// 	 A side note: erase takes O(n) and doing that for n numbers raise quadratic complexity
// This version reasons only with iterators, and does not use any index. 
// It is more efficient than count3, but less efficient than count.

void count3(std::vector<int>& numbers, std::vector<int>& frequencies);
//   Precondition: the vector numbers is ordered by ascending order
//   Postcondition: the vector numbers contains only unique numbers in the original vector, and frequencies
// contains the frequency of each unique number in the original vector.
// This version reasons with both iterators and indices, which is not a good practice.


int main( )
{
	std::vector<int> grades;
	std::vector<int> frequencies;
	std::vector<int> uniqueNumbers;

	input(grades);
	mergeSort(grades, 0, grades.size() - 1);
	count(grades, uniqueNumbers, frequencies);
	// count2(grades, frequencies);	// implementation with iterators, which modifies grades
	// count3(grades, frequencies);	// implementation with iterators and indices, which modifies grades
	print(uniqueNumbers, frequencies);

	std::cout << '\n';
	return 0;
}

void count(const std::vector<int>& numbers, 
		   std::vector<int>& uniqueNumbers, 
		   std::vector<int>& frequencies)
{
	if (numbers.empty())	return;
	uniqueNumbers.push_back(numbers[0]);
	frequencies.push_back(1);

	for (int idx = 1; idx < numbers.size(); ++idx)
	{
		if (numbers[idx] == uniqueNumbers.back())
			frequencies.back()++;
		else
		{
			uniqueNumbers.push_back(numbers[idx]);
			frequencies.push_back(1);
		}
	}
}

void count2(std::vector<int>& numbers, std::vector<int>& frequencies)
{
	if (numbers.empty())	return;
	std::vector<int>::iterator current = numbers.begin();
	frequencies.push_back(1);

	while (current + 1 != numbers.end())
	{
		//   If current value equals next,
		// erase the next value, and increment current freq
		if (*(current) == *(current + 1))
		{
			numbers.erase(current + 1);
			frequencies.back()++;
		}
		else
		{
			++current;
			frequencies.push_back(1);
		}
	}
}

void count3(std::vector<int>& numbers, std::vector<int>& frequencies)
{
	if (numbers.empty())	return;
	std::vector<int>::iterator current = numbers.begin();
	frequencies.push_back(1);
	int idx = 1;

	while (current + 1 != numbers.end())
	{
		if (numbers[idx] == numbers[idx - 1])
		{
			// better logic: numbers.erase(current + 1);
			current = numbers.erase(current);
			frequencies[idx - 1]++;
		}
		else
		{
			frequencies.push_back(1);
			++idx;
			++current;
		}
	}
}

void print(const std::vector<int>& uniqueNumbers, const std::vector<int>& frequencies)
{
	for (size_t idx = 0; idx < uniqueNumbers.size(); idx++)
		std::cout << frequencies[idx] << " grade(s) of " 
			      << uniqueNumbers[idx] << '\n';
}

void input(std::vector<int>& grades)
{
	int number;
	std::cout << "Enter a number of grades (-1 to exit)\n";
	while(true)
	{
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
