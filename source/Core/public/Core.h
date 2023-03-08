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

	RandomIntegerValueGenerator(int NewMinValue, int NewMaxValue);

	void SetValueRange(int NewMinValue, int NewMaxValue);

	int GetRandomValue() const;

private:
	int MinValue;

	int MaxValue;
};