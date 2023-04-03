#include "Djikstra.h"
#include "Graph.h"

#include <queue>
#include <iostream>
#include <map>
#include <stack>
#include <cmath>

int Djikstra::distance(std::pair<int,int> node)
{
	return abs(Graph::srcNode.first - node.first) + abs(Graph::srcNode.second - node.second);
}

void Djikstra::execute()
{
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, Djikstra::cmp> nodes;
	std::map<std::pair<int, int>, int> pathCost;

	nodes.push({ Graph::srcNode.first, Graph::srcNode.second });
	pathCost[{ Graph::srcNode.first, Graph::srcNode.second }] = 0;

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
		SDL_Delay(10);
		Graph::drawGraph();

		for (int k = 0; k < 4; k++)
		{
			dy = node.first+Y[k];
			dx = node.second+X[k];

			if ((dy >= 0 && dx < 30 && dy < 20 && dx >= 0) && (Graph::grid[dy][dx] != -1))
			{
				std::pair<int, int> next = { dy,dx };
				int newCost = pathCost[node] + distance(next);
				if (pathCost.count(next) == 0 || newCost < pathCost[next])
				{
					nodes.push(next);
					path[next] = node;
					pathCost[next] = newCost;
				}
			}
		}
	}

	printPath();
}
