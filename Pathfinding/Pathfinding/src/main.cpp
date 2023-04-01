#include "Graph.h"

int main(int argc, char* argv[])
{
	Graph graph;
	
	int error = 0;
	if (error = graph.init())
	{
		return error;
	}

	Graph::drawGraph();
	while (graph.running())
	{
		graph.handleEvents();
	}

	graph.clean();
	return 0;
}
