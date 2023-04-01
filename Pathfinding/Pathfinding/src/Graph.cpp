#include "Graph.h"
#include "DFS.h"
#include "BFS.h"
#include "Djikstra.h"
#include "Greedy.h"
#include "Astar.h"

#include <iostream>

SDL_Renderer* Graph::renderer = nullptr;
SDL_Event Graph::event;
	
char Graph::grid[20][30] = { 0 };
std::pair<int, int> Graph::srcNode = { 15, 5};
std::pair<int, int> Graph::destNode = {10, 25};

SDL_Rect Graph::clearBtn;
SDL_Rect Graph::dfsBtn;
SDL_Rect Graph::bfsBtn;
SDL_Rect Graph::djikstraBtn;
SDL_Rect Graph::greedyBtn;
SDL_Rect Graph::astarBtn;

int Graph::init()
{
	algorithm = new Astar();
	return TTF_Init() | initWindow();
}

int Graph::initWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "Failed to init subsystems" << std::endl;
		return 1;
	}

	std::cout << "Subsystems Initialized" << std::endl;

	window = SDL_CreateWindow("Pathfinding", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 704, NULL);

	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		return 1;
	}
	std::cout << "Created Window" << std::endl;

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cout << "Failed to create renderer" << std::endl;
		return 1;
	}
	std::cout << "Created Renderer" << std::endl;
	return 0;

}

void Graph::handleEvents()
{
	SDL_PollEvent(&event);

	int row = 0;
	int col = 0;
	Uint32 button = SDL_GetMouseState(&col, &row);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_Rect mouseRect;
		mouseRect.x = col;
		mouseRect.y = row;
		mouseRect.w = 10;
		mouseRect.h = 10;

		if (SDL_HasIntersection(&clearBtn, &mouseRect))
		{
			std::fill(&grid[0][0], &grid[0][0] + sizeof(grid) / sizeof(grid[0][0]), 0);
		}
		if (SDL_HasIntersection(&dfsBtn, &mouseRect))
		{
			algorithm = new DFS();
			resetGraph();
			algorithm->execute();
		}
		if (SDL_HasIntersection(&bfsBtn, &mouseRect))
		{
			algorithm = new BFS();
			resetGraph();
			algorithm->execute();
		}
		if (SDL_HasIntersection(&djikstraBtn, &mouseRect))
		{
			algorithm = new Djikstra();
			resetGraph();
			algorithm->execute();
		}
		if (SDL_HasIntersection(&greedyBtn, &mouseRect))
		{
			algorithm = new Greedy();
			resetGraph();
			algorithm->execute();
		}
		if (SDL_HasIntersection(&astarBtn, &mouseRect))
		{
			algorithm = new Astar();
			resetGraph();
			algorithm->execute();
		}
		break;
	}

	row /= 32;
	col /= 32;
	if (button == SDL_BUTTON_LMASK)
	{
		grid[row][col] = -3;
		drawGraph();
	}
	else if (button == SDL_BUTTON_RMASK)
	{
		grid[row][col] = 0;
		Graph::drawGraph();
	} 
}

void Graph::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "Game Cleaned\n";

}

void Graph::drawGraph()
{
	SDL_SetRenderDrawColor(Graph::renderer, 255, 255, 255, 0);
	SDL_RenderClear(Graph::renderer);
	SDL_Rect cell{0,0,32,32};

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 30; column++)
		{
			cell.x = column * cell.h;
			cell.y = row * cell.w;


			if (row == Graph::srcNode.first && column == Graph::srcNode.second)
			{
				SDL_SetRenderDrawColor(Graph::renderer, 251, 134, 215, 0);
				SDL_RenderFillRect(Graph::renderer, &cell);
			}
			else if (row == Graph::destNode.first && column == Graph::destNode.second)
			{
				SDL_SetRenderDrawColor(Graph::renderer, 176, 247, 14, 0);
				SDL_RenderFillRect(Graph::renderer, &cell);
			}
			else if (Graph::grid[row][column] == -1)
			{
				SDL_SetRenderDrawColor(Graph::renderer, 226, 140, 31, 0);
				SDL_RenderFillRect(Graph::renderer, &cell);
			}
			else if (Graph::grid[row][column] == -3)
			{
				SDL_SetRenderDrawColor(Graph::renderer, 0, 140, 31, 0);
				SDL_RenderFillRect(Graph::renderer, &cell);
			}
			else if (Graph::grid[row][column] == -4)
			{
				SDL_SetRenderDrawColor(Graph::renderer, 10, 10, 50, 0);
				SDL_RenderFillRect(Graph::renderer, &cell);
			}
			SDL_SetRenderDrawColor(Graph::renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(Graph::renderer, &cell);
		}
	}
	SDL_SetRenderDrawColor(Graph::renderer, 255, 255, 255, 0);
	Graph::drawButtons(clearBtn, "clear", {0,0,0}, 32 * 20.5, 20);
	Graph::drawButtons(dfsBtn, "DFS", {0,0,0}, 32 * 20.5, clearBtn.x + clearBtn.w + 50);
	Graph::drawButtons(bfsBtn, "BFS", {0,0,0}, 32 * 20.5, dfsBtn.x + dfsBtn.w + 50);
	Graph::drawButtons(djikstraBtn, "Djikstra", {0,0,0}, 32 * 20.5, bfsBtn.x + bfsBtn.w + 50);
	Graph::drawButtons(greedyBtn, "Greedy", {0,0,0}, 32 * 20.5, djikstraBtn.x + djikstraBtn.w + 50);
	Graph::drawButtons(astarBtn, "A*", {0,0,0}, 32 * 20.5, greedyBtn.x + greedyBtn.w + 50);
	SDL_RenderPresent(Graph::renderer);
}

void Graph::drawButtons(SDL_Rect& btn, const char* text, SDL_Color color, int row, int col)
{
	TTF_Font* font = TTF_OpenFont("font/OpenSans-Regular.ttf", 24);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Graph::renderer, surfaceMessage);

	btn.x = col;  
	btn.y = row;
	btn.w = surfaceMessage->w;
	btn.h = surfaceMessage->h;

	SDL_RenderCopy(Graph::renderer, Message, NULL, &btn);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	TTF_CloseFont(font);
}

void Graph::resetGraph()
{
	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 30; column++)
		{
			if (grid[row][column] != -3)
			{
				grid[row][column] = 0;
			}
		}
	}
}
