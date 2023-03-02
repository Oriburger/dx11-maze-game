#pragma once
#include "../../Core/public/Core.h"

/*
- Date : 23/03/02 LJH
- Class
	- MazeGenerator
		- RecursiveRandomMazeGenerator
		- NonRecursiveRandomMazeGenerator
- Description
	- std ����� ������ ���� �⺻ ���̺귯���� �����ϴ� ���
	- ���丮 ������ Ȱ���Ͽ� Maze�� Client���� ��ȯ
	- RecursiveRandomMazeGenerator
		- ������� �˰������� (DFS Base) �̷θ� ����
	- NonRecursiveRandomMazeGenerator
		- ��������� �˰������� (BFS Base) �̷θ� ����
*/

class MazeGenerator
{
public:
	MazeGenerator() = default;

	~MazeGenerator() = default; 

	virtual class Maze* GenerateNewMaze(int Length) = 0;

	virtual class Maze* GenerateNewMaze(int Width, int Height) = 0;

protected:
	struct Location2D GetRandomSideLocation(int Height, int Width);
};

class RecursiveRandomMazeGenerator : public MazeGenerator
{
public:
	virtual class Maze* GenerateNewMaze(int Length) override;

	virtual class Maze* GenerateNewMaze(int Width, int Height) override;

private:
	void RecursiveMazeSearch(Location2D CurrLocation, class Maze*& Maze);
};