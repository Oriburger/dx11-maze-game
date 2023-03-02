#pragma once

#include "../../Game/public/Maze.h"
#include "../../Game/public/MazeGenerator.h"

int main()
{
	MazeGenerator* mazeGenerator = new RecursiveRandomMazeGenerator();
	Maze* myMaze = mazeGenerator->GenerateNewMaze(5);

	myMaze->PrintMazeToCmd();

	return 0;
}