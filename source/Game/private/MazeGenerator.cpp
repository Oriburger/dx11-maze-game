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

	bool bGenerateResult = false;
	int tryCount = 0;

	while (!bGenerateResult)
	{
		if (tryCount >= 1e5)
		{
			std::cout << "Error) RecursiveRandomMazeGenerator::GenerateNewMaze - Try Count Exceed";
			break;
		}
		Location2D beginLocation = GetSearchBeginLocation(newMaze, !(bool)(++tryCount));

		(*newMaze)[beginLocation.Ypos][beginLocation.Xpos] = -1;
		bGenerateResult = RecursiveMazeSearch(newMaze, beginLocation);
	}
	
	return newMaze;
}

bool RecursiveRandomMazeGenerator::RecursiveMazeSearch(Maze* MyMaze, Location2D CurrLocation, Location2D PrevLocation)
{
	if ((*MyMaze)[CurrLocation.Ypos][CurrLocation.Xpos] != -1) return false;

	(*MyMaze)[CurrLocation.Ypos][CurrLocation.Xpos] = 0;
			
	int dirIdx = randGenerator->GetRandomValue() % 4;

	for (int tryCount = 0; tryCount < 1; tryCount += 1)
	{		
		const Location2D nextLocation = { CurrLocation.Ypos + 2 * dirY[dirIdx], CurrLocation.Xpos + 2 * dirX[dirIdx]};

		if (nextLocation.Ypos > 0 && nextLocation.Ypos < MyMaze->GetHeight() - 1
			&& nextLocation.Xpos > 0 && nextLocation.Xpos < MyMaze->GetWidth() - 1
			&& PrevLocation != nextLocation)
		{
			(*MyMaze)[CurrLocation.Ypos + dirY[dirIdx]][CurrLocation.Xpos + dirX[dirIdx]] = 0;
			RecursiveMazeSearch(MyMaze, nextLocation, CurrLocation);
		}

		dirIdx = (dirIdx + 1) % 4;
	}
	return ((*MyMaze)[MyMaze->GetHeight() - 2][MyMaze->GetWidth() - 2] == 0);
}

Location2D RecursiveRandomMazeGenerator::GetSearchBeginLocation(Maze* MyMaze, bool bInitial)
{
	if (MyMaze == nullptr) return Location2D();
	else if (bInitial == true) return Location2D({ 1, 1 });
	
	for (unsigned ypos = MyMaze->GetHeight() - 2; ypos > 1; ypos -= 2)
	{
		for (unsigned xpos = MyMaze->GetWidth() - 2; xpos > 1; xpos -= 2)
		{
			if ((*MyMaze)[ypos][xpos] == 0)
			{
				return Location2D({ ypos, xpos });
			}
		}
	}
	return Location2D({ 1, 1 });
}
