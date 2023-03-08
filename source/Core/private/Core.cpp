#include "../public/Core.h"

RandomIntegerValueGenerator::RandomIntegerValueGenerator()
{
	MinValue = 0; 
	MaxValue = 99;
}

RandomIntegerValueGenerator::RandomIntegerValueGenerator(int NewMinValue, int NewMaxValue)
{
	SetValueRange(NewMinValue, NewMaxValue);
}

void RandomIntegerValueGenerator::SetValueRange(int NewMinValue, int NewMaxValue)
{
	if (NewMinValue > NewMaxValue) std::swap(NewMinValue, NewMaxValue);
	MinValue = NewMinValue;
	MaxValue = NewMaxValue;
}

int RandomIntegerValueGenerator::GetRandomValue() const
{
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice()); //�Ź� �����Ǿ� ���� ���� ���.
	std::uniform_int_distribution<int> distribution(MinValue, MaxValue);
	return distribution(gen);
}
