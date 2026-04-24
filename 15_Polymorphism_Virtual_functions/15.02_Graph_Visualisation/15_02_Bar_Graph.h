#ifndef BAR_GRAPH_15_02_H
#define BAR_GRAPH_15_02_H

#include "15_02_Graph.h"

namespace myGraph
{
	class BarGraph : public Graph
	{
	public:
		BarGraph();
		virtual void erase() override final;
		virtual void draw() override final;
	private:
	};

} // myGraph

#endif // BAR_GRAPH_15_02_H


