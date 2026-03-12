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

constexpr int MAX_SIZE = 10;

class Player
{
public:
	Player() : name(""), score(0) {};
	Player(const std::string& newName) : name(newName), score(0) {};
	Player(const std::string& newName, const int newScore) : name(newName) { setScore(newScore); }
	const std::string& getName() const { return name; }
	friend std::ostream& operator <<(std::ostream& outputStream, const Player& aPlayer);
	//   Precondition: aPlayer is a valid Player object, outputStream is a valid output stream
	//   Postcondition: aPlayer's name and score have been output to outputStream in the format:
	// 					Player name: <name>
	//					Player score: <score>

	friend std::istream& operator >>(std::istream& inputStream, Player& newPlayer);
	//   Postcondition: newPlayer's name and score have been set to the values entered by the user. 
	// The user is prompted to enter the name and score. The name must not be empty, and the score must be a non-negative integer. 
	// If invalid input is entered, the user is prompted to re-enter the data until valid input is provided.

private:
	std::string name;
	int score;
	void setScore(int number);
};

bool menu(PlayerPtr& myRooster, int& size);
//   Precondition: myRooster is a valid pointer to a dynamic array of Player objects, size is the number of players currently in the array
//   Postcondition: The user has been presented with a menu of options and has selected one. 
// The appropriate action has been taken based on the user's selection.

PlayerPtr addPlayer(const PlayerPtr& myRooster, int& size);
//   Precondition: myRooster is a valid pointer to a dynamic array of Player objects, size is the number of players currently in the array
//   Postcondition: A new Player object has been added to the dynamic array myRooster, and size has been incremented by 1.

char inputValidation();
//   Postcondition: The user has been prompted to enter a character corresponding to a menu option.

std::string enterName(std::istream& inputStream);
//   Precondition: inputStream is a valid input stream
//   Postcondition: The user has been prompted to enter a name, and a valid name has been returned.

int enterScore(std::istream& inputStream);
//   Postcondition: The user has been prompted to enter a score, and a valid non-negative integer score has been returned.

void printRooster(const PlayerPtr& myRooster, int size);
//   Postcondition: The names and scores of all players in the dynamic array myRooster have been printed to the screen.

void queryScore(const PlayerPtr& myRooster, int size);
//   Postcondition: The user has been prompted to enter a player's name, and the score for that player has been printed to the screen. 
// If the player is not found, a message indicating that the player was not found has been printed.

ConstPlayerPtr findPlayer(const PlayerPtr& myRooster, int size, const std::string& namePlayer);
//   Precondition: myRooster is a valid pointer to a dynamic array of Player objects, size is the number of players currently in the array, namePlayer is a valid string
//   Postcondition: A pointer to the Player object in myRooster (i.e. a dynamic array) with a name matching namePlayer has been returned.
// If no such player is found, nullptr has been returned.

int findIdxPlayer(const PlayerPtr& myRooster, int size, const std::string& namePlayer);
//   Postcondition: The index of the Player object in myRooster with a name matching namePlayer has been returned. If no such player is found, -1 has been returned.

void removePlayer(PlayerPtr& myRooster, int& size);
//   Precondition: myRooster is a valid pointer to a dynamic array of Player objects, size is the number of players currently in the array
//   Precondition: The user has been prompted to enter a player's name, and if a player with that name is found in myRooster, 
// that player has been removed from the dynamic array, and size has been decremented by 1.

PlayerPtr helperDelete(const PlayerPtr& myRooster, const int size, const ConstPlayerPtr& idxDeletePlayer);
//   Postcondition: A new dynamic array of Player objects has been created that contains all the players in myRooster except for the player pointed to by idxDeletePlayer.

PlayerPtr helperDeleteByIdx(const PlayerPtr& myRooster, int size, int idxDeletePlayer);
//   Postcondition: A new dynamic array of Player objects has been created that contains all the players in myRooster except for the player at index idxDeletePlayer.

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
			if (size == MAX_SIZE) 
			{
				std::cerr << "Max players reached (" << MAX_SIZE << ")\n";
				break;
			}
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
		std::cout << *(myRooster + idx);
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
	// Search by index
	const int idxDeletePlayer = findIdxPlayer(myRooster, size, namePlayer);
	if (idxDeletePlayer != -1)
	{
		const PlayerPtr temp = helperDeleteByIdx(myRooster, size, idxDeletePlayer);
		delete[] myRooster;
		myRooster = temp;
		size--;
	}
	else
		std::cout << "Player not found\n";
	
	// Search by pointer (address of pointed variable)
	/*
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
	*/
}

PlayerPtr helperDelete(const PlayerPtr& myRooster, const int size, const ConstPlayerPtr& idxDeletePlayer)
{
	const PlayerPtr temp = new Player[size - 1];
	for (int idx = 0, newIdx = 0; idx < size; idx++)
		if ((myRooster + idx) != idxDeletePlayer)
			temp[newIdx++] = myRooster[idx];
	
	return temp;
}

PlayerPtr helperDeleteByIdx(const PlayerPtr& myRooster, const int size, const int idxDeletePlayer)
{
	const PlayerPtr temp = new Player[size - 1];
	for (int idx = 0, newIdx = 0; idx < size; idx++)
		if (idx != idxDeletePlayer)
			temp[newIdx++] = myRooster[idx];

	return temp;
}


ConstPlayerPtr findPlayer(const PlayerPtr& myRooster, const int size, const std::string& namePlayer)
{
	for (int idx = 0; idx < size; idx++)
		if (myRooster[idx].getName() == namePlayer)
			return &myRooster[idx];
	
	return nullptr;
}

int findIdxPlayer(const PlayerPtr& myRooster, const int size, const std::string& namePlayer)
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
