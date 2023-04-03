#include "Graph.h"
#include "Algorithm.h"

#include <stack>

void Algorithm::printPath()
{
	std::stack<std::pair<int, int>> rpath;
	std::pair<int, int> node = {Graph::destNode.first, Graph::destNode.second};
	while(path.count(node))
	{
		node = path[node];
		rpath.push(node);
	}

	while (!rpath.empty())
	{
		node = rpath.top();
		rpath.pop();
		Graph::grid[node.first][node.second] = -4;
		SDL_Delay(50);
		Graph::drawGraph();
	}
}
