#include "DFS.h"
#include "Graph.h"

#include <stack>
#include <iostream>
#include <map>

void DFS::execute()
{
	std::stack<std::pair<int, int>> nodes;

	nodes.push({ Graph::srcNode.first, Graph::srcNode.second });

	while (!nodes.empty())
	{
		std::pair<int,int> node = nodes.top();
		nodes.pop();

		std::cout << node.first << ',' << node.second << std::endl;

		if (Graph::grid[node.first][node.second] < 0)
		{
			continue;
		}

		if (Graph::grid[node.first][node.second] == -3)
		{
			continue;
		}

		if (node.first == Graph::destNode.first && node.second == Graph::destNode.second)
		{
			break;
		}

		Graph::grid[node.first][node.second] = -1;
		SDL_Delay(5);
		Graph::drawGraph();

		for (int k = 0; k < 4; k++)
		{
			dy = node.first+Y[k];
			dx = node.second+X[k];

			if ((dy >= 0 && dx < 30 && dy < 20 && dx >= 0) && (Graph::grid[dy][dx] != -1))
			{
				nodes.push({ dy, dx });
				path[{ dy,dx }] = node;
			}
		}
	}
	printPath();
}
