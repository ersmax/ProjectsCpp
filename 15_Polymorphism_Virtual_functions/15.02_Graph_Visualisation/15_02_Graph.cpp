#include <iostream>
#include <algorithm>
#include "15_02_Graph.h" 

namespace myGraph
{
	Graph::Graph() : maxValue(0)
	{ /* body intentionally left empty */ }

	Graph::Graph(const Graph& anotherGraph) = default;

	int Graph::getCategories() const { return static_cast<int>(data.size()); }

	void Graph::addStatistics(const LabelValue& statistics)
	{
		data.push_back(statistics);
		maxValue = std::max(maxValue, statistics.valueCategory);
	}

	std::istream& operator>>(std::istream& inputStream, Graph& aGraph)
	{
		// TODO: ask how many labels
		// Loop
		// addStat
		// Repeat until n > labels ..
		return inputStream;
	}

	std::istream& operator >>(std::istream& inputStream, LabelValue& aLabel)
	{
		// TODO : using myNamespaceValidation::readName
		// TODO : using myNamespaceValidation::readNumber
		// TODO : readName(inputStream, aLabel.nameCategory) ..
		// TODO : readNumber(inputStream, aLabel.valueCategory) ..
		return inputStream;
	}

} // myGraph
