#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "Geometry.h"

/*
- Date : 23/03/02 LJH
- Description 
	- std ����� ������ ���� �⺻ ���̺귯���� �����ϴ� ���
- Class
	- RandomGenerator

*/

class RandomIntegerValueGenerator
{
public:
	RandomIntegerValueGenerator();

	RandomIntegerValueGenerator(int MinValue, int MaxValue);

	void SetValueRange(int MinValue, int MaxValue);

	int GetRandomValue() const;

private:
	std::random_device RandDevice;

	std::uniform_int_distribution<int> Distribution;
};