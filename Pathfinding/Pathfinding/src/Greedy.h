#pragma once
#include "Algorithm.h"
#include <utility>

class Greedy :
    public Algorithm
{
	struct cmp
	{
		bool operator()(std::pair<int,int> a, std::pair<int,int> b)
		{
			return distance(a) > distance(b);
		}
	};
    void execute() override;
	static int distance(std::pair<int, int> node);
};

