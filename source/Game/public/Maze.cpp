#include "../public/Maze.h"

Maze::Maze()
{
	const int defaultLength = DEFAULT_MAZE_LENGTH;
	Maze(defaultLength, defaultLength);
}

Maze::Maze(int Height, int Width)
{
	Height = std::max(DEFAULT_MAZE_LENGTH, Height);
	Width = std::max(DEFAULT_MAZE_LENGTH, Width);
	MazeArray = std::vector<std::vector<int> >(Height, std::vector<int>(Width, -1));
}

Maze::Maze(Maze&& MazeRef)
{
	this->MazeArray = MazeRef.MazeArray;
}

void Maze::PrintMazeToCmd()
{
	for (int ypos = 0; ypos < (int)GetHeight(); ypos++)
	{
		for (int xpos = 0; xpos < (int)GetWidth(); xpos++)
		{
			std::cout << MazeArray[ypos][xpos] << ' ';
		}
		std::cout << '\n';
	}
}
