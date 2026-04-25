#ifndef LINE_GRAPH_15_02_H
#define LINE_GRAPH_15_02_H

#include "15_02_Graph.h"

namespace myGraph
{
	class LineGraph : public Graph
	{
	public:
		LineGraph();
		LineGraph(const Graph& anotherGraph);
		virtual void draw() override final;
	private:
	};

} // myGraph

#endif // LINE_GRAPH_15_02_H
