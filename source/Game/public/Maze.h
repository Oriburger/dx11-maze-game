#pragma once
#include "../../Core/public/Core.h"
#define DEFAULT_MAZE_LENGTH 3

/*
- Date : 23/03/02 LJH
- Class
	- Maze
- Description
	- Maze의 정보를 담고 있는 클래스 
	- 실제 정보와 출력의 기능을 담고 있다. 
	- Client는 Generator
*/

class Maze
{
public:
	Maze();

	Maze(int Height, int Width);

	Maze(Maze&& MazeRef); //이동 연산

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