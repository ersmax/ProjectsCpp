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
