/*
5.19: 
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

10.07:
Do Programming Project 5.19 but this time use a class named Player to store a
player’s name and score. Be sure to include a constructor with this class that sets
the name and score. Then, use a dynamic array of the Player class to store the
players. Start with a dynamic array that stores no players. To add a player, create
a new dynamic array that is one larger than the current size, and copy the existing
and the new player into it. To remove a player, create a new dynamic array that is
one smaller than the current size, and copy all players into it except the player that
is to be removed.
*/

#include <iostream>
#include <string>

class Player;

typedef Player *PlayerPtr;
typedef const Player *ConstPlayerPtr;

constexpr const char *MENU =	"a. Add a new player and score\n"
								"b. Print all player names and scores\n"
								"c. Enter player's name to know the score\n"
								"d. Enter player's name to remove them\n"
								"e. Exit\n"
								"Enter an option:\n";

class Player
{
public:
	Player() : name(""), score(0) {};
	Player(const std::string& newName) : name(newName), score(0) {};
	Player(const std::string& newName, const int newScore) : name(newName) { setScore(newScore); }
	const std::string& getName() const { return name; }
	friend std::ostream& operator <<(std::ostream& outputStream, const Player& aPlayer);
	friend std::istream& operator >>(std::istream& inputStream, Player& newPlayer);
private:
	std::string name;
	int score;
	void setScore(int number);
};

bool menu(PlayerPtr& myRooster, int& size);
PlayerPtr addPlayer(const PlayerPtr& myRooster, int& size);

char inputValidation();
std::string enterName(std::istream& inputStream);
int enterScore(std::istream& inputStream);
void printRooster(const PlayerPtr& myRooster, int size);
void queryScore(const PlayerPtr& myRooster, int size);
ConstPlayerPtr findPlayer(const PlayerPtr& myRooster, int size, const std::string& namePlayer);
int findIdxPlayer(const PlayerPtr& myRooster, int size, const std::string& namePlayer);
void removePlayer(PlayerPtr& myRooster, int& size);
PlayerPtr helperDelete(const PlayerPtr& myRooster, const int size, const ConstPlayerPtr& idxDeletePlayer);

int main( )
{
	PlayerPtr rooster = nullptr;
	int size = 0;
	while (menu(rooster, size)) {};

	delete [] rooster;
	std::cout << '\n';
	return 0;
}



bool menu(PlayerPtr& myRooster, int& size)
{
	std::cout << MENU;
	switch (char answer = inputValidation())
	{
		case 'a':
		{
			const PlayerPtr newRooster = addPlayer(myRooster, size);
			delete [] myRooster;
			myRooster = newRooster;
			break;
		}
		case 'b':
			printRooster(myRooster, size);
			break;
		case 'c':
			queryScore(myRooster, size);
			break;
		case 'd':
			removePlayer(myRooster, size);
			break;
		case 'e':
			return false;
		default:
			return false;
	}
	return true;
}

PlayerPtr addPlayer(const PlayerPtr& myRooster, int& size)
{
	const PlayerPtr temp = new Player[size + 1];
	for (int idx = 0; idx < size; idx++)
		temp[idx] = myRooster[idx];

	Player newPlayer;
	std::cout << "Enter new player's data:\n";
	std::cin >> newPlayer;
	temp[size] = newPlayer;
	size++;
	return temp;
}



std::istream& operator >>(std::istream& inputStream, Player& newPlayer)
{
	const std::string newName = enterName(inputStream);
	const int newScore = enterScore(inputStream);
	newPlayer.name = newName;
	newPlayer.score = newScore;
	return inputStream;
}

std::ostream& operator <<(std::ostream& outputStream, const Player& aPlayer)
{
	outputStream << "Player name: " << aPlayer.name << '\n'
				 << "Player score: " << aPlayer.score << '\n'; 
	outputStream << "---\n";
	return outputStream;
}

void Player::setScore(const int number)
{
	if (number >= 0)
		score = number;
	else
		throw std::invalid_argument("Score cannot be negative\n");
}

void printRooster(const PlayerPtr& myRooster, const int size)
{
	for (int idx = 0; idx < size; idx++)
		std::cout << *(myRooster + idx) << '\n';
}

void queryScore(const PlayerPtr& myRooster, const int size)
{
	const std::string namePlayer = enterName(std::cin);
	const ConstPlayerPtr searchPlayer = findPlayer(myRooster, size, namePlayer);
	if (searchPlayer != nullptr)
		std::cout << *searchPlayer;
	else
		std::cout << "Player not found\n";

	// By index
	// const int idxPlayer = findIdxPlayer(myRooster, size, namePlayer);
	// if (idxPlayer != -1)
	//	 std::cout << myRooster[idxPlayer];
	// else
	//	 std::cout << "Player not found\n";
}

void removePlayer(PlayerPtr& myRooster, int& size)
{
	const std::string namePlayer = enterName(std::cin);
	const ConstPlayerPtr idxDeletePlayer = findPlayer(myRooster, size, namePlayer);
	if (idxDeletePlayer != nullptr)
	{
		const PlayerPtr temp = helperDelete(myRooster, size, idxDeletePlayer);
		delete [] myRooster;
		myRooster = temp;
		size--;
	}
	else
		std::cout << "Player not found\n";

}

PlayerPtr helperDelete(const PlayerPtr& myRooster, const int size, const ConstPlayerPtr& idxDeletePlayer)
{
	const PlayerPtr temp = new Player[size - 1];
	for (int idx = 0, newIdx = 0; idx < size; idx++)
		if ((myRooster + idx) != idxDeletePlayer)
			temp[newIdx++] = myRooster[idx];
	
	return temp;
}

//void removePlayerByIdx(PlayerPtr& myRooster, int& size)
//{
//	const std::string namePlayer = enterName(std::cin);
//	int idxPlyaer = findIdxPlayer(myRooster,)
//}

ConstPlayerPtr findPlayer(const PlayerPtr& myRooster, const int size, const std::string& namePlayer)
{
	for (int idx = 0; idx < size; idx++)
		if (myRooster[idx].getName() == namePlayer)
			return &myRooster[idx];
	
	return nullptr;
}

int findIdxPlayer(const PlayerPtr& myRooster, int size, const std::string& namePlayer)
{
	for (int idx = 0; idx < size; idx++)
		if (myRooster[idx].getName() == namePlayer)
			return idx;

	return -1;
}

char inputValidation()
{
	char answer;
	while (true)
	{
		if (!(std::cin >> answer))
		{
			std::cout << "Not a valid choice\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		char letter = std::tolower(answer);
		if (letter >= 'a' && letter <= 'e')
			return letter;
		std::cout << "Not a valid choice. Retry\n";
	}
}

std::string enterName(std::istream& inputStream)
{
	std::string answer;
	while (true)
	{
		std::cout << "Enter name:\n";
		//if (!(inputStream >> answer))
		if (!std::getline(inputStream, answer))
		{
			std::cout << "Not a valid name\n";
			inputStream.clear();
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (answer.empty())
		{
			std::cout << "Must provide a name\n";
			continue;								// no ignore, line already consumed '\n'
		}
		return answer;
	}
}

int enterScore(std::istream& inputStream)
{
	int answer;
	while (true)
	{
		std::cout << "Enter a score:\n";
		if (!(inputStream >> answer))
		{
			std::cout << "Not a valid score\n";
			inputStream.clear();
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (answer >= 0)
			return answer;
		std::cout << "Score must be greater than or equal to 0\n";
	}
}
