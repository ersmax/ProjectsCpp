#include <iostream>
#include "15_01_Graph.h" 

namespace myGraph
{
	Graph::Graph()
	{ /* body intentionally left empty */ }

	Graph::~Graph()
	{ /* body intentionally left empty */ }

	void Graph::erase()
	{
		std::cout << "Calling erase() of class Graph\n";
	}

	void Graph::draw()
	{
		std::cout << "Calling draw() of class Graph\n";
	}

} // myGraph
