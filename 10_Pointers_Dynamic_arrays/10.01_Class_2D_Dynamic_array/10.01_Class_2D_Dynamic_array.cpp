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
	~TwoD();
private:
	DoublePtr *arrayPtr;
	void setGrid(int rows, int cols);
	int maxRows;
	int maxCols;
};

int main( )
{
	std::cout << '\n';
	return 0;
}

void TwoD::setGrid(const int rows, const int cols)
{
	if (rows <= 0 || cols <= 0)
		throw std::invalid_argument("Not a valid array\n");

	arrayPtr = new DoublePtr[maxRows];
	for (int idx = 0; idx < maxRows; idx++)
		arrayPtr[idx] = new double[maxCols];

	// Initialize to 0
	for (int idx = 0; idx < maxRows; idx++)
		for (int jdx = 0; jdx < maxCols; jdx++)
			arrayPtr[idx][jdx] = 0;
}

TwoD::~TwoD()
{
	for (int idx = 0; idx < maxRows; idx++)
		delete [] arrayPtr[idx];
	delete [] arrayPtr;
}
