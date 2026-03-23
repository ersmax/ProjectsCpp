//   This is the interface header for a class of partially filled arrays of doubles.

#ifndef PFARRAYD_H_11_02
#define PFARRAYD_H_11_02

#include <iostream>

typedef double *DoublePtr;

namespace myNamespace
{
	class PFArrayD
	{
	public:
		PFArrayD();
		//   Postcondition: Initialize the array with a capacity of 50

		PFArrayD(int capacityValue);
		PFArrayD(const PFArrayD& pfaObject);
		//   Precondition: Copy constructor
		PFArrayD& operator =(const PFArrayD& rightSide);
		//   Precondition: Overloaded assignment operator
		~PFArrayD();

		void addElement(double element);
		//   Precondition: the array is not full
		//   Postcondition: The element has been added

		bool full() const;
		//   Postcondition: Returns true if the array is full, false otherwise

		int getCapacity() const;
		int getNumberUSed() const;
		void emptyArray();
		double& operator [](int idx) const;
		//   Postcondition: Read and change access to elements 0 through numberUsed - 1

		friend std::istream& operator >>(std::istream& inputStream, PFArrayD& myObject);
		//   Precondition: inputStream is open and myObject is not full
		//   Postcondition: The user has entered up to capacity nonnegative numbers, 
		// and these have been stored in myObject. The first negative number has not been stored.

		friend std::ostream& operator <<(std::ostream& outputStream, const PFArrayD& myObject);
		//   Precondition: outputStream is open and myObject is not empty
		//   Postcondition: The elements of myObject have been output on outputStream with one space between them 

	private:
		DoublePtr myArray;
		int capacity;
		int used;
	};

	
} // myNamespace

#endif