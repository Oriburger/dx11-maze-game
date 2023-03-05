#include "../public/Core.h"

RandomIntegerValueGenerator::RandomIntegerValueGenerator()
{
	Distribution = std::uniform_int_distribution<int>(0, 99);
}

RandomIntegerValueGenerator::RandomIntegerValueGenerator(int MinValue, int MaxValue)
{
	SetValueRange(MinValue, MaxValue);
}

void RandomIntegerValueGenerator::SetValueRange(int MinValue, int MaxValue)
{
	if (MinValue > MaxValue) std::swap(MinValue, MaxValue);
	Distribution = std::uniform_int_distribution<int>(MinValue, MaxValue);
}

int RandomIntegerValueGenerator::GetRandomValue() const
{
	std::random_device rd;
	std::mt19937 gen(rd());
	return Distribution(gen);
}
