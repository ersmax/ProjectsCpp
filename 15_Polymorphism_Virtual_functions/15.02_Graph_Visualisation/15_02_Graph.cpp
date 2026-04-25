#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "15_02_Graph.h" 
#include "15_02_Validation.h"

namespace myGraph
{
	Graph::Graph() : maxValue(0)
	{ /* body intentionally left empty */ }

	Graph::Graph(const Graph& anotherGraph) = default;


	const LabelValue& Graph::operator [](const size_t idx) const
	{
		if (idx >= data.size())
			throw std::out_of_range("Index out of range\n");

		return data[idx];
	}

	const std::string& Graph::getLabel(const size_t idx) const
	{
		if (idx >= data.size())
			throw std::out_of_range("Index out of range\n");

		return (*this)[idx].nameCategory;
	}

	double Graph::getValue(const size_t idx) const
	{
		if (idx >= data.size())
			throw std::out_of_range("Index out of range\n");

		return (*this)[idx].valueCategory;
	}

	int Graph::getStars(const size_t idx) const
	{
		if (idx >= numberStars.size())
			throw std::out_of_range("Index out of range\n");

		return numberStars[idx];
	}

	double Graph::getMaxValue() const { return maxValue; }

	int Graph::getCategories() const { return static_cast<int>(data.size()); }

	void Graph::draw()
	{
		std::cout << "Not what you would expect\n";
	}

	void Graph::addStatistics(const LabelValue& statistics)
	{
		data.push_back(statistics);
		maxValue = std::max(maxValue, statistics.valueCategory);
	}

	void Graph::erase()
	{
		data.clear();
		numberStars.clear();
		maxValue = 0.0;
	}

	void Graph::computeStars()
	{
		if (getMaxValue() <= EPSILON)
			throw std::out_of_range("No value exists\n");

		// clear old normalized data, before pushing new stars
		numberStars.clear();	
		for (const LabelValue& label : data)
		{
			int stars = static_cast<int>(MAX_SCALE * label.valueCategory / getMaxValue());
			numberStars.push_back(stars);
		}
	}

	std::istream& operator >>(std::istream& inputStream, Graph& aGraph)
	{
		using myValidation::readNumber;
		int categories;
		do
		{
			std::cout << "How many categories to input?\n";
			readNumber(inputStream, categories);
		} while (categories <= 0);

		for (int idx = 0; idx < categories; idx++)
		{
			LabelValue newLabel;
			inputStream >> newLabel;
			aGraph.addStatistics(newLabel);
		}

		return inputStream;
	}

	std::istream& operator >>(std::istream& inputStream, LabelValue& aLabel)
	{
		using myValidation::readName;
		using myValidation::readNumber;
		do
		{
			std::cout << "Enter the category name:\n";
			readName(inputStream, aLabel.nameCategory);
		} while (aLabel.nameCategory.empty());

		do
		{
			std::cout << "Enter the category value (greater than 0):\n";
			readNumber(inputStream, aLabel.valueCategory);
		} while (aLabel.valueCategory <= EPSILON);

		return inputStream;
	}

} // myGraph
