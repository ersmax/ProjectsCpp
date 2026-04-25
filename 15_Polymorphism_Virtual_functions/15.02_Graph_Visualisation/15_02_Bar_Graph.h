#ifndef BAR_GRAPH_15_02_H
#define BAR_GRAPH_15_02_H

#include "15_02_Graph.h"

namespace myGraph
{
	class BarGraph : public Graph
	{
	public:
		BarGraph();
		//   Postcondition: creates an empty bar graph
		BarGraph(const Graph& anotherGraph);
		//   Postcondition: creates a bar graph with the same LabelValue.nameCategory, 
		// LabelValue.valueCategory, maxValue and numberStars as anotherGraph
		virtual void draw() override final;
		//   Postcondition: draws the bar graph on the screen by placing
		// the character `*` at suitable locations on the screen.

	private:
	};

} // myGraph

#endif // BAR_GRAPH_15_02_H


