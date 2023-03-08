#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "Geometry.h"

/*
- Date : 23/03/02 LJH
- Description 
	- std 기능을 포함한 가장 기본 라이브러리를 포함하는 헤더
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