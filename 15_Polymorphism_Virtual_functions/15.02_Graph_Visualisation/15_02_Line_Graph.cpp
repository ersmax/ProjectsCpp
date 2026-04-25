#include <iostream>
#include <iomanip>
#include "15_02_Line_Graph.h"

namespace myGraph
{
	LineGraph::LineGraph() : Graph()
	{ /* Body intentionally left empty */ }

	LineGraph::LineGraph(const Graph& anotherGraph) : Graph(anotherGraph)
	{ /* Copy LabelValue.nameCategory, LabelValue.valueCategory, maxValue and numberStars */ }

    void LineGraph::draw()
    {
        const int nCategories = getCategories();
        if (nCategories == 0)
        {
            std::cout << "No categories to draw\n";
            return;
        }

        computeStars();

        constexpr int COL_WIDTH = 7;   // wider = cleaner spacing
        constexpr int LINK_WIDTH = 3;  // spacing between columns

        for (int row = MAX_SCALE + 1; row > 0; row--)
        {
            for (int col = 0; col < nCategories; col++)
            {
                const int current = getStars(col);

                // Print value above star
                if (row == current + 1)
                    std::cout << std::setw(COL_WIDTH) << std::fixed << std::setprecision(1) << getValue(col);
                else if (row == current)
                    std::cout << std::setw(COL_WIDTH) << "*";
                else
                    std::cout << std::setw(COL_WIDTH) << " ";

                // Connector (between columns)
                if (col < nCategories - 1)
                {
                    const int next = getStars(col + 1);
                    char connector = ' ';
                    const int midRow = current + (next - current) / 2;
                    if (row == midRow)
                    {
                        if (next == current) connector = '-';
                        else if (next > current) connector = '/';
                        else connector = '\\';
                    }
                    std::cout << std::setw(LINK_WIDTH) << connector;
                }
            }
            std::cout << '\n';
        }

        // X-axis
        constexpr int SINGLE_WIDTH = (COL_WIDTH + LINK_WIDTH);
        const int totWidth = static_cast<int>(SINGLE_WIDTH * nCategories);
        std::cout << std::string(totWidth, '-');
        std::cout << '\n';

        // Labels
        for (int i = 0; i < nCategories; i++)
            std::cout << std::setw(SINGLE_WIDTH) << getLabel(i).substr(0, 4);
        std::cout << '\n';
    }

} // myGraph