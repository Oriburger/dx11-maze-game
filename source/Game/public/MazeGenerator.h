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
};

class RecursiveRandomMazeGenerator : public MazeGenerator
{
public:
	RecursiveRandomMazeGenerator()	{ randGenerator = new RandomIntegerValueGenerator(0, 40000); }

	~RecursiveRandomMazeGenerator()  { delete randGenerator; }

public:
	virtual class Maze* GenerateNewMaze(int Length) override;

	virtual class Maze* GenerateNewMaze(int Height, int Width) override;

private:
	class RandomIntegerValueGenerator* randGenerator; 

	Location2D RecursiveMazeSearch(class Maze* MyMaze, Location2D CurrLocation, Location2D PrevLocation = {0, 0});
};