#include <iostream>
#include <stdexcept>
#include <string>

typedef std::string *StringPtr;
typedef const std::string *ConstStringPtr;


class DynamicStringArray
{
public:
	DynamicStringArray() : size(0), dynamicArray(nullptr) {};
	DynamicStringArray(const DynamicStringArray& rhs);
	~DynamicStringArray() { delete [] dynamicArray; }
	int getSize() const { return size; }
	void addEntry(const std::string& newEntry);
	//  Postcondition: The newEntry is added to the end of the dynamic array. 
	// The size of the array is increased by 1.

	bool deleteEntry(const std::string& entry);
	//   Postcondition: If the entry is found in the dynamic array, 
	// it is deleted and the size of the array is decreased by 1.

	ConstStringPtr getEntry(int idx) const;
	//   Postcondition: If the index is valid, a pointer to the string at that index is returned.

	const DynamicStringArray& operator =(const DynamicStringArray& rhs);
	//   Postcondition: The dynamic array of the rhs object is copied to the current object. 

	const std::string& operator [](int idx) const;
	//   Postcondition: If the index is valid, a reference to the string at that index is returned.
	// If not, an out_of_range exception is thrown.

	friend std::ostream& operator <<(std::ostream& outputStream, const DynamicStringArray& rhs);
	//   Precondition: The outputStream is open and ready for output. rhs is a valid DynamicStringArray object.
	//   Postcondition: The contents of the dynamic array are output to the outputStream in the format {entry1, entry2, ..., entryN}.
	// If the array is empty, {} is output.

private:
	int size;
	StringPtr dynamicArray;
	StringPtr helperEntry(const std::string& newEntry) const;
	StringPtr helperDelete(int idxDelete);
	int searchEntry(const std::string& entry);
};


int main( )
{
	DynamicStringArray myVector;
	myVector.addEntry("hello");
	myVector.addEntry("beautiful");
	myVector.addEntry("world");
	std::cout << myVector;
	myVector.deleteEntry("bad");
	myVector.deleteEntry("beautiful");
	std::cout << myVector;
	try
	{
		std::cout << myVector[2] << '\n';
	} catch (const std::out_of_range& e) {
		std::cout << e.what() << '\n';
	}
	std::cout << myVector[0] << '\n';
	const ConstStringPtr myQuery = myVector.getEntry(1);
	const ConstStringPtr myQuery2 = myVector.getEntry(2);
	if (myQuery == nullptr)
		std::cout << "No valid element at the index 1\n";
	else
		std::cout << "Element at index 1: " << *myQuery << '\n';
	if (myQuery2 == nullptr)
		std::cout << "No valid element at the index 2\n";
	else
		std::cout << "Element at index 2: " << *myQuery2 << '\n';

	std::cout << '\n';
	return 0;
}

std::ostream& operator <<(std::ostream& outputStream, const DynamicStringArray& rhs)
{
	if (rhs.size == 0)
	{
		outputStream << "{}";
		return outputStream;
	}
	outputStream << "{";
	for (int idx = 0; idx < rhs.size - 1; idx++)
		outputStream << rhs.dynamicArray[idx] << ", ";
	
	outputStream << rhs.dynamicArray[rhs.size - 1] << "}\n";
	return outputStream;
}

DynamicStringArray::DynamicStringArray(const DynamicStringArray& rhs) : size(rhs.size), dynamicArray(nullptr)
{
	if (size == 0)	return;
	dynamicArray = new std::string[size];
	for (int idx = 0; idx < rhs.size; idx++)
		dynamicArray[idx] = rhs.dynamicArray[idx];
}

const DynamicStringArray& DynamicStringArray::operator =(const DynamicStringArray& rhs)
{
	if (this == &rhs)	return *this;
	
	if (size != rhs.size)
	{
		size = rhs.size;
		delete [] dynamicArray;
		dynamicArray = (size > 0) ? new std::string[size] : nullptr;
	}
	for (int idx = 0; idx < size; idx++)
		dynamicArray[idx] = rhs.dynamicArray[idx];

	return *this;
}

const std::string& DynamicStringArray::operator [](const int idx) const
{
	if (size == 0 || idx < 0 || idx >= size)
		throw std::out_of_range("Index out of bounds\n");
	return dynamicArray[idx];
}

ConstStringPtr DynamicStringArray::getEntry(const int idx) const
{
	if (idx < 0 || idx >= size)
		return nullptr;
	return (dynamicArray + idx);
	// return &dynamicArray[idx];
}

bool DynamicStringArray::deleteEntry(const std::string& entry)
{
	const int idxDelete = searchEntry(entry);
	if (idxDelete == -1) return false;
	const StringPtr temp = helperDelete(idxDelete);
	delete [] dynamicArray;
	dynamicArray = temp;
	size--;
	return true;
}

StringPtr DynamicStringArray::helperDelete(const int idxDelete)
{
	if (size == 1) return nullptr;
	const StringPtr newArray = new std::string[size - 1];
	for (int idx = 0, newIdx = 0; idx < size; idx++)
		if (idx != idxDelete)
			newArray[newIdx++] = dynamicArray[idx];
	return newArray;
}

int DynamicStringArray::searchEntry(const std::string& entry)
{
	if (size == 0)	return -1;
	for (int idx = 0; idx < size; idx++)
		if (dynamicArray[idx] == entry)
			return idx;

	return -1;
}

void DynamicStringArray::addEntry(const std::string& newEntry)
{
	const StringPtr temp = helperEntry(newEntry);
	delete [] dynamicArray;
	dynamicArray = temp;
	size++;
}

StringPtr DynamicStringArray::helperEntry(const std::string& newEntry) const
{
	const StringPtr newArray = new std::string[size + 1];
	for (int idx = 0; idx < size; idx++)
		newArray[idx] = dynamicArray[idx];
	newArray[size] = newEntry;
	return newArray;
}
