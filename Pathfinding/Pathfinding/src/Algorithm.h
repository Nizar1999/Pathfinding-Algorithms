#pragma once

#include <map>
#include <array>

class Algorithm
{
public:
	virtual void execute() = 0;
	void printPath();

protected:
	std::array<int, 4> X = { -1,1,0,0 };
	std::array<int, 4> Y = { 0,0,-1,1 };

	int dx = 0;
	int dy = 0;

	std::map<std::pair<int, int>, std::pair<int, int>> path;
};

