#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

constexpr int MAX = 1000;
constexpr int BEST = 3;
const std::string PATH = "./06_Structures_Classes/6.11_Highest_Score/Utilities/Scores.txt";

class Player
{
public:
	void setName(const std::string& namePlayer);
	//   Precondition: namePlayer is a valid string
	//   Postcondition: sets the player's name to namePlayer
	void setScore(int scorePlayer);
	//   Precondition: scorePlayer is a valid integer
	//   Postcondition: sets the player's score to scorePlayer
	std::string getName() const;
	int getScore() const;
private:
	std::string name;
	int score;
};

bool processFile(Player players[], int maxSize, int& nPlayers);
//   Precondition: players is an array of size maxSize
//   Postcondition: fills players array with data from the file located at PATH.

bool openFile(const std::string& pathFile, std::ifstream& inputStream);
//   Precondition: pathFile is a valid file path, inputStream is an ifstream object
//   Postcondition: opens the file located at pathFile for reading.

void closeFile(std::ifstream& inputStream);
//   Precondition: inputStream is an open file stream
//   Postcondition: closes the file stream.

void parseFile(std::ifstream& inputStream, Player players[], int maxSize, int& nPlayers);
//   Precondition: inputStream is an open file stream, players is an array of size maxSize,
// nPlayers is the current number of players.
//   Postcondition: reads names and scores from inputStream and fills the players array up to maxSize.

void orderData(Player players[], int nPlayers);
//   Precondition: players is an array of size at least nPlayers
//   Postcondition: sorts players array in descending order of scores.

void mergeSort(Player players[], Player buffer[], int size, int start, int end);
//   Precondition: players is an array of size at least size. buffer is a temporary array 
// of size at least size, to avoid memory churn (allocation/deallocation during recursion).
//   Postcondition: sorts players array in descending order of scores using the merge sort algorithm
// on the subarray defined by [start..end].

void merge(Player players[], Player buffer[], int size, int start, int mid, int end);
//   Precondition: players is an array of size at least size. buffer is a temporary array
//   Postcondition: merges two sorted subarrays of players defined by [start..mid] and [mid+1..end]

void showBest(const Player players[], int size, int topPlayers);
//   Precondition: players is an array of size at least size, topPlayers is a defined constant
//   Postcondition: displays on console the topPlayers players with highest scores.

int main() 
{
	Player players[MAX];
	int nPlayers = 0;
	if (!processFile(players, MAX, nPlayers)) return -1;
	orderData(players, nPlayers);
	showBest(players, nPlayers, BEST);

	std::cout << "\n";
	return 0;
}

void Player::setName(const std::string& namePlayer)
{
	name = namePlayer;
}

void Player::setScore(const int scorePlayer)
{
	score = scorePlayer;
}

std::string Player::getName() const
{
	return name;
}

int Player::getScore() const
{
	return score;
}

bool processFile(Player players[], const int maxSize, int& nPlayers)
{
	std::ifstream inputStream;
	if (!openFile(PATH, inputStream))
	{
		std::cerr << "Cannot open file\n";
		return false;
	} 
	std::cout << "File opened. Copying...\n";
	parseFile(inputStream, players, maxSize, nPlayers);
	closeFile(inputStream);
	return true;
}

bool openFile(const std::string& pathFile, std::ifstream& inputStream)
{
	inputStream.open(pathFile);
	if (!inputStream) return false;
	return true;
}

void closeFile(std::ifstream& inputStream)
{
	inputStream.close();
}

void parseFile(std::ifstream& inputStream, 
			   Player players[], const int maxSize, int& nPlayers)
{
	std::string nameLine, scoreLine;
	nPlayers = 0;	
	while (std::getline(inputStream, nameLine) // make sure to start with a name
		   && nPlayers < maxSize)
	{
		if (nameLine.empty()) continue;
		if (!std::getline(inputStream, scoreLine)) continue;	// expect score in next line

		std::istringstream iss(scoreLine);
		int points;
		while (iss >> points)
		{
			players[nPlayers].setName(nameLine);
			players[nPlayers].setScore(points);
			nPlayers++;
		}
	}
}


void orderData(Player players[], const int nPlayers)
{
	if (nPlayers <= 1) return;
	Player buffer[MAX];
	mergeSort(players, buffer, nPlayers, 0, nPlayers - 1);
}

void mergeSort(Player players[], Player buffer[], const int size, const int start, const int end)
{
	if (start >= end) return;
	const int mid = (start + end) / 2;
	mergeSort(players, buffer, size, start, mid);
	mergeSort(players, buffer, size, mid + 1, end);
	merge(players, buffer, size, start, mid, end);
}

void merge(Player players[], Player buffer[], 
		   const int size, const int start, const int mid, const int end)
{
	int p1 = start, p2 = mid + 1, idxScore = start;
	while ((p1 <= mid) && (p2 <= end))
	{
		if (players[p1].getScore() >= players[p2].getScore())
		{
			buffer[idxScore] = players[p1];
			++p1;
		}
		else
		{
			buffer[idxScore] = players[p2];
			++p2;
		}
		++idxScore;
	}
	// Merge wrap-up
	while (p1 <= mid)
	{
		buffer[idxScore] = players[p1];
		++p1;
		++idxScore;
	}
	while (p2 <= end)
	{
		buffer[idxScore] = players[p2];
		++p2;
		++idxScore;
	}
	for (int idx = start; idx <= end; ++idx)
		players[idx] = buffer[idx];
}

void showBest(const Player players[], const int size, const int topPlayers)
{
	for (int idx = 0; idx < size; ++idx)
	{
		const bool highlight = (idx < topPlayers);
		if (highlight) std::cout << "*** ";
		else		   std::cout << "    ";
		std::cout << "Player #" << std::setw(2) << idx + 1
				  << ": " << std::setw(15) << players[idx].getName()
				  << ", score: " << std::setw(10) << players[idx].getScore();
		if (highlight) std::cout << " ***";
		std::cout << "\n";
	}
}
