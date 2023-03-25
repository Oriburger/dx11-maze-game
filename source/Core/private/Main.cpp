#pragma once
#include "stdafx.h"
#include "../../Engine/public/D3dclass.h"
#include "../../Game/public/Maze.h"
#include "../../Game/public/MazeGenerator.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	D3DClass* myD3DObject = new D3DClass();
	HWND hwnd = CreateWindowA("Maze Generator", "Maze Generator", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT
								, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

	myD3DObject->Initialize(500, 500, false, hwnd, false, 1.0f, 1.0f);

	MazeGenerator* mazeGenerator = new RecursiveRandomMazeGenerator();
	Maze* myMaze = mazeGenerator->GenerateNewMaze(50, 50);

	myMaze->PrintMazeToCmd();

	return 0;
}