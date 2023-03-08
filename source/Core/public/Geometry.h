#pragma once

struct Location2D
{
	unsigned int Ypos;
	unsigned int Xpos;

	bool operator == (const Location2D& L2)
	{
		return this->Ypos == L2.Ypos && this->Xpos == L2.Xpos;
	}

	bool operator != (const Location2D& L2)
	{
		return !(*this == L2);
	}
};