#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Algorithm.h"

#include <utility>

class Graph
{
public:
	int init();
	void handleEvents();
	void clean();

	inline bool running() const { return isRunning; }

	static void drawGraph();
	static void drawButtons(SDL_Rect& btn, const char* text, SDL_Color color, int row, int col);
	static void resetGraph();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static char grid[20][30];
	static std::pair<int, int> srcNode;
	static std::pair<int, int> destNode;
	static SDL_Rect clearBtn;
	static SDL_Rect dfsBtn;
	static SDL_Rect bfsBtn;
	static SDL_Rect djikstraBtn;
	static SDL_Rect greedyBtn;
	static SDL_Rect astarBtn;

private:
	int initWindow();

	SDL_Window* window;
	bool isRunning;
	Algorithm* algorithm;
};

