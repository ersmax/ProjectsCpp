#ifndef LINE_GRAPH_15_02_H
#define LINE_GRAPH_15_02_H

#include "15_02_Graph.h"

namespace myGraph
{
	class LineGraph : public Graph
	{
	public:
		LineGraph();
		//  Postcondition: creates an empty line graph
		LineGraph(const Graph& anotherGraph);
		//  Postcondition: creates a line graph with the same LabelValue.nameCategory,
		// LabelValue.valueCategory, maxValue and numberStars as anotherGraph
		virtual void draw() override final;
		//   Postcondition: draws the line graph on the screen by placing
		// the character `*` at suitable locations on the screen.
	private:
	};

} // myGraph

#endif // LINE_GRAPH_15_02_H
