/*
Reread the code in Display 10.9.Then, write a class TwoD that implements the
two - dimensional dynamic array of doubles using ideas from this display in its
constructors.You should have a private member of type pointer to double to point
to the dynamic array, and two int(or unsigned int) values that are MaxRows and
MaxCols.
You should supply a default constructor for which you are to choose a default
maximum row and column sizes and a parameterized constructor that allows the
programmer to set maximum row and column sizes.
Further, you should provide a void member function that allows setting a particular row 
and column entry and a member function that returns a particular row and
column entry as a value of type double.
Remark: It is difficult or impossible(depending on the details) to overload[] so
it works as you would like for two - dimensional arrays.So simply use accessor and
mutator functions using ordinary function notation.
Overload the + operator as a friend function to add two two - dimensional arrays.
This function should return the TwoD object whose ith row, jth column element is
the sum of the ith row, jth column element of the left - hand operand TwoD object
and the ith row, jth column element of the right - hand operand TwoD object.
Provide a copy constructor, an overloaded operator =, and a destructor.
Declare class member functions that do not change the data as const members.
*/

#include <iostream>

constexpr int MAX = 50;

typedef double *DoublePtr;

class TwoD
{
public:
	TwoD() : maxRows(MAX), maxCols(MAX) { setGrid(MAX, MAX); }
	TwoD(const int rows) : maxRows(rows), maxCols(rows) { setGrid(rows, rows); }
	TwoD(const int rows, const int cols) : maxRows(rows), maxCols(cols) { setGrid(rows, cols); }
	TwoD(const TwoD& secondGrid);
	TwoD& operator =(const TwoD& secondGrid);
	~TwoD();
	void changeValue();
	double getValue() const;
private:
	DoublePtr *arrayPtr;
	void setGrid(int rows, int cols);
	void createGrid();
	int maxRows;
	int maxCols;
};

int validateInput();
double validateNumber();
int* getCoordinates(int maxRows, int maxCols);

int main( )
{
	std::cout << '\n';
	return 0;
}

void TwoD::changeValue()
{
	const int *coordinates = getCoordinates(maxRows, maxCols);
	if (coordinates == nullptr)
		return;

	std::cout << "Enter the desired value:\n";
	arrayPtr[coordinates[0]][coordinates[1]] = validateNumber();
	delete [] coordinates;
}

int* getCoordinates(const int maxRows, const int maxCols)
{
	std::cout << "Enter a valid row to change (1-" << maxRows << "):\n";
	int idxRow = validateInput();
	idxRow--;
	if (idxRow < 0 || idxRow >= maxRows)
	{
		std::cout << "Row does not exist\n";
		return nullptr;
	}
	std::cout << "Enter a valid column to change (1-" << maxCols << "):\n";
	int idxCol = validateInput();
	idxCol--;
	if (idxCol < 0 || idxCol >= maxCols)
	{
		std::cout << "Columns does not exist\n";
		return nullptr;
	}
	return (new int[2] {idxRow, idxCol});
}

void TwoD::setGrid(const int rows, const int cols)
{
	if (rows <= 0 || cols <= 0)
		throw std::invalid_argument("Not a valid array\n");

	createGrid();

	// Initialize to 0
	for (int idxRow = 0; idxRow < maxRows; idxRow++)
		for (int idxCol = 0; idxCol < maxCols; idxCol++)
			arrayPtr[idxRow][idxCol] = 0;
}

void TwoD::createGrid()
{
	arrayPtr = new DoublePtr[maxRows];
	for (int idxRow = 0; idxRow < maxRows; idxRow++)
		arrayPtr[idxRow] = new double[maxCols];
}

TwoD& TwoD::operator =(const TwoD& secondGrid)
{
	// Check same object
	if (this == &secondGrid)
		return *this;
	
	// Check same size
	if (maxRows != secondGrid.maxRows || maxCols != secondGrid.maxCols)
	{
		for (int idxRow = 0; idxRow < maxRows; idxRow++)
			delete [] arrayPtr[idxRow];
		delete [] arrayPtr;
		createGrid();
	}
	// Assign new values
	for (int idxRow = 0; idxRow < maxRows; idxRow++)
		for (int idxCol = 0; idxCol < maxCols; idxCol++)
			arrayPtr[idxRow][idxCol] = secondGrid.arrayPtr[idxRow][idxCol];

	return *this;
}

TwoD::TwoD(const TwoD& secondGrid) :	arrayPtr(nullptr), 
										maxRows(secondGrid.maxRows),
										maxCols(secondGrid.maxCols)
{
	// Deep copy: initialize arrayPtr
	createGrid();

	// Complete, independent copy in the new 2D variable pointed by (*this).arrayPtr
	for (int idxRow = 0; idxRow < maxRows; idxRow++)
		for (int idxCol = 0; idxCol < maxCols; idxCol++)
			arrayPtr[idxRow][idxCol] = secondGrid.arrayPtr[idxRow][idxCol];
}

TwoD::~TwoD()
{
	for (int idxRow = 0; idxRow < maxRows; idxRow++)
		delete [] arrayPtr[idxRow];
	delete [] arrayPtr;
}

int validateInput()
{
	int input;
	while (true)
	{
		if (!(std::cin >> input))
		{
			std::cout << "Not a valid input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return input;
	}
}

double validateNumber()
{
	double input;
	while (true)
	{
		if (!(std::cin >> input))
		{
			std::cout << "Not a valid input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return input;
	}
}
