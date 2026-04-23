#include <iostream>
#include "15_01_Graph.h"
#include "15_01_Bar_Graph.h"
#include "15_01_Line_Graph.h"

int main( )
{
	using myGraph::BarGraph;
	using myGraph::LineGraph;
	using myGraph::Graph;

	BarGraph bar;
	std::cout << "Derived class BarGraph object calling draw() and erase()\n";
	bar.draw();
	bar.erase();

	LineGraph line;
	std::cout << "Derived class LineGraph object calling draw() and erase()\n";
	line.draw();
	line.erase();

	Graph *pGraph;
	pGraph = new LineGraph;
	std::cout << "Calling method draw() on derived class Line Graph\n";
	pGraph->draw();

	std::cout << '\n';
	return 0;
}