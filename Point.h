#pragma once

class Point
{
public:
	int x;
	int y;

public:
	// デフォルトコンストラクタ
	Point() {}

	// コンストラクタ
	Point(int x, int y)
		: x(x), y(y)
	{
	}
};
