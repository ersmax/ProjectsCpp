/*
Create a class named Subscriber that has three member variables:
name – A string that stores the name of the subscriber
numChannels – An integer that tracks how many channels the subscriber subscribes
to.
channelList – A dynamic array of strings used to store the names of the
channels the subscriber subscribes to.
Write appropriate constructor(s), mutator, and accessor functions for the class
along with the following:
• A function that inputs all values from the user, including the list of channel names.
This function will have to support input for an arbitrary number of channels.
• A function that outputs the name and list of all channels.
• A function that resets the number of channels to 0 and the channelList to an
empty list.
• An overloaded assignment operator that correctly makes a new copy of the list
of channels.
• A destructor that releases all memory that has been allocated.
Write a main function that tests all your functions.
*/

#include <iostream>
#include <string>

typedef std::string *StringPtr;

std::string nameValidation(std::istream& inputStream);
int numberValidation(std::istream& inputStream);

class Subscriber
{
public:
	Subscriber() : name(""), numChannels(0), channelList(new std::string[0]) {};
	Subscriber(const std::string& newName) : name(newName), numChannels(0), channelList(new std::string[0]) {};
	Subscriber(const std::string& newName, const std::string newList[], const int newChannels) : name(newName), numChannels(newChannels) { setChannels(newList, newChannels); }
	~Subscriber() { delete [] channelList; }
	const std::string& operator [](int index) const;
	friend std::istream& operator >>(std::istream& inputStream, Subscriber& mySubscriber);
	friend std::ostream& operator <<(std::ostream& outputStream, const Subscriber& mySubscriber);
private:
	void inputChannels(std::istream& inputStream);
	std::string name;
	int numChannels;
	StringPtr channelList;
	void setChannels(const std::string newList[], int newChannels);
};


int main( )
{
	std::string channels[] = {"Cars", "Books"};
	Subscriber aSubscriber("Paul", channels, 2);
	
	std::cout << "Enter new data.\n";
	std::cin >> aSubscriber;
	std::cout << "Data of user: " << aSubscriber;

	std::cout << '\n';
	return 0;
}

std::ostream& operator <<(std::ostream& outputStream, const Subscriber& mySubscriber)
{
	outputStream << mySubscriber.name << '\n';
	for (int idx = 0; idx < mySubscriber.numChannels; idx++)
		outputStream << idx + 1 << " " << mySubscriber.channelList[idx] << '\n';
	return outputStream;
}

std::istream& operator >>(std::istream& inputStream, Subscriber& mySubscriber)
{
	if (mySubscriber.name.empty())
	{
		std::cout << "Enter new username.\n";
		mySubscriber.name = nameValidation(inputStream);
	}
	std::cout << "Enter new channels.\n";
	mySubscriber.inputChannels(inputStream);
	return inputStream;
}

const std::string& Subscriber::operator[](const int index) const
{
	if (index < 0 || index >= numChannels)
		throw std::out_of_range("Index not in the range\n");
	return channelList[index];
}

void Subscriber::inputChannels(std::istream& inputStream)
{
	std::cout << "How many new channels do you want to input?\n";
	const int newChannels = numberValidation(inputStream);
	if (newChannels == 0)	return;

	const StringPtr temp = new std::string[numChannels + newChannels];
	// Copy old channels
	for (int idx = 0; idx < numChannels; idx++)
		temp[idx] = channelList[idx];
	// Input new channels
	for (int idx = numChannels; idx < numChannels + newChannels; idx++)
	{
		std::cout << "Enter name of new channel " << (idx - numChannels + 1) << ":\n";
		temp[idx] = nameValidation(inputStream);
	}
	numChannels += newChannels;
	delete [] channelList;
	channelList = temp;
}

void Subscriber::setChannels(const std::string newList[], const int newChannels)
{
	channelList = new std::string[newChannels];
	for (int idx = 0; idx < newChannels; idx++)
		channelList[idx] = newList[idx];
}

std::string nameValidation(std::istream& inputStream)
{
	std::string name;
	while (true)
	{
		if (!(inputStream >> name))
		{
			std::cout << "Not a valid input\n";
			inputStream.clear();
			inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (name.empty())
		{
			std::cerr << "Input cannot be empty.\n";
			continue;
		}
		inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return name;
	}
}

int numberValidation(std::istream& inputStream)
{
	int input;
	while (true)
	{
		if (!(inputStream >> input))
		{
			std::cout << "Not a valid input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (input < 0)
		{
			std::cerr << "Input must be greater than or equal to 0\n";
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return input;
	}
}