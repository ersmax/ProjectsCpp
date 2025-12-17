/*
Do Programming Project 5.18 except use only one array as a parameter instead
of two arrays. The single array should be of type Player where Player is a class
that you create. The Player class should have a member variable of type string
to store the player’s name and a member variable of type int to score the player’s
score. Encapsulate these variables appropriately. Upon return from your function
the array entry at index 0 should be set to the name and score of the player with the
best score, the entry at index 1 should be set to the name and score of the player
with the second best score, etc.

Program 5.18
This project is an extension of Programming Project 4.16. Consider a text file
named scores.txt that contains player scores for a game. A possible sample is
shown next where Ronaldo’s best score is 10400, Didier’s best score is 9800, etc.
Put at least five names and scores in the file.
Ronaldo
10400
Didier
9800
Pele
12300
Kaka
8400
Cristiano
8000
Write a function named getHighScores that takes two array parameters, an array
of strings and an array of integers. The function should scan through the file and
set the string array entry at index 0 to the name of the player with the highest score
and set the integer array entry at index 0 to the score of the player with the highest
score. The string array entry at index 1 should be set to the name of the player with
the second highest score and the integer array entry at index 1 should be set to the
score of the player with the second highest score. Do the same for the entries at
index 2. Together, these two arrays give you the names and scores of the top three
players. In your main function, test the getHighScores function by calling it and
outputting the top three players and scores.
*/

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
	void setScore(int scorePlayer);
	std::string getName() const;
	int getScore() const;
private:
	std::string name;
	int score;
};

bool processFile(Player players[], int maxSize, int& nPlayers);
bool openFile(const std::string& pathFile, std::ifstream& inputStream);
void closeFile(std::ifstream& inputStream);
void parseFile(std::ifstream& inputStream, Player players[], int maxSize, int& nPlayers);
void orderData(Player players[], int nPlayers);
void mergeSort(Player players[], Player buffer[], int size, int start, int end);
void merge(Player players[], Player buffer[], int size, int start, int mid, int end);
void showBest(const Player players[], int size, int topPlayers);

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
