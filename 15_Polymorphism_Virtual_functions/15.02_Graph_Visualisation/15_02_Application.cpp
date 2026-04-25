#include <iostream>
#include <vector>
#include "15_02_Graph.h"
#include "15_02_Bar_Graph.h"
#include "15_02_Line_Graph.h"

int main( )
{
	using myGraph::BarGraph;
	using myGraph::LineGraph;
	using myGraph::Graph;

	BarGraph *bar = new BarGraph;
	std::cout << "Enter data for the bar graph\n";
	std::cin >> *bar;
	// bar->draw();
	// bar.erase();

	LineGraph *line = new LineGraph(*bar);
	// Copy data from bar graph with copy constructor
	// line->draw();
	// line.erase();

	std::vector<Graph*> someGraphs;
	someGraphs.push_back(bar);
	someGraphs.push_back(line);
	for (Graph* graph : someGraphs)
	{
		graph->draw();
		std::cout << "\n\n";
	}
	
	delete bar;
	delete line;

	std::cout << '\n';
	return 0;
}