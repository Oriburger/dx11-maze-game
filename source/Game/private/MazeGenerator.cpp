#include "../public/MazeGenerator.h"
#include "../public/Maze.h"

Location2D MazeGenerator::GetRandomSideLocation(int Height, int Width)
{
	if (Height <= 0 || Width <= 0) return Location2D();

	srand((unsigned)time(NULL));

	unsigned int ypos = rand() % Height;
	unsigned int xpos = rand() % Width;
	
	if (rand() % 2)
	{
		ypos = rand() % 2 ? 0 : Height - 1;
	}
	else
	{
		xpos = rand() % 2 ? 0 : Width - 1;
	}

	return { ypos, xpos };
}

Maze* RecursiveRandomMazeGenerator::GenerateNewMaze(int Length)
{
	return GenerateNewMaze(Length, Length);
}

Maze* RecursiveRandomMazeGenerator::GenerateNewMaze(int Height, int Width)
{
	Maze* newMaze = new Maze(Width, Height);

	while (!newMaze->SetEntranceLocation(GetRandomSideLocation(Height, Width))) {}
	while (!newMaze->SetExitLocation(GetRandomSideLocation(Height, Width))) {}

	const int dirY[4] = { 1, -1, 0, 0 };
	const int dirX[4] = { 0, 0, -1, 1 };
	const unsigned int width = (int)newMaze->GetWidth();
	const unsigned int height = (int)newMaze->GetHeight();

	

	return newMaze;
}

void RecursiveRandomMazeGenerator::RecursiveMazeSearch(Location2D CurrLocation, Maze*& Maze)
{
	if (Maze == nullptr) return;
	if (CurrLocation.Ypos < 0 || CurrLocation.Ypos >= Maze->GetHeight()) return;
	if (CurrLocation.Xpos < 0 || CurrLocation.Xpos >= Maze->GetWidth()) return;

	//RecursiveMazeSearch 
}