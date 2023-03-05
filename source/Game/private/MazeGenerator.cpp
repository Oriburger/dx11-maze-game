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
	Maze* newMaze = new Maze(Width, Height);

	while(1) //수정 필요
	{
		Location2D entranceLocation = GetRandomSideLocation(newMaze);
		Location2D exitLocation = GetRandomSideLocation(newMaze);

		if (entranceLocation == exitLocation) continue;

		SetEntranceAndExit(newMaze, entranceLocation, exitLocation);
		break;
	}

	RecursiveMazeSearch(newMaze, newMaze->GetEntranceLocation());

	return newMaze;
}

void RecursiveRandomMazeGenerator::SetEntranceAndExit(Maze* MyMaze, Location2D EntranceLocation, Location2D ExitLocation)
{
	if (MyMaze == nullptr) return;
	
	MyMaze->SetEntranceLocation(EntranceLocation);
	MyMaze->SetExitLocation(ExitLocation);
}

Location2D RecursiveRandomMazeGenerator::GetRandomSideLocation(Maze* MyMaze)
{
	if (MyMaze == nullptr) return Location2D();
	if (MyMaze->GetHeight() <= 0 || MyMaze->GetWidth() <= 0) return Location2D();

	unsigned int ypos = randGenerator->GetRandomValue() % MyMaze->GetHeight();
	unsigned int xpos = randGenerator->GetRandomValue() % MyMaze->GetWidth();

	if (randGenerator->GetRandomValue() % 2) ypos = randGenerator->GetRandomValue() % 2 ? 0 : MyMaze->GetHeight() - 1;
	else xpos = randGenerator->GetRandomValue() % 2 ? 0 : MyMaze->GetWidth() - 1;

	return { ypos, xpos };
}

void RecursiveRandomMazeGenerator::RecursiveMazeSearch(Maze* MyMaze, Location2D CurrLocation, Location2D PrevLocation)
{
	if ((*MyMaze)[CurrLocation.Ypos][CurrLocation.Xpos] == 1) return;
	if ((*MyMaze)[CurrLocation.Ypos][CurrLocation.Xpos] == 0 && !(PrevLocation == Location2D()))
	{
		(*MyMaze)[CurrLocation.Ypos][CurrLocation.Xpos] = 1;
		return;
	}

	(*MyMaze)[CurrLocation.Ypos][CurrLocation.Xpos] = 0;

	int dirIdx = randGenerator->GetRandomValue() % 4;
	for (int count = 0; count < 1; count += 1)
	{
		const Location2D nextLocation = { CurrLocation.Ypos + dirY[dirIdx], CurrLocation.Xpos + dirX[dirIdx]};
		if (nextLocation.Ypos == 0 || nextLocation.Ypos == MyMaze->GetHeight() - 1
			|| nextLocation.Xpos == 0 || nextLocation.Xpos == MyMaze->GetWidth() - 1
			|| PrevLocation == nextLocation)
		{
			count -= 1;
			dirIdx = (dirIdx + 1) % 4;
			continue;
		}

		RecursiveMazeSearch(MyMaze, nextLocation, CurrLocation);

		dirIdx = (dirIdx + 1) % 4;
	}
}
