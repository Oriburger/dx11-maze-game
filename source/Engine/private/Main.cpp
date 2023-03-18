#pragma once

#include "../../Game/public/Maze.h"
#include "../../Game/public/MazeGenerator.h"

int main()
{
	UINT createDeviceFlags = 0;

	#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	MazeGenerator* mazeGenerator = new RecursiveRandomMazeGenerator();
	Maze* myMaze = mazeGenerator->GenerateNewMaze(50, 50);

	myMaze->PrintMazeToCmd();

	return 0;
}