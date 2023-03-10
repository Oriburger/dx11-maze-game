#pragma once

#include "../../Game/public/Maze.h"
#include "../../Game/public/MazeGenerator.h"

int main()
{
	UINT createDeviceFlags = 0;

	#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0,
									 createDeviceFlags, 0, 0, 
									 D3D11_SDK_VERSION,
									 &md3dDevice,
									 &featureLevel,
									 &md3dImmediateContext);
	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}
	
	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}
	MessageBox(0, L"D3D11CreateDevice is succeed", 0, 0);

	MazeGenerator* mazeGenerator = new RecursiveRandomMazeGenerator();
	Maze* myMaze = mazeGenerator->GenerateNewMaze(50, 50);

	myMaze->PrintMazeToCmd();

	return 0;
}