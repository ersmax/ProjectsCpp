#include <iomanip>		// for std::setw
#include <iostream>		// for std::cout, std::cin, std::getline
#include <vector>	
#include <string>		
#include <limits>		// for std::numeric_limits

constexpr int MAX_PLAYERS = 10;

class Player
{
public:
	Player() : Player("no name", 0) {};
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
//   Postcondition: displays the menu to the user.

char makeChoice();
//   Postcondition: prompts the user to enter a choice and returns a valid menu option.

bool handleChoice(const char& letter, std::vector<Player>& rooster);
//   Precondition: letter is a valid menu option, rooster is a vector of Player objects.
//   Postcondition: handles the choice selected by the user. 
// Returns false if the user chose to exit the program, true otherwise.

std::string inputName();
//   Postcondition: prompts the user to enter a name and returns it.

int inputScore();
//   Postcondition: prompts the user to enter a score and returns it.

void addPlayer(std::vector<Player>& rooster);
//   Precondition: rooster is a vector of Player objects.
// MAX_PLAYERS is the maximum number of players allowed in the rooster.
//	 Postcondition: adds a new player and score to rooster vector, if there is space available.

void showPlayers(const std::vector<Player>& rooster);
//   Postcondition: displays all player names and their scores.

void scorePlayer(const std::vector<Player>& rooster);
//   Postcondition: prompts the user to enter a player name 
// and displays the corresponding score or a message if the player is not found.

int findPlayer(const std::vector<Player>& rooster, const std::string& aPlayer);
//   Precondition: rooster is a vector of Player objects, 
// aPlayer is the name of the player to search for.
//   Postcondition: searches for aPlayer in rooster vector 
// and returns the score of the player if found, -1 otherwise, which signals error.

void deletePlayer(std::vector<Player>& rooster);
//   Postcondition: prompts the user to enter a player name
// and removes the player from the rooster vector if found.


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
			scorePlayer(rooster);
			break;
		case 'd':
			deletePlayer(rooster);
			break;
		default: 
			break;
	}
	return true;
}

void addPlayer(std::vector<Player>& rooster)
{
	if (rooster.size() >= MAX_PLAYERS)
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
		std::cout << "Enter a score (at least 0)\n";
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

void scorePlayer(const std::vector<Player>& rooster)
{
	if (rooster.empty())
	{
		std::cout << "No players in the rooster\n";
		return;
	}
	const std::string myPlayer = inputName();
	const int scorePlayer = findPlayer(rooster, myPlayer);
	if (scorePlayer == -1)
		std::cout << "No player found\n";
	else
		std::cout << myPlayer << "'s score: " << scorePlayer << '\n';
}

void deletePlayer(std::vector<Player>& rooster)
{
	if (rooster.empty())
	{
		std::cout << "No players in the rooster\n";
		return;
	}
	
	const std::string myPlayer = inputName();
	for (std::vector<Player>::iterator iterator = rooster.begin(); iterator != rooster.end(); ++iterator)
	{
		if (iterator->getName() == myPlayer)
		{
			iterator = rooster.erase(iterator);
			return;
		}
	}
	std::cout << "No player found\n";
}

int findPlayer(const std::vector<Player>& rooster, const std::string& aPlayer)
{
	for (const Player& player : rooster)
	{
		if (player.getName() == aPlayer)
			return player.getScore();
	}
	return -1;
}
