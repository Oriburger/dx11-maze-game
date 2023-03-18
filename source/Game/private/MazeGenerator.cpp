#include "stdafx.h"
#include "../public/MazeGenerator.h"
#include "../public/Maze.h"

const int dirY[4] = { 1, -1, 0, 0 };
const int dirX[4] = { 0, 0, -1, 1 };

Maze* RecursiveRandomMazeGenerator::GenerateNewMaze(int Length)
{
	return GenerateNewMaze(Length, Length);
}

Maze* RecursiveRandomMazeGenerator::GenerateNewMaze(int Height, int Width)
{
	Maze* newMaze = new Maze(Height, Width);
;
	Location2D beginLocation = { 1, 1 };
	for (int tryCount = 0; tryCount < Height * Width; tryCount++)
	{
		(*newMaze)[beginLocation.Ypos][beginLocation.Xpos] = -1;
		beginLocation = RecursiveMazeSearch(newMaze, beginLocation);
		if (beginLocation.Ypos == Height - 2 && beginLocation.Xpos == Width - 2) break;
	}

	for (unsigned ypos = 1; ypos <= Height - 1; ypos += 2)
	{
		for (unsigned xpos = 1; xpos <= Width - 1; xpos += 2)
		{
			RecursiveMazeSearch(newMaze, Location2D({ ypos, xpos }));
		}
	}
	
	return newMaze;
}

Location2D RecursiveRandomMazeGenerator::RecursiveMazeSearch(Maze* MyMaze, Location2D CurrLocation, Location2D PrevLocation)
{
	if ((*MyMaze)[CurrLocation.Ypos][CurrLocation.Xpos] != -1) return { 1, 1 };

	(*MyMaze)[CurrLocation.Ypos][CurrLocation.Xpos] = 0;
			
	int dirIdx = randGenerator->GetRandomValue() % 4;
	Location2D lastLocation = CurrLocation;

	for (int tryCount = 0; tryCount < 1; tryCount += 1)
	{		
		const Location2D nextLocation = { CurrLocation.Ypos + 2 * dirY[dirIdx], CurrLocation.Xpos + 2 * dirX[dirIdx]};

		if (nextLocation.Ypos > 0 && nextLocation.Ypos < MyMaze->GetHeight() - 1
			&& nextLocation.Xpos > 0 && nextLocation.Xpos < MyMaze->GetWidth() - 1
			&& PrevLocation != nextLocation)
		{
			(*MyMaze)[CurrLocation.Ypos + dirY[dirIdx]][CurrLocation.Xpos + dirX[dirIdx]] = 0;
			Location2D tmpLocation = RecursiveMazeSearch(MyMaze, nextLocation, CurrLocation);

			if (tmpLocation.Xpos + tmpLocation.Ypos > lastLocation.Xpos + lastLocation.Ypos)
			{
				lastLocation = tmpLocation;
			}
			continue;
		}
		//tryCount -= 1;
		dirIdx = (dirIdx + 1) % 4;
	}
	return lastLocation;
}