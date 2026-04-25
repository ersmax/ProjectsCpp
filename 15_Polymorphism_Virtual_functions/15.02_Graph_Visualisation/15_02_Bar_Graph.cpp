#include <iostream>
#include <iomanip>
#include "15_02_Bar_Graph.h"

namespace myGraph
{
	BarGraph::BarGraph() : Graph()
	{ /* Body intentionally left empty */ }

	BarGraph::BarGraph(const Graph& anotherGraph) : Graph(anotherGraph)
	{ /* Copy LabelValue.nameCategory, LabelValue.valueCategory, maxValue and numberStars */ }

	void BarGraph::draw()
	{
		const int nCategories = getCategories();
		if (nCategories == 0)
		{
			std::cout << "No categories to draw\n";
			return;
		}
		computeStars();
		constexpr int COL_WIDTH = 8;
		
		// for each row: print axis value and then print * if current bar height >= row
		// Start from MAX_SCALE + 1 to write the label for the max value
		for (int row = MAX_SCALE + 1; row > 0; row--)
		{
			// * column
			for (int col = 0; col < nCategories; col++)
			{
				const int stars = getStars(col);
				if (row == stars + 1)
					std::cout << std::setw(COL_WIDTH) << std::fixed << std::showpoint << std::setprecision(1) << getValue(col);
				else if (stars >= row)	
					std::cout << std::setw(COL_WIDTH) << "*";
				else
					std::cout << std::setw(COL_WIDTH) << "";
			}
			std::cout << "\n";
		}
		for (int col = 0; col < nCategories; col++)
			std::cout << std::string(COL_WIDTH, '-');
		std::cout << '\n';
		for (int col = 0; col < nCategories; col++)
		{
			std::string label = getLabel(col);
			if (label.size() > static_cast<size_t>(COL_WIDTH - 1))
				label = label.substr(0, COL_WIDTH - 1);
			std::cout << std::setw(COL_WIDTH) << label;
		}
		std::cout << '\n';
	}
} // myGraph