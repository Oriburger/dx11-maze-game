#include "../public/Maze.h"

Maze::Maze()
{
	const int defaultLength = DEFAULT_MAZE_LENGTH;
	Maze(defaultLength, defaultLength);
}

Maze::Maze(int Height, int Width)
{
	Height += (Height % 2 == 0);
	Width += (Width % 2 == 0); 
	Height = std::max(DEFAULT_MAZE_LENGTH, Height);
	Width = std::max(DEFAULT_MAZE_LENGTH, Width);
	MazeArray = std::vector<std::vector<int> >(Height, std::vector<int>(Width, -1));

	//가장자리 벽 생성
	for (int h = 0; h < Height; h++)
		MazeArray[h][0] = MazeArray[h][Width - 1] = 1;
	
	for (int w = 0; w < Width; w++)
		MazeArray[0][w] = MazeArray[Height - 1][w] = 1;
}

Maze::Maze(Maze&& MazeRef)
{
	this->MazeArray = MazeRef.MazeArray;
}

Location2D Maze::GetEntranceLocation()
{
	return { 1, 1 };
}

Location2D Maze::GetExitLocation()
{
	return { (unsigned)GetHeight() - 2, (unsigned)GetWidth() - 2 };
}

void Maze::PrintMazeToCmd()
{
	for (int ypos = 0; ypos < (int)GetHeight(); ypos++)
	{
		for (int xpos = 0; xpos < (int)GetWidth(); xpos++)
		{
			std::cout << (MazeArray[ypos][xpos] == 1 ? "■" : (MazeArray[ypos][xpos] == -1 ? "@" : "□"));
		}
		std::cout << '\n';
	}
}
