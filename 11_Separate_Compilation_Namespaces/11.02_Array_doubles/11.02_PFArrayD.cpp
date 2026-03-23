//   This is the implementation file for the interface of a class of partially filled arrays of doubles.

#include <iostream>
#include <cstdlib>
#include "11.02_PFArrayD.h"

namespace myNamespace
{
	PFArrayD::PFArrayD() : capacity(50), used(0)
	{
		myArray = new double[capacity];
	}

	PFArrayD::PFArrayD(const int capacityValue) : capacity(capacityValue), used(0)
	{
		myArray = new double[capacity];
	}

	PFArrayD::PFArrayD(const PFArrayD& pfaObject) : capacity(pfaObject.capacity), used(pfaObject.used)
	{
		myArray = new double[capacity];
		for (int idx = 0; idx < used; idx++)
			myArray[idx] = pfaObject.myArray[idx];
	}

	PFArrayD::~PFArrayD()
	{
		delete [] myArray;
	}

	PFArrayD& PFArrayD::operator =(const PFArrayD& rightSide)
	{
		if (&rightSide == this)		return *this;
		
		if (capacity != rightSide.capacity)
		{
			delete [] myArray;
			myArray = new double[rightSide.capacity];
		}
		
		capacity = rightSide.capacity;
		used = rightSide.used;
		for (int idx = 0; idx < used; idx++)
			myArray[idx] = rightSide.myArray[idx];

		return *this;
	}

	void PFArrayD::addElement(const double element)
	{
		if (used >= capacity)
		{
			std::cout << "Attempt to exceed capacity in PFArrayD\n";
			std::exit(1);
		}
		myArray[used] = element;
		used++;
	}

	double& PFArrayD::operator [](const int idx) const
	{
		if (idx >= used)
		{
			std::cout << "Illegal index in PFArrayD\n";
			std::exit(1);
		}
		return myArray[idx];
	}

	std::istream& operator >>(std::istream& inputStream, PFArrayD& myObject)
	{
		double number;
		inputStream >> number;
		while ((number >= 0) && !(myObject.full()))
		{
			myObject.addElement(number);
			inputStream >> number;
		}
		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const PFArrayD& myObject)
	{
		for (int idx = 0; idx < myObject.used; idx++)
			outputStream << myObject.myArray[idx] << " ";
		outputStream << '\n';
		return outputStream;
	}

	int PFArrayD::getCapacity() const { return capacity; }

	int PFArrayD::getNumberUSed() const { return used; }

	void PFArrayD::emptyArray() { used = 0; }

	bool PFArrayD::full() const { return (capacity == used); }

} // myNamespace
