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
		Graph(const Graph& anotherGraph);
		int getCategories() const;
		double getMaxValue() const;
		const LabelValue& operator [](size_t idx) const;
		const std::string& getLabel(size_t idx) const;
		double getValue(size_t idx) const;
		int getStars(size_t idx) const;
		friend std::istream& operator >>(std::istream& inputStream, Graph& aGraph);
		void addStatistics(const LabelValue& statistics);
		void computeStars();
		void erase();
		virtual void draw() = 0;
		virtual ~Graph() = default;
	private:
		std::vector<LabelValue> data;
		//   an array of double values
		double maxValue;
		//   the max value among all
		std::vector<int> numberStars;
		//   a normalized vector of integers that count stars
	};

	std::istream& operator >>(std::istream& inputStream, LabelValue& aLabel);

} // myGraph

#endif // GRAPH_15_02_H
