#include <iostream>
#include <string>

typedef std::string *StringPtr;

std::string nameValidation(std::istream& inputStream);
int numberValidation(std::istream& inputStream);

class Subscriber
{
public:
	Subscriber() : numChannels(0), channelList(new std::string[0]) {};
	Subscriber(const std::string& newName) : name(newName), numChannels(0), channelList(new std::string[0]) {};
	Subscriber(const std::string& newName, const std::string newList[], const int newChannels) :	name(newName), 
																									numChannels(newChannels) 
																									{ setChannels(newList, newChannels); }
	Subscriber(const Subscriber& rightSide);
	Subscriber& operator =(const Subscriber& rightSide);
	~Subscriber() { delete [] channelList; }
	void reset();
	//   Postcondition: The number of channels is set to 0 and the channelList is set to an empty list.

	const std::string& operator [](int index) const;
	//   Postcondition: The channel at the specified index is returned. 
	// If the index is out of range, an out_of_range exception is thrown.

	friend std::istream& operator >>(std::istream& inputStream, Subscriber& mySubscriber);
	//   Postcondition: The user is prompted to enter the subscriber's name and the list of channels.

	friend std::ostream& operator <<(std::ostream& outputStream, const Subscriber& mySubscriber);
	//   Postcondition: The subscriber's name and the list of channels are output to the outputStream.
private:
	std::string name;
	int numChannels;
	StringPtr channelList;
	void inputChannels(std::istream& inputStream);
	//   Postcondition: The user is prompted to enter the number of channels and the names of the channels.

	void setChannels(const std::string newList[], int newChannels);
	//   Precondition: newList is an array of strings containing the new channel names, 
	// and newChannels is the number of channels in newList.
	//   Postcondition: The channelList is updated to contain the new channel names, and numChannels is updated to newChannels.
};


int main( )
{
	std::string channels[] = {"Cars", "Books"};
	Subscriber aSubscriber("Paul", channels, 2);
	Subscriber aSubscriber2;

	std::cout << "Data of first user: " << aSubscriber;

	std::cout << "Enter data of a second user.\n";
	std::cin >> aSubscriber2;
	std::cout << "Data of second user: " << aSubscriber2;

	std::cout << "The third user has same preferences of user 2\n";
	Subscriber aSubscriber3("Mary");
	aSubscriber3 = aSubscriber2;
	std::cout << "Data of third user: " << aSubscriber3;

	std::cout << "The second user has changed preferences to user #1\n";
	aSubscriber2 = aSubscriber;
	std::cout << "Data of second user: " << aSubscriber2;

	std::cout << "The fourth user has same preference of second, with a new genre of Zebra\n";
	Subscriber aSubscriber4(aSubscriber2);
	std::cin >> aSubscriber4;
	std::cout << "Data of second user: " << aSubscriber2;
	std::cout << "Data of fourth user: " << aSubscriber4;

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

Subscriber& Subscriber::operator =(const Subscriber& rightSide)
{
	if (this == &rightSide)	return *this;

	if (numChannels != rightSide.numChannels)
	{
		delete [] channelList;
		channelList = new std::string[rightSide.numChannels];
	}
	numChannels = rightSide.numChannels;
	for (int idx = 0; idx < numChannels; idx++)
		channelList[idx] = rightSide.channelList[idx];
	return *this;
}

Subscriber::Subscriber(const Subscriber& rightSide) :	numChannels(rightSide.numChannels)
{
	channelList = new std::string[numChannels];
	for (int idx = 0; idx < numChannels; idx++)
		channelList[idx] = rightSide.channelList[idx];
}

void Subscriber::reset()
{
	numChannels = 0;
	delete[] channelList;
	channelList = new std::string[0];
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