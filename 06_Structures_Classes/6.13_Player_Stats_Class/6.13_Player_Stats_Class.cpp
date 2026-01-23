#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

constexpr int MAX = 10;
const std::string MENU = std::string(20, '-') + "\n"
									 "MENU\n" +
									 "a. Add a new player and score\n"
									 "b. Print player names and their scores\n"
									 "c. Show the score by searching the player name\n"
									 "d. Remove a player by typing the name\n"
									 "e. Exit the program\n" +
									 std::string(20, '-') + "\n"
									 "Make a choice:\n";

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


char menu();
//   Postcondition: displays the menu and returns a valid option

bool handleChoice(Player players[], int maxSize, int& size, int choice);
//   Precondition: choice is a valid menu option. players is an array of Players 
// having size up to maxSize
//   Postcondition: handles the choice selected by the user.

void addPlayer(Player players[], int maxSize, int& size);
//   Precondition: players is an array of Players having size up to maxSize
//   Postcondition: adds a new player and score to players array,
// if there is space available.

void showPlayers(const Player players[], int size);
//   Precondition: players is an array of Players having size up to size
//   Postcondition: displays all player names and their scores.

void removePlayer(Player players[], int& size);
//   Precondition: players is an array of Players having size up to size
//   Postcondition: prompts the user to enter a player name and
// removes the player from the list if found.

int findPlayer(const Player players[], int size, const std::string& name);
//   Precondition: players is an array of Players having size up to size
//   Postcondition: searches for name in players array and returns the index 
// of the player in players array of Player ADT if found, -1 otherwise.

void searchPlayer(const Player players[], int size);
//   Precondition: players is an array of Players having size up to size
//   Postcondition: prompts the user to enter a player name and 
// displays the corresponding score or a message if the player is not found.

std::string nameValidation();
//   Postcondition: prompts the user to enter a name and returns it.

int scoreValidation();
//   Postcondition: prompts the user to enter a score and returns it.

int main( )
{
	Player players[MAX];
	int size = 0;
	
	while (true)
	{
		char choice = menu();
		if (!handleChoice(players, MAX, size, choice)) break;
	}
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

char menu()
{
	char answer;
	while (true)
	{
		std::cout << MENU;
		if (!(std::cin >> answer))
		{
			std::cout << "Not a valid choice\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		answer = static_cast<char>(std::tolower(answer));
		if (answer >= 'a' && answer <= 'e')
			return answer;
		std::cout << "Not a valid choice\n";
	}
}

bool handleChoice(Player players[], const int maxSize, int& size, const int choice)
{
	if (choice == 'e')	return false;
	switch (choice)
	{
		case 'a':
			addPlayer(players, maxSize, size);
			break;
		case 'b':
			showPlayers(players, size);
			break;
		case 'c':
			searchPlayer(players, size);
			break;
		case 'd':
			removePlayer(players, size);
			break;
		default:
			break;
	}
	return true;
}

void addPlayer(Player players[], const int maxSize, int& size)
{
	if (size < maxSize) {
		const std::string namePlayer = nameValidation();
		const int scorePlayer = scoreValidation();
		players[size].setName(namePlayer);
		players[size].setScore(scorePlayer);
		size++;
		return;
	}
	std::cout << "Max players reached in the rooster\n";
}

void showPlayers(const Player players[], const int size)
{
	std::cout << std::setw(2) << "#"
			  << std::setw(25) << "Player"
			  << std::setw(10) << "Score\n";
	for (int idx = 0; idx < size; ++idx)
		std::cout << std::setw(2) << idx + 1
			      << std::setw(25) << players[idx].getName()
				  << std::setw(10) << players[idx].getScore() << "\n";
	std::cout << std::string(37, '-') << "\n";
}

void searchPlayer(const Player players[], const int size)
{
	if (size == 0) return;
	const std::string name = nameValidation();
	const int idxPlayer = findPlayer(players, size, name);
	if (idxPlayer != -1)
		std::cout << players[idxPlayer].getName() << "'s score: "
				  << players[idxPlayer].getScore() << "\n";
	else
		std::cout << "No player found\n";
}

void removePlayer(Player players[], int& size)
{
	if (size == 0) return;
	const std::string name = nameValidation();
	const int idxPlayer = findPlayer(players, size, name);
	if (idxPlayer == -1)
		std::cout << "NO player found\n";
	else
	{
		for (int idx = idxPlayer; idx < size - 1; ++idx)
			players[idx] = players[idx + 1];
		
		std::cout << name << " removed!\n";
		--size;
	}
}

int findPlayer(const Player players[], const int size, const std::string& name) {
	for (int idx = 0; idx < size; ++idx)
		if (players[idx].getName() == name)
			return idx;
	return -1;
}

std::string nameValidation()
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
		while (!line.empty() && std::isspace(line.front()))
			line.erase(line.begin());
		while (!line.empty() && std::isspace(line.back()))
			line.pop_back();	// line.erase(line.back()-1)
		if (line.empty())
		{
			std::cout << "Name cannot be empty\n";
			continue;
		}
		return line;
	}
}

int scoreValidation()
{
	int score;
	while (true)
	{
		std::cout << "Enter a score (greater than 0):\n";
		if (!(std::cin >> score))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (score > 0)
			return score;
		std::cout << "Score must be greater than 0\n";
	}
}

