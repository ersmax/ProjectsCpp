/*
In an ancient land, the beautiful princess Eve had many suitors.She decided on
the following procedure to determine which suitor she would marry.First, all of
the suitors would be lined up one after the other and assigned numbers.The first
suitor would be number 1, the second number 2, and so on up to the last suitor,
number n. Starting at the first suitor she would then count three suitors down
the line (because of the three letters in her name) and the third suitor would be
eliminated from winning her hand and removed from the line. Eve would then
continue, counting three more suitors, and eliminating every third suitor. When
she reached the end of the line she would continue counting from the beginning.
For example, if there were six suitors then the elimination process would proceed
as follows:
123456 initial list of suitors, start counting from 1
12456 suitor 3 eliminated, continue counting from 4
1245 suitor 6 eliminated, continue counting from 1
125 suitor 4 eliminated, continue counting from 5
15 suitor 2 eliminated, continue counting from 5
1 suitor 5 eliminated, 1 is the lucky winner
Write a program that uses a vector to determine which position you should stand
in to marry the princess if there are n suitors. You will find the following function
from the Vector class useful:
v.erase(iter);
// Removes element at position iter
For example, to use this function to erase the fourth element from the beginning
of a vector variable named theVector, use
theVector.erase(theVector.begin( ) + 3);
The number 3 is used because the first element in the vector is at index position 0.
*/

#include <iostream>
#include <vector>

constexpr int POSITION = 3;

int input();
//  Postcondition: Asks the user for the number of suitors and returns it.
void createContenders(std::vector<int>& suitors, int pool);
//  Precondition: pool is the number of suitors, suitors is an empty vector.
//  Postcondition: Fills the vector suitors with numbers from 1 to pool.
void showRooster(const std::vector<int>& suitors);
//  Postcondition: Displays the list of suitors.
int selectContender(std::vector<int>& suitors);
//  Precondition: suitors is a vector filled with the suitors' numbers.
//  Postcondition: Eliminates suitors according to the rules and returns the
// number of the winning suitor.

int main( )
{
	std::vector<int> suitors;
	createContenders(suitors, input());
	showRooster(suitors);
	std::cout << "The contender is: " << selectContender(suitors);
	
	std::cout << '\n';
	return 0;
}

int input()
{
	int number;
	while (true)
	{
		std::cout << "Enter a number of suitor:\n";
		if (!(std::cin >> number))
		{
			std::cout << "Wrong input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (number > 0)
			return number;
		std::cout << "Suitors must be at least one\n";
	}
}

void createContenders(std::vector<int>& suitors, const int pool)
{
	for (int idx = 1; idx <= pool; idx++)
		suitors.push_back(idx);
}

void showRooster(const std::vector<int>& suitors)
{
	std::cout << "Contenders: ";
	for (const int suitor : suitors)
		std::cout << suitor << " ";
	std::cout << '\n';
}

int selectContender(std::vector<int>& suitors)
{
	// .begin() returns an iterator pointing to the first element in the vector.
	std::vector<int>::iterator current = suitors.begin();
	while (suitors.size() > 1)
	{
		//  count POSITION - 1 times to get to the POSITION-th suitor
		for (int idx = 1; idx < POSITION; idx++)
		{
			++current;
			if (current == suitors.end())
				current = suitors.begin();
		}
		//   .erase() returns an iterator pointing to the next element.
		// The original iterator passed becomes invalid.
		//   .end() returns an iterator pointing to one past the last element 
		// in the vector.
		current = suitors.erase(current); 
		if (current == suitors.end())
			current = suitors.begin();
	}
	return suitors[0];
}
