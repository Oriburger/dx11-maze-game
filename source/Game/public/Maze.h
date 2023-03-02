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

struct Location2D
{
	unsigned int Ypos;
	unsigned int Xpos;
};

class Maze
{
public:
	Maze();

	Maze(int Height, int Width);

	Maze(Maze&& MazeRef); //�̵� ����

public:
	size_t GetHeight() const { return MazeArray.size(); }

	size_t GetWidth() const { return GetHeight() ? MazeArray[0].size() : 0; }

	void PrintMazeToCmd();

private:
	Location2D EntranceLocation;

	std::vector<std::vector<int> > MazeArray;
};