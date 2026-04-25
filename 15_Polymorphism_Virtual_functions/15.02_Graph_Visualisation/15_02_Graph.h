#ifndef GRAPH_15_02_H
#define GRAPH_15_02_H
#include <vector>
#include <string>
#include <iostream>

namespace myGraph
{
	constexpr int MAX_SCALE = 10;
	constexpr double EPSILON = 1e-9;

	struct LabelValue
	{
		std::string nameCategory;
		double valueCategory;
	};

	class Graph
	{
	public:
		Graph();
		//   Postcondition: creates an empty graph with no categories and maxValue = 0
		Graph(const Graph& anotherGraph);
		//   Postcondition: creates a graph with the same LabelValue.nameCategory, 
		// LabelValue.valueCategory, maxValue and numberStars as anotherGraph
		// This copy constructor is needed to create a BarGraph or LineGraph from an existing Graph
		int getCategories() const;
		//   Postcondition: returns the number of categories in the graph
		double getMaxValue() const;
		//   Postcondition: returns the maximum value among all categories in the graph
		const LabelValue& operator [](size_t idx) const;
		//   Postcondition: returns the LabelValue at index idx. If idx is out of range, throws an out_of_range exception
		const std::string& getLabel(size_t idx) const;
		//   Postcondition: returns the name of the category at index idx. 
		double getValue(size_t idx) const;
		//   Postcondition: returns the value of the category at index idx.
		int getStars(size_t idx) const;
		//   Postcondition: returns the number of stars for the category at index idx.
		friend std::istream& operator >>(std::istream& inputStream, Graph& aGraph);
		//   Postcondition: inputs the number of categories and then inputs the name and value for each category.
		void addStatistics(const LabelValue& statistics);
		//   Postcondition: adds the given LabelValue to the graph and updates maxValue if necessary
		void computeStars();
		//   Postcondition: computes the number of stars for each category based on its value and maxValue, 
		// and stores it in numberStars
		void erase();
		//   Postcondition: erases all data from the graph and resets maxValue to 0
		virtual void draw() = 0;
		//   Postcondition: draws the graph on the screen. 
		// This is a pure virtual function that must be overridden by derived classes
		virtual ~Graph() = default;
		//   Postcondition: destroys the graph. Since there are no dynamically allocated resources, 
		// the default destructor is sufficient
	private:
		std::vector<LabelValue> data;
		//   an array of double values with associated name of the category
		double maxValue;
		//   the max value among all
		std::vector<int> numberStars;
		//   a normalized vector of integers that count stars from 0 to MAX_SCALE for each category, 
		// based on the value and maxValue
	};

	std::istream& operator >>(std::istream& inputStream, LabelValue& aLabel);
	//   Postcondition: inputs the name and value for a LabelValue. The name is read as a single word (no spaces).

} // myGraph

#endif // GRAPH_15_02_H
