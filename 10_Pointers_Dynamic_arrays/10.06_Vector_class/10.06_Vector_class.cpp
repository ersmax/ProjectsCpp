/*
One problem with dynamic arrays is that once the array is created using the new
operator the size cannot be changed. For example, you might want to add or delete
entries from the array similar to the behavior of a vector. This project asks you
to create a class called DynamicStringArray that includes member functions that
allow it to emulate the behavior of a vector of strings.
The class should have the following:
• A private member variable called dynamicArray that references a dynamic array
of type string.
• A private member variable called size that holds the number of entries in the
array.
• A default constructor that sets the dynamic array to nullptr and sets size
to 0.
• A function that returns size.
• A function named addEntry that takes a string as input. The function should
create a new dynamic array one element larger than dynamicArray, copy all
elements from dynamicArray into the new array, add the new string onto the
end of the new array, increment size, delete the old dynamicArray, and then
set dynamicArray to the new array.
• A function named deleteEntry that takes a string as input. The function
should search dynamicArray for the string. If not found, it returns false. If
found, it creates a new dynamic array one element smaller than dynamicArray.
It should copy all elements except the input string into the new array, delete
dynamicArray, decrement size, and return true.
• A function named getEntry that takes an integer as input and returns the
string at that index in dynamicArray. It should return nullptr if the index is
out of dynamicArray’s bounds.
• A copy constructor that makes a copy of the input object’s dynamic array.
• Overload the assignment operator so that the dynamic array is properly copied
to the target object.
• A destructor that frees up the memory allocated to the dynamic array.
Embed your class in a suitable test program.
*/

#include <iostream>
#include <stdexcept>
#include <string>

typedef std::string *StringPtr;


class DynamicStringArray
{
public:
	DynamicStringArray() : size(0), dynamicArray(nullptr) {};
	DynamicStringArray(const DynamicStringArray& rhs);
	~DynamicStringArray() { delete [] dynamicArray; }
	int getSize() const { return size; }
	void addEntry(const std::string& newEntry);
	bool deleteEntry(const std::string& entry);
	const std::string* getEntry(int idx) const;
	const DynamicStringArray& operator =(const DynamicStringArray& rhs);
	const std::string& operator [](int idx) const;
	friend std::ostream& operator <<(std::ostream& outputStream, const DynamicStringArray& rhs);
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
	const std::string* myQuery = myVector.getEntry(1);
	const std::string* myQuery2 = myVector.getEntry(2);
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

const std::string* DynamicStringArray::getEntry(const int idx) const
{
	if (idx < 0 || idx >= size)
		return nullptr;
	return (dynamicArray + idx);
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
