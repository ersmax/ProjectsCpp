/*
Write a program that manages a list of up to ten players and their high scores in the
computer’s memory (not on disk as in Programming Project 18). Use two arrays
to manage the list. One array should store the player’s name, and the other array
should store the player’s high score. Use the index of the arrays to correlate the
names with the scores. In the next chapter you will learn a different way to organize
related data by putting them into a struct or class. Do not use a struct or class for
this program. Your program should support the following features:
a. Add a new player and score (up to ten players).
b. Print all player names and their scores to the screen.
c. Allow the user to enter a player name and output that player’s score or a message
if the player name has not been entered.
d. Allow the user to enter a player name and remove the player from the list.
Create a menu system that allows the user to select which option to invoke.
*/


/* 
Do Programming Project 5.19, but this time use a class named Player to store a
player’s name and score.Be sure to include a constructor with this class that sets
the name and score.Then use a vector of the Player class to store the ten players.
*/

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <limits>

constexpr int MAX_PLAYERS = 10;

class Player
{
public:
	Player();
	Player(const std::string& fullName) : score(0) { setName(fullName); }
	Player(const std::string& fullName, const int score) { setName(fullName); setScore(score); }
	std::string getName() const { return name; }
	int getScore() const { return score; }
private:
	void setName(const std::string& namePlayer) { name = namePlayer; }
	void setScore(const int scorePlayer) { score = scorePlayer; }
	std::string name;
	int score;
};

void menu();
char makeChoice();
bool handleChoice(const char& letter, std::vector<Player>& rooster);
std::string inputName();
int inputScore();
void addPlayer(std::vector<Player>& rooster);
void showPlayers(const std::vector<Player>& rooster);

int main( )
{
	std::vector<Player> rooster;
	rooster.reserve(MAX_PLAYERS);
	while (true)
	{
		menu();
		const char choice = makeChoice();
		if (!handleChoice(choice, rooster))
			break;
	}

	std::cout << '\n';
	return 0;
}

void menu()
{
	std::cout << "a. Add a new player and score \n"
		<< "b. Print all player names and their scores to the screen \n"
		<< "c. Enter a player name and output that player’s score \n"
		<< "d. Enter a player name and remove the player from the list \n"
		<< "0. Exit the program\n";
	std::cout << "Enter a choice:\n";
}

char makeChoice()
{
	char choice;
	while (true)
	{
		if (!(std::cin >> choice))
		{
			std::cout << "Not a valid choice\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		choice = static_cast<char>(std::tolower(choice));
		if ((choice < 'a' || choice > 'd') && choice != '0')
		{
			std::cout << "Not a valid choice\n";
			continue;
		}
		return choice;
 	}
}

bool handleChoice(const char& letter, std::vector<Player>& rooster)
{
	if (letter == '0')	return false;
	switch (letter)
	{
		case 'a':
			addPlayer(rooster);
			break;
		case 'b':
			showPlayers(rooster);
			break;
		case 'c':
			// TODO
			break;
		case 'd':
			// TODO
			break;
		default: 
			break;
	}
	return true;
}

void addPlayer(std::vector<Player>& rooster)
{
	if (rooster.size() > MAX_PLAYERS)
	{
		std::cerr << "Max capacity reached\n";
		return;
	}
	const std::string name = inputName();
	const int score = inputScore();
	const Player aPlayer(name, score);
	rooster.push_back(aPlayer);
}

void showPlayers(const std::vector<Player>& rooster)
{
	std::cout << std::setw(2) << "#"
			  << std::setw(25) << "Player"
			  << std::setw(10) << "Score\n";
	int idx = 1;
	for (const Player& player : rooster)
	{
		std::cout << std::setw(2) << idx 
				  << std::setw(25) << player.getName()
				  << std::setw(10) << player.getScore() << '\n';
		idx++;
	}
	std::cout << std::string(37, '-') << "\n";
}

std::string inputName()
{
	std::string line;
	while (true)
	{
		std::cout << "Enter full name:\n";
		if (!(std::getline(std::cin, line)))
		{
			std::cin.clear();
			continue;
		}
		// erase leading white spaces
		while (!line.empty() && std::isspace(line.front()))
			line.erase(line.begin());
		// erase trailing white space
		while (!line.empty() && std::isspace(line.back()))
			line.pop_back();	// line.erase(line.back() - 1)
		if (line.empty())
		{
			std::cout << "Name cannot be empty\n";
			continue;
		}
		return line;
	}
}

int inputScore()
{
	int score;
	while (true)
	{
		std::cout << "Enter a score (greater than 0)\n";
		if (!(std::cin >> score))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (score >= 0)
			return score;
		std::cout << "Score cannot be less than 0\n";
	}
}
