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

bool Maze::SetEntranceLocation(Location2D NewLocation)
{
	if (NewLocation.Ypos != GetHeight()-1 && NewLocation.Ypos != 0
		&& NewLocation.Xpos != GetWidth()-1 && NewLocation.Xpos != 0) return false; 
	if (NewLocation.Ypos == NewLocation.Xpos) return false;
	if (NewLocation == ExitLocation) return false;

	EntranceLocation = NewLocation;

	return true;
}

bool Maze::SetExitLocation(Location2D NewLocation)
{
	if (NewLocation.Ypos != GetHeight() - 1 && NewLocation.Ypos != 0
		&& NewLocation.Xpos != GetWidth() - 1 && NewLocation.Xpos != 0) return false;
	if (NewLocation.Ypos == NewLocation.Xpos) return false;
	if (NewLocation == EntranceLocation) return false;

	ExitLocation = NewLocation;

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
			std::cout << MazeArray[ypos][xpos] << ' ';
		}
		std::cout << '\n';
	}
}
