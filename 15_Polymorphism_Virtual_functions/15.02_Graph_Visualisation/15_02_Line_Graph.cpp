#include <iostream>
#include "15_02_Line_Graph.h"

namespace myGraph
{
	LineGraph::LineGraph()
	{ /* Body intentionally left empty */ }

	void LineGraph::erase()
	{
		std::cout << "Calling erase() of LineGraph\n";
	}

	void LineGraph::draw()
	{
		std::cout << "Calling draw() of LineGraph\n";
	}

} // myGraph