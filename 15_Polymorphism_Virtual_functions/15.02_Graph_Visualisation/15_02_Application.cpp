/*
Statistics are usually shown in the form of graphs. Graphs can be of different types,
such as bar graphs, line graphs, pie charts, and so on. A bar graph is shown with
vertical or horizontal bars against a scale, while a pie chart is shown by dividing
a circle into proportionate segments. In a well-designed system, these would be
derived from a common class, Graph. You are to implement such a system.
The class Graph is the base class. You should add only BarGraph and LineGraph
classes derived from Graph. Each class has stubs for member functions erase and
draw. Each of these member functions outputs a message telling what function has
been called and what the class of the calling object is. Since these are just stubs, they
do nothing more than output this message. The member functions should take no
arguments. There are three parts to this project:
a. Do the class definitions using no virtual functions. Compile and test.
b. Make the base class member functions virtual. Compile and test.
c. Explain the difference in results.
For a real example, you would have to replace the definition of each of these member
functions with code to do the actual drawing. You will be asked to do this in
Programming Project 15.2.
Use the following main function for all testing:
//This program tests Programming Problem 15.1.
#include <iostream>
#include "graph.h"
#include "bargraph.h"
#include "linegraph.h"
using std::cout;
int main( )
{
BarGraph bar;
cout <<
"\nDerived class BarGraph object calling draw( ) and
erase( ).\n";
bar.draw( );
bar.erase( );
LineGraph line;
cout <<
"\nDerived class LineGraph object calling draw( ) and
erase( ).\n";
line.draw( );
line.erase( );
return 0;
}

Project 15.02
Flesh out Programming Problem 15.1. Give new definitions for the various constructors
and member functions, Graph::draw, Graph::erase, BarGraph::draw,
BarGraph::erase, LineGraph::draw, and LineGraph::erase so that the
draw functions actually draw figures on the screen by placing the character ‘*’
at suitable locations on the screen. For the erase functions, you can simply clear
the screen (by outputting blank lines or by doing something more sophisticated).
There are a lot of details in this and you will have to decide on some of them on
your own.
*/




#include <iostream>
#include "15_02_Graph.h"
#include "15_02_Bar_Graph.h"
#include "15_02_Line_Graph.h"

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