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
	// Copy constructor

	TwoD& operator =(const TwoD& secondGrid);
	~TwoD();
	friend std::ostream& operator <<(std::ostream& outputStream, const TwoD& myVector);
	//   Precondition: outputStream is a valid output stream and myVector is a valid TwoD object.
	//   Postcondition: Writes the contents of the 2D array to the output stream, 
	// with each row on a new line and each element separated by a space.

	friend std::istream& operator >>(std::istream& inputStream, TwoD& myVector);
	//   Postcondition: Reads the contents of the 2D array from the input stream,
	// with each row on a new line and each element separated by a space.
	// If an invalid input is encountered, the function should prompt the user to re-enter 
	// the whole row until valid input is provided. A dynamic temporary array is used 
	// to store the valid input for each row before copying it back to the 2D array.

	DoublePtr operator [](const int coordinate) const { return arrayPtr[coordinate]; }
	//   Precondition: coordinate is a valid row/column index of the 2D array.
	//   Postcondition: Returns a pointer to the row of the 2D array corresponding 
	// to the given coordinate, allowing for array-style access to the elements of the 2D array.

	friend const TwoD operator +(const TwoD& array1, const TwoD& array2);
	//   Precondition: array1 and array2 are valid TwoD objects of the same size 
	// (i.e., they have the same number of rows and columns).
	//   Postcondition: Returns a new TwoD object whose ith row, jth column element is 
	// the sum of the ith row, jth column element of array1 and the ith row, jth column element of array2.

	void changeValue();
	//   Postcondition: Prompts the user to enter valid row and column indices and a new value,
	// and updates the corresponding element in the 2D array with the new value.

	double getValue() const;
	//   Postcondition: Prompts the user to enter valid row and column indices, 
	// and returns the value of the corresponding element in the 2D array.

	int getRows() const { return maxRows; }
	int getCols() const { return maxCols; }
private:
	DoublePtr *arrayPtr;
	void setGrid(int rows, int cols);
	//   Precondition: rows and cols are positive integers representing the number of rows and columns of the 2D array.
	//   Postcondition: Initializes the 2D array with the given number of rows and columns, 
	// and sets all elements to 0. If rows or cols are not positive, the function should throw an exception.
	// Use the helper createGrid() function to allocate memory for the 2D array.

	void createGrid();
	//   Postcondition: Allocates memory for the 2D array based on the current values of maxRows and maxCols,
	// and initializes the arrayPtr member variable to point to the newly allocated 2D array.

	int maxRows;
	int maxCols;
};

int validateInput();
//   Postcondition: Prompts the user to enter an integer and validates the input, returning the integer value.

double validateNumber();
//   Postcondition: Prompts the user to enter a double and validates the input, returning the double value.

int* getCoordinates(int maxRows, int maxCols);
//   Precondition: maxRows and maxCols are positive integers representing the maximum number of rows and columns of the 2D array.
//   Postcondition: Prompts the user to enter valid row and column indices, 
// and returns a pointer to an array of two integers containing the row and column indices (in that order). 
// If the user enters invalid indices, the function should return nullptr.
// The function returns a pointer to a dynamically allocated array of two integers, 
// which should be deallocated by the caller after use.

int main( )
{
	TwoD aVector1(2, 2);
	TwoD aVector2(2, 2);
	std::cout << "Enter valid input for the first vector:\n";
	std::cin >> aVector1;
	std::cout << "Enter valid input for the second vector:\n";
	std::cin >> aVector2;
	std::cout << "First vector:\n";
	std::cout << aVector1;
	std::cout << "Second vector:\n";
	std::cout << aVector2;

	TwoD sumVectors = aVector1 + aVector2;
	std::cout << "Sum of two grids:\n" << sumVectors << '\n';
	std::cout << "Last row, las column element: " << sumVectors[sumVectors.getRows() - 1][sumVectors.getCols() - 1] << '\n';
	std::cout << "Querying the grid\n";
	std::cout << sumVectors.getValue() << '\n';
	std::cout << "Changing the value\n";
	sumVectors.changeValue();
	std::cout << "New sum of two grids:\n" << sumVectors << '\n';
	std::cout << '\n';
	return 0;
}

std::istream& operator >>(std::istream& inputStream, TwoD& myVector)
{
	for (int idxRow = 0; idxRow < myVector.maxRows; idxRow++)
	{
		double input;
		std::cout << "Enter " << idxRow + 1 << " row:\n";
		int idx = 0;
		
		// Use a temporary dynamic array to save the correct row
		const DoublePtr pointTemp = new double[myVector.maxCols];
		while (idx < myVector.maxCols)
		{
			if (!(inputStream >> input))
			{
				std::cout << "Not a valid number. Re-enter the row.\n";
				inputStream.clear();
				inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				idx = 0;
				continue;
			}
			pointTemp[idx] = input;
			idx++;
		}
		inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		// Copy Back the temporary dynamic array and deallocate
		for (int idxCol = 0; idxCol < myVector.maxCols; idxCol++)
			myVector[idxRow][idxCol] = pointTemp[idxCol];
		delete [] pointTemp;
	}
	return inputStream;
}

std::ostream& operator <<(std::ostream& outputStream, const TwoD& myVector)
{
	for (int idxRow = 0; idxRow < myVector.maxRows; idxRow++)
	{
		for (int idxCol = 0; idxCol < myVector.maxCols; idxCol++)
			outputStream << myVector[idxRow][idxCol] << " ";
		outputStream << '\n';
	}
	return outputStream;
}

const TwoD operator +(const TwoD& array1, const TwoD& array2)
{
	if (array1.maxRows != array2.maxRows ||
		array1.maxCols != array2.maxCols)
		throw std::invalid_argument("Cannot add two matrices of different sizes\n");

	TwoD sum(array1.maxRows, array1.maxCols);
	for (int idxRow = 0; idxRow < array1.maxRows; idxRow++)
		for (int idxCol = 0; idxCol < array1.maxCols; idxCol++)
			sum[idxRow][idxCol] = array1[idxRow][idxCol] + array2[idxRow][idxCol];
	return sum;
}

double TwoD::getValue() const
{
	std::cout << "You wish to view a value\n";
	const int* coordinates = getCoordinates(maxRows, maxCols);
	if (coordinates == nullptr)
		return std::numeric_limits<double>::quiet_NaN();

	const double value = arrayPtr[coordinates[0]][coordinates[1]];
	delete [] coordinates;
	return value;
}

void TwoD::changeValue()
{
	std::cout << "You wish to change a value\n";
	const int *coordinates = getCoordinates(maxRows, maxCols);
	if (coordinates == nullptr)
		return;

	std::cout << "Enter the desired value:\n";
	arrayPtr[coordinates[0]][coordinates[1]] = validateNumber();
	delete [] coordinates;
}

int* getCoordinates(const int maxRows, const int maxCols)
{
	std::cout << "Enter a valid row (1-" << maxRows << "):\n";
	int idxRow = validateInput();
	idxRow--;
	if (idxRow < 0 || idxRow >= maxRows)
	{
		std::cout << "Row does not exist\n";
		return nullptr;
	}
	std::cout << "Enter a valid column (1-" << maxCols << "):\n";
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
