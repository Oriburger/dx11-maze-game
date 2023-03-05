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

bool Maze::SetEntranceLocation(Location2D NewLocation)
{
	if (NewLocation.Ypos != GetHeight()-1 && NewLocation.Ypos != 0
		&& NewLocation.Xpos != GetWidth()-1 && NewLocation.Xpos != 0) return false; 
	if (NewLocation.Ypos == NewLocation.Xpos) return false;
	if (NewLocation == ExitLocation) return false;

	MazeArray[EntranceLocation.Ypos][EntranceLocation.Xpos] = 1;
	EntranceLocation = NewLocation;
	MazeArray[EntranceLocation.Ypos][EntranceLocation.Xpos] = 0;

	return true;
}

bool Maze::SetExitLocation(Location2D NewLocation)
{
	if (NewLocation.Ypos != GetHeight() - 1 && NewLocation.Ypos != 0
		&& NewLocation.Xpos != GetWidth() - 1 && NewLocation.Xpos != 0) return false;
	if (NewLocation.Ypos == NewLocation.Xpos) return false;
	if (NewLocation == EntranceLocation) return false;

	MazeArray[ExitLocation.Ypos][ExitLocation.Xpos] = 1;
	ExitLocation = NewLocation;
	MazeArray[ExitLocation.Ypos][ExitLocation.Xpos] = 0;

	return true;
}

Location2D Maze::GetEntranceLocation()
{
	return EntranceLocation;
}

Location2D Maze::GetExitLocation()
{
	return ExitLocation;
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
