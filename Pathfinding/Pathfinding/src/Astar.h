#pragma once
#include "Algorithm.h"
#include <utility>

class Astar :
    public Algorithm
{
	struct cmp
	{
		bool operator()(std::pair<int,int> a, std::pair<int,int> b)
		{
			int fa = h(a) + g(a);
			int fb = h(b) + g(b);
			return fa > fb || fa == fb && h(a) < h(b);
		}
	};
    void execute() override;
	static int h(std::pair<int, int> node);
	static int g(std::pair<int, int> node);

};

