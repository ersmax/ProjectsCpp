#ifndef GRAPH_15_01_H
#define GRAPH_15_01_H

namespace myGraph
{
	class Graph
	{
	public:
		Graph();
		virtual ~Graph() = 0;
		virtual void erase() = 0;
		virtual void draw() = 0;
	private:
	};

} // myGraph

#endif // GRAPH_15_01_H
