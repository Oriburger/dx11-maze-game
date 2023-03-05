#pragma once
#include "../../Core/public/Core.h"
#define DEFAULT_MAZE_LENGTH 3

/*
- Date : 23/03/02 LJH
- Class
	- Maze
- Description
	- Maze�� ������ ��� �ִ� Ŭ���� 
	- ���� ������ ����� ����� ��� �ִ�. 
	- Client�� Generator
*/

class Maze
{
public:
	Maze();

	Maze(int Height, int Width);

	Maze(Maze&& MazeRef); //�̵� ����

	std::vector<int>& operator[](const int& Index) { return MazeArray[Index]; }

public:
	size_t GetHeight() const { return MazeArray.size(); }

	size_t GetWidth() const { return GetHeight() ? MazeArray[0].size() : 0; }

	bool SetEntranceLocation(Location2D NewLocation);

	bool SetExitLocation(Location2D NewLocation);

	Location2D GetEntranceLocation();

	Location2D GetExitLocation();

	void PrintMazeToCmd();

private:
	Location2D EntranceLocation;

	Location2D ExitLocation;

	std::vector<std::vector<int> > MazeArray;
};