#include <iostream>
#include "15_02_Bar_Graph.h"

namespace myGraph
{
	BarGraph::BarGraph()
	{ /* Body intentionally left empty */ }

	void BarGraph::erase()
	{
		std::cout << "Calling erase() of BarGraph\n";
	}

	void BarGraph::draw()
	{
		std::cout << "Calling draw() of BarGraph\n";
	}

} // myGraph