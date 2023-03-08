#pragma once
#include "../../Core/public/Core.h"
#define DEFAULT_MAZE_LENGTH 5

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

	Maze(int Height, int Width); //���ڷ� ¦���� ���޵� ��, ���� ������ Ȧ���� ó���ȴ�.

	Maze(Maze&& MazeRef); //�̵� ����

	std::vector<int>& operator[](const int& Index) { return MazeArray[Index]; }

public:
	size_t GetHeight() const { return MazeArray.size(); }

	size_t GetWidth() const { return GetHeight() ? MazeArray[0].size() : 0; }

	Location2D GetEntranceLocation();

	Location2D GetExitLocation();

	void PrintMazeToCmd();

private:
	std::vector<std::vector<int> > MazeArray;
};