#pragma once
#include "stdafx.h"
#include "../../Engine/public/D3dclass.h"
#include "../../Game/public/Maze.h"
#include "../../Game/public/MazeGenerator.h"

int main()
{
	D3DClass* myD3DObject = new D3DClass();
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	HWND hwnd = CreateWindowA("Maze Generator", "Maze Generator", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT
								, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

	myD3DObject->Initialize(2560, 1440, false, hwnd, false, 1.0f, 1.0f);

	MazeGenerator* mazeGenerator = new RecursiveRandomMazeGenerator();
	Maze* myMaze = mazeGenerator->GenerateNewMaze(50, 50);

	myMaze->PrintMazeToCmd();

	return 0;
}