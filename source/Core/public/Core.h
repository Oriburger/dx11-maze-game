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

	RandomIntegerValueGenerator(int MinValue, int MaxValue);

	void SetValueRange(int MinValue, int MaxValue);

	int GetRandomValue() const;

private:
	std::random_device RandDevice;

	std::uniform_int_distribution<int> Distribution;
};