#ifndef GRAPH_15_02_H
#define GRAPH_15_02_H
#include <vector>
#include <string>
#include <iosfwd>

namespace myGraph
{
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
		friend std::istream& operator >>(std::istream& inputStream, Graph& aGraph);
		void addStatistics(const LabelValue& statistics);
		virtual void erase() = 0;
		virtual void draw() = 0;
		virtual ~Graph() = default;
	private:
		std::vector<LabelValue> data;
		//   an array of double values
		double maxValue;
		//   the max value among all
	};

	std::istream& operator >>(std::istream& inputStream, LabelValue& aLabel);

} // myGraph

#endif // GRAPH_15_02_H
